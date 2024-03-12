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

int mqtt_session_isconnect(MQTTX_t *mqtt_req)
{
	MQTTSession_t *session = NULL;

	if ((mqtt_req) && (session = mqtt_req->session))
	{
		return session->isconnect;
	}
	return 0;
}

MQTTSession_t *mqtt_session_get(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		return mqtt_req->session;
	}
	return NULL;
}

void mqtt_log_cb(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
	if ((mosq) && (userdata))
	{
		MQTTSession_t *session = (MQTTSession_t *)userdata;
		DBG_TR_LN("(%s)", str);
		if (session->log_cb)
		{
			session->log_cb(mosq, userdata, level, str);
		}
	}
}

static void mqtt_connect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	if ((mosq) && (userdata))
	{
		MQTTSession_t *session = (MQTTSession_t *)userdata;

		mqtt_srv_subscribe(session);
		session->count ++;

		session->isconnect = 1;
		DBG_IF_LN("(%s:%d, result: %d, count: %d)", session->hostname, session->port, result, session->count);
		if (session->connect_cb)
		{
			session->connect_cb(mosq, userdata, result);
		}

		mqtt_queue_wakeup(session);
	}
}

static void mqtt_disconnect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	if ((mosq) && (userdata))
	{
		MQTTSession_t *session = (MQTTSession_t *)userdata;

		session->isconnect = 0;
		DBG_WN_LN("(%s:%d, result: %d, count: %d)", session->hostname, session->port, result, session->count);
		if (session->disconnect_cb)
		{
			session->disconnect_cb(mosq, userdata, result);
		}

		mqtt_queue_gosleep(session);
	}
}

static void mqtt_message_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	if ((mosq) && (userdata))
	{
		MQTTSession_t *session = (MQTTSession_t *)userdata;

		DBG_TR_LN("(%s:%d, topic: %s, [%d]%s)", session->hostname, session->port, message->topic, message->payloadlen, (char*) message->payload);
		if (session->root_subscribe_cb)
		{
			session->root_subscribe_cb(mosq, userdata, message);
		}

		MQTTSub_t *cur = NULL;
		for (cur = clist_head(session->sub_list); cur != NULL; cur = clist_item_next(cur))
		{
			bool match = 0;
			mosquitto_topic_matches_sub(cur->topic, message->topic, &match);
			if (match)
			{
				DBG_DB_LN("(match: %d, cur->topic: %s ?= %s)", match, cur->topic, message->topic);
				if (cur->message_cb)
				{
					cur->message_cb(mosq, userdata, message);
				}
			}
		}
	}
}

int mqtt_publish(MQTTSession_t *session, char *topic, char *msg)
{
	int ret = 0;
	if ((session) && (msg))
	{
		return mosquitto_publish(session->mosq, NULL, topic, SAFE_STRLEN(msg), msg, 0, 0);
	}
	return ret;
}

// 1: found
static int mqtt_subscribe_duplicate(MQTTSession_t *session, char *topic, mqtt_message_fn *message_cb)
{
	int ret = 0;

	if (session)
	{
		MQTTSub_t *cur = NULL;

		for (cur = clist_head(session->sub_list); cur != NULL; cur = clist_item_next(cur))
		{
			if ((SAFE_STRCMP(topic, cur->topic)==0) && (message_cb == cur->message_cb))
			{
				ret = 1;
			}
		}
	}

	return ret;
}

void mqtt_subscribe_add(MQTTSession_t *session, char *topic, mqtt_message_fn *message_cb)
{
	if ((session) && (topic) && (message_cb))
	{
		if (mqtt_subscribe_duplicate(session, topic, message_cb) == 1)
		{
			// found
		}
		else
		{
			MQTTSub_t *sub_new = (MQTTSub_t*)SAFE_CALLOC(1, sizeof(MQTTSub_t));
			SAFE_SPRINTF_EX(sub_new->topic, "%s", topic);
			sub_new->message_cb = message_cb;

			DBG_IF_LN("(topic: %s)", sub_new->topic);
			clist_push(session->sub_list, sub_new);
		}
	}
}

static void mqtt_queue_new(MQTTTopic_t *new, MQTTSession_t *session, char *topic, char *msg, mqtt_topic_fn *topic_cb)
{
	if ((new) && (session) && (topic) && (msg))
	{
		new->session = session;
		SAFE_ASPRINTF(new->topic, "%s", topic);
		SAFE_ASPRINTF(new->msg, "%s", msg);
		new->topic_cb = topic_cb;
	}
}

void mqtt_qsub_add(MQTTSession_t *session, char *topic, char *msg, mqtt_topic_fn *topic_cb)
{
	if ((session) && (session->qsub) && (topic) && (msg))
	{
		MQTTTopic_t topic_new;
		mqtt_queue_new(&topic_new, session, topic, msg, topic_cb);

		queuex_add(session->qsub, (void*)&topic_new);
	}
}

