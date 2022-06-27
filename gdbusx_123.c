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
#include <signal.h>
#include <getopt.h>

#include "utilx9.h"
#include "gdbusx_ex.h"
#include "gdbusx_ifac.h"

#define TAG "gbusx_123"

// ** app **
static int is_quit = 0;
static int is_service = 0;

#define GDBUSX_IFAC_FUNC_PREFIXNAME com_github_lankahsu520

// com.github.lankahsu520.agent **
#define GDBUSX_IFAC_NAME_AGENT "com.github.lankahsu520.agent"
#define GDBUSX_PATH_NAME_AGENT "/com/github/lankahsu520/agent"

#define GDBUSX_IFAC_FUNC_AGENT GDBUSX_IFAC_FUNC_CONCAT(GDBUSX_IFAC_FUNC_PREFIXNAME, _agent)
#define GDBUSX_OBJECT_AGENT ComGithubLankahsu520Agent

static GbusX_t gbusx_agent = {
	.name = "gbusx_agent",

	.isfree = 0,
	.isinit = 0,

	.isservice = 0,

	.g_Loop = NULL,
	.g_connection = NULL,
	.g_type = GDBUSX_TYPE_SESSION,

	.iface_name = GDBUSX_IFAC_NAME_AGENT,
	.path_name = GDBUSX_PATH_NAME_AGENT,

	.proxy_flags = GDBUSX_PROXY_FLAGS,
	.g_proxy = NULL,

	.g_ownid = 0,
	.owner_flags = GDBUSX_OWNER_FLAGS,
	.g_skeletion = NULL,
};

// com_github_lankahsu520_agent_call_set_name_sync
static void gbusx_method_Agent_SetName(GbusX_t *gbusx_req, const gchar *arg_name)
{
	gchar *out_response = NULL;
	GError *g_err = NULL;

	if ((gbusx_req) && (gbusx_req->g_proxy))
	{
		GDBUSX_METHOD_SYNC(GDBUSX_IFAC_FUNC_AGENT, _set_name)((GDBUSX_OBJECT_AGENT*)gbusx_req->g_proxy, arg_name, &out_response, NULL, &g_err);

		if (g_err == NULL)
		{
			DBG_IF_LN("(arg_name: %s, out_response:%s)", arg_name, out_response);
		}
		else
		{
			DBG_ER_LN("GDBUSX_METHOD_SYNC error !!! (message: %s)", g_err->message);
		}
	}

	SAFE_G_FREE(out_response);
	SAFE_G_ERR_FREE(g_err);
}

// com_github_lankahsu520_agent_call_set_age_sync
static void gbusx_method_Agent_SetAge(GbusX_t *gbusx_req, gint arg_age)
{
	gchar *out_response = NULL;
	GError *g_err = NULL;

	if ((gbusx_req) && (gbusx_req->g_proxy))
	{
		GDBUSX_METHOD_SYNC(GDBUSX_IFAC_FUNC_AGENT, _set_age)((GDBUSX_OBJECT_AGENT*)gbusx_req->g_proxy, arg_age, &out_response, NULL, &g_err);

		if (g_err == NULL)
		{
			DBG_IF_LN("(arg_age: %d, out_response:%s)", arg_age, out_response);
		}
		else
		{
			DBG_ER_LN("GDBUSX_METHOD_SYNC error !!! (message: %s)", g_err->message);
		}
	}

	SAFE_G_FREE(out_response);
	SAFE_G_ERR_FREE(g_err);
}

// com_github_lankahsu520_agent_call_set_name_age_sync
static void gbusx_method_Agent_SetNameAge(GbusX_t *gbusx_req, const gchar *arg_name, gint arg_age)
{
	gchar *out_response = NULL;
	GError *g_err = NULL;

	if ((gbusx_req) && (gbusx_req->g_proxy))
	{
		GDBUSX_METHOD_SYNC(GDBUSX_IFAC_FUNC_AGENT, _set_name_age)((GDBUSX_OBJECT_AGENT*)gbusx_req->g_proxy, arg_name, arg_age, &out_response, NULL, &g_err);

		if (g_err == NULL)
		{
			DBG_IF_LN("(arg_name: %s, arg_age: %d, out_response:%s)", arg_name, arg_age, out_response);
		}
		else
		{
			DBG_ER_LN("GDBUSX_METHOD_SYNC error !!! (message: %s)", g_err->message);
		}
	}

	SAFE_G_FREE(out_response);
	SAFE_G_ERR_FREE(g_err);
}

