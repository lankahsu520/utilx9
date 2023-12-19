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

#define TAG "jqx"

// ** app **
static int is_quit = 0;

typedef struct JobjItem_STRUCT
{
	void* next;

	json_t *jobj;
} JobjItem_t;

CLIST(jobjX);

QBUF_t qbuf_r;
char *filter = NULL;

static void app_showusage(int exit_code);

void jobjx_jitem_dump(json_t *jparent)
{
	char *value = NULL;
	if (jparent==NULL)
	{
	}
	else if (JSON_CHECK_OBJ(jparent))
	{
		value = JSON_DUMPS_FLAGS(jparent, JSON_FLAGS_VIEW);
	}
	else if (JSON_CHECK_ARY(jparent))
	{
		value = JSON_DUMPS_FLAGS(jparent, JSON_FLAGS_VIEW);
	}
	else if (JSON_CHECK_STR(jparent))
	{
		SAFE_ASPRINTF(value, "\"%s\"", JSON_STR(jparent));
	}
	else if (JSON_CHECK_INT(jparent))
	{
		SAFE_ASPRINTF(value, "%lld", JSON_INT(jparent, 0));
	}
	else if (JSON_CHECK_REAL(jparent))
	{
		SAFE_ASPRINTF(value, "%.03f", JSON_REAL(jparent, 0));
	}

	if (value)
	{
		printf("%s\n", value);
	}
	else
	{
		printf("\n");
	}

	SAFE_FREE(value);
}

void jobjx_dump(void)
{
	while (clist_length(jobjX) > 0)
	{
		JobjItem_t *jitem = (JobjItem_t*)clist_pop(jobjX);
		if (jitem)
		{
			json_t *jobj = jitem->jobj;
			if (jobj)
			{
				jobjx_jitem_dump(jobj);
			}
		}
	}
}

static void jobjx_free_cb(void *item)
{
	JobjItem_t *jitem = (JobjItem_t *)item;
	if (jitem)
	{
		json_t *jobj = jitem->jobj;
		JSON_FREE(jobj);
	}
}

void filter_parser_helper(int deep_s, json_t *jparent, char *saveptr, json_t *jslicing)
{
	int deep = deep_s;
	json_t *jresult = NULL;
	json_t *jslicing_root = NULL;

	if (deep == 0)
	{
		jresult = jparent;
	}

	{
		char *token = NULL;

		while ((token = SAFE_STRTOK_R(NULL, ".", &saveptr)))
		{
			char name[LEN_OF_BUF1024] = "";
			SAFE_SPRINTF_EX(name, "%s", token);

			int is_array = 0;
			int idx_full = 1;
			int idx_b = 0;
			int idx_e = -1;
			char *ary_b = SAFE_STRCHR(name,'[');
			char *ary_e = SAFE_STRCHR(name,']');

			if ((ary_b) && (ary_e))
			{
				// array
				if (SAFE_SSCANF(ary_b, "[%d:%d]", &idx_b, &idx_e) > 0)
				{
					idx_full = 0;
				}
				else if (SAFE_SSCANF(ary_b, "[:%d]", &idx_e) > 0)
				{
					idx_full = 0;
				}
				DBG_DB_LN("(idx_full: %d, idx_b: %d, idx_e: %d)", idx_full, idx_b, idx_e);

				ary_b[0] = '\0';
				is_array = 1;
			}
			DBG_DB_LN("(deep: %d, token: <%s>, name: <%s>, is_array: %d)", deep, token, name, is_array);
			//cat mqtt_honey0000.json | jq ".likes[].name"

			if (SAFE_STRLEN(name) > 0)
			{
				json_t *jtoken = JSON_OBJ_GET_OBJ(jresult, name);
				if (is_array)
				{
					jresult = NULL;
					if (JSON_CHECK_ARY(jtoken))
					{
						if (idx_full==0)
						{
							jslicing_root = JSON_ARY_NEW();
						}

						json_t *jobj_found = NULL;
						int idx = 0;

						JSON_ARY_FOREACH(jtoken, idx, jobj_found)
						{
							//DBG_DB_LN("(idx: %d)", idx);
							if ((idx_full)
								|| ((idx_b <= idx) && (idx < idx_e)))
							{
								char *saveptr_cpy = NULL;
								//DBG_DB_LN("saveptr: [%s]", saveptr);
								SAFE_ASPRINTF(saveptr_cpy, "%s.", saveptr);
								if (saveptr_cpy)
								{
									filter_parser_helper(0, jobj_found, saveptr_cpy, jslicing_root);
									SAFE_FREE(saveptr_cpy);
								}
							}
							else if ((idx_b == idx) && (idx_e == -1))
							{
								// single
								JSON_FREE(jslicing_root);
								jslicing_root = NULL;

								char *saveptr_cpy = NULL;
								//DBG_DB_LN("saveptr: [%s]", saveptr);
								SAFE_ASPRINTF(saveptr_cpy, "%s.", saveptr);
								if (saveptr_cpy)
								{
									filter_parser_helper(0, jobj_found, saveptr_cpy, NULL);
									SAFE_FREE(saveptr_cpy);
								}
								break;
							}
						}
					}
					break;
				}
				else if (jtoken)
				{
					jresult = jtoken;
				}
				else
				{
					jresult = NULL;
					break;
				}
			}
			else if (is_array)
			{
				jresult = NULL;
				if (JSON_CHECK_ARY(jparent))
				{
					if (idx_full==0)
					{
						jslicing_root = JSON_ARY_NEW();
					}

					json_t *jobj_found = NULL;
					int idx = 0;

					JSON_ARY_FOREACH(jparent, idx, jobj_found)
					{
						//DBG_DB_LN("(idx: %d)", idx);
						if ((idx_full)
							|| ((idx_b <= idx) && (idx < idx_e)))
						{
							char *saveptr_cpy = NULL;
							//DBG_DB_LN("saveptr: [%s]", saveptr);
							SAFE_ASPRINTF(saveptr_cpy, "%s.", saveptr);
							if (saveptr_cpy)
							{
								filter_parser_helper(0, jobj_found, saveptr_cpy, jslicing_root);
								SAFE_FREE(saveptr_cpy);
							}
						}
						else if ((idx_b == idx) && (idx_e == -1))
						{
							// single
							JSON_FREE(jslicing_root);
							jslicing_root = NULL;

							char *saveptr_cpy = NULL;
							//DBG_DB_LN("saveptr: [%s]", saveptr);
							SAFE_ASPRINTF(saveptr_cpy, "%s.", saveptr);
							if (saveptr_cpy)
							{
								filter_parser_helper(0, jobj_found, saveptr_cpy, NULL);
								SAFE_FREE(saveptr_cpy);
							}
							break;
						}
					}
				}
				break;
			}

			deep ++;
		}
	}

	if (jslicing)
	{
		json_t *jresult_cpy = JSON_COPY(jresult);
		JSON_ARY_APPEND_OBJ(jslicing, jresult_cpy);
	}
	else if (jslicing_root)
	{
		JobjItem_t *jitem = (JobjItem_t*)SAFE_CALLOC(1, sizeof(JobjItem_t));
		jitem->jobj = jslicing_root;
		clist_push(jobjX, jitem);
	}
	else if (jresult)
	{
		JobjItem_t *jitem = (JobjItem_t*)SAFE_CALLOC(1, sizeof(JobjItem_t));
		jitem->jobj = JSON_COPY(jresult);
		clist_push(jobjX, jitem);
	}
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

		qbuf_free(&qbuf_r);

		clist_free_ex(jobjX, jobjx_free_cb);

		SAFE_FREE(filter);
	}
}

