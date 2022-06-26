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
#ifndef __gbusx_EX_H__
#define __gbusx_EX_H__

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
//** include **
//******************************************************************************
#include <glib/gprintf.h>
#include <gio/gio.h>

//******************************************************************************
//** UTIL_EX_XXX **
//******************************************************************************
//GDBUS
#define UTIL_EX_XBUS

//******************************************************************************
//** UTIL_EX_XBUS **
//******************************************************************************
#ifdef UTIL_EX_XBUS
// https://developer.gimp.org/api/2.0/glib/glib-String-Utility-Functions.html
#define SAFE_G_SPRINTF(X, FMT, args...) \
	({ int __ret =0; do { if (pcheck(X)) __ret = g_sprintf(X, FMT, ## args); else DBG_ER_LN("%s is NULL !!!", #X); } while(0); __ret; })
#define SAFE_G_STRDUP(FMT, args...) \
	({ gchar *__ret = NULL; \
		do { \
			__ret = g_strdup_printf(FMT, ## args); \
		} while(0); \
		__ret; \
	})
#define SAFE_G_FREE(X) \
	do { if ( (X) != NULL ) {g_free(X); X=NULL;} } while(0)
#define SAFE_G_UNREF(X) \
	do { if ( (X) != NULL ) {g_object_unref(X); X=NULL;} } while(0)
#define SAFE_G_ERR_FREE(X) \
	do { if ( (X) != NULL ) {g_error_free(X); X=NULL;} } while(0)

#define SAFE_G_LOOP_RUN(loop) \
	do { \
		if (pcheck(loop)) \
		{ \
			g_main_loop_run(loop); \
		} \
	} while(0)
#define SAFE_G_LOOP_QUIT(loop) \
	do { \
		if (pcheck(loop)) \
		{ \
			g_main_loop_quit(loop); \
			loop=NULL; \
		} \
	} while(0)

#define GDBUSX_CONCAT1_EX(s1) s1
#define GDBUSX_CONCAT1_HELPER(s1) GDBUSX_CONCAT1_EX(s1)

#define GDBUSX_CONCAT2_EX(s1, s2) s1##s2
#define GDBUSX_CONCAT2_HELPER(s1, s2) GDBUSX_CONCAT2_EX(s1, s2)

#define GDBUSX_CONCAT3_EX(s1, s2, s3) s1##s2##s3
#define GDBUSX_CONCAT3_HELPER(s1, s2, s3) GDBUSX_CONCAT3_EX(s1, s2, s3)

#define GDBUSX_CONCAT4_EX(s1, s2, s3, s4) s1##s2##s3##s4
#define GDBUSX_CONCAT4_HELPER(s1, s2, s3, s4) GDBUSX_CONCAT4_EX(s1, s2, s3, s4)

#define GDBUSX_SIGNAL_EMIT(name, match) GDBUSX_CONCAT3_HELPER(name, _emit, match)

#define GDBUSX_METHOD_ASYNC(name, method) GDBUSX_CONCAT3_HELPER(name, _call, method)
#define GDBUSX_METHOD_FINISH(name, method) GDBUSX_CONCAT4_HELPER(name, _call, method, _finish)
#define GDBUSX_METHOD_SYNC(name, method) GDBUSX_CONCAT4_HELPER(name, _call, method, _sync)
#define GDBUSX_METHOD_COMPLETE(name, method) GDBUSX_CONCAT3_HELPER(name, _complete, method)

#define GDBUSX_PROXY_NEW(name) GDBUSX_CONCAT2_HELPER(name, _proxy_new)
#define GDBUSX_PROXY_NEW_FINISH(name) GDBUSX_CONCAT2_HELPER(name, _proxy_new_finish)
#define GDBUSX_PROXY_NEW_SYNC(name) GDBUSX_CONCAT2_HELPER(name, _proxy_new_sync)
#define GDBUSX_PROXY_NEW_FOR_BUS(name) GDBUSX_CONCAT2_HELPER(name, _proxy_new_for_bus)
#define GDBUSX_PROXY_NEW_FOR_BUS_FINISH(name) GDBUSX_CONCAT2_HELPER(name, _proxy_new_for_bus_finish)
#define GDBUSX_PROXY_NEW_FOR_BUS_SYNC(name) GDBUSX_CONCAT2_HELPER(name, _proxy_new_for_bus_sync)

#define GDBUSX_SKELETON_NEW(name) GDBUSX_CONCAT2_HELPER(name, _skeleton_new)

#define GDBUSX_IFAC_FUNC_CONCAT(s1,s2) GDBUSX_CONCAT2_HELPER(s1, s2)

#if (0)
// please check your NAME
#define GDBUSX_IFAC_FUNC_PREFIXNAME com_github_lankahsu520
#define gbusx_IFAC_FUN_DEMO GDBUSX_IFAC_FUNC_CONCAT(GDBUSX_IFAC_FUNC_PREFIXNAME, _demo)

#define gbusx_METHOD_ASYNC_demo GDBUSX_METHOD_ASYNC(gbusx_IFAC_FUN_DEMO, _set_name)
#define gbusx_METHOD_FINISH_demo GDBUSX_METHOD_FINISH(gbusx_IFAC_FUN_DEMO, _set_name)
#define gbusx_METHOD_SYNC_demo GDBUSX_METHOD_SYNC(gbusx_IFAC_FUN_DEMO, _set_name)
#define gbusx_METHOD_demo gbusx_METHOD(gbusx_IFAC_FUN_DEMO, _set_name)

#define gbusx_PROXY_NEW_demo GDBUSX_PROXY_NEW(gbusx_IFAC_NAME_DEMO)
#define gbusx_PROXY_NEW_FINISH_demo GDBUSX_PROXY_NEW_FINISH(gbusx_IFAC_NAME_DEMO)
#define gbusx_PROXY_NEW_SYNC_demo GDBUSX_PROXY_NEW_SYNC(gbusx_IFAC_NAME_DEMO)
#define gbusx_PROXY_NEW_FOR_BUS_demo GDBUSX_PROXY_NEW_FOR_BUS(gbusx_IFAC_NAME_DEMO)
#define gbusx_PROXY_NEW_FOR_BUS_FINISH_demo GDBUSX_PROXY_NEW_FOR_BUS_FINISH(gbusx_IFAC_NAME_DEMO)
#define gbusx_PROXY_NEW_FOR_BUS_SYNC_demo GDBUSX_PROXY_NEW_FOR_BUS_SYNC(gbusx_IFAC_NAME_DEMO)
#define gbusx_SKELETON_NEW_demo GDBUSX_SKELETON_NEW(gbusx_IFAC_NAME_DEMO)
#endif

#define GDBUSX_TYPE_SESSION G_BUS_TYPE_SESSION
#define GDBUSX_PROXY_FLAGS G_DBUS_PROXY_FLAGS_NONE
#define GDBUSX_OWNER_FLAGS G_BUS_NAME_OWNER_FLAGS_NONE
#define GDBUSX_OBJECT GObject

typedef void *(*proxy_register_fn) (void *);

typedef struct GbusX_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isquit;
	int isfree;
	int isinit;

	int isservice;

	GMainLoop *g_Loop;
	GDBusConnection *g_connection;
	guint g_type;

	char *iface_name;
	char *path_name;

	guint proxy_flags;
	GObject *g_proxy;
	proxy_register_fn proxy_register_cb;

	guint g_ownid;
	guint owner_flags;
	GObject *g_skeletion;
	GBusAcquiredCallback bus_acquired_handler;
	GBusNameAcquiredCallback name_acquired_handler;
	GBusNameLostCallback name_lost_handler;

	void *data;
} GbusX_t;

void gbusx_signal_int(GbusX_t *gbusx_req, char *signal_name, void *signal_cb);
void gbusx_client_int(GbusX_t *gbusx_req);

void gbusx_name_acquired_cb(GDBusConnection *connection, const gchar *name, gpointer user_data);
void gbusx_name_lost_cb(GDBusConnection *connection, const gchar *name, gpointer user_data);
void gbusx_server_int(GbusX_t *gbusx_req);

void *gbusx_dummy_thread_handler(void *user);

void gbusx_stop(GbusX_t *gbusx_req);
void gbusx_start(GbusX_t *gbusx_req, char *thread_name, thread_fn thread_cb, proxy_register_fn proxy_register_cb, GBusAcquiredCallback bus_acquired_handler, GBusNameAcquiredCallback name_acquired_handler, GBusNameLostCallback name_lost_handler);

#endif

//******************************************************************************
//** END **
//******************************************************************************

#ifdef __cplusplus
}
#endif

#endif
