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

#include "uv_123.h"

#define USE_ASYNC_CREATE
#define USE_TIMER_CREATE
#define USE_THREAD_CREATE
#define USE_QUEUE_CREATE
//#define USE_IDLE_CREATE
//#define USE_FS_CREATE
#define USE_EVENT_CREATE

#define MAX_OF_TEST 1

#define TEST_TXT_FILENAME "/tmp/123.txt"

// ** app **
static int is_quit = 0;
static uv_loop_t *uv_loop = NULL;

#ifdef USE_ASYNC_CREATE
uv_async_t uv_async_fd;
#endif

static int app_quit(void)
{
	return is_quit;
}

#ifdef USE_TIMER_CREATE
uv_timer_t uv_timer_1_fd;
uv_timer_t uv_timer_2_fd;

void timer_1_loop(uv_timer_t *handle)
{
	static int count = 0;
	count++;
	DBG_IF_LN("(count: %d)", count);
	sleep(2); // this will lock loop
	if (count >= MAX_OF_TEST)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_IF_LN("%s", DBG_TXT_BYE_BYE);
	}
}

void timer_2_loop(uv_timer_t *handle)
{
	static int count = 0;
	count++;
	DBG_IF_LN("(count: %d)", count);
	if (count >= MAX_OF_TEST)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_IF_LN("%s", DBG_TXT_BYE_BYE);
	}
}
#endif

#ifdef USE_THREAD_CREATE

uv_thread_t uv_thread_req;

void thread_loop(void *arg)
{
	static int count = 0;
	while (count < 10)
	{
		count++;
		DBG_IF_LN("(count: %d)", count);

#ifdef USE_ASYNC_CREATE
		uv_async_fd.data = (void*) &count;
		SAFE_UV_ASYNC(&uv_async_fd);
#endif

		usleep(100*1000);
	}

#ifdef USE_ASYNC_CREATE
	SAFE_UV_CLOSE(&uv_async_fd, NULL);
#endif

	DBG_IF_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
}
#endif

#ifdef USE_QUEUE_CREATE
#define MAX_OF_QUEUE 10 // libuv can handle 4 at the same time
int work_data[MAX_OF_QUEUE];
uv_work_t uv_work_req[MAX_OF_QUEUE];

void queue_work_finisher(uv_work_t *req, int status)
{
	int id = *((int*) req->data);
	DBG_IF_LN("%s (id: %d, status: %d)", DBG_TXT_BYE_BYE, id, status);
}

void queue_work_handler(uv_work_t *req)
{
	int count = 0;
	while ( (count < MAX_OF_TEST) && (app_quit()==0) )
	{
		count++;
		int id = *((int*) req->data);
		DBG_IF_LN("(id: %d, count: %d)", id, count);

		while ( (id>0) && (app_quit()==0) )
		{
			id --;
		}
	}
}

#endif

#ifdef USE_IDLE_CREATE
uv_idle_t uv_idle_fd;

