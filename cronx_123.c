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

#define TAG "cronx_123"

#define USE_CRONX_123_UV
#define USE_ASYNC_CREATE

// ** app **
static int is_quit = 0;

char clock_alarm[LEN_OF_BUF128] = "39 17 * * 1-5 2022 ";

#ifdef USE_CRONX_123_UV
static uv_loop_t *uv_loop = NULL;
uv_timer_t uv_timer_1sec_fd;
uv_timer_t uv_timer_60secs_fd;
uv_timer_t uv_timer_30mins_fd;
uv_async_t uv_async_fd;
#endif

static int app_quit(void)
{
	return is_quit;
}

#ifdef USE_CRONX_123_UV
void timer_1sec_loop(uv_timer_t *handle)
{
	//static int count = 0;
	//count++;
	//DBG_TR_LN("(count: %d)", count);

	time_t now_t = time((time_t *)NULL);
	struct tm *now_tm = localtime(&now_t);
	DBG_DB_LN("(%02d:%02d:%02d)", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);

	if (app_quit()==1)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
	else if (now_tm->tm_sec==0)
	{
		//cronx_validate("*/3 0,9,10-13,21-23 * * * ", now_tm);
		//cronx_validate("* 0,9,10-13,21-23 * * * 2021 ", now_tm);
		if (0 < cronx_validate(clock_alarm, now_tm))
		{
			DBG_WN_LN("Alarm !!! (%s)", clock_alarm);
		}
	}
}

void timer_60secs_loop(uv_timer_t *handle)
{
	//static int count = 0;
	//count++;
	//DBG_TR_LN("(count: %d)", count);

	time_t now_t = time((time_t *)NULL);
	struct tm *now_tm = localtime(&now_t);
	DBG_DB_LN("(%02d:%02d:%02d)", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);

	if (app_quit()==1)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
}

void timer_30mins_loop(uv_timer_t *handle)
{
	//app_save();

	if (app_quit()==1)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
}

void app_stop_uv(uv_async_t *handle, int force)
{
	static int is_free = 0;
	if ((is_free==0) && (app_quit()==1))
	{
		is_free = 1;
		if (uv_loop)
		{
			SAFE_UV_TIMER_CLOSE(&uv_timer_1sec_fd, NULL);
			SAFE_UV_TIMER_CLOSE(&uv_timer_60secs_fd, NULL);
			SAFE_UV_TIMER_CLOSE(&uv_timer_30mins_fd, NULL);

			if (handle)
			{
				SAFE_UV_CLOSE(handle, NULL);
			}

			if (force)
			{
				SAFE_UV_LOOP_CLOSE(uv_loop);
			}
		}
	}
}

#ifdef USE_ASYNC_CREATE
void async_loop(uv_async_t *handle)
{
	DBG_IF_LN(DBG_TXT_ENTER);

	app_stop_uv(handle, 0);
}
#endif
#endif

void app_save(void)
{

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

#ifdef USE_CRONX_123_UV
#ifdef USE_ASYNC_CREATE
		SAFE_UV_ASYNC(&uv_async_fd);
#else
		app_stop_uv(NULL, 1);
#endif
#endif
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
}

static void app_loop(void)
{
	DBG_WN_LN("%s (clock_alarm: [%s])", DBG_TXT_RUN_LOOP, clock_alarm);

#ifdef USE_CRONX_123_UV
	{
		SAFE_UV_LOOP_INIT(uv_loop);

#ifdef USE_ASYNC_CREATE
		SAFE_UV_ASYNC_INIT(uv_loop, &uv_async_fd, async_loop);
#endif

		SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_1sec_fd);
		SAFE_UV_TIMER_START(&uv_timer_1sec_fd, timer_1sec_loop, 1000, 1000); // 1st: 1, 2nd: 1+1, 3rd: 1+1+1, 4th: 1+1+1+1 .....
		// please use the another callback function.
		SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_60secs_fd);
		SAFE_UV_TIMER_START(&uv_timer_60secs_fd, timer_60secs_loop, 60*1000, 60*1000); // 1st: 60, 2nd: 60+60, 3rd: 60+60+60, 4th: 60+60+60+60 .....
		SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_30mins_fd);
		SAFE_UV_TIMER_START(&uv_timer_30mins_fd, timer_30mins_loop, 30*60*1000, 30*60*1000); // 1st:30, 2nd: 30+30, 3rd: 30+30+30, 4th: 30+30+30+30 .....

		SAFE_UV_LOOP_RUN(uv_loop);
		SAFE_UV_LOOP_CLOSE(uv_loop);
	}
#else
	while (app_quit()==0)
	{
		sleep(1);
	}
#endif

	goto exit_loop;

exit_loop:
	app_stop();
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
const char* short_options = "d:a:h";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "alarm",       required_argument,   NULL,    'a'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		"  -d, --debug       debug level\n"
		"  -a, --alarm       alarm\n"
		"  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		"  %s -a \"*/1 * * * * 2022 \" -d 2\n", TAG);
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
			case 'a':
				if (optarg)
				{
					SAFE_SPRINTF_EX(clock_alarm, "%s", optarg);
				}
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

// cronx_123 -a "*/1 * * * * 2022 " -d 2
// cronx_123 -d 3 -a "39 17 * * 1-5 2022 "
int main(int argc, char *argv[])
{
	app_ParseArguments(argc, argv);
	app_signal_register();
	atexit(app_exit);

	SAFE_STDOUT_NONE();
	if (app_init() == -1)
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
