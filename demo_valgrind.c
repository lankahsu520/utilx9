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

#define TAG "demo_000"

#define USE_DEFINITELY_LOST
#define USE_INDIRECTLY_LOST
#define USE_POSSIBLY_LOST
#define USE_STILL_REACHABLE

// ** app **
static int is_quit = 0;

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

#ifdef USE_DEFINITELY_LOST
#define MAX_OF_DEFINITELY_LOST LEN_OF_BUF128
static void definitely_lost_fn(void)
{
	DBG_IF_LN("call SAFE_CALLOC ... (size: %d)", MAX_OF_DEFINITELY_LOST);
	char *tmpbuff = SAFE_CALLOC(1, MAX_OF_DEFINITELY_LOST);
	SAFE_SPRINTF(tmpbuff, "%s", DBG_TXT_HELLO_WORLD);
}
#endif

#ifdef USE_INDIRECTLY_LOST
#define DATA_OF_INDIRECTLY_LOST "lanka"
#define JSON_ARY_APPEND_OBJ_INDIRECTLY(jary, jval) \
	({ int __ret = -1; \
		do { if ((jary) && (jval)) __ret = json_array_append_new(jary, jval); else DBG_ER_LN("%p or %p is NULL !!!", jary, jval); } while(0); \
		__ret; \
	})

static void indirectly_lost_fn(void)
{
#ifdef UTIL_EX_JSON
	json_t *jroot = JSON_ARY_NEW();
	if (jroot)
	{
		// jsonp_strndup(value, len);
		size_t len = SAFE_STRLEN(DATA_OF_INDIRECTLY_LOST) + 1;
		DBG_IF_LN("call JSON_ARY_APPEND_OBJ_INDIRECTLY ... (size: %zd)", len);
		JSON_ARY_APPEND_OBJ_INDIRECTLY(jroot, JSON_JSTR(DATA_OF_INDIRECTLY_LOST));
		JSON_FREE(jroot);
	}
#endif
}
#endif

#ifdef USE_POSSIBLY_LOST
#define MAX_OF_POSSIBLY_LOST LEN_OF_NAME32
#define COUNT_OF_POSSIBLY_LOST 2
typedef struct member_STRUCT
{
	int id;
	char name[LEN_OF_NAME32];
} member_t;
member_t *lk_members = NULL;

static void member_assign(member_t *member, char *name, int id)
{
	//member->name = SAFE_CALLOC(1, MAX_OF_POSSIBLY_LOST);
	SAFE_SPRINTF(member->name, "%s", name);
	member->id = id;
}

static void member_create(member_t **members, int count)
{
	*members = (member_t *)SAFE_CALLOC(count, sizeof(member_t));
}

static void possibly_lost_fn(void)
{
	//member_t *members_root = lk_members;

	DBG_IF_LN("call member_create ... (count: %d, size: %ld)", COUNT_OF_POSSIBLY_LOST, COUNT_OF_POSSIBLY_LOST*sizeof(member_t));
	member_create(&lk_members, COUNT_OF_POSSIBLY_LOST);
	member_assign(lk_members, "lanka", 0); lk_members++;
	member_assign(lk_members, "mary", 0);
}
#endif

#ifdef USE_STILL_REACHABLE
#define MAX_OF_STILL_REACHABLE LEN_OF_BUF512
static void still_reachable_fn(void)
{
	static char *reachable = NULL;
	DBG_IF_LN("call SAFE_CALLOC ... (reachable, size: %d)", MAX_OF_STILL_REACHABLE);
	reachable = SAFE_CALLOC(1, MAX_OF_STILL_REACHABLE);
	SAFE_SPRINTF(reachable, "lanka");
}
#endif

static void app_loop(void)
{
#ifdef USE_DEFINITELY_LOST
	definitely_lost_fn();
#endif

#ifdef USE_INDIRECTLY_LOST
	indirectly_lost_fn();
#endif

#ifdef USE_POSSIBLY_LOST
	possibly_lost_fn();
#endif

#ifdef USE_STILL_REACHABLE
	still_reachable_fn();
#endif
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
