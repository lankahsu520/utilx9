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

//#define USE_LWS_MINIMAL

#ifdef USE_LWS_MINIMAL
struct msg {
	void *payload; /* is malloc'd */
	size_t len;
};

struct per_session_data__minimal {
	struct per_session_data__minimal *pss_list;
	struct lws *wsi;
	int last; /* the last message number we sent */
};

struct per_vhost_data__minimal {
	struct lws_context *context;
	struct lws_vhost *vhost;
	const struct lws_protocols *protocol;

	struct per_session_data__minimal *pss_list; /* linked-list of live pss*/

	struct msg amsg; /* the one pending message... */
	int current; /* the current message number we are caching */
};

static void
__minimal_destroy_message(void *_msg)
{
	struct msg *msg = _msg;

	free(msg->payload);
	msg->payload = NULL;
	msg->len = 0;
}

static int callback_minimal(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	struct per_session_data__minimal *pss = (struct per_session_data__minimal *)user;
	struct per_vhost_data__minimal *vhd =(struct per_vhost_data__minimal *)lws_protocol_vh_priv_get(lws_get_vhost(wsi), lws_get_protocol(wsi));
	int m;

	DBG_IF_LN("%d %s !!! (wsi: %p)", reason, translate_lws_cb(reason), wsi);
	switch (reason)
	{
		case LWS_CALLBACK_PROTOCOL_INIT:
			vhd = lws_protocol_vh_priv_zalloc(lws_get_vhost(wsi), lws_get_protocol(wsi), sizeof(struct per_vhost_data__minimal));
			vhd->context = lws_get_context(wsi);
			vhd->protocol = lws_get_protocol(wsi);
			vhd->vhost = lws_get_vhost(wsi);
			break;

		case LWS_CALLBACK_ESTABLISHED:
			/* add ourselves to the list of live pss held in the vhd */
			lws_ll_fwd_insert(pss, pss_list, vhd->pss_list);
			pss->wsi = wsi;
			pss->last = vhd->current;
			break;

		case LWS_CALLBACK_CLOSED:
			/* remove our closing pss from the list of live pss */
			lws_ll_fwd_remove(struct per_session_data__minimal, pss_list,
					  pss, vhd->pss_list);
			break;

		case LWS_CALLBACK_SERVER_WRITEABLE:
			if (!vhd->amsg.payload)
				break;

			if (pss->last == vhd->current)
				break;

			/* notice we allowed for LWS_PRE in the payload already */
			m = lws_write(wsi, ((unsigned char *)vhd->amsg.payload) +
				      LWS_PRE, vhd->amsg.len, LWS_WRITE_TEXT);
			if (m < (int)vhd->amsg.len) {
				lwsl_err("ERROR %d writing to ws\n", m);
				return -1;
			}

			pss->last = vhd->current;
			break;

		case LWS_CALLBACK_RECEIVE:
			if (vhd->amsg.payload)
				__minimal_destroy_message(&vhd->amsg);

			vhd->amsg.len = len;
			/* notice we over-allocate by LWS_PRE */
			vhd->amsg.payload = malloc(LWS_PRE + len);
			if (!vhd->amsg.payload) {
				lwsl_user("OOM: dropping\n");
				break;
			}

			memcpy((char *)vhd->amsg.payload + LWS_PRE, in, len);
			vhd->current++;

			/*
			 * let everybody know we want to write something on them
			 * as soon as they are ready
			 */
			lws_start_foreach_llp(struct per_session_data__minimal **,
					      ppss, vhd->pss_list) {
				lws_callback_on_writable((*ppss)->wsi);
			} lws_end_foreach_llp(ppss, pss_list);
			break;

		default:
			break;
	}

	return 0;
}
#else
static int lws2_simple_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	int ret = -1;

	LWSCtx_t *lws_ctx = lws2_protocol_user(wsi);

	if ((lws_ctx) && (lws_ctx->callback))
	{
		ret = lws_ctx->callback(wsi, reason, user, in, len);
	}

	if ( ret != 0 )
	{
		//DBG_WN_LN("%d %s !!! (wsi: %p)", reason, translate_lws_cb(reason), wsi);
		switch( reason )
		{
			case LWS_CALLBACK_HTTP:
#if (0)
				//DBG_WN_LN("(reason: %d-%s)", reason, translate_lws_cb(reason));
				lws_serve_http_file( wsi, "example.html", "text/html", NULL, 0 );
#endif
				DBG_DB_LN("%d %s !!! (wsi: %p)", reason, translate_lws_cb(reason), wsi);
				break;

			//case LWS_CALLBACK_WSI_CREATE: // 29
			case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: // 19
			case LWS_CALLBACK_ESTABLISHED: // 0
			case LWS_CALLBACK_CLIENT_ESTABLISHED: // 3
				{
					lws2_lock(lws_ctx);
					LWSSession_t *session = (LWSSession_t*)user;//SAFE_CALLOC(1, sizeof(LWSSession_t));
					if (session)
					{
						if (clist_contains(lws_ctx->session_list, session)==1)
						{
							DBG_IF_LN("%d %s - dupicate !!! (session: %p)", reason, translate_lws_cb(reason), session);
						}
						else
						{
							if (lws_ctx->cinfo.foreign_loops)
							{
								session->use_foreign_loops = 1;
							}
							else
							{
								session->use_foreign_loops = 0;
							}
							session->wsi = wsi;
							CLIST_STRUCT_INIT(session, msg_list);
							//SAFE_MUTEX_ATTR_RECURSIVE(session->in_mtx);

							DBG_IF_LN("%d %s !!! (session: %p)", reason, translate_lws_cb(reason), session);
							//lws_set_wsi_user(wsi, (void *)session);

							clist_push(lws_ctx->session_list, session);
						}
					}
					lws2_unlock(lws_ctx);
				}
				break;

			case LWS_CALLBACK_RECEIVE: // 6
				{
					lws2_lock(lws_ctx);
					if ( lws_ctx->wsi_id == LWS_WSI_ID_SERVER )
					{
						if (lws_ctx->isecho)
						{
							//lws2_session_write_q_push((LWSSession_t *)user, in, len);
							lws2_session_write_q_broadcast(lws_ctx, in, len);
						}
					}
					lws2_unlock(lws_ctx);
				}
				break;

			case LWS_CALLBACK_SERVER_WRITEABLE: // 11
				{
					lws2_lock(lws_ctx);
					if ( lws_ctx->wsi_id == LWS_WSI_ID_SERVER )
					{
						lws2_session_write((LWSSession_t *)user);
					}
					lws2_unlock(lws_ctx);
				}
				break;

			case LWS_CALLBACK_CLIENT_WRITEABLE: // 10
				{
					lws2_lock(lws_ctx);
					if ( lws_ctx->wsi_id == LWS_WSI_ID_CLIENT )
					{
						lws2_session_write((LWSSession_t *)user);
					}
					lws2_unlock(lws_ctx);
				}
				break;

			case LWS_CALLBACK_WSI_DESTROY: // 30
				{
					if ( (lws_ctx->isfree == 0 ) && (user) )
					{
						LWSSession_t *session = (LWSSession_t*)user;
						lws2_session_lock(session);
						lws2_session_pop(lws_ctx, session);
						lws2_session_unlock(session);
					}
				}
				break;

			default:
				DBG_DB_LN("%d %s !!! (wsi: %p)", reason, translate_lws_cb(reason), wsi);
				break;
		}
	}

	return 0;
}

