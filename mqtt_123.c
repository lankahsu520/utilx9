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
#define USE_MQTT_DEMO

#define TAG "mqtt_123"

// ** app **
static int is_quit = 0;

char mqtt_cert_path[LEN_OF_DIRNAME] = "/work/IoT/mqtt/common";

#ifdef USE_UV
#define USE_ASYNC_CREATE
#define USE_TIMER_CREATE
static uv_loop_t *uv_loop = NULL;
uv_async_t uv_async_fd;

uv_timer_t uv_timer_1sec_fd;
#endif

char iface_dev[LEN_OF_NAME_DEV] = "eth0";
char iface_mac[LEN_OF_MAC]= "9C65F9361C00";

#ifdef USE_MQTT_DEMO
static void mqtt123_connect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	MQTTSession_t *session = (MQTTSession_t *)userdata;

	DBG_IF_LN("(%s:%d, result: %d)", session->hostname, session->port, result);
}

static void mqtt123_disconnect_cb(struct mosquitto *mosq, void *userdata, int result)
{
	MQTTSession_t *session = (MQTTSession_t *)userdata;

	DBG_IF_LN("(%s:%d, result: %d)", session->hostname, session->port, result);
}

static void mqtt123_root_subscribe_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	MQTTSession_t *session = (MQTTSession_t *)userdata;

	DBG_IF_LN("(%s:%d, topic: %s, [%d]%s)", session->hostname, session->port, message->topic, message->payloadlen, (char*) message->payload);
}

static MQTTSession_t mqtt123_session = {
	.hostname = "192.168.50.9",
	.port = 1883,
	.keepalive = 60,
	//.topic = "9C65F9361C00/#",
	.topic_root = MQTT_TOPIC_SUB_ROOT_MASK,
	.topic_id = MQTT_TOPIC_ID_USER,

	.clean_session = true,
	.user=JVAL_C_USERNAME_BROADCAST,
	.pass="guest",

	.tls_version = "tlsv1.2",
	.certificate_file = "/work/IoT/mqtt/common/mqtt_beex.crt",
	.privatekey_file = "/work/IoT/mqtt/common/mqtt_beex.key",
	.ca_file = "/work/IoT/mqtt/common/mqtt.ca",
	.isconnect = 0,

	.log_cb = NULL,
	.connect_cb = mqtt123_connect_cb,
	.disconnect_cb = mqtt123_disconnect_cb,

	.root_subscribe_cb = mqtt123_root_subscribe_cb,
};

MQTTX_t mqtt123_data = {
	.name = "mqtt123_data",

	.isfree = 0,
	.isinit = 0,
	.dbg_more = DBG_LVL_MAX,

	.session = &mqtt123_session,
};

static void mqtt123_init(MQTTX_t *mqtt_req)
{
	MQTTSession_t *session = mqtt_session_get(mqtt_req);

	if (session->topic_id == MQTT_TOPIC_ID_USER)
	{
		SAFE_SPRINTF_EX(session->topic_root, MQTT_TOPIC_SUB_ROOT_MASK, session->user, "/");
	}
	else
	{
		SAFE_SPRINTF_EX(session->topic_root, MQTT_TOPIC_SUB_ROOT_MASK, "", "");
	}
	mqtt_thread_init( mqtt_req );
}

#endif

static int app_quit(void)
{
	return is_quit;
}

#ifdef USE_UV
#ifdef USE_TIMER_CREATE
void timer_1sec_loop(uv_timer_t *handle)
{
	int count = 0;
	count ++;

	//DBG_TR_LN(DBG_TXT_ENTER);
	//SAFE_UV_ASYNC(&uv_async_fd);

	if (app_quit()==1)
	{
		//SAFE_UV_TIMER_STOP(handle);
		SAFE_UV_TIMER_CLOSE(handle, NULL);
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
	else
	{
		char topic[LEN_OF_TOPIC] = "";

		char c_uuid[LEN_OF_UUID]="CCC3F3BB";
		int nodeid = 2;
		int epid = 0;
		int issueid = JKEY_ISSUEID_MOTION;

		if (mqtt123_session.topic_id == MQTT_TOPIC_ID_USER)
		{
			SAFE_SPRINTF_EX(topic, MQTT_TOPIC_SUB_ROOT_MASK_METHODID_MACID_NODEID_EPID_ISSUEID, mqtt123_session.user, "/", JVAL_METHODID_EVENT, iface_mac, c_uuid, nodeid, epid, issueid);
		}
		else
		{
			SAFE_SPRINTF_EX(topic, MQTT_TOPIC_SUB_ROOT_MASK_METHODID_MACID_NODEID_EPID_ISSUEID, "", "", JVAL_METHODID_EVENT, iface_mac, c_uuid, nodeid, epid, issueid);
		}
		//mqtt_publish(mqtt123_data.session, "0/0/9C65F9361C00/CCC3F3BB/2/0/0001000C", "{\"name\":\"Motion Sensor\",\"val\":\"idle\"}");
		//mqtt_qpub_add(mqtt123_data.session, "0/0/9C65F9361C00/CCC3F3BB/2/0/0001000C", "{\"name\":\"Motion Sensor\",\"val\":\"idle\"}", NULL);
		mqtt_qpub_add(mqtt123_data.session, topic, "{\"name\":\"Motion Sensor\",\"val\":\"idle\"}", NULL);
	}
}
#endif

void app_stop_uv(uv_async_t *handle, int force)
{
	static int is_free = 0;
	if ( (is_free==0) && (app_quit()==1) )
	{
		is_free = 1;
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
	}
}

#ifdef USE_ASYNC_CREATE
void async_loop(uv_async_t *handle)
{
	DBG_IF_LN(DBG_TXT_ENTER);

	app_stop_uv(handle, 0);
}
#endif

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

#ifdef USE_MQTT_DEMO
		{
			mqtt_thread_stop(&mqtt123_data);
			mqtt_thread_close(&mqtt123_data);
		}
#endif

#ifdef USE_UV
#ifdef USE_ASYNC_CREATE
		SAFE_UV_ASYNC(&uv_async_fd);
#else
#error "Please use USE_ASYNC_CREATE !!!"
		app_stop_uv(NULL, 1);
#endif
#endif
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, TAG);
	}
}

