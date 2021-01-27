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

#define DBG_TMP_Y(format,args...) //DBG_LN_Y(format, ## args)
#define DBG_TMP_DUMP(ibuf,len,delim,format,args...) //DBG_TR_DUMP(ibuf,len,delim,format,## args)

CLIST(WSListHead);

static WSDiscoveryCtx_t *wsd_info = NULL;

clist_t ws_list_head(void)
{
	return WSListHead;
}

static WSList_t *ws_entry_push(clist_t head, int mask, const char *XAddrs, const char *Types, const char *MetadataVersion)
{
	WSList_t *ws_entry = (WSList_t *)SAFE_CALLOC(1, sizeof(WSList_t));

	ws_entry->mask = mask;
	SAFE_SNPRINTF(ws_entry->url, sizeof(ws_entry->url), "%s", XAddrs);

	if (Types)
	{
#if (0)
		char *cTypes = SAFE_STRCHR(Types, ':');
		if (cTypes) cTypes=cTypes+1;
		else cTypes = Types;
#endif

		SAFE_SNPRINTF(ws_entry->types, sizeof(ws_entry->types), "%s", Types);
	}
	if (MetadataVersion)
	{
		SAFE_SNPRINTF(ws_entry->version, sizeof(ws_entry->version), "%s", MetadataVersion);
	}
	
	clist_push(head, ws_entry);

	return ws_entry;
}

static WSList_t *ws_entry_search(clist_t head, const char *XAddrs)
{
	WSList_t *cur;
	
	for (cur = clist_head(head); cur != NULL; cur = clist_item_next(cur))
	{
		if (!SAFE_STRCMP((char *)XAddrs, cur->url)) {
			return cur;
		}
	}
	
	return NULL;
}

static void ws_entry_print_ex(clist_t head)
{
	WSList_t *cur = NULL;
	for (cur = clist_head(head); cur != NULL; cur = clist_item_next(cur))
	{
		DBG_IF_LN("(types: %s, version: %s, url: %s)", cur->types, cur->version, cur->url);
	}
}

static void ws_entry_item_free(void *item)
{
	//WSList_t *cur = (WSList_t *)item;
}

void ws_entry_print(void)
{
	ws_entry_print_ex( ws_list_head() );
}

void ws_entry_init(void)
{
	clist_init( ws_list_head() );
}

void ws_entry_free(void)
{
	clist_free_ex( ws_list_head(), ws_entry_item_free );
}

void ws_devices_refresh(void)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if (wsd_req)
	{
		ws_entry_free();
		ws_entry_init();
		wsdiscovery_sender(wsd_req, SOAP_ACTION_ID_PROBE_DEVICE);
		wsdiscovery_sender(wsd_req, SOAP_ACTION_ID_PROBE_NETWORKVIDEOTRANSMITTER);
	}
}

void ws_device_add(ChainXCtx_t *chainX_req, soap_node_t *node)
{
	const char *Types = NULL;
	soap_node_t *Types_node = soap_element_fetch(node, NULL, "Types", NULL, NULL);
	if (Types_node)
	{
		Types = soap_element_text(Types_node, 0);
	}

	const char *Scopes = NULL;
	soap_node_t *Scopes_node = soap_element_fetch(node, NULL, "Scopes", NULL, NULL);
	if (Scopes_node)
	{
		Scopes = soap_element_text(Scopes_node, 0);
	}

	const char *XAddrs = NULL;
	soap_node_t *XAddrs_node = soap_element_fetch(node, NULL, "XAddrs", NULL, NULL);
	if (XAddrs_node)
	{
		XAddrs = soap_element_text(XAddrs_node, 0);
	}

	const char *MetadataVersion = NULL;
	soap_node_t *MetadataVersion_node = soap_element_fetch(node, NULL, "MetadataVersion", NULL, NULL);
	if (MetadataVersion_node)
	{
		MetadataVersion = soap_element_text(MetadataVersion_node, 0);
	}

	char *XAddrs_new = NULL;
	SAFE_ASPRINTF(XAddrs_new, "%s", XAddrs);
	if (XAddrs_new)
	{
		char *first = NULL;
		char *saveptr = NULL;
		if ( (first = SAFE_STRTOK_R(XAddrs_new, " ", &saveptr)) )
		{
			DBG_TR_LN("(XAddrs: %s)", first);
			WSList_t *ws_entry = ws_entry_search( ws_list_head(), first);
			if (ws_entry)
			{
				// found the same
			}
			else
			{
				int mask = WSDISCOVERY_FILTER_MASK_OTHERS;
				if ( (Scopes) && (SAFE_STRSTR((char*)Scopes, "onvif")) )
				{
					mask = WSDISCOVERY_FILTER_MASK_ONVIF;
				}
				ws_entry_push( ws_list_head(), mask, first, Types, MetadataVersion);
				ws_entry_print();
			}
		}
		else
		{
			DBG_ER_LN("XAddrs is NULL !!!");
		}
		SAFE_FREE(XAddrs_new);
	}
}