#endif

static struct lws_protocols protocols_simple[] =
{
#ifdef USE_LWS_MINIMAL
	{
		.name = "lws-minimal",
		.callback = callback_minimal,
		.per_session_data_size = sizeof(struct per_session_data__minimal),
		.rx_buffer_size = LEN_OF_WEBSOCKET,
		//.user = (void *)&lws_req,
	},
#else
	{
		.name = LWS_SUB_PROTOCOL_HTTP,
		.callback = lws2_simple_cb,
		.per_session_data_size = sizeof(LWSSession_t),
		.rx_buffer_size = LEN_OF_WEBSOCKET,
		//.user = (void *)&lws_req,
	},
#endif
	{ NULL, NULL, 0, 0 } /* terminator */
};

char* translate_lws_cb(enum lws_callback_reasons reason)
{
	switch( reason )
	{
		case LWS_CALLBACK_ESTABLISHED: // 0
			return "LWS_CALLBACK_ESTABLISHED";
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: // 1
			return "LWS_CALLBACK_CLIENT_CONNECTION_ERROR";
		case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH: // 2
			return "LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH";
		case LWS_CALLBACK_CLIENT_ESTABLISHED: // 3
			return "LWS_CALLBACK_CLIENT_ESTABLISHED";
		case LWS_CALLBACK_CLOSED: // 4
			return "LWS_CALLBACK_CLOSED";
		case LWS_CALLBACK_CLOSED_HTTP: // 5
			return "LWS_CALLBACK_CLOSED_HTTP";
		case LWS_CALLBACK_RECEIVE: // 6
			return "LWS_CALLBACK_RECEIVE";
		case LWS_CALLBACK_CLIENT_RECEIVE: // 8
			return "LWS_CALLBACK_CLIENT_RECEIVE";
		case LWS_CALLBACK_CLIENT_WRITEABLE: // 10
			return "LWS_CALLBACK_CLIENT_WRITEABLE";
		case LWS_CALLBACK_SERVER_WRITEABLE: // 11
			return "LWS_CALLBACK_SERVER_WRITEABLE";
		case LWS_CALLBACK_FILTER_NETWORK_CONNECTION: // 17
			return "LWS_CALLBACK_FILTER_NETWORK_CONNECTION";
		case LWS_CALLBACK_FILTER_HTTP_CONNECTION: // 18
			return "LWS_CALLBACK_FILTER_HTTP_CONNECTION";
		case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: // 19
			return "LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED";
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION: // 20
			return "LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION";
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS: // 21
			return "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS";
		case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS: // 22
			return "LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS";
		case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER: // 24
			return "LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER";
		case LWS_CALLBACK_PROTOCOL_INIT: // 27
			return "LWS_CALLBACK_PROTOCOL_INIT";
		case LWS_CALLBACK_PROTOCOL_DESTROY: // 28
			return "LWS_CALLBACK_PROTOCOL_DESTROY";
		case LWS_CALLBACK_WSI_CREATE: // 29
			return "LWS_CALLBACK_WSI_CREATE";
		case LWS_CALLBACK_WSI_DESTROY: // 30
			return "LWS_CALLBACK_WSI_DESTROY";
		case LWS_CALLBACK_GET_THREAD_ID: // 31
			return "LWS_CALLBACK_GET_THREAD_ID";
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE: // 38
			return "LWS_CALLBACK_WS_PEER_INITIATED_CLOSE";
		case LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP: // 44
			return "LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP";
		case LWS_CALLBACK_HTTP_BIND_PROTOCOL: // 49
			return "LWS_CALLBACK_HTTP_BIND_PROTOCOL";
		case LWS_CALLBACK_ADD_HEADERS: // 53
			return "LWS_CALLBACK_ADD_HEADERS";
		case LWS_CALLBACK_EVENT_WAIT_CANCELLED: // 71
			return "LWS_CALLBACK_EVENT_WAIT_CANCELLED";
		case LWS_CALLBACK_CLIENT_CLOSED: // 75
			return "LWS_CALLBACK_CLIENT_CLOSED";
		case LWS_CALLBACK_WS_SERVER_DROP_PROTOCOL: // 78
			return "LWS_CALLBACK_WS_SERVER_DROP_PROTOCOL";
		case LWS_CALLBACK_WS_CLIENT_DROP_PROTOCOL: // 80
			return "LWS_CALLBACK_WS_CLIENT_DROP_PROTOCOL";
		case LWS_CALLBACK_CLIENT_HTTP_BIND_PROTOCOL: // 85
			return "LWS_CALLBACK_CLIENT_HTTP_BIND_PROTOCOL";
		case LWS_CALLBACK_HTTP_CONFIRM_UPGRADE: // 86
			return "LWS_CALLBACK_HTTP_CONFIRM_UPGRADE";
		default:
			return "LWS_CALLBACK_XXX";
			break;
	}
}