static void app_loop(void)
{
	json_t *jroot = JSON_LOADS_EASY_OR_NEW(qbuf_buff(&qbuf_r));

#if (0)
	DBG_WN_LN("%s", qbuf_buff(&qbuf_r));
	DBG_WN_LN("filter: %s", filter);
#else
	int deep = 0;

	char *filter_cpy = NULL;
	SAFE_ASPRINTF(filter_cpy, "%s", filter);

	if (filter_cpy)
	{
		filter_cpy = str_trim_char(filter_cpy, "\"", SAFE_STRLEN("\""));

		char *saveptr = filter_cpy;
		char *filter_sub = NULL;

		while ((filter_sub = SAFE_STRTOK_R(NULL, ",", &saveptr)))
		{
			filter_parser_helper(deep, jroot, filter_sub, NULL);
		}
	}

	jobjx_dump();

	SAFE_FREE(filter_cpy);
#endif

	JSON_FREE(jroot);
}

static int app_init(void)
{
	int ret = 0;

	clist_init(jobjX);

	qbuf_init(&qbuf_r, MAX_OF_QBUF_4MB);
	size_t nread = 0;
	SAFE_IOCTL(0, FIONREAD, &nread);

	DBG_TR_LN("(nread: %zd)", nread);

	if (nread)
	{
		char tmpbuf[LEN_OF_BUF1024] = "";
		while ((nread=SAFE_READ(0, tmpbuf, sizeof(tmpbuf))) > 0)
		{
			qbuf_write(&qbuf_r, tmpbuf, nread);
			SAFE_MEMSET(tmpbuf, 0, sizeof(tmpbuf));
		}
	}

	if (qbuf_total(&qbuf_r) <=0)
	{
		DBG_ER_LN("Please input data !!!");
		app_showusage(-1);
	}

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
			case 'h':
				app_showusage(-1);
				break;
			default:
				SAFE_ASPRINTF(filter, "%s", optarg);
				break;
		}
	}

	if (argc > optind)
	{
		int i = 0;
		//for (i = optind; i < argc; i++)
		for (i = optind; i < optind+1; i++)
		{
			SAFE_ASPRINTF(filter, "%s", argv[i]);
		}
	}

	if (filter==NULL)
	{
		SAFE_ASPRINTF(filter, ".");
	}
}

// echo '{"fruit":{"name":"apple","color":"green","price":1.20}}' | jq '.'
// echo '{"fruit":{"name":"apple","color":"green","price":1.20}}' | jq '.fruit'
// echo '{"fruit":{"name":"apple","color":"green","price":1.20}}' | jq '.fruit.color'
// echo '{ "with space": "hello" }' | jq '."with space"'
// echo '["x","y","z"]' | jq '.[]'
// echo '[{"name":"apple","color":"green","price":1.2},{"name":"banana","color":"yellow","price":0.5},{"name":"kiwi","color":"green","price":1.25}]' | jq '.[].name'
// echo '[{"name":"apple","color":"green","price":1.2},{"name":"banana","color":"yellow","price":0.5},{"name":"kiwi","color":"green","price":1.25}]' | jq '.[1].price'
// echo '[1,2,3,4,5,6,7,8,9,10]' | jq '.[6:9]'
// echo '[1,2,3,4,5,6,7,8,9,10]' | jq '.[:6]'
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

	//DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
