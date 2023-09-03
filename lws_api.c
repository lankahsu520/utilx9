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
struct msg
{
	void *payload; /* is malloc'd */
	size_t len;
};

struct per_session_data__minimal
{
	struct per_session_data__minimal *pss_list;
	struct lws *wsi;
	int last; /* the last message number we sent */
};

struct per_vhost_data__minimal
{
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
			{
				break;
			}

			if (pss->last == vhd->current)
			{
				break;
			}

			/* notice we allowed for LWS_PRE in the payload already */
			m = lws_write(wsi, ((unsigned char *)vhd->amsg.payload) +
						  LWS_PRE, vhd->amsg.len, LWS_WRITE_TEXT);
			if (m < (int)vhd->amsg.len)
			{
				lwsl_err("ERROR %d writing to ws\n", m);
				return -1;
			}

			pss->last = vhd->current;
			break;

		case LWS_CALLBACK_RECEIVE:
			if (vhd->amsg.payload)
			{
				__minimal_destroy_message(&vhd->amsg);
			}

			vhd->amsg.len = len;
			/* notice we over-allocate by LWS_PRE */
			vhd->amsg.payload = malloc(LWS_PRE + len);
			if (!vhd->amsg.payload)
			{
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
								  ppss, vhd->pss_list)
			{
				lws_callback_on_writable((*ppss)->wsi);
			}
			lws_end_foreach_llp(ppss, pss_list);
			break;

