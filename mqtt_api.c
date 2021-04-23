/***************************************************************************
 * Copyright (C) 2017 - 2020, Lanka Hsu, <lankahsu@gmail.com>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include "utilx9.h"

void mqtt_log_cb(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
	MQTTSession *session = (MQTTSession *)userdata;
	DBG_TR_LN("(%s)", str);
	if (session->log_cb)
	{
		session->log_cb(mosq, userdata, level, str);
	}
}

static void mqtt_connect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	MQTTSession *session = (MQTTSession *)userdata;

	session->isconnect = 1;
	DBG_TR_LN("(%s:%d, result: %d)", session->hostname, session->port, result);
	if (session->connect_cb)
	{
		session->connect_cb(mosq, userdata, result);
	}
}

static void mqtt_disconnect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	MQTTSession *session = (MQTTSession *)userdata;

	session->isconnect = 0;
	DBG_TR_LN("(%s:%d, result: %d)", session->hostname, session->port, result);
	if (session->disconnect_cb)
	{
		session->disconnect_cb(mosq, userdata, result);
	}
}

static void mqtt_message_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	MQTTSession *session = (MQTTSession *)userdata;

	DBG_TR_LN("(%s:%d, topic: %s, [%d]%s)", session->hostname, session->port, message->topic, message->payloadlen, (char*) message->payload);
	if (session->message_cb)
	{
		session->message_cb(mosq, userdata, message);
	}

	MQTTSub_t *cur = NULL;
	for (cur = clist_head(session->sub_list); cur != NULL; cur = clist_item_next(cur))
	{
		bool match = 0;
		mosquitto_topic_matches_sub(cur->topic, message->topic, &match);
		if (match)
		{
			DBG_DB_LN("(match: %d, cur->topic: %s ?= %s)", match, cur->topic, message->topic);
			if (cur->message_cb) cur->message_cb(mosq, userdata, message);
		}
	}
}

int mqtt_publish(MQTTSession *session, char *topic, char *msg)
{
	int ret = 0;
	if (session)
	{
		return mosquitto_publish(session->mosq, NULL, topic, SAFE_STRLEN(msg), msg, 0, 0);
	}
	return ret;
}

// 1: found
static int mqtt_subscribe_duplicate(MQTTSession *session, char *topic, mqtt_message_fn *message_cb)
{
	int ret = 0;
	MQTTSub_t *cur = NULL;

	for (cur = clist_head(session->sub_list); cur != NULL; cur = clist_item_next(cur))
	{
		if ( (SAFE_STRCMP(topic, cur->topic)==0) && (message_cb == cur->message_cb) )
		{
			ret = 1;
		}
	}
	return ret;
}

void mqtt_subscribe_add(MQTTSession *session, char *topic, mqtt_message_fn *message_cb)
{
	if ( (session) && (topic) && (message_cb) )
	{
		if (mqtt_subscribe_duplicate(session, topic, message_cb) == 1)
		{
			// found
		}
		else
		{
			MQTTSub_t *sub_new = (MQTTSub_t*)SAFE_CALLOC(1, sizeof(MQTTSub_t));
			SAFE_SPRINTF(sub_new->topic, "%s", topic);
			sub_new->message_cb = message_cb;

			DBG_IF_LN("(topic: %s)", sub_new->topic);
			clist_push(session->sub_list, sub_new);
		}
	}
}

static void mqtt_queue_new(MQTTTopic_t *new, MQTTSession *session, char *topic, char *msg)
{
	if ( (new) && (session) && (topic) && (msg) )
	{
		new->session = session;
		SAFE_ASPRINTF(new->topic, "%s", topic);
		SAFE_ASPRINTF(new->msg, "%s", msg);
	}
}

void mqtt_qsub_add(MQTTSession *session, char *topic, char *msg)
{
	if ( (session) && (topic) && (msg) )
	{
		MQTTTopic_t topic_new;
		mqtt_queue_new(&topic_new, session, topic, msg);

		queue_add(session->qsub, (void*)&topic_new);
	}
}

static int mqtt_qsub_exec_cb(void *arg)
{
	MQTTTopic_t *data_pop = (MQTTTopic_t *)arg;

	if (data_pop)
	{

		SAFE_FREE(data_pop->topic);
		SAFE_FREE(data_pop->msg);
	}

	return 0;
}

void mqtt_qpub_add(MQTTSession *session, char *topic, char *msg)
{
	if ( (session) && (topic) && (msg) )
	{
		MQTTTopic_t topic_new;
		mqtt_queue_new(&topic_new, session, topic, msg);

		queue_add(session->qpub, (void*)&topic_new);
	}
}

static int mqtt_qpub_exec_cb(void *arg)
{
	MQTTTopic_t *data_pop = (MQTTTopic_t *)arg;

	if (data_pop)
	{
		mqtt_publish(data_pop->session, data_pop->topic, data_pop->msg);

		SAFE_FREE(data_pop->topic);
		SAFE_FREE(data_pop->msg);
	}

	return 0;
}

static int mqtt_queue_free_cb(void *arg)
{
	MQTTTopic_t *data_pop = (MQTTTopic_t *)arg;

	if (data_pop)
	{
		SAFE_FREE(data_pop->topic);
		SAFE_FREE(data_pop->msg);
	}

	return 0;
}

static void mqtt_queue_stop(MQTTSession *session)
{
	if (session)
	{
		queue_thread_stop(session->qpub);
		queue_thread_stop(session->qsub);
	}
}

static void mqtt_queue_close(MQTTSession *session)
{
	if (session)
	{
		queue_thread_close(session->qpub);
		session->qpub = NULL;
		queue_thread_close(session->qsub);
		session->qsub = NULL;
	}
}

static void mqtt_queue_init(MQTTSession *session)
{
	if (session)
	{
		session->qpub = queue_thread_init("qpub", MAX_OF_QPUB, sizeof(MQTTTopic_t), mqtt_qpub_exec_cb, mqtt_queue_free_cb);
		if (session->qpub)
		{
			queue_isready(session->qpub, 20);
		}
		session->qsub = queue_thread_init("qsub", MAX_OF_QSUB, sizeof(MQTTTopic_t), mqtt_qsub_exec_cb, mqtt_queue_free_cb);
		if (session->qsub)
		{
			queue_isready(session->qsub, 20);
		}
	}
}

static void mqtt_srv_subscribe(MQTTSession *session)
{
	if (session)
	{
		if (SAFE_STRLEN(session->topic) > 0)
		{
			//mosquitto_subscribe(mqtt_ctx->mosq, NULL, "9C65F9361C00/#", 0);
			mosquitto_subscribe(session->mosq, NULL, session->topic, 0);
			DBG_IF_LN("(topic: %s)", session->topic);
		}

		CLIST_STRUCT_INIT(session, sub_list);
	}
}

static struct mosquitto *mqtt_srv_open(MQTTCtx_t *mqtt_ctx)
{
	struct mosquitto *mosq = NULL;

	if (mqtt_ctx->isinit == 0)
	{
		mqtt_ctx->isinit = 1;
		mosquitto_lib_init();
	}

	{
		int major;
		int minor;
		int rev;

		mosquitto_lib_version(&major, &minor, &rev);
		DBG_IF_LN("(ver: %d.%d.%d)", major, minor, rev);
	}

	if (mqtt_ctx->session)
	{
		MQTTSession *session = mqtt_ctx->session;

		SAFE_MEMSET(session->clientid, 0, LEN_OF_VAL32);
		SAFE_SPRINTF(session->clientid, "%d", getpid());

		session->mqtt_ctx = (void*)mqtt_ctx;

		mosq = mosquitto_new(session->clientid, session->clean_session, session);
		if (mosq)
		{
			session->mosq = mosq;
			//mqtt_ctx->isready = 1;

			//mosquitto_username_pw_set(mosq, userName, password);
			if ( mqtt_ctx->dbg_more < DBG_LVL_MAX )
			{
				mosquitto_log_callback_set(mosq, mqtt_log_cb);
			}

			mosquitto_connect_callback_set(mosq, mqtt_connect_cb);
			mosquitto_disconnect_callback_set(mosq, mqtt_disconnect_cb);
			mosquitto_message_callback_set(mosq, mqtt_message_cb);
		}
	}

	return mosq;
}

static void mqtt_srv_close(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		DBG_IF_LN("%s", DBG_TXT_BYE_BYE);
		if (mqtt_ctx->session)
		{
			MQTTSession *session = mqtt_ctx->session;
			mosquitto_destroy(session->mosq);
			session->mosq = NULL;
		}

		if (mqtt_ctx->isinit==1)
		{
			mqtt_ctx->isinit = 0;
			mosquitto_lib_cleanup();
		}
	}
}

static void *mqtt_thread_handler( void *user )
{
	MQTTCtx_t *mqtt_ctx = (MQTTCtx_t*)user;

	if (mqtt_ctx)
	{
		struct mosquitto *mosq = mqtt_srv_open(mqtt_ctx);

		if (mosq)
		{
			MQTTSession *session = mqtt_ctx->session;
			DBG_IF_LN("call mosquitto_connect ... (%s:%d, keepalive: %d, topic: %s)", session->hostname,  session->port, session->keepalive, session->topic);
			int rc = mosquitto_connect(mosq, session->hostname, session->port, session->keepalive);

			mqtt_queue_init(session);

			mqtt_srv_subscribe(session);

			while (mqtt_ctx->isquit == 0)
			{
				rc = mosquitto_loop(mosq, -1, 1);
				if ( (mqtt_ctx->isquit==0) && (rc) )
				{
					DBG_WN_LN("call mosquitto_reconnect ...");
					sleep(10);
					mosquitto_reconnect(mosq);
				}

			}
		}

		mqtt_srv_close(mqtt_ctx);
	}

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	return NULL;
}

void mqtt_lock(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		SAFE_THREAD_LOCK_EX(mqtt_ctx);
	}
}

void mqtt_unlock(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		SAFE_THREAD_UNLOCK_EX(mqtt_ctx);
	}
}

void mqtt_signal(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		SAFE_THREAD_SIGNAL_EX(mqtt_ctx);
	}
}

void mqtt_wait(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		SAFE_THREAD_WAIT_EX(mqtt_ctx);
	}
}

static void mqtt_thread_free(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx==NULL) return;

	{
		SAFE_MUTEX_DESTROY(&mqtt_ctx->in_mtx);
		SAFE_COND_DESTROY(&mqtt_ctx->in_cond);
	}
	SAFE_FREE(mqtt_ctx);
}

void mqtt_thread_stop(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		mqtt_lock(mqtt_ctx);
		mqtt_ctx->isquit = 1;
		mqtt_signal(mqtt_ctx);
		mqtt_unlock(mqtt_ctx);

		mqtt_queue_stop(mqtt_ctx->session);
	}
}

void mqtt_thread_close(MQTTCtx_t *mqtt_ctx)
{
	if ((mqtt_ctx) && (mqtt_ctx->isfree == 0))
	{
		mqtt_ctx->isfree ++;

		SAFE_THREAD_JOIN_EX(mqtt_ctx);

		MQTTSession *session = mqtt_ctx->session;
		if (session)
		{
			mqtt_queue_close(session);
			clist_free(session->sub_list);
		}

		DBG_TR_LN("call mqtt_thread_free ... (name: %s)", mqtt_ctx->name);
		mqtt_thread_free(mqtt_ctx);
	}
}

static void mqtt_thread_mutex_init(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx==NULL) return;

	int rc = SAFE_MUTEX_ATTR_RECURSIVE(mqtt_ctx->in_mtx);
	if (rc == 0)
	{
		SAFE_COND_ATTR_NORMAL(mqtt_ctx->in_cond);
	}
}

void mqtt_thread_init(MQTTCtx_t *mqtt_ctx)
{
	if (mqtt_ctx)
	{
		mqtt_thread_mutex_init(mqtt_ctx);
		SAFE_THREAD_CREATE(mqtt_ctx->tid, NULL, mqtt_thread_handler, mqtt_ctx);
	}
}

