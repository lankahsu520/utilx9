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

static int is_quit = 0;

static void wsd_ProbeMatches_cb(ChainX_t *chainX_req, soap_node_t *ProbeMatch_node)
{
	if (chainX_req)
	{
		DBG_IF_LN("[%s:%d]", inet_ntoa(chainX_req->addr_frm.sin_addr), ntohs(chainX_req->addr_frm.sin_port));
	}

	if (ProbeMatch_node)
	{
		soap_node_t *Address_node = soap_element_fetch(ProbeMatch_node, NULL, "Address", NULL, NULL);
		if (Address_node)
		{
			DBG_IF_LN("(Address: %s)", soap_element_text(Address_node, 0));
		}

		soap_node_t *Types_node = soap_element_fetch(ProbeMatch_node, NULL, "Types", NULL, NULL);
		if (Types_node)
		{
			DBG_IF_LN("(Types: %s)", soap_element_text(Types_node, 0));
		}

		soap_node_t *Scopes_node = soap_element_fetch(ProbeMatch_node, NULL, "Scopes", NULL, NULL);
		if (Scopes_node)
		{
			DBG_IF_LN("(Scopes: %s)", soap_element_text(Scopes_node, 0));
		}
		
		soap_node_t *XAddrs_node = soap_element_fetch(ProbeMatch_node, NULL, "XAddrs", NULL, NULL);
		if (XAddrs_node)
		{
			DBG_IF_LN("(XAddrs: %s)", soap_element_text(XAddrs_node, 0));
		}
		printf("\n");

		ws_device_add(chainX_req, ProbeMatch_node);
	}
}

static void wsd_Probe_cb(ChainX_t *chainX_req, soap_node_t *parent_node)
{
	if (chainX_req)
	{
		DBG_IF_LN("[%s:%d]", inet_ntoa(chainX_req->addr_frm.sin_addr), ntohs(chainX_req->addr_frm.sin_port));
	}

	DBG_IF_LN("%s\n", DBG_TXT_NON_IMPLEMENT);
}

static void wsd_Hello_cb(ChainX_t *chainX_req, soap_node_t *Hello_node)
{
	if (chainX_req)
	{
		DBG_IF_LN("[%s:%d]", inet_ntoa(chainX_req->addr_frm.sin_addr), ntohs(chainX_req->addr_frm.sin_port));
	}

	if (Hello_node)
	{
		soap_node_t *Types_node = soap_element_fetch(Hello_node, NULL, "Types", NULL, NULL);
		if (Types_node)
		{
			DBG_IF_LN("(Types: %s)", soap_element_text(Types_node, 0));
		}

		soap_node_t *Scopes_node = soap_element_fetch(Hello_node, NULL, "Scopes", NULL, NULL);
		if (Scopes_node)
		{
			DBG_IF_LN("(Scopes: %s)", soap_element_text(Scopes_node, 0));
		}

		soap_node_t *XAddrs_node = soap_element_fetch(Hello_node, NULL, "XAddrs", NULL, NULL);
		if (XAddrs_node)
		{
			DBG_IF_LN("(XAddrs: %s)", soap_element_text(XAddrs_node, 0));
		}

		soap_node_t *MetadataVersion_node = soap_element_fetch(Hello_node, NULL, "MetadataVersion", NULL, NULL);
		if (MetadataVersion_node)
		{
			DBG_IF_LN("(MetadataVersion: %s)", soap_element_text(MetadataVersion_node, 0));
		}
		printf("\n");
	}
}

static void wsd_Others_cb(ChainX_t *chainX_req, soap_node_t *parent_node)
{
	if (chainX_req)
	{
		DBG_IF_LN("[%s:%d]", inet_ntoa(chainX_req->addr_frm.sin_addr), ntohs(chainX_req->addr_frm.sin_port));
	}

	char *buffer = soap_element_2string(parent_node);
	if (buffer)
	{
		DBG_TR_LN("(%s)\n", buffer);
		SAFE_FREE(buffer);
	}
}

void chainX_linked_cb(ChainX_t *chainX_req)
{
	if (chainX_linked_check(chainX_req)==0)
	{
		WSDiscoveryX_t *wsd_req = (WSDiscoveryX_t *)chainX_req->c_data;
		// send 1st
		wsdiscovery_sender(wsd_req, SOAP_ACTION_ID_PROBE_DEVICE);
	}
	else
	{
	}
}

void chainX_post_cb(ChainX_t *chainX_req, char *buff, int buff_len)
{
	DBG_IF_LN("%s", buff);
}

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static int app_quit(void)
{
	return is_quit;
}

static void app_stop(void)
{
	if (app_quit()==0)
	{	
		app_set_quit(1);
		//app_wakeup();

		if (wsdiscovery_get())
		{
			wsdiscovery_stop();
			wsdiscovery_close();
		}
		ws_entry_free();

		DBG_TR_LN("exit");
	}
}

static void app_exit(void)
{
	app_stop();
	DBG_TR_LN("exit");
}

static void app_signal_handler(int signum)
{
	//ICLOUD_DEBUGLN(DBG_LVL_ERROR, "(signum: %d)", signum);
	switch (signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
			break;
	}
}

static void app_signal_register(void)
{
	signal(SIGINT, app_signal_handler );
	signal(SIGTERM, app_signal_handler );
	signal(SIGHUP, app_signal_handler );
	signal(SIGUSR1, app_signal_handler );
	signal(SIGUSR2, app_signal_handler );
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	dbg_lvl_set(DBG_LVL_TRACE);
	app_signal_register();
	atexit(app_exit);

#if (1)
	ws_entry_init();

	if ( wsdiscovery_open() )
	{
		wsdiscovery_probematches_register(wsd_ProbeMatches_cb);
		wsdiscovery_probe_register(wsd_Probe_cb);
		wsdiscovery_hello_register(wsd_Hello_cb);
		wsdiscovery_others_register(wsd_Others_cb);
		
		wsdiscovery_linked_register(chainX_linked_cb);
		sleep(2);
	}

	while (app_quit() == 0)
	{
#if (0)
		if ( (wsd_info) && (wsd_info->chainX_req) )
		{
			wsdiscovery_sender(wsd_info, SOAP_ACTION_ID_PROBE_DEVICE);
			wsdiscovery_sender(wsd_info, SOAP_ACTION_ID_PROBE_NETWORKVIDEOTRANSMITTER);
		}
#endif
		sleep(2);
	}

	app_stop();
#else
	wsdiscovery_probe(chainX_post_cb);
#endif
	exit(0);
}
