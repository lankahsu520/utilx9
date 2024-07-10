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

#define TAG "select_123"

// ** app **
static int is_quit = 0;
// 1s=1000ms=1000000us
int interval = 1000; //us
int duration = 60; //s

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
	}
}

static void app_loop(void)
{
	int pid = pidof(TAG);
	DBG_ER_LN("(TAG: %s, pid: %d)", TAG, pid);

	{
		double hold_t = 0;
		time_t run_t = time(NULL);
		time_t last_t = time(NULL);

		DBG_ER_LN("duration: %d, usleep(%d) ...", duration, interval);
		hold_t = 0;
		run_t = time(NULL);
		while ( (hold_t< duration) && (app_quit()<1) )
		{
			last_t = time(NULL);
			hold_t = time_diff_secs(last_t, run_t);

			SAFE_SELECT_EX(0, NULL, NULL, NULL, interval/1000, interval%1000);
			//usleep(timeout);
			//DBG_ER_LN("(hold_t: %f, last_t: %zd)", hold_t, last_t);
		}
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
const char* short_options = "d:u:i:h";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "duration",    required_argument,   NULL,    'u'  },
	{ "interval",    required_argument,   NULL,    'i'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf( "Usage: %s\n"
					"  -d, --debug        debug level\n"
					"  -u, --duration     duration(s)\n"
					"  -i, --interval     interval(us)\n"
					"  -h, --help\n", TAG);
	printf( "Version: %s\n", version_show());
	printf( "Example:\n"
					"  %s -d 3 -u 60 -i 1000\n", TAG);
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
			case 'u':
				duration = atoi(optarg);
				break;
			case 'i':
				interval = atoi(optarg);
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
