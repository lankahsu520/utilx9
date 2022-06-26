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
#include "ubus_ex.h"

pthread_t ubus_tid = 0;
QUIT_ID is_quit = QUIT_ID_NONE;
READY_ID is_ready = READY_ID_NONE;

const char * const p_type_str[] = {
	[BLOBMSG_TYPE_UNSPEC] = "Unspec",
	[BLOBMSG_TYPE_ARRAY] = "Array",
	[BLOBMSG_TYPE_TABLE] = "Table",
	[BLOBMSG_TYPE_STRING] = "String",
	[BLOBMSG_TYPE_INT64] = "Integer64",
	[BLOBMSG_TYPE_INT32] = "Integer32",
	[BLOBMSG_TYPE_INT16] = "Integer16",
	[BLOBMSG_TYPE_INT8] = "Integer8",
};

char ubus_root[LEN_OF_BUF256] = UBUS_UNIX_SOCKET_EX;
struct ubus_context *ubus_conn = NULL;

typedef struct UEventList_STRUCT
{
	void* next;

	struct ubus_event_handler *ev;
} UEventList_t;

CLIST(ubus_event_list);

typedef struct USubscriberList_STRUCT
{
	void* next;

	struct ubus_subscriber *s;
} USubscriberList_t;

CLIST(ubus_subscriber_list);

typedef struct UTimerList_STRUCT
{
	void* next;

	struct uloop_timeout *u_timer;
	int msecs;
} UTimerList_t;

CLIST(ubus_timer_list);

typedef struct UEventQueue_STRUCT
{
	void* next;

	char *obj_name;
	struct blob_buf bbuf;
} UEventQueue_t;

CLIST(ubus_event_queue);

void uloop_timeout_set_ex(void)
{
	UTimerList_t *cur = NULL;

	for (cur = clist_head(ubus_timer_list); cur != NULL; cur = clist_item_next(cur))
	{
		struct uloop_timeout *u_timer = cur->u_timer;
		int msecs = cur->msecs;
		uloop_timeout_set(u_timer, msecs);
	}
}

static void uloop_timerlist_stop(void)
{
	UTimerList_t *cur = NULL;

	for (cur = clist_head(ubus_timer_list); cur != NULL; cur = clist_item_next(cur))
	{
		struct uloop_timeout *u_timer = cur->u_timer;
		uloop_timeout_cancel(u_timer);
	}
}

int uloop_timerlist_add(uloop_timeout_handler cb, int msecs)
{
	int ret = -1;
	UTimerList_t *ubus_timer = (UTimerList_t *)SAFE_CALLOC(1, sizeof(UTimerList_t));

	if (ubus_timer)
	{
		ubus_timer->u_timer = (struct uloop_timeout *)SAFE_CALLOC(1, sizeof(struct uloop_timeout));
		if (ubus_timer->u_timer)
		{
			ubus_timer->u_timer->cb = cb;
			ubus_timer->msecs = msecs;
			//uloop_timeout_set(ubus_timer->u_timer, msecs);
			clist_add(ubus_timer_list, ubus_timer);
			ret = 0;
		}
		else
		{
			DBG_ER_LN("SAFE_CALLOC error - u_timer !!! (msecs: %d)", msecs);
			SAFE_FREE(ubus_timer);
		}
	}
	else
	{
		DBG_ER_LN("SAFE_CALLOC error - ubus_timer !!! (msecs: %d)", msecs);
	}

	return ret;
}

static void uloop_timerlist_item_free(void *item)
{
	UTimerList_t *ubus_timer = (UTimerList_t *)item;

	if ((ubus_timer) && (ubus_timer->u_timer))
	{
		SAFE_FREE(ubus_timer->u_timer);
	}
}

static void uloop_timerlist_free(void)
{
	clist_free_ex(ubus_timer_list, uloop_timerlist_item_free);
}

void uloop_end_ex(void)
{
	uloop_timerlist_stop();
	uloop_end();
}

