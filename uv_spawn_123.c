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

#define USE_ASYNC_CREATE
#define USE_TIMER_CREATE
#define USE_SPAWN_CREATE
#define USE_SPAWN_SIMPLE_CREATE

#define TAG "uv_spawn_123"

// ** app **
static int is_quit = 0;
static uv_loop_t *uv_loop = NULL;

#ifdef USE_SPAWN_CREATE
SpawnX_t spawn_info =
{
	.loop = NULL,
	.argc = 0,
};
#endif

#ifdef USE_SPAWN_CREATE
void uv_spawn_ping(void)
{
	SpawnX_t *spawn_req  = &spawn_info;

	spawn_req->loop = uv_loop;

	//SAFE_SPRINTF_EX(spawn_req->name, "./util_123");
	SAFE_SPRINTF_EX(spawn_req->name, "ping");
	spawn_req->argc = 0;
	spawn_req->args[spawn_req->argc++] = spawn_req->name;
	spawn_req->args[spawn_req->argc++] = "8.8.8.8";
	spawn_req->args[spawn_req->argc++] = NULL;

	uv_spawn_open_ex(spawn_req);
}
#endif

#ifdef USE_SPAWN_SIMPLE_CREATE
// please put child_req and options in global area
uv_process_t child_req;
uv_process_options_t child_options;

void uv_spawn_simple_test(char *hostname)
{
	char *child_args[20];
	child_args[0] = "ping";
	child_args[1] = hostname;
	child_args[2] = NULL;

	child_options.exit_cb = NULL;
	child_options.file = "ping";
	child_options.args = child_args;
	child_options.flags = UV_PROCESS_DETACHED;

	int r;
	if ((r = uv_spawn(uv_loop, &child_req, &child_options)))
	{
		DBG_IF_LN("uv_spawn error !!! (%s)", uv_strerror(r));
	}
	else
	{
		DBG_IF_LN("uv_spawn ... (ping %s)", hostname);
	}
	uv_unref((uv_handle_t*) &child_req);
}
#endif


#ifdef USE_TIMER_CREATE
uv_timer_t uv_timer_1sec_fd;
void timer_1sec_loop(uv_timer_t *handle)
{
	static int count = 0;
	count++;
	DBG_IF_LN("(count: %d)", count);

	if (count==2)
	{
#ifdef USE_SPAWN_CREATE
		uv_spawn_ping();
#endif
	}
	else if ((count%3) == 0)
	{
#ifdef USE_SPAWN_SIMPLE_CREATE
		//uv_spawn_simple_test("192.168.50.72");
		//uv_spawn_simple_detached(uv_loop, &child_req, &child_options, 2, "ping", "192.168.50.72");

		{
			SpawnX_t *spawn_req = (SpawnX_t *)SAFE_CALLOC(1, sizeof(SpawnX_t));
			spawn_req->loop = uv_loop;
			spawn_req->child_req.data = spawn_req;
			uv_spawn_simple_detached(spawn_req, 3, "/work/rootfs/sbin/iot_kvsWebrtc.sh", "restart", "1");
		}

		{
			SpawnX_t *spawn_req = (SpawnX_t *)SAFE_CALLOC(1, sizeof(SpawnX_t));
			spawn_req->loop = uv_loop;
			spawn_req->child_req.data = spawn_req;
			uv_spawn_simple_detached(spawn_req, 3, "/work/rootfs/sbin/baresip_123.sh", "restart", "1");
		}

		//uv_spawn_simple_test("192.168.50.1");
		//uv_spawn_simple_detached(uv_loop, &child_req, &child_options, 2, "ping", "192.168.50.1");
#endif
	}
}
#endif

static int app_quit(void)
{
	return is_quit;
}

void app_stop_uv(uv_async_t *handle, int force)
{
	static int is_free = 0;
	if ((is_free==0) && (app_quit()==1))
	{
		is_free = 1;
		if (uv_loop)
		{
			DBG_IF_LN("call SAFE_UV_TIMER_CLOSE ~~~");
#ifdef USE_TIMER_CREATE
			SAFE_UV_TIMER_CLOSE(&uv_timer_1sec_fd, NULL);
#endif

			DBG_IF_LN("call uv_spawn_close_ex ~~~");
#ifdef USE_SPAWN_CREATE
			uv_spawn_close_ex(&spawn_info);
#endif

			DBG_IF_LN("call SAFE_UV_CLOSE ~~~");
			if (handle)
			{
				SAFE_UV_CLOSE(handle, NULL);
			}

			DBG_IF_LN("call SAFE_UV_LOOP_CLOSE ~~~");
			if (force)
			{
				SAFE_UV_LOOP_CLOSE(uv_loop);
			}
		}
	}
	DBG_IF_LN("exit");
}

#ifdef USE_ASYNC_CREATE
uv_async_t uv_async_fd;
int async_count = 0;

void async_loop(uv_async_t *handle)
{
	async_count ++;

	DBG_IF_LN("(async_count: %d)", async_count);

	app_stop_uv(handle, 0);
}
#endif

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static void app_stop(void)
{
	if (app_quit()==0)
	{
		app_set_quit(1);

#ifdef USE_ASYNC_CREATE
		SAFE_UV_ASYNC(&uv_async_fd);
#else
#error "Please use USE_ASYNC_CREATE !!!"
		app_stop_uv(NULL, 1);
#endif
	}
}

static void app_loop(void)
{
	SAFE_UV_LOOP_INIT(uv_loop);

#ifdef USE_ASYNC_CREATE
	uv_async_fd.data = (void *) &async_count;
	SAFE_UV_ASYNC_INIT(uv_loop, &uv_async_fd, async_loop);
#endif

#ifdef USE_TIMER_CREATE
	SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_1sec_fd);
	SAFE_UV_TIMER_START(&uv_timer_1sec_fd, timer_1sec_loop, 1000, 1000); // 1st: 1, 2nd: 1+1, 3rd: 1+1+1, 4th: 1+1+1+1 .....
#endif

	SAFE_UV_LOOP_RUN(uv_loop);
	SAFE_UV_LOOP_CLOSE(uv_loop);

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
