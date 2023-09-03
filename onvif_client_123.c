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

#define TAG "onvif_client"

//#define USE_DAEMON
#define MAX_OF_TASK 20

char *snapshot_prefixname = "snapshot";;
char *video_filename = "video.h264";

#if (1)
//static int srv_port = 1018;
//static char srv_ip[LEN_OF_IP] = "192.168.50.170";

static int srv_port = 80;
static char srv_ip[LEN_OF_IP] = "192.168.50.21";
static char srv_user[LEN_OF_USER]="";
static char srv_pass[LEN_OF_PASS]="";

static int http_auth = 0;

char device_url[LEN_OF_URL_ONVIF]="http://192.168.50.21/onvif/device_service";
char media_url[LEN_OF_URL_ONVIF]="http://192.168.50.21/onvif/media_service";

char device_url_path[LEN_OF_URL_PATH]="/onvif/device_service";
char media_url_path[LEN_OF_URL_PATH]="/onvif/media_service";

#else
static int srv_port = 80;
static char srv_ip[LEN_OF_IP] = "192.168.50.182";
static char srv_user[LEN_OF_USER]="admin";
static char srv_pass[LEN_OF_PASS]="admin";

char device_url[LEN_OF_URL_ONVIF]="http://192.168.50.238/onvif/device_service";
char media_url[LEN_OF_URL_ONVIF]="http://192.168.50.238/onvif/media_service";
#endif

char profile_token[LEN_OF_VAL32] ="profile1";
// "Profile00Token"

typedef struct TaskInfo_Struct
{
	unsigned short gid;
	int32_t cid;

	SOAP_ACTION_ID id;
	char cmd[LEN_OF_CMDLINE];
} TaskInfo_t;
QueueX_t *qtask = NULL;

void qtask_push(unsigned short gid, int32_t cid, SOAP_ACTION_ID id)
{
	TaskInfo_t task_new =
	{
		.gid = gid,
		.cid = cid,
		.id = id
	};
	//SAFE_SPRINTF(task_req.cmd, "%s", cmd);

	queuex_push(qtask, (void*)&task_new);
}