static void app_loop(void)
{
#ifdef USE_MQTT_DEMO
	{
		SAFE_SPRINTF(mqtt123_session.certificate_file, "%s/mqtt_beex.crt", mqtt_cert_path);
		SAFE_SPRINTF(mqtt123_session.privatekey_file, "%s/mqtt_beex.key", mqtt_cert_path);
		SAFE_SPRINTF(mqtt123_session.ca_file, "%s/mqtt.ca", mqtt_cert_path);

		mqtt123_init(&mqtt123_data);
	}
#endif

#ifdef USE_UV
	{
		SAFE_UV_LOOP_INIT(uv_loop);

#ifdef USE_ASYNC_CREATE
		SAFE_UV_ASYNC_INIT(uv_loop, &uv_async_fd, async_loop);
#endif

#ifdef USE_TIMER_CREATE
		SAFE_UV_TIMER_INIT(uv_loop, &uv_timer_1sec_fd);
		SAFE_UV_TIMER_START(&uv_timer_1sec_fd, timer_1sec_loop, 1000, 1000); // 1st: 1, 2nd: 1+1, 3rd: 1+1+1, 4th: 1+1+1+1 .....
#endif

		SAFE_UV_LOOP_RUN(uv_loop);
		SAFE_UV_LOOP_CLOSE(uv_loop);
	}
#else
	while ( app_quit()==0 )
	{
		sleep(1);
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
const char* short_options = "d:f:p:i:u:w:c:h";
static struct option long_options[] =
{
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "host",        required_argument,   NULL,    'f'  },
	{ "port",        required_argument,   NULL,    'p'  },
	{ "iface",       required_argument,   NULL,    'i'  },

	{ "user",        required_argument,   NULL,    'u'  },
	{ "pass",        required_argument,   NULL,    'w'  },

	{ "certpath",    required_argument,   NULL,    'c'  },

	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf( "Usage: %s\n"
					"  -d, --debug       debug level\n"
					"  -f, --host        hostname\n"
					"  -p, --port        port\n"
					"  -i, --iface       iface\n"
					"  -u, --user        user\n"
					"  -w, --pass        pass\n"
					"  -c, --certpath    certpath\n"
					"  -h, --help\n", TAG);
	printf( "Version: %s\n", version_show());
	printf( "Example:\n"
					"  %s -d 2 -f 192.168.50.9 -p 1883\n", TAG);
	exit(exit_code);
}

static void app_ParseArguments(int argc, char **argv)
{
	int opt;

	MQTTSession_t *session = mqtt_session_get(&mqtt123_data);

	while((opt = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'f':
#ifdef USE_MQTT_DEMO
				if (optarg)
				{
					SAFE_SPRINTF_EX(session->hostname, "%s", optarg);
				}
#endif
				break;
			case 'p':
#ifdef USE_MQTT_DEMO
				if (optarg)
				{
					session->port = atoi(optarg);
				}
#endif
				break;
			case 'i':
				if (optarg)
				{
					SAFE_SPRINTF_EX(iface_dev, "%s", optarg);
				}
				break;
			case 'd':
				if (optarg)
				{
					dbg_lvl_set(atoi(optarg));
				}
				break;
			case 'u':
#ifdef USE_MQTT_DEMO
				if (optarg)
				{
					SAFE_SPRINTF_EX(session->user, "%s", optarg);
				}
#endif
				break;
			case 'w':
#ifdef USE_MQTT_DEMO
				if (optarg)
				{
					SAFE_SPRINTF_EX(session->pass, "%s", optarg);
				}
#endif
				break;
			case 'c':
				SAFE_SPRINTF_EX(mqtt_cert_path, "%s", optarg);
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

	SAFE_STDOUT_NONE();
	if ( app_init() == -1 )
	{
		return -1;
	}

	app_loop();

	DBG_WN_LN(DBG_TXT_BYE_BYE);
	return 0;
}
