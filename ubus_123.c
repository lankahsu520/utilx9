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
#include "ubus_ex.h"

#define TAG "ubus_123"

#define USE_UBUS_ULOOP
#define USE_UBUS_DEMO_AND_TIMER
#define USE_UBUS_UNICAST
#define USE_UBUS_NOTIFY
#define USE_UBUS_EVENT

// ** app **
static int is_quit = 0;
static int is_list = 0;
static int is_service = 0;
static int is_notify = 0;
static int is_event = 0;

char msg[LEN_OF_BUF256]="";


static void app_showusage(int exit_code);

#ifdef USE_UBUS_UNICAST
// sudo build_xxx/ubus call u_o_echo m_echo '{"msg":"lanka"}'
static int ubus_srv_handler_echo(struct ubus_context *ubus_req, struct ubus_object *obj, struct ubus_request_data *req, const char *method, struct blob_attr *msg);

const struct blobmsg_policy ubus_p_echo[] =
{
	[UBUS_P_ECHO_ID_MSG] = { .name = UBUS_P_ECHO_MSG, .type = BLOBMSG_TYPE_STRING },
};

static const struct ubus_method ubus_u_m_echo[] =
{
	UBUS_METHOD(UBUS_M_ECHO, ubus_srv_handler_echo, ubus_p_echo),
};

static struct ubus_object_type ubus_u_t_echo =
	UBUS_OBJECT_TYPE(UBUS_U_O_ECHO, ubus_u_m_echo);

struct ubus_object ubus_srv_u_obj =
{
	.name = UBUS_U_O_ECHO,
	.type = &ubus_u_t_echo,
	.methods = ubus_u_m_echo,
	.n_methods = ARRAY_SIZE(ubus_u_m_echo),
};
#endif

#ifdef USE_UBUS_NOTIFY
static struct ubus_method ubus_m_m_echo[] = {};

static struct ubus_object_type ubus_m_t_echo =
	UBUS_OBJECT_TYPE(UBUS_M_O_ECHO, ubus_m_m_echo);

struct ubus_object ubus_srv_m_obj =
{
	.name = UBUS_M_O_ECHO,
	.type = &ubus_m_t_echo,
	//.subscribe_cb = ubus_srv_subscribe_cb, // please use ubus_srv_object_subscribe
};
#endif


//******************************************************************************
//** function **
//******************************************************************************
#ifdef USE_UBUS_UNICAST
void ubus_invoke_echo_cb(struct ubus_request *req, int type, struct blob_attr *msg)
{
	struct blob_attr *tb[UBUS_P_ECHO_ID_MAX];
	blobmsg_parse(ubus_p_echo, ARRAY_SIZE(ubus_p_echo), tb, blob_data(msg), blob_len(msg));

	const char *cResponse = NULL;

	if (tb[UBUS_P_ECHO_ID_MSG] != NULL)
	{
		cResponse = blobmsg_data(tb[UBUS_P_ECHO_ID_MSG]);
	}

	char *cMsg = blobmsg_format_json_indent(msg, true, -1);
	DBG_ER_LN("(cResponse: %s, cMsg: %s)", cResponse, cMsg);
	SAFE_FREE(cMsg);
}

static int ubus_srv_handler_echo(struct ubus_context *ubus_req, struct ubus_object *obj, struct ubus_request_data *req, const char *method, struct blob_attr *msg)
{
	struct blob_attr *tb[UBUS_P_ECHO_ID_MAX];
	blobmsg_parse(ubus_p_echo, ARRAY_SIZE(ubus_p_echo), tb, blob_data(msg), blob_len(msg));

	const char *cRequest = NULL;
	if (tb[UBUS_P_ECHO_ID_MSG] != NULL)
	{
		cRequest = blobmsg_data(tb[UBUS_P_ECHO_ID_MSG]);
	}

	char *cMsg = blobmsg_format_json_indent(msg, true, -1);
	DBG_ER_LN("%s (cRequest: %s, cMsg: %s)", DBG_TXT_GOT, cRequest, cMsg);
	SAFE_FREE(cMsg);

	{
		// reply
		struct blob_buf bbuf = {};
		blob_buf_init(&bbuf, 0);
		char *rval = NULL;
		SAFE_ASPRINTF(rval, "%s", cRequest);
		blobmsg_add_string(&bbuf, UBUS_P_ECHO_MSG, rval);
		ubus_send_reply(ubus_req, req, bbuf.head);
		SAFE_FREE(rval);
		blob_buf_free(&bbuf);
	}

	return 0;
}
#endif