LWSCtx_t *lws2_protocol_user(struct lws *wsi)
{
	LWSCtx_t *lws_ctx = NULL;
	const struct lws_protocols *protocol = lws_get_protocol( wsi );
	//struct lws_context *context = lws_get_context( wsi );
	//LWSCtx_t *lws_ctx = (LWSCtx_t *)protocol->user;

	if (protocol)
	{
		lws_ctx = (LWSCtx_t *)protocol->user;
	}

	return lws_ctx;
}

void lws2_session_lock(LWSSession_t *session)
{
	LWSCtx_t *lws_ctx = lws2_protocol_user(session->wsi);

	if (lws_ctx->isfree == 0 )
	{
		lws2_lock(lws_ctx);
	}
}

void lws2_session_unlock(LWSSession_t *session)
{
	LWSCtx_t *lws_ctx = lws2_protocol_user(session->wsi);
	if (lws_ctx->isfree == 0 )
	{
		lws2_unlock(lws_ctx);
	}
}

static void lws2_session_msg_free_cb(void *item)
{
	LWSMsg_t *msg = (LWSMsg_t *)item;
	if (msg)
	{
		char *payload = msg->payload;
		SAFE_FREE(payload);
	}
}

static void lws2_session_free_cb(void *item)
{
	LWSSession_t *session = (LWSSession_t *)item;
	DBG_IF_LN("(session: %p)", session);
	if (session)
	{
		clist_free_ex(session->msg_list, lws2_session_msg_free_cb);
	}
}