static gboolean gbusx_signal_Agent_Bonjour_cb(GDBUSX_OBJECT_AGENT *object, const gchar *arg_greeting, gpointer userdata)
{
	DBG_IF_LN("(arg_greeting: %s)", arg_greeting);

	return TRUE;
}

// com_github_lankahsu520_agent_emit_bonjour
static void gbusx_signal_Agent_Bonjour(GbusX_t *gbusx_req)
{
	if (gbusx_req->g_skeletion)
	{
		static gint count = 0;
		time_t now_t = time((time_t *)NULL);
		gchar greeting[LEN_OF_BUF128] = "";

		count ++;
		SAFE_G_SPRINTF(greeting, "%ld - %d", now_t, count);
		GDBUSX_SIGNAL_EMIT(GDBUSX_IFAC_FUNC_AGENT, _bonjour)((GDBUSX_OBJECT_AGENT*)gbusx_req->g_skeletion, greeting);
	}
}

// com_github_lankahsu520_agent_call_set_name
static gboolean Agent_setName(GDBUSX_OBJECT_AGENT *object, GDBusMethodInvocation *invocation, const gchar *arg_name, gpointer user_data)
{
	gchar *retStr = NULL;

	DBG_IF_LN("(arg_name: %s)", arg_name);

	retStr = SAFE_G_STRDUP("Hello world %s !!!", arg_name);
	GDBUSX_METHOD_COMPLETE(GDBUSX_IFAC_FUNC_AGENT, _set_name)(object, invocation, retStr);
	SAFE_G_FREE(retStr);

	return TRUE;
}

// com_github_lankahsu520_agent_call_set_age
static gboolean Agent_setAge(GDBUSX_OBJECT_AGENT *object, GDBusMethodInvocation *invocation, gint arg_age, gpointer user_data)
{
	gchar *retStr = NULL;

	DBG_IF_LN("(arg_age: %d)", arg_age);

	retStr = SAFE_G_STRDUP("Your age %d.", arg_age);
	GDBUSX_METHOD_COMPLETE(GDBUSX_IFAC_FUNC_AGENT, _set_name)(object, invocation, retStr);
	SAFE_G_FREE(retStr);

	return TRUE;
}

// com_github_lankahsu520_agent_call_set_name_age
static gboolean Agent_setNameAge(GDBUSX_OBJECT_AGENT *object, GDBusMethodInvocation *invocation, const gchar *arg_name, gint arg_age, gpointer user_data)
{
	gchar *retStr = NULL;

	DBG_IF_LN("(arg_name: %s, arg_age: %d)", arg_name, arg_age);

	retStr = SAFE_G_STRDUP ("Hello world !!! (%s-%d)", arg_name, arg_age);
	GDBUSX_METHOD_COMPLETE(GDBUSX_IFAC_FUNC_AGENT, _set_name_age)(object, invocation, retStr);
	SAFE_G_FREE(retStr);

	return TRUE;
}