void idle_loop(uv_idle_t* handle)
{
#if (1)
	DBG_IF_LN("Hello World !!!");
	SAFE_UV_IDLE_STOP(handle);
#else
	static int count = 0;
	count++;
	DBG_IF_LN("(count: %d)", count);
	if (count>=MAX_OF_TEST)
	{
		SAFE_UV_IDLE_STOP(handle);
		DBG_IF_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
#endif
}
#endif

#ifdef USE_FS_CREATE
char filename_r[LEN_OF_FULLNAME] = "/etc/xinetd.conf";

char buffer[LEN_OF_BUF256];
static uv_buf_t buf_req;

uv_fs_t fs_open_r_req;
uv_fs_t fs_open_w_req;
uv_fs_t fs_read_req;
uv_fs_t fs_write_req;

uv_pipe_t pipe_w_fd;

void fs_read_cb(uv_fs_t *req);

void fs_write_cb(uv_fs_t *req)
{
	if (req->result < 0)
	{
		DBG_ER_LN("write error !!! (%s)", uv_strerror(req->result));
	}
	else
	{
		SAFE_UV_FS_READ(uv_loop, &fs_read_req, fs_open_r_req.result, &buf_req, 1, -1, fs_read_cb);
	}
}

static void pipe_w_cb(uv_write_t *req, int status)
{
	UvWriteEx_t *wreq = (UvWriteEx_t *)req;
	DBG_ER_LN("(len: %zd)", wreq->buf.len);
}

void fs_read_cb(uv_fs_t *req)
{
	if (req->result < 0)
	{
		DBG_ER_LN("read error !!! (%s)", uv_strerror(req->result));
	}
	else if (req->result == 0)
	{
		uv_fs_t fs_close_req;

		// synchronous
		SAFE_UV_FS_CLOSE(uv_loop, &fs_close_req, fs_open_r_req.result, NULL);

		// pipe
		SAFE_UV_CLOSE(&pipe_w_fd, NULL);
	}
	else if (req->result > 0)
	{
		ssize_t nread = req->result;

		buf_req.len = nread;
		DBG_ER_LN("(nread: %zd)", nread);

		// display on screen
		SAFE_UV_FS_WRITE(uv_loop, &fs_write_req, 1, &buf_req, 1, -1, fs_write_cb);

		// write data to ...
		uv_write_ex((uv_stream_t *)&pipe_w_fd, nread, buf_req.base, pipe_w_cb);
	}
}

void fs_open_cb(uv_fs_t *req)
{
	if (req->result >= 0)
	{
		buf_req = SAFE_UV_BUF_INIT(buffer, sizeof(buffer));
		SAFE_UV_FS_READ(uv_loop, &fs_read_req, req->result, &buf_req, 1, -1, fs_read_cb);
	}
	else
	{
		DBG_ER_LN("open error !!! (%s)", SAFE_UV_STRERROR((int) req->result));
	}
}

#endif

#ifdef USE_EVENT_CREATE
UvEvent_t fs_event_req =
{
	.name = TAG,
	.filename = TEST_TXT_FILENAME,
	.isquit = 0,
	.flags = UV_FS_EVENT_RECURSIVE,
};

#endif

void app_stop_uv(uv_async_t *handle, int force)
{
	static int is_free = 0;
	if ((is_free==0) && (app_quit()==1))
	{
		is_free = 1;
		if (uv_loop)
		{
#ifdef USE_TIMER_CREATE
			SAFE_UV_TIMER_CLOSE(&uv_timer_1_fd, NULL);
			SAFE_UV_TIMER_CLOSE(&uv_timer_2_fd, NULL);
#endif

#ifdef USE_QUEUE_CREATE
			int i = 0;

			for (i=0; i<MAX_OF_QUEUE; i++)
			{
				DBG_IF_LN("(SAFE_UV_CANCEL: %d)", i);
				SAFE_UV_CANCEL(&uv_work_req[i]);
			}
#endif

#ifdef USE_FS_CREATE
			SAFE_UV_FS_REQ_CLEANUP(&fs_open_r_req);
			SAFE_UV_FS_REQ_CLEANUP(&fs_read_req);
			SAFE_UV_FS_REQ_CLEANUP(&fs_open_w_req);
			SAFE_UV_FS_REQ_CLEANUP(&fs_write_req);
#endif

#ifdef USE_EVENT_CREATE
			uv_event_close_ex(&fs_event_req);
#endif

#ifdef USE_THREAD_CREATE
			SAFE_UV_THREAD_JOIN_EX(&uv_thread_req);
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
	}
}

#ifdef USE_ASYNC_CREATE
uv_async_t uv_async_fd;
int async_count = 0;

void async_loop(uv_async_t *handle)
{
	int percentage = *((int*) handle->data);

	DBG_IF_LN("(percentage: %d)", percentage);

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
	SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_1_fd);
	SAFE_UV_TIMER_START(&uv_timer_1_fd, timer_1_loop, 1000, 3000); // 1st: 1, 2nd: 1+3, 3rd: 1+3+3, 4th: 1+3+3+3 .....
	// please use the another callback function.
	SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_2_fd);
	SAFE_UV_TIMER_START(&uv_timer_2_fd, timer_2_loop, 3000, 1000); // 1st: 3, 2nd: 3+1, 3rd: 3+1+1, 4th: 3+1+1+1 .....
#endif

#ifdef USE_THREAD_CREATE
	SAFE_UV_THREAD_CREATE(&uv_thread_req, thread_loop, NULL);
#endif

#ifdef USE_QUEUE_CREATE
	int i = 0;

	for (i=0; i<MAX_OF_QUEUE; i++)
	{
		work_data[i] = i+1;
		uv_work_req[i].data = (void *) &work_data[i];
		SAFE_UV_QUEUE_WORK(uv_loop, &uv_work_req[i], queue_work_handler, queue_work_finisher);
	}
#endif

#ifdef USE_IDLE_CREATE
	SAFE_UV_IDLE_INIT(uv_loop, &uv_idle_fd);
	SAFE_UV_IDLE_START(&uv_idle_fd, idle_loop);
#endif

#ifdef USE_FS_CREATE
	// asynchronous and write to pipe
	int fd = SAFE_UV_FS_OPEN(uv_loop, &fs_open_w_req, TEST_TXT_FILENAME, O_CREAT|O_WRONLY, 0666, NULL);
	if (fd >=0)
	{
		SAFE_UV_PIPE_INIT(uv_loop, &pipe_w_fd, 0);
		SAFE_UV_PIPE_OPEN(&pipe_w_fd, fd);
	}

	// synchronous and read
	DBG_ER_LN("(filename_r: %s)", filename_r);
	if (strlen(filename_r) > 0)
	{
		SAFE_UV_FS_OPEN(uv_loop, &fs_open_r_req, filename_r, O_RDONLY, 0, fs_open_cb);
	}
#endif

#ifdef USE_EVENT_CREATE
	fs_event_req.loop = uv_loop;
	uv_event_open_ex(&fs_event_req);
#endif

	SAFE_UV_LOOP_RUN(uv_loop);
	//SAFE_UV_LOOP_CLOSE(uv_loop);
	SAFE_UV_LOOP_CLOSE_VALGRIND(uv_loop);

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
const char* short_options = "d:f:h";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
#ifdef USE_FS_CREATE
	{ "file",        required_argument,   NULL,    'f'  },
#endif
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		"  -d, --debug       debug level\n"
#ifdef USE_FS_CREATE
		"  -f, --file        filename_r\n"
#endif
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
#ifdef USE_FS_CREATE
			case 'f':
				if (optarg)
				{
					SAFE_SPRINTF_EX(filename_r, "%s", optarg);
				}
				break;
#endif
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