#ifdef USE_UBUS_NOTIFY
static void ubus_srv_subscribe_cb(struct ubus_context *ubus_req, struct ubus_object *obj_u)
{
	DBG_IF_LN("(has_subscribers: %d)", obj_u->has_subscribers);
}

static int ubus_cli_subscribe_cb(struct ubus_context *ubus_req, struct ubus_object *obj_u, struct ubus_request_data *req, const char *method, struct blob_attr *msg)
{
	char *cMsg = blobmsg_format_json_indent(msg, true, -1);

	if (SAFE_STRCMP((char *)method, UBUS_M_ECHO) == 0)
	{
		DBG_DB_LN("%s (method: %s, cMsg: %s)", DBG_TXT_GOT, method, cMsg);
	}
	else
	{
		DBG_DB_LN("%s (method: %s, cMsg: %s)", DBG_TXT_NO_SUPPORT, method, cMsg);
	}

	SAFE_FREE(cMsg);

	return 0;
}

static void ubus_cli_remove_cb(struct ubus_context *ubus_req, struct ubus_subscriber *obj_s, uint32_t id)
{
	if (obj_s)
	{
		struct ubus_object *obj_u = &obj_s->obj;
		if (obj_u)
		{
			DBG_ER_LN("(obj_name: %s, id: 0x%08X)", obj_u->name, id);
		}
	}
}

void ubus_srv_publish(void)
{
	static int p_count = 0;
	p_count++;

	char tmpbuf[LEN_OF_VAL32] = "";
	SAFE_SPRINTF_EX(tmpbuf, "p_count: %d", p_count);

	ubus_srv_notify_simple(UBUS_M_ECHO, &ubus_srv_m_obj, UBUS_P_ECHO_MSG, tmpbuf);
}
#endif

#ifdef USE_UBUS_EVENT
void ubus_srv_event(void)
{
	static int e_count = 0;
	e_count++;

	char tmpbuf[LEN_OF_VAL32] = "";
	SAFE_SPRINTF_EX(tmpbuf, "(e_count: %d)", e_count);

	ubus_srv_send_event_simple(UBUS_B_O_ECHO, UBUS_P_ECHO_MSG, tmpbuf);
}

static void ubus_cli_event_cb(struct ubus_context *ctx, struct ubus_event_handler *ev, const char *type, struct blob_attr *msg)
{
	if (msg)
	{
		if (SAFE_STRCMP((char*)type, UBUS_B_O_ECHO) == 0)
		{
			char *cMsg = blobmsg_format_json_indent(msg, true, -1);
			DBG_DB_LN("%s (type: %s, cMsg: %s)", DBG_TXT_GOT, type, cMsg);
			SAFE_FREE(cMsg);
		}
	}
}
#endif

void timer_3sec_loop(struct uloop_timeout *t)
{
#ifdef USE_UBUS_NOTIFY
	ubus_srv_publish();
#endif
#ifdef USE_UBUS_EVENT
	ubus_srv_event();
#endif
	uloop_timeout_set(t, 3 * 1000);
}

static int app_quit(void)
{
	return is_quit;
}

