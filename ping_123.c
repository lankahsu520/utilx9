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

#define TAG "ping_123"

ChainX_t chainX_i =
{
	.mode = CHAINX_MODE_ID_PING,
	.sockfd = -1,

	//.netinfo.addr.ipv4="8.8.8.8",
	//.netinfo.addr.ipv4="192.168.50.1",
	.netinfo.port = 0,
	.isfree = 0,

	.recycle = 1,
	.retry_hold = 0,
	.select_wait = 0,
	.verbose = 1,
};

int option_index = 0;
const char* short_options = "i:c:vh";
static struct option long_options[] =
{
	{ "interval",    required_argument,   NULL,    'i'  },
	{ "count",       required_argument,   NULL,    'c'  },
	{ "verbose",     no_argument,         NULL,    'v'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		   "  -i, --interval    interval\n"
		   "  -c, --count       count\n"
		   "  -v, --verbose     verbose\n"
		   "  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		   "  ping_123 -i 1 -c 3 google.com\n"
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
			case 'c':
				if (optarg)
				{
					chainX_recycle_set(&chainX_i, atoi(optarg));
				}
				break;
			case 'i':
				if (optarg)
				{
					chainX_i.select_wait = atoi(optarg);
				}
				break;
			case 'v':
				chainX_i.verbose = 1;
				break;
			default:
				app_showusage(-1);
				break;
		}
	}

	if (argc > optind)
	{
		int i = 0;
		//for (i = optind; i < argc; i++)
		for (i = optind; i < optind+1; i++)
		{
			chainX_hostname_set(&chainX_i, argv[i]);
		}
	}
}

int main(int argc, char* argv[])
{
	app_ParseArguments(argc, argv);

	if ((strlen(chainX_ip_get(&chainX_i)) > 0) ||
			(strlen(chainX_hostname_get(&chainX_i)) > 0))
	{
		int count = chainX_ping(&chainX_i);
		DBG_IF_LN("(count: %d/%d)", count, chainX_i.recycle);
	}
	else
	{
		app_showusage(-1);
	}

	exit(0);
}
