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

static int lws2_simple_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	int ret = -1;

	LWSCtx_t *lws_ctx = lws2_protocol_user(wsi);

	if ((lws_ctx) && (lws_ctx->callback))
	{
		ret = lws_ctx->callback(wsi, reason, user, in, len);
	}

	if ( ret == -1 )
	{
		//DBG_WN_LN("(wsi: %p, user: %p, lws_ctx: %p, reason: %d - %s)", wsi, user, lws_ctx, reason, translate_lws_cb(reason));
		switch( reason )
		{
			case LWS_CALLBACK_HTTP:
#if (0)
				//DBG_WN_LN("(reason: %d-%s)", reason, translate_lws_cb(reason));
				lws_serve_http_file( wsi, "example.html", "text/html", NULL, 0 );
#endif
				break;

			//case LWS_CALLBACK_WSI_CREATE:
			case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED:
			case LWS_CALLBACK_ESTABLISHED:
				{
					lws2_lock(lws_ctx);
					LWSSession_t *session = (LWSSession_t*)user;//SAFE_CALLOC(1, sizeof(LWSSession_t));
					if (session)
					{
						session->wsi = wsi;
						CLIST_STRUCT_INIT(session, msg_list);
						SAFE_MUTEX_ATTR_RECURSIVE(session->in_mtx);

						DBG_IF_LN("LWS_CALLBACK_ESTABLISHED !!! (session: %p)", session);
						//lws_set_wsi_user(wsi, (void *)session);

						clist_push(lws_ctx->session_list, session);
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
					lws2_lock(lws_ctx);
					{
						LWSSession_t *session = (LWSSession_t *)user;
						if (session)
						{
							clist_free(session->msg_list);
							SAFE_MUTEX_DESTROY_EX(session);
							DBG_IF_LN("LWS_CALLBACK_WSI_DESTROY !!! (session: %p)", session);
							clist_remove(lws_ctx->session_list, session);
						}
					}
					lws2_unlock(lws_ctx);
				}
				break;

			default:
				DBG_DB_LN("(wsi: %p, reason: %d - %s)", wsi, reason, translate_lws_cb(reason));
				break;
		}
	}

	return 0;
}

static struct lws_protocols protocols_simple[] =
{
	{
		.name = LWS_SUB_PROTOCOL_HTTP,
		.callback = lws2_simple_cb,
		.per_session_data_size = sizeof(LWSSession_t),
		.rx_buffer_size = LEN_OF_WEBSOCKET,
		//.user = (void *)&lws_req,
	},
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
		case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: // 19
			return "LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED";
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION: // 20
			return "LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION";
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

int lws2_session_lock(LWSSession_t *session)
{
	return SAFE_THREAD_LOCK_EX(session);
}

int lws2_session_unlock(LWSSession_t *session)
{
	return SAFE_THREAD_UNLOCK_EX(session);
}

void lws2_session_write(LWSSession_t *session)
{
	if (session)
	{
		lws2_session_lock(session);

		LWSMsg_t *msg = clist_pop(session->msg_list);
		SAFE_LWS_WRITE(session->wsi, msg->payload, msg->payload_len, LWS_WRITE_TEXT);
		SAFE_FREE(msg);

		if (clist_length(session->msg_list) > 0 )
		{
			lws_callback_on_writable(session->wsi);
		}

		lws2_session_unlock(session);
	}
}

void lws2_session_write_q_push(LWSSession_t *session, char *payload, int payload_len)
{
	if (session)
	{
		lws2_session_lock(session);

		LWSMsg_t *msg = (LWSMsg_t*)SAFE_CALLOC(1, sizeof(LWSMsg_t));
		SAFE_LWS_MEMCPY(msg->payload, payload, payload_len, LEN_OF_WEBSOCKET);
		msg->payload_len = payload_len;
		clist_push(session->msg_list, msg);

		lws_callback_on_writable(session->wsi);

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

int lws2_lock(LWSCtx_t *lws_ctx)
{
	return SAFE_THREAD_LOCK_EX(lws_ctx);
}

int lws2_unlock(LWSCtx_t *lws_ctx)
{
	return SAFE_THREAD_UNLOCK_EX(lws_ctx);
}

static void lws2_mutex_init(LWSCtx_t *lws_ctx)
{
	if (lws_ctx==NULL) return;

	int rc = SAFE_MUTEX_ATTR_RECURSIVE(lws_ctx->in_mtx);
	if (rc == 0)
	{
#ifdef USE_THREAD_CLOCK
		SAFE_COND_ATTR_CLOCK(lws_ctx->in_cond);
#else
		SAFE_COND_ATTR_NORMAL(lws_ctx->in_cond);
#endif
	}
}

static void lws2_mutex_free(LWSCtx_t *lws_ctx)
{
	SAFE_MUTEX_DESTROY_EX(lws_ctx);
	SAFE_COND_DESTROY_EX(lws_ctx);
}

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

		if (loop)
		{
			lws_ctx->cinfo.options = options;
			lws_ctx->cinfo.foreign_loops = (void*[]){loop};
			DBG_DB_LN("(loop: %p, options: %d)", loop, lws_ctx->cinfo.options);
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
		lws2_mutex_init(lws_ctx);

		CLIST_STRUCT_INIT(lws_ctx, session_list);

		SAFE_SPRINTF(lws_ctx->hostname, "%s", address);
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

void lws2_cli_close(LWSCtx_t *lws_ctx)
{
	if (lws_ctx)
	{
		DBG_IF_LN("%s (port: %d)", DBG_TXT_BYE_BYE, lws_ctx->ccinfo.port);
		if (lws_ctx->isquit == 0)
		{
			lws_ctx->isquit = 1;
			if (lws_ctx->context)
			{
				lws_context_destroy( lws_ctx->context );
				lws_ctx->context = NULL;
			}
			//clist_free(lws_ctx->session_list);
			lws2_mutex_free(lws_ctx);
		}
	}
}

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

		if (loop)
		{
			lws_ctx->cinfo.options = options;
			lws_ctx->cinfo.foreign_loops = (void*[]){loop};
			DBG_DB_LN("(loop: %p, options: %d)", loop, lws_ctx->cinfo.options);
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
			while( lws_ctx->isquit == 0 )
			{
				lws_service( lws_ctx->context, timeout_ms );
			}
		}
	}
}

void lws2_srv_close(LWSCtx_t *lws_ctx)
{
	if (lws_ctx)
	{
		DBG_IF_LN("%s (port: %d, context: %p)", DBG_TXT_BYE_BYE, lws_ctx->cinfo.port, lws_ctx->context);
		if (lws_ctx->isquit == 0)
		{
			lws_ctx->isquit = 1;
			if (lws_ctx->context)
			{
				lws_context_destroy( lws_ctx->context );
				lws_ctx->context = NULL;
			}

			//clist_free(lws_ctx->session_list);
			lws2_mutex_free(lws_ctx);
		}
	}
}