static void app_loop(void)
{
	if (is_list)
	{
		if (ubus_conn_init())
		{
			ubus_cli_list_register(NULL, NULL);
		}
	}
	else if (is_service)
	{
		struct ubus_context *ubus_req = NULL;
		if ((ubus_req = ubus_srv_init()))
		{
#ifdef USE_UBUS_UNICAST
			ubus_srv_add_object_ex(ubus_req, &ubus_srv_u_obj);
#endif
#ifdef USE_UBUS_NOTIFY
			ubus_srv_object_subscribe(ubus_req, &ubus_srv_m_obj, ubus_srv_subscribe_cb);
#endif

#ifdef USE_UBUS_DEMO_AND_TIMER
			uloop_timerlist_add(timer_3sec_loop, 3 * 1000);
#endif

#ifdef USE_UBUS_ULOOP
			{
				DBG_IF_LN("ubus listen ... (ubus_root: %s, local_id: 0x%08X)", ubus_root_get(), ubus_req->local_id);
				uloop_init();
				ubus_add_uloop_ex(ubus_req);
				uloop_timeout_set_ex();

				uloop_run();
				uloop_done();
			}
#else
			if (0 == ubus_thread_init())
			{
				while (app_quit()==0)
				{
					static int pub = 0;

					pub++;
					DBG_ER_LN("(pub: %d)", pub);

#ifdef USE_UBUS_DEMO_AND_TIMER
#else
					if ((pub%3) == 0)
					{
#ifdef USE_UBUS_NOTIFY
						ubus_srv_publish();
#endif
#ifdef USE_UBUS_EVENT
						ubus_srv_event();
#endif
					}
#endif
					sleep(1);
				}
			}
#endif
		}
	}
	else if (is_notify)
	{
#ifdef USE_UBUS_NOTIFY
		struct ubus_context *ubus_req = NULL;
		if ((ubus_req = ubus_conn_init()))
		{
			if (0 == ubus_cli_subscribe(UBUS_M_O_ECHO, ubus_cli_subscribe_cb, ubus_cli_remove_cb))
			{
				DBG_IF_LN("ubus client/notify ... (ubus_root: %s, local_id: 0x%08X)", ubus_root_get(), ubus_req->local_id);
#ifdef USE_UBUS_ULOOP
				uloop_init();
				ubus_add_uloop_ex(ubus_req);
				uloop_run();
				uloop_done();
#else
				if (0 == ubus_thread_init())
				{
					while (app_quit()==0)
					{
						sleep(1);
					}
				}
#endif
			}
		}
#else
		DBG_ER_LN("%s", DBG_TXT_NO_SUPPORT);
#endif
	}
	else if (is_event)
	{
#ifdef USE_UBUS_EVENT
		struct ubus_context *ubus_req = NULL;
		if ((ubus_req = ubus_conn_init()))
		{
			if (0 == ubus_cli_register_event(UBUS_B_O_ECHO, ubus_cli_event_cb))
			{
				DBG_IF_LN("ubus client/event ... (ubus_root: %s, local_id: 0x%08X)", ubus_root_get(), ubus_req->local_id);
				uloop_init();
				ubus_add_uloop_ex(ubus_req);
				uloop_run();
				uloop_done();
			}
		}
#else
		DBG_ER_LN("%s", DBG_TXT_NO_SUPPORT);
#endif
	}
	else if (SAFE_STRLEN(msg) > 0)
	{
#ifdef USE_UBUS_UNICAST
		struct ubus_context *ubus_req = NULL;
		if ((ubus_req = ubus_conn_init()))
		{
			struct blob_buf bbuf = {};
			blob_buf_init(&bbuf, 0);
			blobmsg_add_string(&bbuf, UBUS_P_ECHO_MSG, msg);
			ubus_cli_invoke_ex(UBUS_U_O_ECHO, UBUS_M_ECHO, &bbuf, ubus_invoke_echo_cb, TIMEOUT_OF_UBUS_REPLY);
			blob_buf_free(&bbuf);
		}
#else
		DBG_ER_LN("%s", DBG_TXT_NO_SUPPORT);
#endif
	}
	else
	{
		app_showusage(-1);
	}
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
		DBG_DB_LN("call app_set_quit ~~~");
		app_set_quit(1);

#ifdef USE_UBUS_ULOOP
		uloop_end_ex();
		ubus_conn_free();
#else
		ubus_thread_stop();
		ubus_thread_close();
#endif
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
const char* short_options = "d:m:slneh";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "msg",         required_argument,   NULL,    'm'  },
	{ "service",     no_argument,         NULL,    's'  },
	{ "list",        no_argument,         NULL,    'l'  },
	{ "notify",      no_argument,         NULL,    'n'  },
	{ "event",       no_argument,         NULL,    'e'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		"  -d, --debug       debug level\n"
		"  -m, --msg         message\n"
		"  -s, --service\n"
		"  -l, --list\n"
		"  -n, --notify\n"
		"  -e, --event\n"
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
			case 'm':
				if (optarg)
				{
					SAFE_SPRINTF_EX(msg, "%s", optarg);
				}
				break;
			case 's':
				is_service = 1;
				break;
			case 'l':
				is_list = 1;
				break;
			case 'n':
				is_notify = 1;
				break;
			case 'e':
				is_event = 1;
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

// sudo -E valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./ubus_123 -s
// valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./ubus_123 -s
// valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./ubus_123 -d 3 -e
// valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./ubus_123 -d 3 -n
// ./ubus_123 -l
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
