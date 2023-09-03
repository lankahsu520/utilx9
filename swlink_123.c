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
#include <linux/switch.h>

#define TAG "swlink_123"

// ** app **
static int is_quit = 0;

SWLinkX_t sw_req =
{
	.cdev = "switch0",
	.port = 0,
	.cmd = SWLINK_CMD_ID_GET,
	.ckey = "link",
};

static int app_quit(void)
{
	return is_quit;
}

static void print_attr_val(const struct switch_attr *attr, const struct switch_val *val)
{
	int i;

	switch (attr->type)
	{
		case SWITCH_TYPE_INT:
			DBG_IF_LN("%d", val->value.i);
			break;
		case SWITCH_TYPE_STRING:
			// port:0 link:up speed:100baseT full-duplex
			// port:0 link:down
			DBG_IF_LN("%s", val->value.s);
			break;
		case SWITCH_TYPE_PORTS:
			for (i = 0; i < val->len; i++)
			{
				DBG_IF_LN("%d%s ",
						  val->value.ports[i].id,
						  (val->value.ports[i].flags &
						   SWLIB_PORT_FLAG_TAGGED) ? "t" : "");
			}
			break;
		default:
			DBG_IF_LN("?unknown-type?");
			break;
	}
}

static void app_loop(void)
{
	sw_req.dev = swlib_connect(sw_req.cdev);
	swlib_scan(sw_req.dev);

	sw_req.attr = swlib_lookup_attr(sw_req.dev, SWLIB_ATTR_GROUP_PORT, sw_req.ckey);

	sw_req.val.port_vlan = sw_req.port;

	int i = 10;
	while (i>0)
	{
		swlib_get_attr(sw_req.dev, sw_req.attr, &sw_req.val);
		print_attr_val(sw_req.attr, &sw_req.val);
		sleep(1);
		i--;
	}

	swlib_free_all(sw_req.dev);

}

static int app_init(void)
{
	int ret = 0;

	return ret;
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
	}
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
			DBG_ER_LN("(Version: %s)", version_show());
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
const char* short_options = "d:h";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		   "  -d, --debug       debug level\n"
		   "  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		   "  %s -d 4\n", TAG);
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