// bus_acquired_handler
static void gbusx_bus_acquired_Agent_cb(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	GbusX_t *gbusx_req = (GbusX_t*)user_data;
	GError *g_err = NULL;

	gbusx_req->g_skeletion = (GObject*)GDBUSX_SKELETON_NEW(GDBUSX_IFAC_FUNC_AGENT)();
	if (gbusx_req->g_skeletion)
	{
		(void) g_signal_connect(gbusx_req->g_skeletion, "handle-set-name", G_CALLBACK(Agent_setName), NULL);
		(void) g_signal_connect(gbusx_req->g_skeletion, "handle-set-age", G_CALLBACK(Agent_setAge), NULL);
		(void) g_signal_connect(gbusx_req->g_skeletion, "handle-set-name-age", G_CALLBACK(Agent_setNameAge), NULL);

		(void) g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(gbusx_req->g_skeletion),
																						connection,
																						gbusx_req->path_name,
																						&g_err);
		if(g_err == 0)
		{
			DBG_IF_LN("(gbusx_req->name: %s, name: %s)", gbusx_req->name, name);
		}
		else
		{
			DBG_ER_LN("g_dbus_interface_skeleton_export - error !!! (gbusx_req->name: %s, name: %s, message: %s)", gbusx_req->name, name, g_err->message);
			SAFE_G_LOOP_QUIT(gbusx_req->g_Loop);
		}
	}
	else
	{
		DBG_ER_LN("GDBUSX_SKELETON_NEW error !!! (gbusx_req->name: %s, name: %s)", gbusx_req->name, name);
	}
	SAFE_G_ERR_FREE(g_err);
}

static void *gbusx_proxy_register_Agent_cb(void *user)
{
	GbusX_t *gbusx_req = (GbusX_t *)user;

	DBG_DB_LN("%s (gbusx_req->name: %s, isservice: %d)", DBG_TXT_ENTER, gbusx_req->name, gbusx_req->isservice);
	if (gbusx_req->g_connection)
	{
		GError *g_err = NULL;
		while ( (threadx_isquit(&gbusx_req->tidx)==0) && (gbusx_req->isquit==0) && (gbusx_req->g_proxy==NULL) )
		{
			// com_github_lankahsu520_boss_proxy_new_sync
			gbusx_req->g_proxy = (GDBUSX_OBJECT*)GDBUSX_PROXY_NEW_SYNC(GDBUSX_IFAC_FUNC_AGENT)(gbusx_req->g_connection,
																														gbusx_req->proxy_flags,
																														gbusx_req->iface_name,
																														gbusx_req->path_name,
																														NULL,
																														&g_err);
			if (gbusx_req->g_proxy)
			{
				DBG_IF_LN("%s (%s, is_quit: %d)", DBG_TXT_LINKED, gbusx_req->iface_name, threadx_isquit(&gbusx_req->tidx));
				break;
			}
			else
			{
				DBG_ER_LN("GDBUSX_PROXY_NEW_SYNC - error !!! (message: %s)", g_err->message);
			}

			SAFE_G_ERR_FREE(g_err);
			sleep(1);
		}
	
		SAFE_G_ERR_FREE(g_err);
	}

	if (gbusx_req->g_proxy)
	{
		gbusx_signal_int(gbusx_req, "bonjour", gbusx_signal_Agent_Bonjour_cb);
	}

	return NULL;
}

void Agent_stop(void)
{
	GbusX_t *gbusx_req = (GbusX_t *)&gbusx_agent;

	gbusx_stop(gbusx_req);
}

void Agent_start(void)
{
	GbusX_t *gbusx_req = (GbusX_t *)&gbusx_agent;

	gbusx_req->tidx.data = (void *)gbusx_req;

	gbusx_req->isservice = is_service;
	gbusx_start(gbusx_req, "thread_gbusx_agent", gbusx_dummy_thread_handler, gbusx_proxy_register_Agent_cb, &gbusx_bus_acquired_Agent_cb, &gbusx_name_acquired_cb, &gbusx_name_lost_cb);

}

// com.github.lankahsu520.boss **
#define gbusx_IFAC_NAME_BOSS "com.github.lankahsu520.boss"
#define gbusx_PATH_NAME_BOSS "/com/github/lankahsu520/boss"

#define gbusx_IFAC_FUNC_BOSS GDBUSX_IFAC_FUNC_CONCAT(GDBUSX_IFAC_FUNC_PREFIXNAME, _boss)
#define gbusx_OBJECT_BOSS ComGithubLankahsu520Boss

