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

#define USE_UV
#ifdef USE_UV
#define USE_ASYNC_CREATE
#define USE_TIMER_CREATE
#endif

#define TAG "lws_123"

// ** app **
static int is_quit = 0;
static int is_service = 0;
static int is_echo = 0;

static uv_loop_t *uv_loop = NULL;

#ifdef USE_ASYNC_CREATE
uv_async_t uv_async_fd;
#endif

static int lws2_client_cb(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	int ret = -1;

	LWSCtx_t *lws_ctx = lws2_protocol_user(wsi);

	switch( reason )
	{
		case LWS_CALLBACK_CLIENT_RECEIVE: // 8
			{
				lws2_lock(lws_ctx);
				char tmpbuf[LEN_OF_WEBSOCKET] = "";
				SAFE_MEMCPY(tmpbuf, in, len, LEN_OF_WEBSOCKET);
				DBG_IF_LN("(tmpbuf: %s)", tmpbuf);
				lws2_unlock(lws_ctx);
				ret  = 0;
			}
			break;

		default:
			break;
	}

	return ret;
}

LWSCtx_t lws_req = {
	.name = TAG,
	.isquit = 0,
	.isecho = 0,

	.cinfo = {0},
	.context = NULL,
	.ccinfo = {0},
	.callback = lws2_client_cb,
};

static int app_quit(void)
{
	return is_quit;
}

#ifdef USE_TIMER_CREATE
uv_timer_t uv_timer_1sec_fd;
void timer_1sec_loop(uv_timer_t *handle)
{
	//DBG_TR_LN(DBG_TXT_ENTER);
	//SAFE_UV_ASYNC(&uv_async_fd);

	if (app_quit()==1)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
	else
	{
		if (is_service)
		{ // server mode, send to myself
		}
		else
		{ // client mode
			static int cli_count = 0;

			if (lws2_session_count(&lws_req) > 0)
			{
				char tmpbuf[LEN_OF_WEBSOCKET] = "";

				//DBG_IF_LN(">>>>>>>>>> (&lws_req: %p)", &lws_req);
				SAFE_SPRINTF(tmpbuf, "(cli_count: %d)", cli_count);

				lws2_session_write_q_broadcast(&lws_req, tmpbuf, SAFE_STRLEN(tmpbuf));
			}
			else if (cli_count%10==0)
			{
				const struct lws_protocols *protocols = lws_req.cinfo.protocols;
				lws2_cli_open(&lws_req, "localhost", WEBSOCKETS_PORT_7681, (char*)protocols[0].name);
			}
			cli_count++;
		}
	}
}
#endif

void app_stop_uv(uv_async_t *handle, int force)
{
	static int is_free = 0;
	if ( (is_free==0) && (app_quit()==1) )
	{
		is_free = 1;
#ifdef USE_UV
		if (uv_loop)
		{
#ifdef USE_TIMER_CREATE
			SAFE_UV_TIMER_CLOSE(&uv_timer_1sec_fd, NULL);
#endif

			if (handle)
			{
				SAFE_UV_CLOSE(handle, NULL);
			}

			if (force)
			{
				SAFE_UV_LOOP_CLOSE(uv_loop);
			}
		}
#endif
	}
}

#ifdef USE_ASYNC_CREATE
//uv_async_t uv_async_fd;
int async_count = 0;

void async_loop(uv_async_t *handle)
{
	DBG_IF_LN(DBG_TXT_ENTER);

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

		if (is_service)
		{
			lws2_srv_close( &lws_req );
		}
		else
		{
			lws2_cli_close( &lws_req );
		}
	}
}

static void app_loop(void)
{
#ifdef USE_UV
	SAFE_UV_LOOP_INIT(uv_loop);

#ifdef USE_ASYNC_CREATE
	uv_async_fd.data = (void *) &async_count;
	SAFE_UV_ASYNC_INIT(uv_loop, &uv_async_fd, async_loop);
#endif

#ifdef USE_TIMER_CREATE
	SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_1sec_fd);
	SAFE_UV_TIMER_START(&uv_timer_1sec_fd, timer_1sec_loop, 1000, 1000); // 1st: 1, 2nd: 1+1, 3rd: 1+1+1, 4th: 1+1+1+1 .....
#endif
#endif

	if (is_service)
	{
		lws2_srv_init(&lws_req, WEBSOCKETS_PORT_7681, NULL, LWS_SERVER_OPTION_LIBUV, uv_loop);

		lws_req.isecho = is_echo;
		lws2_srv_open(&lws_req, 1000000);
	}
	else
	{
		lws2_cli_init(&lws_req, NULL, LWS_SERVER_OPTION_LIBUV, uv_loop);

		const struct lws_protocols *protocols = lws_req.cinfo.protocols;
		lws2_cli_open(&lws_req, "localhost", WEBSOCKETS_PORT_7681, (char*)protocols[0].name);
	}

#ifdef USE_UV
	SAFE_UV_LOOP_RUN(uv_loop);
	SAFE_UV_LOOP_CLOSE(uv_loop);
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
	signal(SIGINT, app_signal_handler );
	signal(SIGTERM, app_signal_handler );
	signal(SIGHUP, app_signal_handler );
	signal(SIGUSR1, app_signal_handler );
	signal(SIGUSR2, app_signal_handler );

	signal(SIGPIPE, SIG_IGN );
}

int option_index = 0;
const char* short_options = "d:seh";
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
	printf( "Usage: %s\n"
					"  -d, --debug       debug level\n"
					"  -s, --service\n"
					"  -e, --echo\n"
					"  -h, --help\n", TAG);
	printf( "Version: %s\n", version_show());
	printf( "Example:\n"
					"  %s -d 4 -s -e\n", TAG);
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
				is_service = 1;
				break;
			case 'e':
				is_echo = 1;
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

// simple-libwebsockets-example
// https://github.com/iamscottmoyers/simple-libwebsockets-example
// export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH
// valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./lws_123 -s -e
// ./lws_123 -s -e
// ./lws_123
// http://192.168.50.51:7681
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
