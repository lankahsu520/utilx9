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

#define TAG "queuex_123"

#define MAX_OF_QTEST 30
QueueX_t *test_q;

typedef struct TestX_Struct
{
	int idx;
} TestX_t;

int idx = 0;

static int test_q_exec_cb(void *arg)
{
	TestX_t *data_pop = (TestX_t *)arg;

	if ( (data_pop) )
	{
		DBG_IF_LN("(data_pop->idx: %d)", data_pop->idx);
		idx--;
	}

	return 0;
}


static int test_q_free_cb(void *arg)
{
	TestX_t *data_pop = (TestX_t *)arg;

	if (data_pop)
	{
	}

	return 0;
}

void test_push(int idx)
{
	TestX_t data_new = { .idx = 0 };

	data_new.idx = idx;
	queuex_push(test_q, (void*)&data_new);
}

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

static void app_loop(void)
{

	test_q = queuex_thread_init("test", MAX_OF_QTEST, sizeof(TestX_t), test_q_exec_cb, test_q_free_cb);

	test_q->dbg_more = DBG_LVL_INFO;
	queuex_isready(test_q, 5);

	while ( ( idx < 5 ) && (is_quit==0) )
	{
#if (0)
		idx++;
		DBG_IF_LN("(idx: %d)", idx);
		sleep(1);
#else
		test_push(idx++);
#endif
	}

	while (idx>0)
	{
		sleep(1);
	}

	{
		queuex_thread_stop(test_q);
		queuex_thread_close(test_q);
	}

	exit(0);
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

int main(int argc, char* argv[])
{
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