void lws2_session_pop(LWSCtx_t *lws_ctx, LWSSession_t *session)
{
	if (session)
	{
		clist_free_ex(session->msg_list, lws2_session_msg_free_cb);
		//SAFE_MUTEX_DESTROY_EX(session);
		DBG_IF_LN("(session: %p)", session);
		if (lws_ctx)
		{
			clist_remove(lws_ctx->session_list, session);
		}
	}
}

void lws2_session_write(LWSSession_t *session)
{
	if (session)
	{
		lws2_session_lock(session);

		LWSMsg_t *msg = clist_pop(session->msg_list);
		if ( (msg) && (msg->payload) )
		{
			SAFE_LWS_WRITE(session->wsi, msg->payload, msg->payload_len, LWS_WRITE_TEXT);
			SAFE_FREE(msg->payload);

			if (clist_length(session->msg_list) > 0 )
			{
				lws_callback_on_writable(session->wsi);
				// 20211122 Lanka Hsu: send data ASAP
				// https://issueexplorer.com/issue/warmcat/libwebsockets/2358
				if (session->use_foreign_loops==0)
				{
					lws_cancel_service_pt(session->wsi);
				}
			}
		}
		SAFE_FREE(msg);

		lws2_session_unlock(session);
	}
}

void lws2_session_write_q_push(LWSSession_t *session, char *payload, int payload_len)
{
	if (session)
	{
		lws2_session_lock(session);

		LWSMsg_t *msg = (LWSMsg_t*)SAFE_CALLOC(1, sizeof(LWSMsg_t));
		if (msg)
		{
			msg->payload = (char*)SAFE_CALLOC(1, LWS_SEND_BUFFER_PRE_PADDING + payload_len + 1);
			if (msg->payload)
			{
				SAFE_LWS_MEMCPY(msg->payload, payload, payload_len, payload);
			}

			msg->payload_len = payload_len;
			clist_push(session->msg_list, msg);

			lws_callback_on_writable(session->wsi);
			// 20211122 Lanka Hsu: send data ASAP
			// https://issueexplorer.com/issue/warmcat/libwebsockets/2358
			if (session->use_foreign_loops==0)
			{
				lws_cancel_service_pt(session->wsi);
			}
		}
		lws2_session_unlock(session);
	}
}