static GbusX_t gbusx_boss = {
	.name = "gbusx_boss",

	.isfree = 0,
	.isinit = 0,

	.isservice = 0,

	.g_Loop = NULL,
	.g_connection = NULL,
	.g_type = GDBUSX_TYPE_SESSION,

	.iface_name = gbusx_IFAC_NAME_BOSS,
	.path_name = gbusx_PATH_NAME_BOSS,

	.proxy_flags = GDBUSX_PROXY_FLAGS,
	.g_proxy = NULL,

	.g_ownid = 0,
	.owner_flags = GDBUSX_OWNER_FLAGS,
	.g_skeletion = NULL,
};
	
// com_github_lankahsu520_boss_call_set_name_age_sync
static void gbusx_method_Boss_SetNameAge(GbusX_t *gbusx_req, const gchar *arg_name, gint arg_age)
{
	gchar *out_response = NULL;
	GError *g_err = NULL;

	if ((gbusx_req) && (gbusx_req->g_proxy))
	{
		GDBUSX_METHOD_SYNC(gbusx_IFAC_FUNC_BOSS, _set_name_age)((gbusx_OBJECT_BOSS*)gbusx_req->g_proxy, arg_name, arg_age, &out_response, NULL, &g_err);

		if (g_err == NULL)
		{
			DBG_IF_LN("(arg_name: %s, arg_age: %d, out_response:%s)", arg_name, arg_age, out_response);
		}
		else
		{
			DBG_ER_LN("GDBUSX_METHOD_SYNC error !!! (message: %s)", g_err->message);
		}
	}

	SAFE_G_FREE(out_response);
	SAFE_G_ERR_FREE(g_err);
}

// com_github_lankahsu520_boss_call_set_name_age
static gboolean Boss_setNameAge(gbusx_OBJECT_BOSS *object, GDBusMethodInvocation *invocation, const gchar *arg_name, gint arg_age, gpointer user_data)
{
	gchar *retStr = NULL;

	DBG_IF_LN("(arg_name: %s, arg_age: %d)", arg_name, arg_age);

	retStr = SAFE_G_STRDUP ("Yes sir !!! (%s-%d)", arg_name, arg_age);
	GDBUSX_METHOD_COMPLETE(gbusx_IFAC_FUNC_BOSS, _set_name_age)(object, invocation, retStr);
	SAFE_G_FREE(retStr);

	return TRUE;
}

// bus_acquired_handler
static void gbusx_bus_acquired_Boss_cb(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
	GbusX_t *gbusx_req = (GbusX_t*)user_data;
	GError *g_err = NULL;

	gbusx_req->g_skeletion = (GObject*)GDBUSX_SKELETON_NEW(gbusx_IFAC_FUNC_BOSS)();
	if (gbusx_req->g_skeletion)
	{
		(void) g_signal_connect(gbusx_req->g_skeletion, "handle-set-name-age", G_CALLBACK(Boss_setNameAge), NULL);

		(void) g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(gbusx_req->g_skeletion),
																						connection,
																						gbusx_req->path_name,
																						&g_err);
		if(g_err == 0)
		{
			DBG_IF_LN("(gbusx_req->name: %s, name: %s)", gbusx_req->name, name);
		}
		else
		{
			DBG_ER_LN("g_dbus_interface_skeleton_export - error !!! (gbusx_req->name: %s, name: %s, message: %s)", gbusx_req->name, name, g_err->message);
			SAFE_G_LOOP_QUIT(gbusx_req->g_Loop);
		}
	}
	else
	{
		DBG_ER_LN("GDBUSX_SKELETON_NEW error !!! (gbusx_req->name: %s, name: %s)", gbusx_req->name, name);
	}
	SAFE_G_ERR_FREE(g_err);
}

