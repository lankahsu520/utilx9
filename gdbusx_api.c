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
#include "gdbusx_ex.h"

void gbusx_signal_int(GbusX_t *gbusx_req, char *signal_name, void *signal_cb)
{
	if (gbusx_req->g_proxy)
	{
		DBG_IF_LN("%s (%s/%s)", DBG_TXT_LINKED, gbusx_req->iface_name, signal_name);
		g_signal_connect(gbusx_req->g_proxy, signal_name, G_CALLBACK(signal_cb), NULL);
	}
}

void gbusx_client_int(GbusX_t *gbusx_req)
{
	GError *g_err = NULL;

	gbusx_req->g_Loop = g_main_loop_new(NULL,FALSE); 
	if (gbusx_req->g_Loop)
	{
		while ( (threadx_isquit(&gbusx_req->tidx)==0) && (gbusx_req->isquit==0) && (gbusx_req->g_connection==NULL) )
		{
			gbusx_req->g_connection = g_bus_get_sync(gbusx_req->g_type, NULL, &g_err);
			if (gbusx_req->g_connection)
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
void gbusx_name_acquired_cb(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	GbusX_t *gbusx_req = (GbusX_t*)user_data;
	DBG_IF_LN("(gbusx_req->name: %s, name: %s)", gbusx_req->name, name);
}

// name_lost_handler
void gbusx_name_lost_cb(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	GbusX_t *gbusx_req = (GbusX_t*)user_data;
	DBG_IF_LN("(gbusx_req->name: %s, name: %s)", gbusx_req->name, name);

	if (connection == NULL)
	{
		DBG_ER_LN("connection is NULL !!! (gbusx_req->name: %s, name: %s)", gbusx_req->name, name);
	}
	SAFE_G_LOOP_QUIT(gbusx_req->g_Loop);
}

void gbusx_server_int(GbusX_t *gbusx_req)
{
	GError *g_err = NULL;

	gbusx_req->g_Loop = g_main_loop_new(NULL,FALSE); 
	if (gbusx_req->g_Loop)
	{
		gbusx_req->g_ownid = g_bus_own_name(GDBUSX_TYPE_SESSION,
																			gbusx_req->iface_name,
																			gbusx_req->owner_flags,
																			gbusx_req->bus_acquired_handler,
																			gbusx_req->name_acquired_handler,
																			gbusx_req->name_lost_handler,
																			gbusx_req,
																			NULL);
	}

	SAFE_G_ERR_FREE(g_err);
}

void *gbusx_dummy_thread_handler(void *user)
{
	GbusX_t *gbusx_req = (GbusX_t *)user;
	ThreadX_t *tidx_req = (ThreadX_t*)&gbusx_req->tidx;

	threadx_detach(tidx_req);

	DBG_WN_LN("%s (thread_name: %s, isservice: %d)", DBG_TXT_RUN_LOOP, tidx_req->name, gbusx_req->isservice);

	if (gbusx_req->isservice)
	{
		gbusx_server_int(gbusx_req);
		
		if ( (threadx_isquit(tidx_req)==0) && (gbusx_req->g_Loop) )
		{
			SAFE_G_LOOP_RUN(gbusx_req->g_Loop);
		}
	}
	else
	{
		gbusx_client_int(gbusx_req);
		if (gbusx_req->proxy_register_cb)
		{
			gbusx_req->proxy_register_cb(gbusx_req);
		}

		if ( (threadx_isquit(tidx_req)==0) && (gbusx_req->g_connection) && (gbusx_req->g_proxy) )
		{
			SAFE_G_LOOP_RUN(gbusx_req->g_Loop);
		}
	}

	threadx_leave(tidx_req);
	DBG_WN_LN("%s (thread_name: %s, isservice: %d)", DBG_TXT_BYE_BYE, tidx_req->name, gbusx_req->isservice);

	return NULL;
}
void gbusx_stop(GbusX_t *gbusx_req)
{
	if ((gbusx_req) && (gbusx_req->g_Loop))
	{
		SAFE_G_LOOP_QUIT(gbusx_req->g_Loop);
	}
	threadx_stop(&gbusx_req->tidx);
	threadx_close(&gbusx_req->tidx);
	
	SAFE_G_UNREF(gbusx_req->g_proxy);
	SAFE_G_UNREF(gbusx_req->g_skeletion);
}

void gbusx_start(GbusX_t *gbusx_req, char *thread_name, thread_fn thread_cb, proxy_register_fn proxy_register_cb, GBusAcquiredCallback bus_acquired_handler, GBusNameAcquiredCallback name_acquired_handler, GBusNameLostCallback name_lost_handler)
{
	gbusx_req->tidx.thread_cb = thread_cb;
	gbusx_req->tidx.data = (void *)gbusx_req;

	gbusx_req->proxy_register_cb = proxy_register_cb;

	gbusx_req->bus_acquired_handler = bus_acquired_handler;
	gbusx_req->name_acquired_handler = name_acquired_handler;
	gbusx_req->name_lost_handler=  name_lost_handler;

	threadx_init(&gbusx_req->tidx, thread_name);
}