void wsdiscovery_probematches_register(wsdiscovery_response_fn cb)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if (wsd_req)
	{
		wsd_req->probematches_cb = cb;
	}
}

void wsdiscovery_probe_register(wsdiscovery_response_fn cb)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if (wsd_req)
	{
		wsd_req->probe_cb = cb;
	}
}

void wsdiscovery_hello_register(wsdiscovery_response_fn cb)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if (wsd_req)
	{
		wsd_req->hello_cb = cb;
	}
}

void wsdiscovery_others_register(wsdiscovery_response_fn cb)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if (wsd_req)
	{
		wsd_req->others_cb = cb;
	}
}

void wsdiscovery_linked_register(chainX_linked_fn cb)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if ( (wsd_req) && (wsd_req->chainX_req) )
	{
		chainX_linked_register(wsd_req->chainX_req, cb);
	}
}

static void wsdiscovery_response(ChainXCtx_t *chainX_req, char *buff, int buff_len)
{
	if ((chainX_req) && (buff) &&(buff_len))
	{
		//DBG_TMP_Y("%s:%d - [%s] \n", inet_ntoa(chainX_req->addr_frm.sin_addr), ntohs(chainX_req->addr_frm.sin_port), buff);
		WSDiscoveryCtx_t *wsd_req = (WSDiscoveryCtx_t *)chainX_req->c_data;
		if (wsd_req)
		{
			soap_node_t *response_node = soap_load_string(buff);
			if ( response_node ) 
			{
				soap_node_t *Hello_node = soap_element_fetch(response_node, NULL, "Hello", NULL, NULL);
				soap_node_t *Probe_node = soap_element_fetch(response_node, NULL, "Probe", NULL, NULL);
				soap_node_t *ProbeMatch_node = soap_element_fetch(response_node, NULL, "ProbeMatch", NULL, NULL);

				if (Hello_node)
				{
					if (wsd_req->hello_cb) wsd_req->hello_cb(chainX_req, Hello_node);
				}
				else if (ProbeMatch_node)
				{
					if (wsd_req->probematches_cb) wsd_req->probematches_cb(chainX_req, ProbeMatch_node);
				}
				else if (Probe_node)
				{
					if (wsd_req->probe_cb) wsd_req->probe_cb(chainX_req, Probe_node);
				}
				else
				{
					if (wsd_req->others_cb) wsd_req->others_cb(chainX_req, response_node);
				}

				soap_element_delete(response_node);
			}
		}
	}
}

static char *wsdiscovery_xml(SOAP_ACTION_ID act_id)
{
	switch (act_id)
	{
		case SOAP_ACTION_ID_PROBE_DEVICE:
			return WSD_XML_PROBE_DEVICE;
			break;
		case SOAP_ACTION_ID_PROBE_NETWORKVIDEOTRANSMITTER:
			return WSD_XML_PROBE_NETWORKVIDEOTRANSMITTER;
			break;

		case SOAP_ACTION_ID_PROBE_NETWORKVIDEODISPLAY:
			return WSD_XML_PROBE_NETWORKVIDEODISPLAY;
			break;

		default:
			return SOAP_XML_NULL;
			break;
	}
}

static void wsdiscovery_uuid_gen(ChainXCtx_t *chainX_req, soap_node_t *request_node)
{
	//ChainXCtx_t *chainX_req = wsd_req->chainX_req;
	//SoapCtx_t *soap = wsd_req->soap;

	if ( (chainX_req) && (request_node) )
	{
		soap_node_t *MessageID_node = soap_element_fetch(request_node, NULL, "MessageID", NULL, NULL);
		if (MessageID_node)
		{
			os_random_uuid(chainX_req->session);
			char *messageid = NULL;
			SAFE_ASPRINTF(messageid, "uuid:%s", chainX_req->session);
			if (messageid)
			{
				DBG_TR_LN("(messageid: %s)", messageid);
				soap_element_text_set(MessageID_node, 0, messageid);
				SAFE_FREE(messageid);
			}
		}
	}
}