		default:
			break;
	}

	return 0;
}
#else
static int lws2_simple_cb(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	int ret = -1;

	LWSX_t *lws_req = lws2_protocol_user(wsi);

	if ((lws_req) && (lws_req->callback))
	{
		ret = lws_req->callback(wsi, reason, user, in, len);
	}

	if (ret != 0)
	{
		//DBG_WN_LN("%d %s !!! (wsi: %p)", reason, translate_lws_cb(reason), wsi);
		switch (reason)
		{
			case LWS_CALLBACK_HTTP:
#if (0)
				//DBG_WN_LN("(reason: %d-%s)", reason, translate_lws_cb(reason));
				lws_serve_http_file(wsi, "example.html", "text/html", NULL, 0);
#endif
				DBG_DB_LN("%d %s !!! (wsi: %p)", reason, translate_lws_cb(reason), wsi);
				break;

			//case LWS_CALLBACK_WSI_CREATE: // 29
			case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: // 19
			case LWS_CALLBACK_ESTABLISHED: // 0
			case LWS_CALLBACK_CLIENT_ESTABLISHED: // 3
			{
				lws2_lock(lws_req);
				LWSSession_t *session = (LWSSession_t*)user;//SAFE_CALLOC(1, sizeof(LWSSession_t));
				if (session)
				{
					if (clist_contains(lws_req->session_list, session)==1)
					{
						DBG_IF_LN("%d %s - dupicate !!! (session: %p)", reason, translate_lws_cb(reason), session);
					}
					else
					{
						if (lws_req->cinfo.foreign_loops)
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

						clist_push(lws_req->session_list, session);
					}
				}
				lws2_unlock(lws_req);
			}
			break;

			case LWS_CALLBACK_RECEIVE: // 6
			{
				lws2_lock(lws_req);
				if (lws_req->wsi_id == LWS_WSI_ID_SERVER)
				{
					if (lws_req->isecho)
					{
						//lws2_session_write_q_push((LWSSession_t *)user, in, len);
						lws2_session_write_q_broadcast(lws_req, in, len);
					}
				}
				lws2_unlock(lws_req);
			}
			break;

			case LWS_CALLBACK_SERVER_WRITEABLE: // 11
			{
				lws2_lock(lws_req);
				if (lws_req->wsi_id == LWS_WSI_ID_SERVER)
				{
					lws2_session_write((LWSSession_t *)user);
				}
				lws2_unlock(lws_req);
			}
			break;

			case LWS_CALLBACK_CLIENT_WRITEABLE: // 10
			{
				lws2_lock(lws_req);
				if (lws_req->wsi_id == LWS_WSI_ID_CLIENT)
				{
					lws2_session_write((LWSSession_t *)user);
				}
				lws2_unlock(lws_req);
			}
			break;

			case LWS_CALLBACK_WSI_DESTROY: // 30
			{
				if ((lws_req->isfree == 0) && (user))
				{
					LWSSession_t *session = (LWSSession_t*)user;
					lws2_session_lock(session);
					lws2_session_pop(lws_req, session);
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
	switch (reason)
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
		case LWS_CALLBACK_RECEIVE_PONG: // 7
			return "LWS_CALLBACK_RECEIVE_PONG";
		case LWS_CALLBACK_CLIENT_RECEIVE: // 8
			return "LWS_CALLBACK_CLIENT_RECEIVE";
		case LWS_CALLBACK_CLIENT_RECEIVE_PONG: // 9
			return "LWS_CALLBACK_CLIENT_RECEIVE_PONG";
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
		case LWS_CALLBACK_CLOSED_CLIENT_HTTP: // 45
			return "LWS_CALLBACK_CLOSED_CLIENT_HTTP";
		case LWS_CALLBACK_RECEIVE_CLIENT_HTTP: // 46
			return "LWS_CALLBACK_RECEIVE_CLIENT_HTTP";
		case LWS_CALLBACK_COMPLETED_CLIENT_HTTP: // 47
			return "LWS_CALLBACK_COMPLETED_CLIENT_HTTP";
		case LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ: // 48
			return "LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ";
		case LWS_CALLBACK_HTTP_BIND_PROTOCOL: // 49
			return "LWS_CALLBACK_HTTP_BIND_PROTOCOL";
		case LWS_CALLBACK_ADD_HEADERS: // 53
			return "LWS_CALLBACK_ADD_HEADERS";
		case LWS_CALLBACK_CLIENT_HTTP_WRITEABLE: // 57
			return "LWS_CALLBACK_CLIENT_HTTP_WRITEABLE";
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

LWSX_t *lws2_protocol_user(struct lws *wsi)
{
	LWSX_t *lws_req = NULL;
	const struct lws_protocols *protocol = lws_get_protocol(wsi);
	//struct lws_context *context = lws_get_context( wsi );
	//LWSX_t *lws_req = (LWSX_t *)protocol->user;

	if (protocol)
	{
		lws_req = (LWSX_t *)protocol->user;
	}

	return lws_req;
}

void lws2_session_lock(LWSSession_t *session)
{
	LWSX_t *lws_req = lws2_protocol_user(session->wsi);

	if (lws_req->isfree == 0)
	{
		lws2_lock(lws_req);
	}
}

void lws2_session_unlock(LWSSession_t *session)
{
	LWSX_t *lws_req = lws2_protocol_user(session->wsi);
	if (lws_req->isfree == 0)
	{
		lws2_unlock(lws_req);
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

void lws2_session_pop(LWSX_t *lws_req, LWSSession_t *session)
{
	if (session)
	{
		clist_free_ex(session->msg_list, lws2_session_msg_free_cb);
		//SAFE_MUTEX_DESTROY_EX(session);
		DBG_IF_LN("(session: %p)", session);
		if (lws_req)
		{
			clist_remove(lws_req->session_list, session);
		}
	}
}

void lws2_session_write(LWSSession_t *session)
{
	if (session)
	{
		lws2_session_lock(session);

		LWSMsg_t *msg = clist_pop(session->msg_list);
		if ((msg) && (msg->payload))
		{
			SAFE_LWS_WRITE(session->wsi, msg->payload, msg->payload_len, LWS_WRITE_TEXT);
			SAFE_FREE(msg->payload);

			if (clist_length(session->msg_list) > 0)
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

void lws2_session_write_q_broadcast(LWSX_t *lws_req, char *payload, int payload_len)
{
	if (lws_req)
	{
		LWSSession_t *cur = NULL;

		for (cur = clist_head(lws_req->session_list); cur != NULL; cur = clist_item_next(cur))
		{
			lws2_session_write_q_push(cur, payload, payload_len);
		}
	}
}

int lws2_session_count(LWSX_t *lws_req)
{
	int ret = 0;

	if (lws_req)
	{
		ret = clist_length(lws_req->session_list);
	}

	return ret;
}

static void lws2_context_close(LWSX_t *lws_req)
{
	if ((lws_req) && (lws_req->context))
	{
		DBG_IF_LN("%s (port: %d, context: %p)", DBG_TXT_BYE_BYE, lws_req->cinfo.port, lws_req->context);
		if (lws_req->context)
		{
			//for libwebsockets-4.2.2
			//clist_free_ex(lws_req->session_list, lws2_session_free_cb);
			clist_pop_ex(lws_req->session_list, lws2_session_free_cb);

			lws_context_destroy(lws_req->context);
			lws_req->context = NULL;
		}
	}
}

void lws2_lock(LWSX_t *lws_req)
{
	if (lws_req)
	{
		ThreadX_t *tidx_req = &lws_req->tidx;
		threadx_lock(tidx_req);
	}
}

void lws2_unlock(LWSX_t *lws_req)
{
	if (lws_req)
	{
		ThreadX_t *tidx_req = &lws_req->tidx;
		threadx_unlock(tidx_req);
	}
}

#if (0)
static void lws2_mutex_init(LWSX_t *lws_req)
{
	ThreadX_t *tidx_req = &lws_req->tidx;
	threadx_mutex_init(tidx_req);
}

static void lws2_mutex_free(LWSX_t *lws_req)
{
	ThreadX_t *tidx_req = &lws_req->tidx;
	threadx_mutex_free(tidx_req);
}
#endif

void lws2_cli_init(LWSX_t *lws_req, struct lws_protocols *protocols, unsigned int options, uv_loop_t *loop)
{
	if (lws_req)
	{
		//SAFE_MEMSET(lws_req, 0, sizeof(LWSX_t));

		lws_req->wsi_id = LWS_WSI_ID_CLIENT;

		lws_req->cinfo.port = CONTEXT_PORT_NO_LISTEN;
		if (protocols)
		{
			lws_req->cinfo.protocols = protocols;
		}
		else
		{
			protocols = protocols_simple;
			lws_req->cinfo.protocols = protocols;
		}
		lws_req->cinfo.gid = -1;
		lws_req->cinfo.uid = -1;
		{
			// to set user as lws_req
			int idx = 0;
			while (protocols[idx].name)
			{
				DBG_IF_LN("(protocols[%d].name: %s)", idx, protocols[idx].name);
				protocols[idx].user = (void *)lws_req;
				idx ++;
			}
		}

		lws_req->cinfo.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

		if (lws_req->security)
		{
			if ((SAFE_ACCESS(lws_req->certificate_file, F_OK) == -1) ||
					(SAFE_ACCESS(lws_req->privatekey_file, F_OK) == -1))
			{
				DBG_ER_LN("SAFE_ACCESS error !!! (certificate_file: %s, privatekey_file: %s)", lws_req->certificate_file, lws_req->privatekey_file);
			}
			else
			{
				lws_req->cinfo.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
				lws_req->cinfo.ssl_cert_filepath = lws_req->certificate_file;
				lws_req->cinfo.ssl_private_key_filepath = lws_req->privatekey_file;
			}
		}

		if (loop)
		{
			lws_req->cinfo.options |= options;
			lws_req->cinfo.foreign_loops = (void*[])
			{
				loop
			};
			DBG_DB_LN("(loop: %p, options: %" PRIu64 ")", loop, (uint64_t)lws_req->cinfo.options);
		}

		struct lws_context *context = lws_create_context(&lws_req->cinfo);
		if (context)
		{
			lws_req->context = context;
		}
		else
		{
			DBG_ER_LN("lws_create_context error !!!");
		}
	}
}

void lws2_cli_open(LWSX_t *lws_req, char *address, int port, char *filename)
{
	if ((lws_req) && (lws_req->context))
	{
		CLIST_STRUCT_INIT(lws_req, session_list);

		SAFE_SPRINTF_EX(lws_req->hostname, "%s", address);
		lws_req->ccinfo.context = lws_req->context;
		lws_req->ccinfo.address = address;
		lws_req->ccinfo.port = port;
		lws_req->ccinfo.path = "/";
		lws_req->ccinfo.host = lws_canonical_hostname(lws_req->context);
		lws_req->ccinfo.origin = "origin";
		lws_req->ccinfo.protocol = filename;

		lws_client_connect_via_info(&lws_req->ccinfo);

		if (lws2_session_count(lws_req) >  0)
		{
			DBG_IF_LN("link - ok !!! (host: %s:%d, filename: %s)", lws_req->ccinfo.host, lws_req->ccinfo.port, filename);
		}
		else
		{
			DBG_IF_LN("link - fail !!! (host: %s:%d, filename: %s)", lws_req->ccinfo.host, lws_req->ccinfo.port, filename);
		}
	}
}

#if (0)
void lws2_cli_close(LWSX_t *lws_req)
{
	if ((lws_req) && (lws_req->context))
	{
		lws_cancel_service(lws_req->context);

		DBG_IF_LN("%s (port: %d)", DBG_TXT_BYE_BYE, lws_req->ccinfo.port);
		//for libwebsockets-4.2.2
		//clist_free_ex(lws_req->session_list, lws2_session_free_cb);
		clist_pop_ex(lws_req->session_list, lws2_session_free_cb);

		lws_context_destroy(lws_req->context);
		lws_req->context = NULL;
		//lws2_mutex_free(lws_req);
	}
}
#endif

void lws2_srv_init(LWSX_t *lws_req, int port, struct lws_protocols *protocols, unsigned int options, uv_loop_t *loop)
{
	if (lws_req)
	{
		//SAFE_MEMSET(lws_req, 0, sizeof(LWSX_t));

		lws_req->wsi_id = LWS_WSI_ID_SERVER;

		lws_req->cinfo.port = port;
		if (protocols)
		{
			lws_req->cinfo.protocols = protocols;
		}
		else
		{
			protocols = protocols_simple;
			lws_req->cinfo.protocols = protocols;
		}
		lws_req->cinfo.gid = -1;
		lws_req->cinfo.uid = -1;
		{
			// to set user as lws_req
			int idx = 0;
			while (protocols[idx].name)
			{
				DBG_IF_LN("(protocols[%d].name: %s)", idx, protocols[idx].name);
				protocols[idx].user = (void *)lws_req;
				idx ++;
			}
		}

		lws_req->cinfo.vhost_name = "0.0.0.0";

		lws_req->cinfo.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

		if (lws_req->security)
		{
			if ((SAFE_ACCESS(lws_req->certificate_file, F_OK) == -1) ||
					(SAFE_ACCESS(lws_req->privatekey_file, F_OK) == -1))
			{
				DBG_ER_LN("SAFE_ACCESS error !!! (certificate_file: %s, privatekey_file: %s)", lws_req->certificate_file, lws_req->privatekey_file);
			}
			else
			{
				lws_req->cinfo.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
				lws_req->cinfo.ssl_cert_filepath = lws_req->certificate_file;
				lws_req->cinfo.ssl_private_key_filepath = lws_req->privatekey_file;
			}
		}

		if (loop)
		{
			lws_req->cinfo.options |= options;
			lws_req->cinfo.foreign_loops = (void*[])
			{
				loop
			};
			DBG_DB_LN("(loop: %p, options: %" PRIu64 ")", loop, (uint64_t)lws_req->cinfo.options);
		}

		struct lws_context *context = lws_create_context(&lws_req->cinfo);
		if (context)
		{
			lws_req->context = context;
		}
		else
		{
			DBG_ER_LN("lws_create_context error !!!");
		}
	}
}

#if (0)
void lws2_srv_open(LWSX_t *lws_req, int timeout_ms)
{
	if (lws_req)
	{
		lws2_mutex_init(lws_req);

		CLIST_STRUCT_INIT(lws_req, session_list);

		DBG_IF_LN("listen !!! (port: %d, context: %p)", lws_req->cinfo.port, lws_req->context);
		if (lws_req->cinfo.foreign_loops)
		{
		}
		else
		{
			while (threadx_isquit(tidx_req) == 0)
			{
				lws_service(lws_req->context, timeout_ms);
			}
		}
	}
}
#endif

static void *lws2_thread_handler(void *user)
{
	LWSX_t *lws_req = (LWSX_t*)user;

	if (lws_req)
	{
		ThreadX_t *tidx_req = &lws_req->tidx;
		threadx_detach(tidx_req);

		CLIST_STRUCT_INIT(lws_req, session_list);

		if (lws_req->cinfo.foreign_loops)
		{
			DBG_IF_LN("%s (threadx_timewait_simple, port: %d, context: %p)", DBG_TXT_RUN_LOOP, lws_req->cinfo.port, lws_req->context);
			while (threadx_isquit(tidx_req) == 0)
			{
				threadx_timewait_simple(tidx_req, 1000);
			}
		}
		else
		{
			DBG_IF_LN("%s (lws_service, port: %d, context: %p)", DBG_TXT_RUN_LOOP, lws_req->cinfo.port, lws_req->context);
			while (threadx_isquit(tidx_req) == 0)
			{
				lws_service(lws_req->context, lws_req->timeout_ms);
			}
		}

//exit_lws2:
		lws2_context_close(lws_req);

		threadx_leave(tidx_req);
	}
	DBG_IF_LN(DBG_TXT_BYE_BYE);

	return NULL;
}

void lws2_thread_stop(LWSX_t *lws_req)
{
	if (lws_req)
	{
		ThreadX_t *tidx_req = &lws_req->tidx;
		threadx_stop(tidx_req);

		if (lws_req->context)
		{
			lws_cancel_service(lws_req->context);
		}
	}
}

void lws2_thread_close(LWSX_t *lws_req)
{
	if ((lws_req) && (lws_req->isfree == 0))
	{
		lws_req->isfree ++;

		ThreadX_t *tidx_req = &lws_req->tidx;
		threadx_close(tidx_req);
	}
}

void lws2_thread_init(LWSX_t *lws_req)
{
	if (lws_req)
	{
		ThreadX_t *tidx_req = &lws_req->tidx;
		tidx_req->thread_cb = lws2_thread_handler;
		tidx_req->data = lws_req;
		threadx_init(tidx_req, lws_req->name);
	}
}

