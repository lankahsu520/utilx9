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

#define TAG "dbusx_456"

// ** app **
static int is_quit = 0;
static int is_service = 0;
char msg[LEN_OF_BUF4096]="";

static DbusX_t dbusx_456 =
{
	.name = "dbusx_456",

	.isfree = 0,
	.isinit = 0,

	.path = DBUS_PATH_LANKAHSU520,
	.dbus_conn = NULL,
	.dbus_conn_listen = NULL,
};

static DBusHandlerResult dbus_filter_cb(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	//const char *method = dbus_message_get_member(message);
	//const char *iface = dbus_message_get_interface(message);
	//const char *path = dbus_message_get_path(message);

	if (dbus_message_is_signal(message, DBUS_S_IFAC_LANKAHSU520_DEMO, DBUS_S_NAME_COMMAND))
	{
		//handled = demo_signal_cb(connection, message, NULL);
		const char *signal_name = dbus_message_get_member(message);
		handled = demo_signal_name_cb(connection, message, signal_name, NULL);
	}
#if (1)
	else if (dbus_message_is_signal(message, DBUS_S_IFAC_LANKAHSU520_DEMO, "DBUS_TYPE_INT16"))
	{
		const char *signal_name = dbus_message_get_member(message);
		handled = demo_signal_name_cb(connection, message, signal_name, NULL);
	}
	else if (dbus_message_is_signal(message, DBUS_S_IFAC_LANKAHSU520_DEMO, "DBUS_TYPE_INT32"))
	{
		const char *signal_name = dbus_message_get_member(message);
		handled = demo_signal_name_cb(connection, message, signal_name, NULL);
	}
	else if (dbus_message_is_signal(message, DBUS_S_IFAC_LANKAHSU520_DEMO, "DBUS_TYPE_INT64"))
	{
		const char *signal_name = dbus_message_get_member(message);
		handled = demo_signal_name_cb(connection, message, signal_name, NULL);
	}
#endif
	else if (dbus_message_is_method_call(message, DBUS_M_IFAC_LANKAHSU520_DEMO, DBUS_METHOD_COMMAND))
	{
		handled = dbusx_method_echo_cb(connection, message, NULL);
	}

	return handled;
}

static int dbus_match_cb(DBusConnection *dbus_listen, DBusError *err, void *usr_data)
{
	int ret = -1;

	// add a rule for which messages we want to see
	dbus_bus_add_match(dbus_listen, DBUS_S_MATCH_LANKAHSU520_DEMO, err); // see signals from the given interface
	if (dbus_error_is_set(err))
	{
		DBG_ER_LN("dbus_bus_add_match error !!! (%s, %s)", DBUS_S_MATCH_LANKAHSU520_DEMO, err->message);
		goto exit_match;
	}

	dbus_bus_request_name(dbus_listen, DBUS_DEST_LANKAHSU520, DBUS_NAME_FLAG_REPLACE_EXISTING, err);
	if (dbus_error_is_set(err))
	{
		DBG_ER_LN("dbus_bus_request_name error !!! (%s, %s)", DBUS_DEST_LANKAHSU520, err->message);
		goto exit_match;
	}

	ret = 0;

exit_match:

	return ret;
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

		if (is_service)
		{
			dbusx_thread_close(&dbusx_456);
		}
	}
}

static void app_loop(void)
{
	if (is_service)
	{
		dbusx_thread_init(dbus_match_cb, dbus_filter_cb, &dbusx_456);

		while (app_quit()==0)
		{
			sleep(1);
		}
	}
	else
	{
		dbusx_client_init(&dbusx_456);

		{
			// signal - send string
			dbusx_signal_str(&dbusx_456, DBUS_S_IFAC_LANKAHSU520_DEMO, DBUS_S_NAME_COMMAND, msg);
		}

		if (1)
		{
			// method - send string
			char *retStr = dbusx_method_str2str(&dbusx_456, DBUS_DEST_LANKAHSU520, DBUS_M_IFAC_LANKAHSU520_DEMO, DBUS_METHOD_COMMAND, msg, TIMEOUT_OF_DBUS_REPLY);
			DBG_IF_LN("(retStr: %s)", retStr);
			SAFE_FREE(retStr);
		}

#if (1)
		{
			int16_t demo_16 = 16;
			dbusx_signal_helper(&dbusx_456, DBUS_S_IFAC_LANKAHSU520_DEMO, "DBUS_TYPE_INT16", DBUS_TYPE_INT16, (void *)&demo_16);

			int32_t demo_32 = 32;
			dbusx_signal_helper(&dbusx_456, DBUS_S_IFAC_LANKAHSU520_DEMO, "DBUS_TYPE_INT32", DBUS_TYPE_INT32, (void *)&demo_32);

			int64_t demo_64 = 64;
			dbusx_signal_helper(&dbusx_456, DBUS_S_IFAC_LANKAHSU520_DEMO, "DBUS_TYPE_INT64", DBUS_TYPE_INT64, (void *)&demo_64);
		}
#endif

		dbusx_conn_free(&dbusx_456);
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
	signal(SIGINT, app_signal_handler);
	signal(SIGTERM, app_signal_handler);
	signal(SIGHUP, app_signal_handler);
	signal(SIGUSR1, app_signal_handler);
	signal(SIGUSR2, app_signal_handler);

	signal(SIGPIPE, SIG_IGN);
}

int option_index = 0;
const char* short_options = "d:e:sh";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "service",     no_argument,         NULL,    's'  },
	{ "echo",        no_argument,         NULL,    'e'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		   "  -d, --debug       debug level\n"
		   "  -e, --echo        message\n"
		   "  -s, --service\n"
		   "  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		   "  %s -d 4 -s\n", TAG);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'd':
				if (optarg)
				{
					dbg_lvl_set(atoi(optarg));
				}
				break;
			case 'e':
				if (optarg)
				{
					SAFE_SPRINTF_EX(msg, "%s", optarg);
				}
				break;
			case 's':
				is_service = 1;
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

	if (app_init() == -1)
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