void wsdiscovery_sender(WSDiscoveryCtx_t *wsd_req, SOAP_ACTION_ID act_id)
{
	if (wsd_req)
	{
		soap_node_t *request_node = soap_load_string(wsdiscovery_xml(act_id));
		if (request_node)
		{
			wsdiscovery_uuid_gen(wsd_req->chainX_req, request_node);
			
			int buffer_len = 0;
			char *buffer = soap_element_2string(request_node);
			if ( (buffer) && (buffer_len = strlen(buffer)) )
			{
				chainX_multi_sender(wsd_req->chainX_req, buffer, buffer_len);
				SAFE_FREE(buffer);
			}

			soap_element_delete(request_node);
		}
	}
}

void wsdiscovery_probe(chainX_post_fn cb)
{
	if (cb)
	{
		ChainXCtx_t chainXms = {
			.mode = CHAINX_MODE_ID_MULTI_SENDER,
			.sockfd = -1,

			.status = 0,
			.isquit = 0,
			.isfree = 0,

			.security = 0,
			.noblock = 1,

			.select_wait = TIMEOUT_OF_SELECT_1,

			.recycle = 5,
		};

		chainX_ip_set(&chainXms, WS_DISCOVERY_IPV4);
		chainX_port_set(&chainXms, WS_DISCOVERY_PORT);
		chainX_post_register(&chainXms, cb);

		soap_node_t *request_node = soap_load_string(wsdiscovery_xml(SOAP_ACTION_ID_PROBE_DEVICE));
		if (request_node)
		{
			{
				wsdiscovery_uuid_gen(&chainXms, request_node);
			}
			int buffer_len = 0;
			char *buffer = soap_element_2string(request_node);
			if ( (buffer) && (buffer_len = strlen(buffer)) )
			{
				DBG_TMP_Y("%s", buffer);
				chainX_multi_sender_and_post(&chainXms, buffer, buffer_len);
				SAFE_FREE(buffer);
			}
			soap_element_delete(request_node);
		}
	}
}

WSDiscoveryCtx_t *wsdiscovery_get(void)
{
	return wsd_info;
}

static void wsdiscovery_free(WSDiscoveryCtx_t *wsd_req)
{
	if (wsd_req)
	{
		SAFE_FREE(wsd_req->chainX_req);
		SAFE_FREE(wsd_req);
	}
}

void wsdiscovery_stop(void)
{
	WSDiscoveryCtx_t *wsd_req = wsdiscovery_get();
	if (wsd_req)
	{
		chainX_thread_stop(wsd_req->chainX_req);
	}
}

void wsdiscovery_close(void)
{
	WSDiscoveryCtx_t *wsd_req = wsd_info;
	if (wsd_req)
	{
		chainX_thread_close(wsd_req->chainX_req);
		wsdiscovery_free(wsd_req);
		wsd_info = NULL;
	}
}

static WSDiscoveryCtx_t *wsdiscovery_init(void)
{
	WSDiscoveryCtx_t *wsd_req = (WSDiscoveryCtx_t*)SAFE_CALLOC(1, sizeof(WSDiscoveryCtx_t));
	if (wsd_req)
	{
		ChainXCtx_t *chainX_req = (ChainXCtx_t*)SAFE_CALLOC(1, sizeof(ChainXCtx_t));
		if (chainX_req)
		{
			wsd_req->chainX_req = chainX_req;
			
			chainX_req->mode = CHAINX_MODE_ID_MULTI_RECEIVER;
			chainX_req->sockfd = -1;
			chainX_req->c_data = (void*)wsd_req;
			chainX_req->select_wait = TIMEOUT_OF_SELECT_1;
			chainX_req->retry_hold = TIMEOUT_OF_RETRY_HOLD,
			chainX_req->noblock =  1;
			chainX_req->in_detach = 0;
			
			chainX_ip_set(chainX_req, WS_DISCOVERY_IPV4);
			chainX_port_set(chainX_req, WS_DISCOVERY_PORT);
			chainX_post_register(chainX_req, wsdiscovery_response);

			chainX_thread_init(chainX_req);
		}
		else
		{
			SAFE_FREE(wsd_req);
		}
	}
	return wsd_req;
}

WSDiscoveryCtx_t *wsdiscovery_open(void)
{
	if (wsd_info==NULL)
	{
		wsd_info = wsdiscovery_init();
	}
	return wsd_info;
}