void lws2_session_write_q_broadcast(LWSCtx_t *lws_ctx, char *payload, int payload_len)
{
	if (lws_ctx)
	{
		LWSSession_t *cur = NULL;

		for (cur = clist_head(lws_ctx->session_list); cur != NULL; cur = clist_item_next(cur))
		{
			lws2_session_write_q_push(cur, payload, payload_len);
		}
	}
}

int lws2_session_count(LWSCtx_t *lws_ctx)
{
	int ret = 0;

	if (lws_ctx)
	{
		ret = clist_length(lws_ctx->session_list);
	}

	return ret;
}

static void lws2_context_close(LWSCtx_t *lws_ctx)
{
	if ( (lws_ctx) && (lws_ctx->context) )
	{
		DBG_IF_LN("%s (port: %d, context: %p)", DBG_TXT_BYE_BYE, lws_ctx->cinfo.port, lws_ctx->context);
		if (lws_ctx->context)
		{
			//for libwebsockets-4.2.2
			//clist_free_ex(lws_ctx->session_list, lws2_session_free_cb);
			clist_pop_ex(lws_ctx->session_list, lws2_session_free_cb);

			lws_context_destroy( lws_ctx->context );
			lws_ctx->context = NULL;
		}
	}
}

void lws2_lock(LWSCtx_t *lws_ctx)
{
	if (lws_ctx)
	{
		ThreadX_t *tidx_req = &lws_ctx->tidx;
		threadx_lock(tidx_req);
	}
}

void lws2_unlock(LWSCtx_t *lws_ctx)
{
	if (lws_ctx)
	{
		ThreadX_t *tidx_req = &lws_ctx->tidx;
		threadx_unlock(tidx_req);
	}
}

#if (0)
static void lws2_mutex_init(LWSCtx_t *lws_ctx)
{
	ThreadX_t *tidx_req = &lws_ctx->tidx;
	threadx_mutex_init(tidx_req);
}

static void lws2_mutex_free(LWSCtx_t *lws_ctx)
{
	ThreadX_t *tidx_req = &lws_ctx->tidx;
	threadx_mutex_free(tidx_req);
}
#endif

void lws2_cli_init(LWSCtx_t *lws_ctx, struct lws_protocols *protocols, unsigned int options, uv_loop_t *loop)
{
	if ( lws_ctx )
	{
		//SAFE_MEMSET(lws_ctx, 0, sizeof(LWSCtx_t));

		lws_ctx->wsi_id = LWS_WSI_ID_CLIENT;

		lws_ctx->cinfo.port = CONTEXT_PORT_NO_LISTEN;
		if (protocols)
		{
			lws_ctx->cinfo.protocols = protocols;
		}
		else
		{
			protocols = protocols_simple;
			lws_ctx->cinfo.protocols = protocols;
		}
		lws_ctx->cinfo.gid = -1;
		lws_ctx->cinfo.uid = -1;
		{
			// to set user as lws_ctx
			int idx = 0;
			while ( protocols[idx].name )
			{
				DBG_IF_LN("(protocols[%d].name: %s)", idx, protocols[idx].name);
				protocols[idx].user = (void *)lws_ctx;
				idx ++;
			}
		}

		lws_ctx->cinfo.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

		if (lws_ctx->security)
		{
			if ( ( SAFE_ACCESS(lws_ctx->certificate_file, F_OK) == -1 ) ||
				( SAFE_ACCESS(lws_ctx->privatekey_file, F_OK) == -1 ) )
			{
				DBG_ER_LN("SAFE_ACCESS error !!! (certificate_file: %s, privatekey_file: %s)", lws_ctx->certificate_file, lws_ctx->privatekey_file);
			}
			else
			{
				lws_ctx->cinfo.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
				lws_ctx->cinfo.ssl_cert_filepath = lws_ctx->certificate_file;
				lws_ctx->cinfo.ssl_private_key_filepath = lws_ctx->privatekey_file;
			}
		}

		if (loop)
		{
			lws_ctx->cinfo.options |= options;
			lws_ctx->cinfo.foreign_loops = (void*[]){loop};
			DBG_DB_LN("(loop: %p, options: %ld)", loop, lws_ctx->cinfo.options);
		}

		struct lws_context *context = lws_create_context( &lws_ctx->cinfo );
		if (context)
		{
			lws_ctx->context = context;
		}
		else
		{
			DBG_ER_LN("lws_create_context error !!!");
		}
	}
}

