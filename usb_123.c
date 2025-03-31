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

#define TAG "usb_123"

// ** app **
static int is_quit = 0;

#if (0) // ID 0658:0200 Sigma Designs, Inc. Aeotec Z-Stick Gen5 (ZW090) - UZB
#define VENDOR_ID 0x0658
#define PRODUCT_ID 0x0200
#endif

#if (0) //yokis
#define VENDOR_ID 0x1072
#define PRODUCT_ID 0x0100
#endif

#if (0) //any
#define VENDOR_ID LIBUSB_HOTPLUG_MATCH_ANY
#define PRODUCT_ID LIBUSB_HOTPLUG_MATCH_ANY
#endif

#if (1) // ID 10C4:8468 Tiqiaa
#define VENDOR_ID 0x10C4
#define PRODUCT_ID 0x8468
#endif

int usb_hotplug_cb(struct libusb_context *ctx, struct libusb_device *usb_dev, libusb_hotplug_event event, void *user_data);

UsbX_t usbx_main =
{
	.usb_req= NULL,
	.usb_dev_handle = NULL,
	.usb_cnt = -1,

	.vendor_id = VENDOR_ID,
	.product_id = PRODUCT_ID,

	.usb_hotplug_handle = -1,
	.usb_hotplug_fn = usb_hotplug_cb,

	.usb_reset = 0,

	.usb_iface_idx = 0,
	.usb_claim = -1,
	.usb_endpoint = 1,
	.bmAttributes = 0x03,
	.wMaxPacketSize = 0x40,

	.res_size = 0,
	.req_size = 0,
	.usb_timeout = 2000,

	.dbg_lvl = LIBUSB_LOG_LEVEL_INFO,
	//.dbg_lvl = LIBUSB_LOG_LEVEL_DEBUG,
};

static void LIBUSB_CALL usb_read_cb(struct libusb_transfer *transfer)
{
	DBG_WN_LN(">>>>> (status: %d-%s, type: %c, timeout: %d)", transfer->status, libusb_error_name(transfer->status), transfer->type, transfer->timeout);
}

int usb_hotplug_cb(struct libusb_context *ctx, struct libusb_device *usb_dev, libusb_hotplug_event event, void *user_data)
{
	UsbX_t *usbX_req = (UsbX_t *)user_data;

	DBG_WN_LN("(event: %d)", event);
	switch (event)
	{
		case LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED:
			DBG_WN_LN("LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED");
			usbX_dev_open(usbX_req, usb_dev);
			usbX_dev_print_ex(usbX_req);

			usbX_dev_read_poll(&usbx_main, usb_read_cb);
			break;
		case LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT:
		default:
			DBG_WN_LN("LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT");
			usbX_req->usb_claim = -1;
			usbX_dev_close(usbX_req);
			break;
	}

	return 0;
}

void request_version(UsbX_t *usbX_req)
{
	int idx = 0;
	unsigned char *request = usbX_req->request;

	request[idx++] = 0x00; // USB frame - Data size
	request[idx++] = 0x55; // Start
	request[idx++] = 0x80; // Message Type (LSB)
	request[idx++] = 0xFF; // Message Type (MSB)
	request[idx++] = 0x01; // Data Length (LSB)
	request[idx++] = 0x00; // Data Length (MSB)
	request[idx++] = 0x01; // Version request
	uint8_t crc = buff_crc8_xor(NULL, (uint8_t *)request+1, idx);
	request[idx++] = crc;

	DBG_DB_LN("(crc: %u - 0x%02X)", crc, crc);
	request[0] = idx-1;
	DBG_IF_DUMP(request, idx, " ", "usb_buff:");
}

#include <linux/netlink.h>

void usb_hotplug_loop(void)
{
	//int sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
	int sockfd = socket(PF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);

	if (sockfd >= 0)
	{
		char buff[LEN_OF_BUF1024];
		int buff_len = sizeof(buff);
		struct sockaddr_nl socknl;

		{
			SAFE_MEMSET(&socknl, 0, sizeof(socknl));
			socknl.nl_pad = 0;
			//socknl.nl_family = AF_NETLINK;
			socknl.nl_family = PF_NETLINK;
			socknl.nl_pid = getpid();
			socknl.nl_groups = 1; /* receive broadcast message*/
		}
		{
			SAFE_SSETOPT(sockfd, SOL_SOCKET, SO_RCVBUF, &buff_len, sizeof(buff_len));
		}

		if (SAFE_BIND(sockfd, (struct sockaddr *)&socknl, sizeof(socknl))  >= 0)
		{
			fd_set fdrset;
			while (1)
			{
				struct timeval tv;
				tv.tv_sec = 0;
				tv.tv_usec = 100 * 1000;

				//SAFE_FD_ZERO(&fdrset);
				//SAFE_FD_SET(sockfd, &fdrset);
				SAFE_FD_SET_EX(sockfd, &fdrset);
				int result = SAFE_SELECT(sockfd + 1, &fdrset, NULL, NULL, &tv);

				if (result == -1)
				{
					DBG_ER_LN("select error !!! (result: %d, errno: %d %s)", result, errno, strerror(errno));
				}
				else if (result==0)
				{
					// no isset
				}
				else if (SAFE_FD_ISSET(sockfd, &fdrset))
				{
					int read_len = recv(sockfd, &buff, sizeof(buff), 0);
					if (read_len > 0)
					{
						if (((SAFE_STRNCMP(buff, "remove@", SAFE_STRLEN("remove@")) == 0) || (SAFE_STRNCMP(buff, "add@", SAFE_STRLEN("add@")) == 0))
							&& (SAFE_STRSTR(buff, "usb"))
						)
						{
							DBG_IF_LN("%s", buff);
						}
					}
				}
			}
		}

		SAFE_SCLOSE(sockfd);
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

		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
}

static void app_loop(void)
{
#if (1)
	if (usbX_listen_open(&usbx_main, NULL) >= 0)
	{
		usbX_dev_print_ex(&usbx_main);

		while ( app_quit() == 0 )
		{
			sleep(1);
		}
		//int nwrite = 0;
		//usbX_dev_write(&usbx_main, &nwrite, 2000);
		//usbX_dev_read(&usbx_main, 2000);
	}

	usbX_dev_close(&usbx_main);
	usbX_listen_close(&usbx_main);
#else
	usb_hotplug_loop();
#endif

	goto exit_loop;

exit_loop:
	app_stop();
}

static int app_init(void)
{
	int ret = 0;

	//dbg_lvl_set(DBG_LVL_DEBUG);
	if (dbg_lvl_get() == DBG_LVL_TRACE)
	{
		if (putenv("LIBUSB_DEBUG=4") != 0)	// LIBUSB_LOG_LEVEL_DEBUG
			printf("Unable to set debug level");
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
	signal(SIGINT, app_signal_handler );
	signal(SIGTERM, app_signal_handler );
	signal(SIGHUP, app_signal_handler );
	signal(SIGUSR1, app_signal_handler );
	signal(SIGUSR2, app_signal_handler );

	signal(SIGPIPE, SIG_IGN );
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
	printf( "Usage: %s\n"
					"  -d, --debug       debug level\n"
					"  -h, --help\n", TAG);
	printf( "Version: %s\n", version_show());
	printf( "Example:\n"
					"  %s -d 2\n", TAG);
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

// sudo usb_123 -d 2
int main(int argc, char* argv[])
{
	app_ParseArguments(argc, argv);
	app_signal_register();
	atexit(app_exit);

	SAFE_STDOUT_NONE();
	if ( app_init() == -1 )
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
