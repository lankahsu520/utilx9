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
#include <sys/sysinfo.h>
#include <libssh/libssh.h>

#define TAG "sshX_123"

static int is_quit = 0;

char whoami[LEN_OF_USER] = "";

SSH_t ssh_data =
{
//.server_ip = "192.168.50.100",
//.server_ip = "localhost",
//.server_ip = "192.168.50.109",

//.server_port = 2222, //22,
//.server_user = "pikachu",
//.server_pass_enc = "Njk2NDEyNzY=",
	.session = NULL,
	.channel = NULL,

	.cols = 80,
	.rows = 24,

	.verbosity = 0,
};

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static int app_quit(void)
{
	return is_quit;
}

static void app_loop(void)
{
	DBG_TR_LN("enter");

	DBG_TR_LN("call ssh_new ...");
	if(sshX_client(&ssh_data) == NULL)
	{
		DBG_ER_LN("ssh_new error !!!");
		return ;
	}

	sshX_interactive(&ssh_data);
	sshX_stop(&ssh_data);
}

static void app_stop(void)
{
	DBG_TR_LN("enter");
	if(app_quit()==0)
	{
		app_set_quit(1);

		sshX_stop(&ssh_data);
	}
}

static void app_free(void)
{

}

static void app_exit(void)
{
	DBG_TR_LN("enter");

	app_stop();

	app_free();
}

static void app_signal_handler(int signum)
{
	switch(signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
			//signal(signum, SIG_DFL);
			break;
		case SIGPIPE:
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
const char* short_options = "i:p:u:s:vh";
static struct option long_options[] =
{
	{ "ip",          required_argument,   NULL,    'i'  },
	{ "port",        required_argument,   NULL,    'p'  },
	{ "user",        required_argument,   NULL,    'u'  },
	{ "pass",        required_argument,   NULL,    's'  },
	{ "verbose",     no_argument,         NULL,    'v'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		   "  -i, --ip          ip\n"
		   "  -p, --port        port\n"
		   "  -u, --user        user\n"
		   "  -s, --pass        pass\n"
		   "  -v, --verbose\n"
		   "  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		   "  %s -i localhost -p 22 -u admin -s hahahaha\n", TAG
		  );
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'i':
				if(optarg)
				{
					SAFE_SPRINTF(ssh_data.server_ip, "%s", optarg);
				}
				break;
			case 'p':
				if(optarg)
				{
					ssh_data.server_port = atoi(optarg);
				}
				break;
			case 'v':
				ssh_data.verbosity = 1;
				break;
			case 'u':
				if(optarg)
				{
					SAFE_SPRINTF(ssh_data.server_user, "%s", optarg);
				}
				break;
			case 's':
				if(optarg)
				{
					SAFE_SPRINTF(ssh_data.server_pass_dec, "%s", optarg);
				}
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

static void app_init(int argc, char **argv)
{
	app_signal_register();
	atexit(app_exit);

	dbg_lvl_set(DBG_LVL_INFO);
	//dbg_lvl_set(DBG_LVL_TRACE);

	SAFE_SNPRINTF(whoami, sizeof(whoami), "%s", sys_username());
	SAFE_SNPRINTF(ssh_data.server_user, sizeof(ssh_data.server_user), "%s", whoami);

	app_ParseArguments(argc, argv);

	if(strlen(ssh_data.server_ip) <= 0)
	{
		app_showusage(-1);
	}
}

int main(int argc, char* argv[])
{
	app_init(argc, argv);

	//if ( ( daemon(0,1) == 0 ) )
	{
		app_loop();
	}

	exit(0);
}