void lws2_cli_open(LWSCtx_t *lws_ctx, char *address, int port, char *filename)
{
	if ( lws_ctx )
	{
		CLIST_STRUCT_INIT(lws_ctx, session_list);

		SAFE_SPRINTF_EX(lws_ctx->hostname, "%s", address);
		lws_ctx->ccinfo.context = lws_ctx->context;
		lws_ctx->ccinfo.address = address;
		lws_ctx->ccinfo.port = port;
		lws_ctx->ccinfo.path = "/";
		lws_ctx->ccinfo.host = lws_canonical_hostname( lws_ctx->context );
		lws_ctx->ccinfo.origin = "origin";
		lws_ctx->ccinfo.protocol = filename;

		lws_client_connect_via_info(&lws_ctx->ccinfo);

		if ( lws2_session_count(lws_ctx) >  0 )
		{
			DBG_IF_LN("link - ok !!! (host: %s:%d, filename: %s)", lws_ctx->ccinfo.host, lws_ctx->ccinfo.port, filename);
		}
		else
		{
			DBG_IF_LN("link - fail !!! (host: %s:%d, filename: %s)", lws_ctx->ccinfo.host, lws_ctx->ccinfo.port, filename);
		}
	}
}

#if (0)
void lws2_cli_close(LWSCtx_t *lws_ctx)
{
	if ( (lws_ctx) && (lws_ctx->context) )
	{
		lws_cancel_service(lws_ctx->context );

		DBG_IF_LN("%s (port: %d)", DBG_TXT_BYE_BYE, lws_ctx->ccinfo.port);
		//for libwebsockets-4.2.2
		//clist_free_ex(lws_ctx->session_list, lws2_session_free_cb);
		clist_pop_ex(lws_ctx->session_list, lws2_session_free_cb);

		lws_context_destroy( lws_ctx->context );
		lws_ctx->context = NULL;
		//lws2_mutex_free(lws_ctx);
	}
}
#endif

void lws2_srv_init(LWSCtx_t *lws_ctx, int port, struct lws_protocols *protocols, unsigned int options, uv_loop_t *loop)
{
	if (lws_ctx)
	{
		//SAFE_MEMSET(lws_ctx, 0, sizeof(LWSCtx_t));

		lws_ctx->wsi_id = LWS_WSI_ID_SERVER;

		lws_ctx->cinfo.port = port;
		if (protocols)
		{
			lws_ctx->cinfo.protocols = protocols;
		}
		else
		{
			protocols = protocols_simple;
			lws_ctx->cinfo.protocols = protocols;
		}
		lws_ctx->cinfo.gid = -1;
		lws_ctx->cinfo.uid = -1;
		{
			// to set user as lws_ctx
			int idx = 0;
			while ( protocols[idx].name )
			{
				DBG_IF_LN("(protocols[%d].name: %s)", idx, protocols[idx].name);
				protocols[idx].user = (void *)lws_ctx;
				idx ++;
			}
		}

		lws_ctx->cinfo.vhost_name = "0.0.0.0";

		lws_ctx->cinfo.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

		if (lws_ctx->security)
		{
			if ( ( SAFE_ACCESS(lws_ctx->certificate_file, F_OK) == -1 ) ||
				( SAFE_ACCESS(lws_ctx->privatekey_file, F_OK) == -1 ) )
			{
				DBG_ER_LN("SAFE_ACCESS error !!! (certificate_file: %s, privatekey_file: %s)", lws_ctx->certificate_file, lws_ctx->privatekey_file);
			}
			else
			{
				lws_ctx->cinfo.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
				lws_ctx->cinfo.ssl_cert_filepath = lws_ctx->certificate_file;
				lws_ctx->cinfo.ssl_private_key_filepath = lws_ctx->privatekey_file;
			}
		}

		if (loop)
		{
			lws_ctx->cinfo.options |= options;
			lws_ctx->cinfo.foreign_loops = (void*[]){loop};
			DBG_DB_LN("(loop: %p, options: %ld)", loop, lws_ctx->cinfo.options);
		}

		struct lws_context *context = lws_create_context( &lws_ctx->cinfo );
		if (context)
		{
			lws_ctx->context = context;
		}
		else
		{
			DBG_ER_LN("lws_create_context error !!!");
		}
	}
}

