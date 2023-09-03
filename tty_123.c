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

#define TAG "tty_123"

// ** app **
static int is_quit = 0;

ChainX_t chainX_T =
{
	.mode = CHAINX_MODE_ID_TTY,
	.ttyfd = -1,

	.status = 0,
	.isfree = 0,

	.security = 0,
	.noblock = 1,

	.retry_hold = TIMEOUT_OF_RETRY_HOLD,
	.select_wait = TIMEOUT_OF_SELECT_1,
	.c_data = NULL,

	.ttyinfo.speed = 57600,
	.ttyinfo.parity = 'n',
	.ttyinfo.databits = 8,
	.ttyinfo.stopbits = 1,
};

static int app_quit(void)
{
	return is_quit;
}

#ifdef UTIL_EX_TTY
static void tty_response(ChainX_t *chainX_req, char *buff, int buff_len)
{
	if((chainX_req) && (buff))
	{
#if (1)
		DBG_IF_LN("(buff: %s, buff_len: %d)", buff, buff_len);
#else
		QBUF_t *qbuf = (QBUF_t *)chainX_req->c_data;

		if(qbuf)
		{
			char *breakptr = NULL;

			qbuf_write(qbuf, buff, buff_len);
			//DBG_IF_LN(">>>>>>>>>>>>%s, %d, %02x", buff, buff_len, buff[buff_len-1]);
			if((breakptr = qbuf_memchr(qbuf, COMMAND_DELIMITED_NEWLINE, NULL)) ||
					(breakptr = qbuf_memchr(qbuf, COMMAND_DELIMITED_RETURN, NULL)) ||
					(breakptr = qbuf_memchr(qbuf, COMMAND_DELIMITED_NULL, NULL))
			  )
			{
				char *startptr = qbuf_buff(qbuf);
				int cmdline_len = (int)(breakptr - startptr) + 1;

				//DBG_IF_LN("(linelen: %d, startptr: %s)", linelen, startptr);
				char *cmdline = NULL;
				if((cmdline_len>0) && (cmdline = SAFE_CALLOC(1, cmdline_len+1)))
				{
					SAFE_SNPRINTF(cmdline, cmdline_len, "%s", startptr);
					if(strlen(cmdline) > 0)
					{
						SOCKETX_WRITE(chainX_req, cmdline, cmdline_len);
						DBG_IF_LN("(cmdline: %s)", cmdline);
					}
				}
				SAFE_FREE(cmdline);

				qbuf_read(qbuf, NULL, cmdline_len + 1 - 1);
			}
		}
#endif
	}
}

static void tty_linked(ChainX_t *chainX_req)
{
	if(chainX_linked_check(chainX_req)==0)
	{
		DBG_IF_LN("%s (ttyname: %s)", DBG_TXT_LINKED, chainX_req->ttyinfo.ttyname);
	}
	else
	{
		DBG_IF_LN("%s (%s, ttyname: %s)", DBG_TXT_BYE_BYE, TAG, chainX_req->ttyinfo.ttyname);
	}
}

static int tty_init(void)
{
	int ret = -1;
	chainX_serial_register(&chainX_T, tty_response);
	chainX_linked_register(&chainX_T, tty_linked);

	if(chainX_thread_init(&chainX_T)==-1)
	{
		return ret;
	}

	while(app_quit() == 0)
	{
		char buff[LEN_OF_VAL32]="";
		//SAFE_SPRINTF_EX(buff, "%03d\r\n", i++);
		SAFE_SPRINTF_EX(buff, "AT\r\n");
		DBG_IF_LN("(buff: %s, %zd)", buff, strlen(buff));
		SOCKETX_WRITE(&chainX_T, buff, strlen(buff));
		sleep(5);
	}
	ret =0;

	return ret;
}
#endif

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static void app_stop(void)
{
	if(app_quit()==0)
	{
		app_set_quit(1);


#ifdef UTIL_EX_TTY
		chainX_thread_stop(&chainX_T);
		chainX_thread_close(&chainX_T);
#endif
	}
}
static void app_showusage(int exit_code);

static void app_loop(void)
{
#ifdef UTIL_EX_TTY
	if(tty_init() == -1)
	{
		app_showusage(-1);
		goto exit_loop;
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
	switch(signum)
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
const char* short_options = "d:t:b:h";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "tty",         required_argument,   NULL,    't'  },
	{ "baudrate",    required_argument,   NULL,    'b'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		   "  -d, --debug       debug level\n"
		   "  -t, --tty         tty name\n"
		   "  -b, --baudrate    baud rate\n"
		   "  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		   "  %s -t /dev/ttyS0 -b 57600n8\n", TAG);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'd':
				if(optarg)
				{
					dbg_lvl_set(atoi(optarg));
				}
				break;
			case 't':
				if(optarg)
				{
#ifdef UTIL_EX_TTY
					chainX_tty_setname(&chainX_T, optarg);
#endif
				}
				break;
			case 'b':
				if(optarg)
				{
#ifdef UTIL_EX_TTY
					int baudrate = 57600;
					char parity='n';
					int databits = 8;
					SAFE_SSCANF(optarg, "%d%c%d", &baudrate, &parity, &databits);
					DBG_IF_LN("(baudrate: %d, parity: %c, databits: %d)", baudrate, parity, databits);
					chainX_tty_setbaudrate(&chainX_T, baudrate);
					chainX_tty_setparity(&chainX_T, parity);
					chainX_tty_setdatabits(&chainX_T, databits);
#endif
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
	//dbg_lvl_set(DBG_LVL_DEBUG);

	if(app_init() == -1)
	{
		return -1;
	}

	app_loop();

	return 0;
}
