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

#define USE_UV
#ifdef USE_UV
#define USE_ASYNC_CREATE
#define USE_TIMER_CREATE
#endif

#define TAG "mqtt_123"

// ** app **
static int is_quit = 0;

static uv_loop_t *uv_loop = NULL;

char iface_mac[LEN_OF_MAC]= "9C65F9361C00";

#ifdef USE_ASYNC_CREATE
uv_async_t uv_async_fd;
#endif

static void hornet_message_put_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	MQTTSession *session = (MQTTSession *)userdata;

	DBG_IF_LN("(%s:%d, topic: %s, [%d]%s)", session->hostname, session->port, message->topic, message->payloadlen, (char*) message->payload);
}

static void hornet_message_event_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	MQTTSession *session = (MQTTSession *)userdata;

	DBG_IF_LN("(%s:%d, topic: %s, [%d]%s)", session->hostname, session->port, message->topic, message->payloadlen, (char*) message->payload);
}

static void hornet_connect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	MQTTSession *session = (MQTTSession *)userdata;

	DBG_IF_LN("(%s:%d, result: %d)", session->hostname, session->port, result);

	char topic[LEN_OF_TOPIC] = "";
	SAFE_SPRINTF(topic, MQTT_TOPIC_SUB_ROOT_MASK_METHODID, JVAL_METHODID_EVENT, iface_mac);
	mqtt_subscribe_add(session, topic, hornet_message_event_cb);

	SAFE_SPRINTF(topic, MQTT_TOPIC_SUB_ROOT_MASK_METHODID, JVAL_METHODID_PUT, iface_mac);
	mqtt_subscribe_add(session, topic, hornet_message_put_cb);

	SAFE_SPRINTF(topic, MQTT_TOPIC_SUB_ROOT_MASK_METHODID, JVAL_METHODID_GET, iface_mac);
	mqtt_subscribe_add(session, topic, hornet_message_put_cb);
}

static void hornet_disconnect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	MQTTSession *session = (MQTTSession *)userdata;

	DBG_IF_LN("(%s:%d, result: %d)", session->hostname, session->port, result);
}

static void hornet_message_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
}

static MQTTSession hornet_session = {
	.hostname = "192.168.50.9",
	.port = 1883,
	.keepalive = 60,
	//.topic = "9C65F9361C00/#",
	.topic = "",

	.clean_session = true,
	.isconnect = 0,

	.log_cb = NULL,
	.connect_cb = hornet_connect_cb,
	.disconnect_cb = hornet_disconnect_cb,
	.message_cb = hornet_message_cb,
};

MQTTCtx_t hornet_data = {
	.name = "hornet_data",
	.isinit = 0,
	.isquit = 0,

	.dbg_more = DBG_LVL_MAX,
	.session = &hornet_session,

};

static void hornet_init(void)
{
	SAFE_SPRINTF(hornet_session.topic, "%s/#", iface_mac);
	//DBG_ER_LN(">>>>>>>>>>>>>> %s", hornet_session.topic);
	mqtt_thread_init( &hornet_data );
}

#ifdef USE_TIMER_CREATE
uv_timer_t uv_timer_1sec_fd;
void timer_1sec_loop(uv_timer_t *handle)
{
	//DBG_TR_LN(DBG_TXT_ENTER);
	//SAFE_UV_ASYNC(&uv_async_fd);

	char topic[LEN_OF_TOPIC] = "";

	char c_uuid[LEN_OF_UUID]="CCC3F3BB";
	int nodeid = 2;
	int epid = 0;
	int issueid = JKEY_ISSUEID_MOTION;
	SAFE_SPRINTF(topic, MQTT_TOPIC_PUB_ROOT_MASK, JVAL_METHODID_EVENT, JVAL_PROTOCOLID_ZWAVES2, iface_mac, c_uuid, nodeid, epid, issueid);
	//mqtt_publish(hornet_data.session, "0/0/9C65F9361C00/CCC3F3BB/2/0/0001000C", "{\"name\":\"Motion Sensor\",\"val\":\"idle\"}");
	//mqtt_qpub_add(hornet_data.session, "0/0/9C65F9361C00/CCC3F3BB/2/0/0001000C", "{\"name\":\"Motion Sensor\",\"val\":\"idle\"}");
	mqtt_qpub_add(hornet_data.session, topic, "{\"name\":\"Motion Sensor\",\"val\":\"idle\"}");
}
#endif

static int app_quit(void)
{
	return is_quit;
}

void app_stop_uv(uv_async_t *handle, int force)
{
	static int is_free = 0;
	if ( (is_free==0) && (app_quit()==1) )
	{
		is_free = 1;
#ifdef USE_UV
		if (uv_loop)
		{
#ifdef USE_TIMER_CREATE
			SAFE_UV_TIMER_CLOSE(&uv_timer_1sec_fd, NULL);
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
#endif
	}
}

#ifdef USE_ASYNC_CREATE
//uv_async_t uv_async_fd;
int async_count = 0;

void async_loop(uv_async_t *handle)
{
	DBG_IF_LN(DBG_TXT_ENTER);

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

		mqtt_thread_stop(&hornet_data);
		mqtt_thread_close(&hornet_data);

#ifdef USE_ASYNC_CREATE
		SAFE_UV_ASYNC(&uv_async_fd);
#else
		app_stop_uv(NULL, 1);
#endif
	}
}

static void app_loop(void)
{
#ifdef USE_UV
	SAFE_UV_LOOP_INIT(uv_loop);

#ifdef USE_ASYNC_CREATE
	uv_async_fd.data = (void *) &async_count;
	SAFE_UV_ASYNC_INIT(uv_loop, &uv_async_fd, async_loop);
#endif

#ifdef USE_TIMER_CREATE
	SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_1sec_fd);
	SAFE_UV_TIMER_START(&uv_timer_1sec_fd, timer_1sec_loop, 1000, 1000); // 1st: 1, 2nd: 1+1, 3rd: 1+1+1, 4th: 1+1+1+1 .....
#endif
#endif

	hornet_init();

#ifdef USE_UV
	SAFE_UV_LOOP_RUN(uv_loop);
	SAFE_UV_LOOP_CLOSE(uv_loop);
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
					"  %s -d 4\n", TAG);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	while((opt = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1)
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

// ./mqtt_123
int main(int argc, char *argv[])
{
	app_ParseArguments(argc, argv);
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