#if (0)
void lws2_srv_open(LWSCtx_t *lws_ctx, int timeout_ms)
{
	if (lws_ctx)
	{
		lws2_mutex_init(lws_ctx);

		CLIST_STRUCT_INIT(lws_ctx, session_list);

		DBG_IF_LN("listen !!! (port: %d, context: %p)", lws_ctx->cinfo.port, lws_ctx->context);
		if ( lws_ctx->cinfo.foreign_loops )
		{
		}
		else
		{
			while (threadx_isquit(tidx_req) == 0)
			{
				lws_service( lws_ctx->context, timeout_ms );
			}
		}
	}
}
#endif

static void *lws2_thread_handler( void *user )
{
	LWSCtx_t *lws_ctx = (LWSCtx_t*)user;

	if (lws_ctx)
	{
		ThreadX_t *tidx_req = &lws_ctx->tidx;
		threadx_detach(tidx_req);

		CLIST_STRUCT_INIT(lws_ctx, session_list);

		if ( lws_ctx->cinfo.foreign_loops )
		{
			DBG_IF_LN("%s (threadx_timewait_simple, port: %d, context: %p)", DBG_TXT_RUN_LOOP, lws_ctx->cinfo.port, lws_ctx->context);
			while (threadx_isquit(tidx_req) == 0)
			{
				threadx_timewait_simple( tidx_req, 1000 );
			}
		}
		else
		{
			DBG_IF_LN("%s (lws_service, port: %d, context: %p)", DBG_TXT_RUN_LOOP, lws_ctx->cinfo.port, lws_ctx->context);
			while (threadx_isquit(tidx_req) == 0)
			{
				lws_service( lws_ctx->context, lws_ctx->timeout_ms );
			}
		}

//exit_lws2:
		lws2_context_close(lws_ctx);

		threadx_leave(tidx_req);
	}
	DBG_IF_LN(DBG_TXT_BYE_BYE);

	return NULL;
}

void lws2_thread_stop(LWSCtx_t *lws_ctx)
{
	if (lws_ctx)
	{
		ThreadX_t *tidx_req = &lws_ctx->tidx;
		threadx_stop(tidx_req);

		lws_cancel_service(lws_ctx->context );
	}
}

void lws2_thread_close(LWSCtx_t *lws_ctx)
{
	if ((lws_ctx) && (lws_ctx->isfree == 0))
	{
		lws_ctx->isfree ++;

		ThreadX_t *tidx_req = &lws_ctx->tidx;
		threadx_close(tidx_req);
	}
}

void lws2_thread_init(LWSCtx_t *lws_ctx)
{
	if (lws_ctx)
	{
		ThreadX_t *tidx_req = &lws_ctx->tidx;
		tidx_req->thread_cb = lws2_thread_handler;
		tidx_req->data = lws_ctx;
		threadx_init(tidx_req, lws_ctx->name);
	}
}