void qtask_GetCapabilities(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_DEVICE_GETCAPABILITIES,
		.act_ns = "tds",
		.act_name = "GetCapabilities",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", device_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		soap_node_t *curr_node = soap_element_fetch(response_node, NULL, "Capabilities", NULL, NULL);
		curr_node = soap_element_1st_child(curr_node);
		while(curr_node)
		{
			const char *Name = soap_element_name(curr_node);
			if(SAFE_STRSTR((char *)Name, "Extension"))
			{
				soap_node_t *Extension_node = soap_element_1st_child(curr_node);
				while(Extension_node)
				{
					const char *SubName = soap_element_name(Extension_node);
					char *XAddr = NULL;
					soap_node_t *XAddr_node = soap_element_fetch(Extension_node, NULL, "XAddr", NULL, NULL);
					if(XAddr_node)
					{
						XAddr = (char*)soap_element_text(XAddr_node, NULL);
					}

					DBG_IF_LN("(gid:%d.%d, %s: %s)", task->gid, task->cid, SubName, XAddr);

					Extension_node = soap_element_next_sibling(Extension_node);
				}
			}
			else
			{
				char *XAddr = NULL;
				soap_node_t *XAddr_node = soap_element_fetch(curr_node, NULL, "XAddr", NULL, NULL);
				if(XAddr_node)
				{
					XAddr = (char*)soap_element_text(XAddr_node, NULL);
				}

				if(SAFE_STRSTR((char *)Name, "Device"))
				{
					SAFE_SPRINTF(device_url, "%s", XAddr);
				}
				else if(SAFE_STRSTR((char *)Name, "Media"))
				{
					SAFE_SPRINTF(media_url, "%s", XAddr);
				}

				DBG_IF_LN("(gid:%d.%d, %s: %s)", task->gid, task->cid, Name, XAddr);
			}
			curr_node = soap_element_next_sibling(curr_node);
		}

		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetDeviceInformation(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_DEVICE_GETDEVICEINFORMATION,
		.act_ns = "tds",
		.act_name = "GetDeviceInformation",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", device_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		char *Manufacturer = NULL;
		char *Model = NULL;
		char *FirmwareVersion = NULL;
		char *SerialNumber = NULL;
		char *HardwareId = NULL;

		soap_node_t *Manufacturer_node = soap_element_fetch(response_node, NULL, "Manufacturer", NULL, NULL);
		if(Manufacturer_node)
		{
			Manufacturer = (char*)soap_element_text(Manufacturer_node, NULL);
		}

		soap_node_t *Model_node = soap_element_fetch(response_node, NULL, "Model", NULL, NULL);
		if(Model_node)
		{
			Model = (char*)soap_element_text(Model_node, NULL);
		}

		soap_node_t *FirmwareVersion_node = soap_element_fetch(response_node, NULL, "FirmwareVersion", NULL, NULL);
		if(FirmwareVersion_node)
		{
			FirmwareVersion = (char*)soap_element_text(FirmwareVersion_node, NULL);
		}

		soap_node_t *SerialNumber_node = soap_element_fetch(response_node, NULL, "SerialNumber", NULL, NULL);
		if(SerialNumber_node)
		{
			SerialNumber = (char*)soap_element_text(SerialNumber_node, NULL);
		}

		soap_node_t *HardwareId_node = soap_element_fetch(response_node, NULL, "HardwareId", NULL, NULL);
		if(HardwareId_node)
		{
			HardwareId = (char*)soap_element_text(HardwareId_node, NULL);
		}

		DBG_IF_LN("(gid:%d.%d, Manufacturer: %s)", task->gid, task->cid, Manufacturer);
		DBG_IF_LN("(gid:%d.%d, Model: %s)", task->gid, task->cid, Model);
		DBG_IF_LN("(gid:%d.%d, FirmwareVersion: %s)", task->gid, task->cid, FirmwareVersion);
		DBG_IF_LN("(gid:%d.%d, SerialNumber: %s)", task->gid, task->cid, SerialNumber);
		DBG_IF_LN("(gid:%d.%d, HardwareId: %s)", task->gid, task->cid, HardwareId);

		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetHostname(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_DEVICE_GETHOSTNAME,
		.act_ns = "tds",
		.act_name = "GetHostname",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", device_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		char *FromDHCP = NULL;
		char *Name = NULL;

		soap_node_t *FromDHCP_node = soap_element_fetch(response_node, NULL, "FromDHCP", NULL, NULL);
		if(FromDHCP_node)
		{
			FromDHCP = (char*)soap_element_text(FromDHCP_node, NULL);
		}

		soap_node_t *Name_node = soap_element_fetch(response_node, NULL, "Name", NULL, NULL);
		if(Name_node)
		{
			Name = (char*)soap_element_text(Name_node, NULL);
		}

		DBG_IF_LN("(gid:%d.%d, FromDHCP: %s, Name: %s)", task->gid, task->cid, FromDHCP, Name);

		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetNetworkInterfaces(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_DEVICE_GETNETWORKINTERFACES,
		.act_ns = "tds",
		.act_name = "GetNetworkInterfaces",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", device_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		int idx = 0;
		soap_node_t *curr_node = soap_element_fetch(response_node, NULL, "NetworkInterfaces", NULL, NULL);
		//soap_element_print(curr_node);
		while(curr_node)
		{
			const char *token = soap_element_attr(curr_node, "token");
			char *Enabled = NULL;
			char *Name = NULL;
			char *HwAddress = NULL;
			char *MTU = NULL;

			soap_node_t *Enabled_node = soap_element_fetch(curr_node, NULL, "Enabled", NULL, NULL);
			if(Enabled_node)
			{
				Enabled = (char*)soap_element_text(Enabled_node, NULL);
			}

			soap_node_t *Info_node = soap_element_fetch(curr_node, NULL, "Info", NULL, NULL);
			if(Info_node)
			{
				soap_node_t *Name_node = soap_element_fetch(Info_node, NULL, "Name", NULL, NULL);
				if(Name_node)
				{
					Name = (char*)soap_element_text(Name_node, NULL);
				}

				soap_node_t *HwAddress_node = soap_element_fetch(Info_node, NULL, "HwAddress", NULL, NULL);
				if(HwAddress_node)
				{
					HwAddress = (char*)soap_element_text(HwAddress_node, NULL);
				}

				soap_node_t *MTU_node = soap_element_fetch(Info_node, NULL, "MTU", NULL, NULL);
				if(MTU_node)
				{
					MTU = (char*)soap_element_text(MTU_node, NULL);
				}
			}

			DBG_IF_LN("(gid:%d.%d, [%d] token: %s, Enabled: %s, Name: %s, HwAddress: %s, MTU: %s)", task->gid, task->cid, idx, token, Enabled, Name, HwAddress, MTU);
			soap_node_t *IPv4_node = soap_element_fetch(curr_node, NULL, "IPv4", NULL, NULL);
			if(IPv4_node)
			{
				soap_node_t *Enabled_node = soap_element_fetch(IPv4_node, NULL, "Enabled", NULL, NULL);
				if(Enabled_node)
				{
					Enabled = (char*)soap_element_text(Enabled_node, NULL);
				}

				DBG_IF_LN("(gid:%d.%d, [%d] IPv4 Enabled: %s)", task->gid, task->cid, idx, Enabled);
			}
			soap_node_t *IPv6_node = soap_element_fetch(curr_node, NULL, "IPv6", NULL, NULL);
			if(IPv6_node)
			{
				soap_node_t *Enabled_node = soap_element_fetch(IPv6_node, NULL, "Enabled", NULL, NULL);
				if(Enabled_node)
				{
					Enabled = (char*)soap_element_text(Enabled_node, NULL);
				}

				DBG_IF_LN("(gid:%d.%d, [%d] IPv6 Enabled: %s)", task->gid, task->cid, idx, Enabled);
			}

			idx ++;
			curr_node = soap_element_next_sibling(curr_node);
		}

		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetServices(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_DEVICE_GETSERVICES,
		.act_ns = "tds",
		.act_name = "GetServices",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", device_url);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		soap_node_t *curr_node = soap_element_fetch(response_node, NULL, "Service", NULL, NULL);
		//soap_element_print(curr_node);
		while(curr_node)
		{
			char *Namespace = NULL;
			char *XAddr = NULL;
			soap_node_t *Namespace_node = soap_element_fetch(curr_node, NULL, "Namespace", NULL, NULL);
			Namespace = (char*)soap_element_text(Namespace_node, NULL);

			soap_node_t *XAddr_node = soap_element_fetch(curr_node, NULL, "XAddr", NULL, NULL);
			XAddr = (char*)soap_element_text(XAddr_node, NULL);

			DBG_IF_LN("(gid:%d.%d, Namespace: %s)", task->gid, task->cid, Namespace);
			DBG_IF_LN("(gid:%d.%d, XAddr: %s)", task->gid, task->cid, XAddr);


			curr_node = soap_element_next_sibling(curr_node);
		}

		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetScopes(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_DEVICE_GETSCOPES,
		.act_ns = "tds",
		.act_name = "GetScopes",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", device_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		int idx = 0;
		soap_node_t *curr_node = soap_element_fetch(response_node, NULL, "Scopes", NULL, NULL);
		//soap_element_print(curr_node);
		while(curr_node)
		{
			char *ScopeDef = NULL;
			char *ScopeItem = NULL;

			soap_node_t *ScopeDef_node = soap_element_fetch(curr_node, NULL, "ScopeDef", NULL, NULL);
			if(ScopeDef_node)
			{
				ScopeDef = (char*)soap_element_text(ScopeDef_node, NULL);
			}

			soap_node_t *ScopeItem_node = soap_element_fetch(curr_node, NULL, "ScopeItem", NULL, NULL);
			if(ScopeItem_node)
			{
				ScopeItem = (char*)soap_element_text(ScopeItem_node, NULL);
			}

			DBG_IF_LN("(gid:%d.%d, [%d] ScopeDef: %s, ScopeItem: %s)", task->gid, task->cid, idx, ScopeDef, ScopeItem);
			idx ++;
			curr_node = soap_element_next_sibling(curr_node);
		}

		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetProfiles(TaskInfo_t *task)
{
	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_MEDIA_GETPROFILES,
		.act_ns = "trt",
		.act_name = "GetProfiles",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = NULL
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", media_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		char *token = NULL;
		soap_node_t *curr_node = soap_element_fetch(response_node, NULL, "Profiles", NULL, NULL);
		//soap_element_print(curr_node);
		while((curr_node) && (token==NULL))
		{
			//soap_element_print(Profiles_node);
			if(token==NULL)
			{
				SAFE_ASPRINTF(token, "%s", soap_element_attr(curr_node, "token"));
			}
			curr_node = soap_element_next_sibling(curr_node);
		}

		DBG_IF_LN("(gid:%d.%d, token: %s)", task->gid, task->cid, token);
		SAFE_SPRINTF(profile_token, "%s", token);
		SAFE_FREE(token);
		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetSnapshotUri(TaskInfo_t *task)
{
	char *token = profile_token;

	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI,
		.act_ns = "trt",
		.act_name = "GetSnapshotUri",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)token
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", media_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		soap_node_t *Uri_node = soap_element_fetch(response_node, NULL, "Uri", NULL, NULL);
		if(Uri_node)
		{
			char *snapshot_uri = (char*)soap_element_text(Uri_node, NULL);
			DBG_DB_LN("GetSnapshotUri (snapshot_uri: %s)",  snapshot_uri);

			if(onvif_GetSnapshot(&onvif_req, snapshot_uri, snapshot_prefixname) == 0)
			{
				DBG_IF_LN("GetSnapshot ok !!! (gid:%d.%d, %s.jpg)", task->gid, task->cid, snapshot_prefixname);
			}
			else
			{
				DBG_IF_LN("GetSnapshot fail !!! (gid:%d.%d, %s.jpg)", task->gid, task->cid, snapshot_prefixname);
			}
		}
		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_GetStreamUri(TaskInfo_t *task)
{
	char *token = profile_token;

	OnvifX_t onvif_req =
	{
		.act_id = SOAP_ACTION_ID_MEDIA_GETSTREAMURI,
		.act_ns = "trt",
		.act_name = "GetStreamUri",
		.netinfo.port = 0,
		.http_auth = http_auth,
		.request = (void *)token
	};
	SAFE_SPRINTF(onvif_req.netinfo.url, "%s", media_url);
	SAFE_SPRINTF(onvif_req.netinfo.user, "%s", srv_user);
	SAFE_SPRINTF(onvif_req.netinfo.pass, "%s", srv_pass);

	soap_node_t *response_node = onvif_GetCommon(&onvif_req);
	if(response_node)
	{
		soap_node_t *Uri_node = soap_element_fetch(response_node, NULL, "Uri", NULL, NULL);
		if(Uri_node)
		{
			char *media_uri = (char*)soap_element_text(Uri_node, NULL);
			DBG_DB_LN("GetStreamUri (media_uri: %s)",  media_uri);

			if(onvif_GetVideoClip(&onvif_req, media_uri, video_filename, 15) == 0)
			{
				DBG_IF_LN("qtask_GetStreamUri ok !!! (gid:%d.%d, %s)", task->gid, task->cid, video_filename);
			}
			else
			{
				DBG_IF_LN("qtask_GetStreamUri fail !!! (gid:%d.%d, %s)", task->gid, task->cid, video_filename);
			}
		}
		soap_element_delete(response_node);
	}
	else
	{
		DBG_ER_LN("%s (%s)", DBG_TXT_NO_SUPPORT, onvif_req.netinfo.url);
	}
	printf("\n");
}

void qtask_process(TaskInfo_t *task)
{
	//DBG_IF_LN("(id: %d, gid:%d.%d)", task->id, task->gid, task->cid);
	switch(task->id)
	{
		case SOAP_ACTION_ID_GETCOMMON:
			DBG_IF_LN("SOAP_ACTION_ID_GETCOMMON (gid:%d.%d)", task->gid, task->cid);
			break;

		case SOAP_ACTION_ID_DEVICE_GETCAPABILITIES:
			qtask_GetCapabilities(task);
			break;
		case SOAP_ACTION_ID_DEVICE_GETDEVICEINFORMATION:
			qtask_GetDeviceInformation(task);
			break;
		case SOAP_ACTION_ID_DEVICE_GETHOSTNAME:
			qtask_GetHostname(task);
			break;
		case SOAP_ACTION_ID_DEVICE_GETNETWORKINTERFACES:
			qtask_GetNetworkInterfaces(task);
			break;
		case SOAP_ACTION_ID_DEVICE_GETSERVICES:
			qtask_GetServices(task);
			break;
		case SOAP_ACTION_ID_DEVICE_GETSCOPES:
			qtask_GetScopes(task);
			break;

		case SOAP_ACTION_ID_MEDIA_GETPROFILES:
			qtask_GetProfiles(task);
			break;
		case SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI:
			qtask_GetSnapshotUri(task);
			break;
		case SOAP_ACTION_ID_MEDIA_GETSTREAMURI:
			qtask_GetStreamUri(task);
			break;

		default:
			break;
	}

}

static int qtask_exec_cb(void *arg)
{
	TaskInfo_t *data_pop = (TaskInfo_t *)arg;

	if(data_pop)
	{
		qtask_process(data_pop);
	}

	return 0;
}

// ** app **
#define TIMEOUT_OF_APP 5
static int is_quit = 0;

static pthread_mutex_t app_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t app_cond = PTHREAD_COND_INITIALIZER;

static void app_set_quit(int mode)
{
	is_quit = mode;
}

static int app_quit(void)
{
	return is_quit;
}

#ifdef USE_DAEMON
static void app_loop(void)
{
	// nothing
}
#endif

void app_wakeup(void)
{
	SAFE_THREAD_LOCK(&app_mutex);
	SAFE_THREAD_SIGNAL(&app_cond);
	SAFE_THREAD_UNLOCK(&app_mutex);
}

#ifdef USE_DAEMON
static void app_wait(void)
{
	SAFE_THREAD_LOCK(&app_mutex);
	SAFE_THREAD_TIMEWAIT(&app_cond, &app_mutex, (TIMEOUT_OF_APP*1000));
	//int ret = SAFE_THREAD_WAIT(&app_cond, &app_mutex);
	SAFE_THREAD_UNLOCK(&app_mutex);

	//ICLOUD_DEBUGLN(DBG_LVL_TRACE, "(ret: %d)", ret);
}
#endif

static void app_stop(void)
{
	if(app_quit()==0)
	{
		app_set_quit(1);
		app_wakeup();

		queuex_thread_stop(qtask);
		queuex_thread_close(qtask);
	}
}

static void app_exit(void)
{
	app_stop();
	DBG_TR_LN("exit");
}

static void app_signal_handler(int signum)
{
	DBG_TR_LN("(signum: %d)", signum);
	switch(signum)
	{
		case SIGINT:
		case SIGTERM:
		case SIGHUP:
			app_stop();
			break;

		case SIGUSR1:
			qtask_push(256, 0, SOAP_ACTION_ID_MEDIA_GETPROFILES);
			break;

		case SIGUSR2:
			//qtask_push(256, 0, SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI);
			qtask_push(256, 0, SOAP_ACTION_ID_DEVICE_GETHOSTNAME);
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
}

int option_index = 0;
const char* short_options = "i:p:u:s:e:m:ad:h";
static struct option long_options[] =
{
	{ "ip",          required_argument,   NULL,    'i'  },
	{ "port",        required_argument,   NULL,    'p'  },
	{ "user",        required_argument,   NULL,    'u'  },
	{ "pass",        required_argument,   NULL,    's'  },
	{ "dpath",       required_argument,   NULL,    'e'  },
	{ "mpath",       required_argument,   NULL,    'm'  },
	{ "auth",        no_argument,         NULL,    'a'  },
	{ "debug",       required_argument,   NULL,    'd'  },
	{ "help",        no_argument,         NULL,    'h'  },
	{ 0,             0,                      0,    0    }
};

static void app_showusage(int exit_code)
{
	printf("Usage: %s\n"
		   "  -d, --debug       debug level\n"
		   "  -i, --ip          ip\n"
		   "  -p, --port        port\n"
		   "  -u, --user        user\n"
		   "  -s, --pass        pass\n"
		   "  -e, --dpath       device url path\n"
		   "  -m, --mpath       media url path\n"
		   "  -a, --auth        http auth\n"
		   "  -h, --help\n", TAG);
	printf("Version: %s\n", version_show());
	printf("Example:\n"
		   "  %s -i 192.168.50.239 -p 80 -u admin -s hahahaha\n", TAG
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
			case 'd':
				if(optarg)
				{
					dbg_lvl_set(atoi(optarg));
				}
				break;
			case 'i':
				if(optarg)
				{
					SAFE_SPRINTF(srv_ip, "%s", optarg);
				}
				break;
			case 'p':
				if(optarg)
				{
					srv_port = atoi(optarg);
				}
				break;
			case 'u':
				if(optarg)
				{
					SAFE_SPRINTF(srv_user, "%s", optarg);
				}
				break;
			case 's':
				if(optarg)
				{
					SAFE_SPRINTF(srv_pass, "%s", optarg);
				}
				break;
			case 'e':
				if(optarg)
				{
					SAFE_SPRINTF(device_url_path, "%s", optarg);
				}
				break;
			case 'm':
				if(optarg)
				{
					SAFE_SPRINTF(media_url_path, "%s", optarg);
				}
				break;
			case 'a':
				http_auth = 1;
				break;
			default:
				app_showusage(-1);
				break;
		}
	}
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");
	dbg_lvl_set(DBG_LVL_DEBUG);

	app_ParseArguments(argc, argv);
	app_signal_register();
	atexit(app_exit);

	if(strlen(srv_ip)>0)
	{
		if(srv_port==0)
		{
			srv_port=80;
		}
		SAFE_SPRINTF(device_url, "http://%s:%d%s", srv_ip, srv_port, device_url_path);
		SAFE_SPRINTF(media_url, "http://%s:%d%s", srv_ip, srv_port, media_url_path);
	}
	DBG_IF_LN("%s (%s:%d, %s:%s, device_url_path: %s, media_url_path: %s)", DBG_TXT_START, srv_ip, srv_port, srv_user, srv_pass, device_url_path, media_url_path);

#ifdef USE_DAEMON
	int result = daemon(0,1);
	if(result == 0)
#endif
	{
		qtask = queuex_thread_init("qtask", MAX_OF_TASK, sizeof(TaskInfo_t), qtask_exec_cb, NULL);
		usleep(500*1000);

		qtask_push(769, 0, SOAP_ACTION_ID_DEVICE_GETCAPABILITIES);
		qtask_push(769, 0, SOAP_ACTION_ID_DEVICE_GETDEVICEINFORMATION);
		qtask_push(769, 0, SOAP_ACTION_ID_DEVICE_GETHOSTNAME);
		qtask_push(769, 0, SOAP_ACTION_ID_DEVICE_GETSERVICES);
		qtask_push(769, 0, SOAP_ACTION_ID_DEVICE_GETSCOPES);
		qtask_push(769, 0, SOAP_ACTION_ID_DEVICE_GETNETWORKINTERFACES);

		qtask_push(769, 0, SOAP_ACTION_ID_MEDIA_GETPROFILES);
		qtask_push(769, 0, SOAP_ACTION_ID_MEDIA_GETSTREAMURI);

		qtask_push(769, 0, SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI);

#ifdef USE_DAEMON
		while(app_quit() == 0)
		{
			app_loop();
			app_wait();
		}
#else
		while(!queuex_isempty(qtask))
		{
			sleep(1);
		}
#endif
	}

	DBG_TR_LN("exit");
	return 0;
}