int ubus_cli_register_event(const char *pattern, ubus_event_handler_t cb)
{
	int ret = -1;
	UEventList_t *ubus_event = (UEventList_t *)SAFE_CALLOC(1, sizeof(UEventList_t));

	if (ubus_event)
	{
		ubus_event->ev = (struct ubus_event_handler *)SAFE_CALLOC(1, sizeof(struct ubus_event_handler));
		if (ubus_event->ev)
		{
			ubus_event->ev->cb = cb;

			int result = ubus_register_event_handler(ubus_conn_get(), ubus_event->ev, pattern);
			if (result)
			{
				DBG_ER_LN("ubus_register_event_handler error !!! (pattern: %s, ret: %d %s)", pattern, ret, ubus_strerror(ret));
				SAFE_FREE(ubus_event->ev);
				SAFE_FREE(ubus_event);
			}
			else
			{
				DBG_DB_LN("(pattern: %s)", pattern);
				clist_add(ubus_event_list, ubus_event);
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("SAFE_CALLOC error - ev !!! (pattern: %s)", pattern);
			SAFE_FREE(ubus_event);
		}
	}
	else
	{
		DBG_ER_LN("SAFE_CALLOC error - ubus_event !!! (pattern: %s)", pattern);
	}

	return ret;
}

static int ubus_cli_subscribe_ex(char *obj_name, struct ubus_subscriber *s)
{
	int ret = ubus_register_subscriber(ubus_conn_get(), s);
	if (ret)
	{
		DBG_ER_LN("ubus_register_subscriber error !!! (obj_name: %s, ret: %d %s)", obj_name, ret, ubus_strerror(ret));
		goto exit_sub;
	}

	uint32_t obj_id;
	ret = ubus_lookup_id(ubus_conn_get(), obj_name, &obj_id);
	if (ret)
	{
		DBG_ER_LN("ubus_lookup_id error !!! (obj_name: %s, ret: %d %s)", obj_name, ret, ubus_strerror(ret));
		goto exit_sub;
	}

	ret = ubus_subscribe(ubus_conn_get(), s, obj_id);
	if (ret)
	{
		DBG_ER_LN("ubus_subscribe error !!! (obj_name: %s, ret: %d %s)", obj_name, ret, ubus_strerror(ret));
		goto exit_sub;
	}

	ret = 0;
exit_sub:
	return ret;
}

int ubus_cli_subscribe(char *obj_name, ubus_handler_t cb, ubus_remove_handler_t remove_cb)
{
	int ret = -1;
	USubscriberList_t *ubus_subscriber = (USubscriberList_t *)SAFE_CALLOC(1, sizeof(USubscriberList_t));

	if (ubus_subscriber)
	{
		ubus_subscriber->s = (struct ubus_subscriber *)SAFE_CALLOC(1, sizeof(struct ubus_subscriber));
		if (ubus_subscriber->s)
		{
			ubus_subscriber->s->cb = cb;
			ubus_subscriber->s->remove_cb = remove_cb;

			int result = ubus_cli_subscribe_ex(obj_name, ubus_subscriber->s);
			if (result)
			{
				DBG_ER_LN("ubus_cli_subscribe_ex error !!! (obj_name: %s)", obj_name);
				SAFE_FREE(ubus_subscriber->s);
				SAFE_FREE(ubus_subscriber);
			}
			else
			{
				DBG_DB_LN("(obj_name: %s)", obj_name);
				clist_add(ubus_subscriber_list, ubus_subscriber);
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("SAFE_CALLOC error - s !!! (obj_name: %s)", obj_name);
			SAFE_FREE(ubus_subscriber);
		}
	}
	else
	{
		DBG_ER_LN("SAFE_CALLOC error - ubus_subscriber !!! (obj_name: %s)", obj_name);
	}

	return ret;
}

int ubus_cli_invoke_ex(char *obj_name, const char *method, struct blob_buf *bbuf, ubus_data_handler_t cb, int timeout)
{
	if ( ubus_quit() == QUIT_ID_NOW ) return -1;
	uint32_t obj_id;

	if (ubus_lookup_id(ubus_conn_get(), obj_name, &obj_id))
	{
		DBG_ER_LN("ubus_lookup_id error !!! (obj_name: %s)", obj_name);
		return -1;
	}

	return ubus_invoke(ubus_conn_get(), obj_id, method, bbuf->head, cb, 0, timeout);
}

static int ubus_srv_notify_ex(struct ubus_object *obj, const char *type, struct blob_buf *bbuf)
{
	return ubus_notify(ubus_conn_get(), obj, type, bbuf->head, -1);
}

int ubus_srv_notify_simple(const char *method, struct ubus_object *obj, char *key, char *val)
{
	if ( ubus_quit() == QUIT_ID_NOW ) return -1;
	DBG_DB_LN("(method: %s, key: %s, val: %s)", method, key, val);

	struct blob_buf bbuf = {};
	blob_buf_init(&bbuf, 0);
	blobmsg_add_string(&bbuf, key, val);
	int ret = ubus_srv_notify_ex( obj, method, &bbuf);
	blob_buf_free(&bbuf);
	return ret;
}

int ubus_srv_send_event_ex(const char *obj_name, struct blob_buf *bbuf)
{
	if ( ubus_quit() == QUIT_ID_NOW ) return -1;
	return ubus_send_event(ubus_conn_get(), obj_name, bbuf->head);
}

int ubus_srv_send_event_simple(const char *obj_name, char *key, char *val)
{
	int ret = 0;

	if ( ubus_quit() == QUIT_ID_NOW ) return -1;

#ifdef SEND_EVENT_DIRECTLY
	struct blob_buf bbuf = {};
	blob_buf_init(&bbuf, 0);
	blobmsg_add_string(&bbuf, key, val);
	ret = ubus_srv_send_event_ex(obj_name, &bbuf);
	DBG_DB_LN("(obj_name: %s, key: %s, val: %s)", obj_name, key, val);
	blob_buf_free(&bbuf);
#else
	UEventQueue_t *ubus_equeue = (UEventQueue_t *)SAFE_CALLOC(1, sizeof(UEventQueue_t));
	if (ubus_equeue)
	{
		SAFE_ASPRINTF(ubus_equeue->obj_name, "%s", obj_name);
		blob_buf_init(&ubus_equeue->bbuf, 0);
		blobmsg_add_string(&ubus_equeue->bbuf, key, val);
		clist_add(ubus_event_queue, ubus_equeue);
		ret = 0;
	}
	else
	{
		ret = -1;
	}
#endif
	return ret;
}

static void ubus_srv_add_object_show(struct ubus_object *srv_obj)
{
	const char *o_name = srv_obj->name;
	const struct ubus_method *methods = srv_obj->methods;
	int n_methods = srv_obj->n_methods;
	int i = 0;

	if (n_methods)
	{
		for (i=0; i<n_methods; i++)
		{
			const char *m_name = methods[i].name;

			const struct blobmsg_policy *policy = methods[i].policy;
			int n_policy = methods[i].n_policy;

			int j = 0;
			for (j=0; j<n_policy; j++)
			{
				const char *p_name = policy[j].name;
				enum blobmsg_type typeid = policy[j].type;
				const char *p_type = p_type_str[0];
				if (typeid < __BLOBMSG_TYPE_LAST)
					p_type = p_type_str[typeid];

				DBG_IF_LN("(%s/%s, %s-%s)", o_name, m_name, p_name, p_type);
			}
		}
	}
	else
	{
		DBG_IF_LN("(%s)", o_name);
	}
}

int ubus_srv_add_object_ex(struct ubus_context *ctx, struct ubus_object *obj)
{
	ubus_srv_add_object_show(obj);
	return ubus_add_object(ctx, obj);
}

int ubus_srv_object_subscribe(struct ubus_context *ctx, struct ubus_object *obj, ubus_state_handler_t subscribe_cb)
{
	obj->subscribe_cb = subscribe_cb;
	return ubus_srv_add_object_ex(ctx, obj);
}

static const char *json_format_type(void *priv, struct blob_attr *attr)
{
	static const char * const attr_types[] = {
		[BLOBMSG_TYPE_INT8] = "\"Boolean\"",
		[BLOBMSG_TYPE_INT32] = "\"Integer\"",
		[BLOBMSG_TYPE_STRING] = "\"String\"",
		[BLOBMSG_TYPE_ARRAY] = "\"Array\"",
		[BLOBMSG_TYPE_TABLE] = "\"Table\"",
	};
	const char *type = NULL;
	int typeid;

	if (blob_id(attr) != BLOBMSG_TYPE_INT32)
		return NULL;

	typeid = blobmsg_get_u32(attr);
	if (typeid < ARRAY_SIZE(attr_types))
		type = attr_types[typeid];
	if (!type)
		type = "\"(unknown)\"";

	return type;
}

static void ubus_cli_list_cb(struct ubus_context *ctx, struct ubus_object_data *obj, void *priv)
{
	struct blob_attr *cur;
	char *s;
	int rem;

	DBG_IF_LN("'%s' @%08x", obj->path, obj->id);

	if (!obj->signature)
		return;

	blob_for_each_attr(cur, obj->signature, rem) {
		s = blobmsg_format_json_with_cb(cur, false, json_format_type, NULL, -1);
		DBG_IF_LN("\t%s", s);
		SAFE_FREE(s);
	}
}

void ubus_cli_list_register(const char *path, ubus_lookup_handler_t cb)
{
	if (cb)
	{
		ubus_lookup(ubus_conn_get(), path, cb, NULL);
	}
	else
	{
		ubus_lookup(ubus_conn_get(), path, ubus_cli_list_cb, NULL);
	}
}

static void ubus_cli_event_item_free(void *item)
{
	UEventList_t *ubus_event = (UEventList_t *)item;

	if ((ubus_event) && (ubus_event->ev))
	{
		SAFE_FREE(ubus_event->ev);
	}
}

static void ubus_cli_event_list_free(void)
{
	clist_free_ex(ubus_event_list, ubus_cli_event_item_free);
}

static void ubus_cli_subscriber_item_free(void *item)
{
	USubscriberList_t *ubus_subscriber  = (USubscriberList_t *)item;

	if ((ubus_subscriber) && (ubus_subscriber->s))
	{
		SAFE_FREE(ubus_subscriber->s);
	}
}

static void ubus_cli_subscriber_list_free(void)
{
	clist_free_ex(ubus_subscriber_list, ubus_cli_subscriber_item_free);
}

static void ubus_srv_equeue_item_free(void *item)
{
	UEventQueue_t *ubus_equeue = (UEventQueue_t *)item;

	if (ubus_equeue)
	{
		blob_buf_free(&ubus_equeue->bbuf);
		SAFE_FREE(ubus_equeue->obj_name);
	}
}

static void ubus_srv_equeue_free(void)
{
	clist_free_ex(ubus_event_queue, ubus_srv_equeue_item_free);
}

static void ubus_srv_conn_lost(struct ubus_context *ctx)
{
	struct ubus_context *ubus_req = ubus_conn_get();
	DBG_ER_LN("(local_id: 0x%08X)", ubus_req->local_id);
}

struct ubus_context *ubus_srv_init(void)
{
	struct ubus_context *ubus_req = ubus_conn_init();
	if ( ubus_req == NULL )
	{
		goto exit_ubus;
	}

	ubus_req->connection_lost = ubus_srv_conn_lost;

exit_ubus:
	return ubus_req;
}

#ifdef SEND_EVENT_DIRECTLY
#else
void timer_200msec_loop(struct uloop_timeout *t)
{
	while ( clist_length(ubus_event_queue) > 0 )
	{
		UEventQueue_t *item = (UEventQueue_t*)clist_pop(ubus_event_queue);

		int ret = ubus_srv_send_event_ex(item->obj_name, &item->bbuf);
		DBG_DB_LN("(obj_name: %s, ret: %d)", item->obj_name, ret);
		blob_buf_free(&item->bbuf);

		SAFE_FREE(item->obj_name);
		SAFE_FREE(item);
	}

	uloop_timeout_set(t, TIMEOUT_OF_EVENT_200MSEC);
}
#endif

void ubus_conn_free(void)
{
	if ( ubus_conn_get() )
	{
		uloop_timerlist_free();

		ubus_srv_equeue_free();
		ubus_cli_subscriber_list_free();
		ubus_cli_event_list_free();

		ubus_free( ubus_conn_get() );
	}
}

struct ubus_context *ubus_conn_init(void)
{
	DBG_DB_LN("(ubus_root: %s)", ubus_root);
	if (SAFE_STRLEN(ubus_root) <= 0)
	{
		ubus_conn = ubus_connect(NULL);
	}
	else
	{
		ubus_conn = ubus_connect(ubus_root);
	}

	if ( ubus_conn == NULL)
	{
		DBG_ER_LN("ubus_connect error !!!");
	}

	clist_init(ubus_event_list);
	clist_init(ubus_subscriber_list);
	clist_init(ubus_timer_list);
	clist_init(ubus_event_queue);

#ifdef SEND_EVENT_DIRECTLY
#else
	uloop_timerlist_add(timer_200msec_loop, TIMEOUT_OF_EVENT_200MSEC);
#endif

	return ubus_conn;
}

struct ubus_context *ubus_conn_get(void)
{
	return ubus_conn;
}

void ubus_root_set(char *path)
{
	SAFE_SPRINTF_EX(ubus_root, "%s", path);
}

char *ubus_root_get(void)
{
	return ubus_root;
}

void ubus_quit_set(QUIT_ID quit)
{
	is_quit = quit;
}

QUIT_ID ubus_quit(void)
{
	return is_quit;
}

void ubus_ready_set(READY_ID ready)
{
	is_ready = ready;
}

READY_ID ubus_ready(void)
{
	int retry = 3;
	while ( ( is_ready != READY_ID_OK ) && ( retry > 0 ) && ( ubus_quit() == QUIT_ID_NONE ) )
	{
		retry--;
		sleep(1);
	}

	if ( is_ready == READY_ID_OK )
	{
		return READY_ID_OK;
	}
	else
	{
		DBG_ER_LN("(retry: %d)", retry);
		return READY_ID_NONE;
	}
}

void ubus_add_uloop_ex(struct ubus_context *ctx)
{
	if (ctx)
	{
		ubus_add_uloop(ctx);
#ifdef FD_CLOEXEC
		fcntl(ctx->sock.fd, F_SETFD, fcntl(ctx->sock.fd, F_GETFD) | FD_CLOEXEC);
#endif
	}
}

static void *ubus_thread_handler(void *arg)
{
	//struct ubus_context *ubus_req = (struct ubus_object *)arg;
	//SAFE_THREAD_DETACH( pthread_self() );

	//struct ubus_context *ubus_req = ubus_srv_conn_get();
	//if ( ubus_req != NULL )
	if ( (ubus_conn_get()) )
	{
		//DBG_IF_LN("ubus listen ... (ubus_root: %s, local_id: 0x%08X)", ubus_root, ubus_req->local_id);
		DBG_IF_LN("ubus listen ... (ubus_root: %s)", ubus_root);
		uloop_init();
		ubus_add_uloop_ex( ubus_conn_get() );
		uloop_timeout_set_ex();

		ubus_ready_set(READY_ID_OK);
		uloop_run();
		ubus_ready_set(READY_ID_NONE);
		uloop_done();
	}

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	return NULL;
}

int ubus_thread_init(void)
{
	if (SAFE_THREAD_CREATE(ubus_tid, NULL, ubus_thread_handler, (void*)NULL) != 0)
	{
		DBG_ER_LN("SAFE_THREAD_CREATE error !!!");
		return -1;
	}

	ubus_ready();

	return 0;
}

void ubus_thread_stop(void)
{
	ubus_quit_set(QUIT_ID_NOW);

	if (ubus_tid != 0)
	{
		pthread_kill(ubus_tid, SIGINT);
	}
	uloop_end_ex();

	sleep(1);
}

void ubus_thread_close(void)
{
	static int is_free = 0;
	if (is_free == 0)
	{
		is_free ++;
		if (ubus_tid != 0)
		{
			pthread_join(ubus_tid, NULL);
			ubus_tid = 0;
		}
		ubus_conn_free();
	}
}