static int mqtt_qsub_exec_cb(void *arg)
{
	MQTTTopic_t *data_pop = (MQTTTopic_t *)arg;

	if (data_pop)
	{
		data_pop->topic_cb(data_pop->session, data_pop->topic, data_pop->msg);
		SAFE_FREE(data_pop->topic);
		SAFE_FREE(data_pop->msg);
	}

	return 0;
}

void mqtt_qpub_add(MQTTSession_t *session, char *topic, char *msg, mqtt_topic_fn *topic_cb)
{
	if ((session) && (session->qpub) && (topic) && (msg))
	{
		MQTTTopic_t topic_new;
		mqtt_queue_new(&topic_new, session, topic, msg, topic_cb);

		queuex_add(session->qpub, (void*)&topic_new);
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

void mqtt_queue_wakeup(MQTTSession_t *session)
{
	if (session)
	{
		queuex_wakeup(session->qpub);
		queuex_wakeup(session->qsub);
	}
}

void mqtt_queue_gosleep(MQTTSession_t *session)
{
	if (session)
	{
		queuex_gosleep(session->qpub);
		queuex_gosleep(session->qsub);
	}
}

static void mqtt_queue_close(MQTTSession_t *session)
{
	if (session)
	{
		queuex_thread_stop(session->qpub);
		queuex_thread_close(session->qpub);

		queuex_thread_stop(session->qsub);
		queuex_thread_close(session->qsub);
	}
}

static void mqtt_queue_init(MQTTSession_t *session)
{
	if (session)
	{
		session->qpub = queuex_thread_init("qpub", MAX_OF_QPUB, sizeof(MQTTTopic_t), mqtt_qpub_exec_cb, mqtt_queue_free_cb);
		if (session->qpub)
		{
			queuex_isready(session->qpub, 20);
		}
		queuex_gosleep(session->qpub);

		session->qsub = queuex_thread_init("qsub", MAX_OF_QSUB, sizeof(MQTTTopic_t), mqtt_qsub_exec_cb, mqtt_queue_free_cb);
		if (session->qsub)
		{
			queuex_isready(session->qsub, 20);
		}
		queuex_gosleep(session->qsub);
	}
}

void mqtt_srv_subscribe(MQTTSession_t *session)
{
	if (session)
	{
		if (SAFE_STRLEN(session->topic_root) > 0)
		{
			mosquitto_subscribe(session->mosq, NULL, session->topic_root, 0);
			DBG_IF_LN("(topic: %s)", session->topic_root);
		}

	}
}

static struct mosquitto *mqtt_srv_open(MQTTX_t *mqtt_req)
{
	int result = 0;
	struct mosquitto *mosq = NULL;

	if (mqtt_req->isinit == 0)
	{
		mqtt_req->isinit = 1;
		DBG_DB_LN("call mosquitto_lib_init ~~~");
		mosquitto_lib_init();
	}

	{
		int major;
		int minor;
		int rev;

		mosquitto_lib_version(&major, &minor, &rev);
		DBG_IF_LN("(ver: %d.%d.%d)", major, minor, rev);
	}

	if (mqtt_req->session)
	{
		MQTTSession_t *session = mqtt_req->session;

		if (SAFE_STRLEN(session->clientid) > 0)
		{
		}
		else
		{
			SAFE_MEMSET(session->clientid, 0, LEN_OF_VAL32);
			SAFE_SPRINTF_EX(session->clientid, "%s-%d", session->macid, getpid());
		}

		session->mqtt_req = (void*)mqtt_req;

		mosq = mosquitto_new(session->clientid, session->clean_session, session);
		if (mosq)
		{
			session->mosq = mosq;
			//mqtt_req->isready = 1;

			// username / password
			if ((SAFE_STRLEN(session->user) > 0) && (SAFE_STRLEN(session->pass) > 0))
			{
				result = mosquitto_username_pw_set(mosq, session->user, session->pass);
				DBG_IF_LN("mosquitto_username_pw_set (result: %d, user: %s)", result, session->user);
			}

			//
			if ((session->ca_file) && (SAFE_STRLEN(session->ca_file)>0)
				&& (session->certificate_file) && (SAFE_STRLEN(session->certificate_file)>0)
				&& (session->privatekey_file) && (SAFE_STRLEN(session->privatekey_file)>0)
				)
			{
				//--tls-version : TLS protocol version, can be one of tlsv1.3 tlsv1.2 or tlsv1.1.
				//								Defaults to tlsv1.2 if available.
				if (SAFE_STRLEN(session->tls_version) == 0)
				{
					SAFE_SPRINTF_EX(session->tls_version, "all");
				}
				mosquitto_tls_opts_set(mosq, 1, session->tls_version, NULL);
				mosquitto_tls_insecure_set(mosq, 1);
				mosquitto_tls_set(mosq, session->ca_file, NULL, session->certificate_file, session->privatekey_file, NULL);
				DBG_IF_LN("(ca_file: %s, certificate_file: %s, privatekey_file: %s, tls_version: %s)", session->ca_file, session->certificate_file, session->privatekey_file, session->tls_version);
			}

			if (mqtt_req->dbg_more < DBG_LVL_MAX)
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

static void mqtt_srv_close(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		DBG_IF_LN("%s", DBG_TXT_BYE_BYE);
		if (mqtt_req->session)
		{
			MQTTSession_t *session = mqtt_req->session;
			if (session->mosq)
			{
				mosquitto_destroy(session->mosq);
				session->mosq = NULL;
			}
		}

		if (mqtt_req->isinit==1)
		{
			mqtt_req->isinit = 0;
			mosquitto_lib_cleanup();
		}
	}
}

static void *mqtt_thread_handler(void *user)
{
	MQTTX_t *mqtt_req = (MQTTX_t*)user;

	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_detach(tidx_req);

		MQTTSession_t *session = mqtt_req->session;
		CLIST_STRUCT_INIT(session, sub_list);
		mqtt_queue_init(session);

		session->count = 0;
		//struct mosquitto *mosq = NULL;
		struct mosquitto *mosq = mqtt_srv_open(mqtt_req);
		if (mosq)
		{
#if (1)
			int rc = 0;
			DBG_IF_LN("call mosquitto_connect_async ~~~ (%s:%d, keepalive: %d, topic: %s)", session->hostname,  session->port, session->keepalive, session->topic_root);
			rc = mosquitto_connect_async(mosq, session->hostname, session->port, session->keepalive);
			//rc = mosquitto_connect(mosq, session->hostname, session->port, session->keepalive);
			if (rc)
			{
				DBG_ER_LN("mosquitto_connect_async error !!! (rc: %d, %s)", rc, mosquitto_strerror(rc));
				goto exit_mqtt;
			}

			//mqtt_srv_subscribe(session);

			rc = mosquitto_loop_start(mosq);
			if (rc)
			{
				DBG_ER_LN("mosquitto_loop_start error !!! (rc: %d, %s)", rc, mosquitto_strerror(rc));
				goto exit_mqtt;
			}

			while (threadx_isquit(tidx_req) == 0)
			{
				threadx_timewait_simple(tidx_req, 10*1000);
			}
			mosquitto_disconnect(mosq);
			mosquitto_loop_stop(mosq, true);
#else
			DBG_IF_LN("call mosquitto_connect ... (%s:%d, keepalive: %d, topic: %s)", session->hostname,  session->port, session->keepalive, session->topic);
			int rc = mosquitto_connect(mosq, session->hostname, session->port, session->keepalive);

			mqtt_srv_subscribe(session);

			while (threadx_isquit(tidx_req) == 0)
			{
				rc = mosquitto_loop(mosq, -1, 1);
				if ((threadx_isquit(tidx_req)==0) && (rc))
				{
					DBG_WN_LN("call mosquitto_reconnect ...");
					if (MOSQ_ERR_SUCCESS == mosquitto_reconnect(mosq))
					{
					}
					else
					{
						//mqtt_timewait(mqtt_req, 10*1000);
						sleep(10);
					}
				}
			}
#endif
		}

exit_mqtt:
		mqtt_srv_close(mqtt_req);
		//sk_free(SSL_COMP_get_compression_methods());
		//SSL_COMP_free_compression_methods();

		mqtt_queue_close(mqtt_req->session);
		clist_free(session->sub_list);

		threadx_leave(tidx_req);
	}

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	return NULL;
}

void mqtt_lock(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_lock(tidx_req);
	}
}

void mqtt_unlock(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_unlock(tidx_req);
	}
}

void mqtt_signal(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_wakeup(tidx_req);
	}
}

int mqtt_timewait(MQTTX_t *mqtt_req, int ms)
{
	int ret = EINVAL;

	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		ret = threadx_timewait(tidx_req, ms);
	}

	return ret;
}

void mqtt_wait(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_wait(tidx_req);
	}
}

void mqtt_wakeup(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_wakeup(tidx_req);
	}
}

int mqtt_isquit(MQTTX_t *mqtt_req)
{
	int isquit = 0;
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		isquit = threadx_isquit(tidx_req);
	}
	return isquit;
}

void mqtt_thread_stop(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_stop(tidx_req);
	}
}

void mqtt_thread_close(MQTTX_t *mqtt_req)
{
	if ((mqtt_req) && (mqtt_req->isfree == 0))
	{
		mqtt_req->isfree ++;

		ThreadX_t *tidx_req = &mqtt_req->tidx;
		threadx_close(tidx_req);
	}
}

void mqtt_thread_init(MQTTX_t *mqtt_req)
{
	if (mqtt_req)
	{
		ThreadX_t *tidx_req = &mqtt_req->tidx;
		tidx_req->thread_cb = mqtt_thread_handler;
		tidx_req->data = mqtt_req;
		threadx_init(tidx_req, mqtt_req->name);
	}
}