static void *gbusx_proxy_register_Boss_cb(void *user)
{
	GbusX_t *gbusx_req = (GbusX_t *)user;

	DBG_DB_LN("%s (gbusx_req->name: %s, isservice: %d)", DBG_TXT_ENTER, gbusx_req->name, gbusx_req->isservice);
	if (gbusx_req->g_connection)
	{
		GError *g_err = NULL;
		while ( (threadx_isquit(&gbusx_req->tidx)==0) && (gbusx_req->isquit==0) && (gbusx_req->g_proxy==NULL) )
		{
			// com_github_lankahsu520_boss_proxy_new_sync
			gbusx_req->g_proxy = (GDBUSX_OBJECT*)GDBUSX_PROXY_NEW_SYNC(gbusx_IFAC_FUNC_BOSS)(gbusx_req->g_connection,
																														gbusx_req->proxy_flags,
																														gbusx_req->iface_name,
																														gbusx_req->path_name,
																														NULL,
																														&g_err);
			if (gbusx_req->g_proxy)
			{
				DBG_IF_LN("%s (%s, is_quit: %d)", DBG_TXT_LINKED, gbusx_req->iface_name, threadx_isquit(&gbusx_req->tidx));
				break;
			}
			else
			{
				DBG_ER_LN("GDBUSX_PROXY_NEW_SYNC - error !!! (message: %s)", g_err->message);
			}

			SAFE_G_ERR_FREE(g_err);
			sleep(1);
		}
	
		SAFE_G_ERR_FREE(g_err);
	}

	return NULL;
}

void Boss_stop(void)
{
	GbusX_t *gbusx_req = (GbusX_t *)&gbusx_boss;

	gbusx_stop(gbusx_req);
}

void Boss_start(void)
{
	GbusX_t *gbusx_req = (GbusX_t *)&gbusx_boss;

	gbusx_req->tidx.data = (void *)gbusx_req;

	gbusx_req->isservice = is_service;
	gbusx_start(gbusx_req, "thread_gbusx_boss", gbusx_dummy_thread_handler, gbusx_proxy_register_Boss_cb, &gbusx_bus_acquired_Boss_cb, &gbusx_name_acquired_cb, &gbusx_name_lost_cb);

}

static int app_quit(void)
{
	return is_quit;
}

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static void app_stop(void)
{
	if (app_quit()==0)
	{
		app_set_quit(1);

		Agent_stop();
		Boss_stop();
	}
}

static void app_loop(void)
{
	Agent_start();
	Boss_start();

	while (app_quit()==0)
	{
#if (1)
		{
			if (is_service==1)
			{
				gbusx_signal_Agent_Bonjour(&gbusx_agent);
				sleep(5);
			}
			else
			{
				if (0)
				{
					gbusx_method_Agent_SetName(&gbusx_agent, "Mary");
					gbusx_method_Agent_SetAge(&gbusx_agent, 18);
				}

				gbusx_method_Agent_SetNameAge(&gbusx_agent, "Mary", 18);
				gbusx_method_Boss_SetNameAge(&gbusx_boss, "Lanka", 19);
				sleep(3);
			}
		}
#else
		sleep(1);
#endif
	}
}

static int app_init(void)
{
	int ret = 0;

	return ret;
}

static void app_exit(void)
{
	app_stop();
}

static void app_signal_handler(int signum)
{
	DBG_ER_LN("(signum: %d)", signum);
	switch (signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
			break;
		case SIGPIPE:
			break;

		case SIGUSR1:
			break;

		case SIGUSR2:
			dbg_lvl_round();
			DBG_ER_LN("dbg_lvl_get(): %d", dbg_lvl_get());
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

	signal(SIGPIPE, SIG_IGN );
}

int option_index = 0;
const char* short_options = "d:e:sh";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "service",     no_argument,         NULL,    's'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf( "Usage: %s\n"
					"  -d, --debug       debug level\n"
					"  -s, --service\n"
					"  -h, --help\n", TAG);
	printf( "Version: %s\n", version_show());
	printf( "Example:\n"
					"  %s -d 4 -s\n", TAG);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while((opt = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'd':
				if (optarg)
				{
					dbg_lvl_set(atoi(optarg));
				}
				break;
			case 's':
				{
					is_service = 1;
				}
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	app_ParseArguments(argc, argv);
	app_signal_register();
	atexit(app_exit);

	if ( app_init() == -1 )
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
