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

void xbus_signal_int(Xbus_t *xbus_req, char *signal_name, void *signal_cb)
{
	if (xbus_req->g_proxy)
	{
		DBG_IF_LN("%s (%s/%s)", DBG_TXT_LINKED, xbus_req->iface_name, signal_name);
		g_signal_connect(xbus_req->g_proxy, signal_name, G_CALLBACK(signal_cb), NULL);
	}
}

void xbus_client_int(Xbus_t *xbus_req)
{
	GError *g_err = NULL;

	xbus_req->g_Loop = g_main_loop_new(NULL,FALSE); 
	if (xbus_req->g_Loop)
	{
		while ( (threadx_isquit(&xbus_req->tidx)==0) && (xbus_req->isquit==0) && (xbus_req->g_connection==NULL) )
		{
			xbus_req->g_connection = g_bus_get_sync(xbus_req->g_type, NULL, &g_err);
			if (xbus_req->g_connection)
			{
				break;
			}
			else
			{
				DBG_ER_LN("g_bus_get_sync - error !!! (message: %s)", g_err->message);
			}

			SAFE_G_ERR_FREE(g_err);
			sleep(1);
		}
	}

	SAFE_G_ERR_FREE(g_err);
}

// name_acquired_handler
void xbus_name_acquired_cb(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	Xbus_t *xbus_req = (Xbus_t*)user_data;
	DBG_IF_LN("(xbus_req->name: %s, name: %s)", xbus_req->name, name);
}

// name_lost_handler
void xbus_name_lost_cb(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	Xbus_t *xbus_req = (Xbus_t*)user_data;
	DBG_IF_LN("(xbus_req->name: %s, name: %s)", xbus_req->name, name);

	if (connection == NULL)
	{
		DBG_ER_LN("connection is NULL !!! (xbus_req->name: %s, name: %s)", xbus_req->name, name);
	}
	SAFE_G_LOOP_QUIT(xbus_req->g_Loop);
}

void xbus_server_int(Xbus_t *xbus_req)
{
	GError *g_err = NULL;

	xbus_req->g_Loop = g_main_loop_new(NULL,FALSE); 
	if (xbus_req->g_Loop)
	{
		xbus_req->g_ownid = g_bus_own_name(XBUS_TYPE_SESSION,
																			xbus_req->iface_name,
																			xbus_req->owner_flags,
																			xbus_req->bus_acquired_handler,
																			xbus_req->name_acquired_handler,
																			xbus_req->name_lost_handler,
																			xbus_req,
																			NULL);
	}

	SAFE_G_ERR_FREE(g_err);
}

void *xbus_dummy_thread_handler(void *user)
{
	Xbus_t *xbus_req = (Xbus_t *)user;
	ThreadX_t *tidx_req = (ThreadX_t*)&xbus_req->tidx;

	threadx_detach(tidx_req);

	DBG_WN_LN("%s (thread_name: %s, isservice: %d)", DBG_TXT_RUN_LOOP, tidx_req->name, xbus_req->isservice);

	if (xbus_req->isservice)
	{
		xbus_server_int(xbus_req);
		
		if ( (threadx_isquit(tidx_req)==0) && (xbus_req->g_Loop) )
		{
			SAFE_G_LOOP_RUN(xbus_req->g_Loop);
		}
	}
	else
	{
		xbus_client_int(xbus_req);
		if (xbus_req->proxy_register_cb)
		{
			xbus_req->proxy_register_cb(xbus_req);
		}

		if ( (threadx_isquit(tidx_req)==0) && (xbus_req->g_connection) && (xbus_req->g_proxy) )
		{
			SAFE_G_LOOP_RUN(xbus_req->g_Loop);
		}
	}

	threadx_leave(tidx_req);
	DBG_WN_LN("%s (thread_name: %s, isservice: %d)", DBG_TXT_BYE_BYE, tidx_req->name, xbus_req->isservice);

	return NULL;
}
void xbus_stop(Xbus_t *xbus_req)
{
	if ((xbus_req) && (xbus_req->g_Loop))
	{
		SAFE_G_LOOP_QUIT(xbus_req->g_Loop);
	}
	threadx_stop(&xbus_req->tidx);
	threadx_close(&xbus_req->tidx);
	
	SAFE_G_UNREF(xbus_req->g_proxy);
	SAFE_G_UNREF(xbus_req->g_skeletion);
}

void xbus_start(Xbus_t *xbus_req, char *thread_name, thread_fn thread_cb, proxy_register_fn proxy_register_cb, GBusAcquiredCallback bus_acquired_handler, GBusNameAcquiredCallback name_acquired_handler, GBusNameLostCallback name_lost_handler)
{
	xbus_req->tidx.thread_cb = thread_cb;
	xbus_req->tidx.data = (void *)xbus_req;

	xbus_req->proxy_register_cb = proxy_register_cb;

	xbus_req->bus_acquired_handler = bus_acquired_handler;
	xbus_req->name_acquired_handler = name_acquired_handler;
	xbus_req->name_lost_handler=  name_lost_handler;

	threadx_init(&xbus_req->tidx, thread_name);
}

