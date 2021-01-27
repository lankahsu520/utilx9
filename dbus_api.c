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
#include "utilx9.h"

static pthread_t dbus_tid = 0;
static QUIT_ID is_quit = READY_ID_NONE;

static char dbus_path[LEN_OF_BUF256] = "/com/xbox/123";
static DBusConnection *dbus_conn = NULL;
static DBusConnection *dbus_conn_listen = NULL;

static dbus_match_fn *dbus_add_match_cb = NULL;
static dbus_filter_fn *dbus_filter_user_cb = NULL;

DBusHandlerResult demo_signal_cb(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	DBusError dbus_err;

	char *val = NULL;

	SAFE_DBUS_ERR_INIT(&dbus_err);

	if (!dbus_message_get_args(message, &dbus_err, DBUS_TYPE_STRING, &val, DBUS_TYPE_INVALID))
	{
		DBG_ER_LN("dbus_message_get_args error !!! (message: %s)", dbus_err.message);
		handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		goto done;
	}

	DBG_DB_LN("%s (val: %s)", DBG_TXT_GOT, val);

	handled = DBUS_HANDLER_RESULT_HANDLED;

done:
	SAFE_DBUS_ERR_FREE(&dbus_err);

	return handled;
}

DBusHandlerResult echo_method_cb(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	DBusError dbus_err;
	DBusMessage *dbus_msg_res; //response
	char *val = NULL;
	char *retStr = NULL;

	dbus_msg_res = dbus_message_new_method_return(message);
	if (!dbus_msg_res)
	{
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	}

	SAFE_DBUS_ERR_INIT(&dbus_err);

	if (!dbus_message_get_args(message, &dbus_err, DBUS_TYPE_STRING, &val, DBUS_TYPE_INVALID))
	{
		DBG_ER_LN("dbus_message_get_args error !!! (message: %s)", dbus_err.message);
		handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
		goto done;
	}

	DBG_DB_LN("%s (val: %s)", DBG_TXT_GOT, val);
	SAFE_ASPRINTF(retStr, "%s", val);

	dbus_message_append_args(dbus_msg_res, DBUS_TYPE_STRING, &retStr, DBUS_TYPE_INVALID);
	dbus_connection_send(connection, dbus_msg_res, NULL);

	handled = DBUS_HANDLER_RESULT_HANDLED;

done:
	SAFE_FREE(retStr);
	SAFE_DBUS_MSG_FREE(dbus_msg_res);
	SAFE_DBUS_ERR_FREE(&dbus_err);

	return handled;
}

int dbus_signal_simple(const char *ifac,char *cmd, int itype, void *arg)
{
	int ret = -1;
	DBusMessage *dbus_msg_req = NULL;

	if ( dbus_conn == NULL )
	{
		DBG_ER_LN("dbus_conn is NULL !!!");
		goto exit_send;
	}
	else if ( (ifac == NULL) || (cmd == NULL) )
	{
		DBG_ER_LN("ifac or cmd is NULL !!! (ifac: %p, cmd: %p)", ifac, cmd);
		goto exit_send;
	}
	else if (arg == NULL)
	{
		DBG_ER_LN("arg is NULL !!! (arg: %p)", arg);
		goto exit_send;
	}

	// create a signal and check for errors
	dbus_msg_req = dbus_message_new_signal(dbus_path, ifac, cmd);
	if (NULL == dbus_msg_req)
	{
		DBG_ER_LN("dbus_message_new_signal error !!!");
		goto exit_send;
	}

	switch (itype)
	{
		case DBUS_TYPE_STRING:
			if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_STRING, (char *)&arg, DBUS_TYPE_INVALID))
			{
				goto exit_send;
			}
			break;
		case DBUS_TYPE_INT32:
			if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_INT32, (int*)arg, DBUS_TYPE_INVALID))
			{
				goto exit_send;
			}
			break;
		case DBUS_TYPE_UINT32:
			if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_UINT32, (unsigned int*)arg, DBUS_TYPE_INVALID))
			{
				goto exit_send;
			}
			break;
	}

	// send the message and flush the connection
	if (!dbus_connection_send(dbus_conn, dbus_msg_req, NULL))
	{
		DBG_ER_LN("dbus_connection_send error !!!");
		goto exit_send;
	}
	ret = 0;

exit_send:
	SAFE_DBUS_MSG_FREE(dbus_msg_req);

	return ret;
}

int dbus_signal_str(const char *ifac, char *cmd, char *arg)
{
	return dbus_signal_simple(ifac, cmd, DBUS_TYPE_STRING, (void*)arg);
}

int dbus_signal_xint2uint(const char *ifac, char *cmd, int itype, unsigned int *arg)
{
	return dbus_signal_simple(ifac, cmd, itype, (void*)arg);
}

char *dbus_method_key_val(const char *dest, const char *ifac, char *cmd, char *key, const char *val, int timeout)
{
	DBusError dbus_err;
	DBusMessage *dbus_msg_req = NULL;
	DBusMessage *dbus_msg_res = NULL;
	DBusMessageIter dbus_iter;
	char *retStr = NULL;

	SAFE_DBUS_ERR_INIT(&dbus_err);

	//LOGE_EX(TAG,"(cmd: %s, key: %s, val: %s)", cmd, key, val);
	if ( dbus_conn == NULL )
	{
		DBG_ER_LN("dbus_conn is NULL !!!");
		goto exit_send;
	}
	else if ( (ifac == NULL) || (cmd == NULL) )
	{
		DBG_ER_LN("ifac or cmd is NULL !!! (ifac: %p, cmd: %p)", ifac, cmd);
		goto exit_send;
	}
	else if ( (key == NULL) || (val == NULL) )
	{
		DBG_ER_LN("key or val is NULL !!! (key: %p, val: %p)", key, val);
		goto exit_send;
	}

	dbus_msg_req = dbus_message_new_method_call(dest, dbus_path, ifac, cmd);

	if (dbus_msg_req == NULL)
	{
		DBG_ER_LN("dbus_msg_req is NULL !!!");
		goto exit_send;
	}

	if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_STRING, (char *)&key, DBUS_TYPE_STRING, (char *)&val, DBUS_TYPE_INVALID))
	{
		goto exit_send;
	}

	dbus_msg_res = dbus_connection_send_with_reply_and_block (dbus_conn, dbus_msg_req, timeout, &dbus_err);
	if (dbus_msg_res == NULL)
	{
		DBG_ER_LN("dbus_connection_send_with_reply_and_block error !!! (message: %s)", dbus_err.message);
	}
	else
	{
		if (!dbus_message_iter_init(dbus_msg_res, &dbus_iter))
		{
			DBG_ER_LN("dbus_message_iter_init error !!! (message: %s)", dbus_err.message);
		}
		else
		{
			char *response = NULL;
			dbus_message_iter_get_basic(&dbus_iter, &response);
			if ( response )
			{
				SAFE_ASPRINTF(retStr, "%s", response);
			}
		}
	}

exit_send:
	SAFE_DBUS_MSG_FREE(dbus_msg_req);
	SAFE_DBUS_MSG_FREE(dbus_msg_res);
	SAFE_DBUS_ERR_FREE(&dbus_err);

	if (retStr==NULL)
	{
		SAFE_ASPRINTF(retStr, "\n");
	}

	return retStr;
}

char *dbus_method_simple(const char *dest, const char *ifac, char *cmd, int itype, void *arg, int otype, int timeout)
{
	DBusError dbus_err;
	DBusMessage *dbus_msg_req = NULL;
	DBusMessage *dbus_msg_res = NULL;
	DBusMessageIter dbus_iter;
	char *retStr = NULL;

	SAFE_DBUS_ERR_INIT(&dbus_err);

	if ( dbus_conn == NULL )
	{
		DBG_ER_LN("dbus_conn is NULL !!!");
		goto exit_send;
	}
	else if ( (ifac == NULL) || (cmd == NULL) )
	{
		DBG_ER_LN("ifac or cmd is NULL !!! (ifac: %p, cmd: %p)", ifac, cmd);
		goto exit_send;
	}
	else if (arg == NULL)
	{
		DBG_ER_LN("arg is NULL !!!");
		goto exit_send;
	}

	dbus_msg_req = dbus_message_new_method_call(dest, dbus_path, ifac, cmd);

	if (dbus_msg_req == NULL)
	{
		DBG_ER_LN("dbus_msg_req is NULL !!!");
		goto exit_send;
	}

	switch (itype)
	{
		case DBUS_TYPE_STRING:
			if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_STRING, (char *)&arg, DBUS_TYPE_INVALID))
			{
				goto exit_send;
			}
			//SAFE_SPRINTF(arg_str, "%s", (char *)arg);
			break;
		case DBUS_TYPE_INT32:
			if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_INT32, (int*)arg, DBUS_TYPE_INVALID))
			{
				goto exit_send;
			}
			break;
		case DBUS_TYPE_UINT32:
			if (!dbus_message_append_args(dbus_msg_req, DBUS_TYPE_UINT32, (unsigned int*)arg, DBUS_TYPE_INVALID))
			{
				goto exit_send;
			}
			break;
	}

	dbus_msg_res = dbus_connection_send_with_reply_and_block(dbus_conn, dbus_msg_req, timeout, &dbus_err);
	if (dbus_msg_res == NULL)
	{
		DBG_ER_LN("dbus_connection_send_with_reply_and_block error !!! (message: %s, timeout: %d)", dbus_err.message, timeout);
	}
	else
	{
		if (!dbus_message_iter_init(dbus_msg_res, &dbus_iter))
		{
			DBG_ER_LN("dbus_message_iter_init error !!! (message: %s)", dbus_err.message);
		}
		else
		{
			switch (otype)
			{
				case DBUS_TYPE_STRING:
					{
						char *response = NULL;
						dbus_message_iter_get_basic(&dbus_iter, &response);
						if ( response )
						{
							SAFE_ASPRINTF(retStr, "%s", response);
						}
					}
					break;
				case DBUS_TYPE_INT32:
				case DBUS_TYPE_UINT32:
					{
						int response = 0;
						dbus_message_iter_get_basic(&dbus_iter, &response);
						SAFE_ASPRINTF(retStr, "%d", response);
					}
					break;
#ifdef UTIL_EX_JSON
				case DBUS_TYPE_ARRAY:
					{
						json_t *jresponse = JSON_ARY_NEW();
						DBusMessageIter dSubIter;
						dbus_message_iter_recurse(&dbus_iter, &dSubIter);
						do
						{
							char *response = NULL;
							dbus_message_iter_get_basic(&dSubIter, &response);

							if (response)
							{
								JSON_ARY_APPEND_STR(jresponse, response);
								DBG_DB_LN("(response: %s)", response);
							}
						}
						while( dbus_message_iter_next(&dSubIter) == TRUE );

						retStr = JSON_DUMPS_EASY( jresponse );
						JSON_FREE(jresponse);
					}
#endif
					break;
			}
		}
	}

exit_send:
	SAFE_DBUS_MSG_FREE(dbus_msg_req);
	SAFE_DBUS_MSG_FREE(dbus_msg_res);
	SAFE_DBUS_ERR_FREE(&dbus_err);

	if (retStr==NULL)
	{
		SAFE_ASPRINTF(retStr, "\n");
	}

	return retStr;
}

char *dbus_method_str2str(const char *dest, const char *ifac, char *cmd, char *arg, int timeout)
{
	return dbus_method_simple(dest, ifac, cmd, DBUS_TYPE_STRING, (void*)arg, DBUS_TYPE_STRING, timeout);
}

char *dbus_method_str2int(const char *dest, const char *ifac, char *cmd, char *arg, int timeout)
{
	char *retStr = dbus_method_simple(dest, ifac, cmd, DBUS_TYPE_STRING, (void*)arg, DBUS_TYPE_INT32, timeout);
	return retStr;
}

char *dbus_method_xint2uint(const char *dest, const char *ifac, char *cmd, int itype, unsigned int *arg, int timeout)
{
	return dbus_method_simple(dest, ifac, cmd, itype, (void*)arg, DBUS_TYPE_UINT32, timeout);
}

static DBusHandlerResult dbus_filter(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	const char *method = dbus_message_get_member(message);
	const char *iface = dbus_message_get_interface(message);
	const char *path = dbus_message_get_path(message);

	if (dbus_filter_user_cb)
	{
		handled = dbus_filter_user_cb(connection, message, usr_data);
	}

	if ( handled != DBUS_HANDLER_RESULT_HANDLED )
	{
		DBG_DB_LN("DBUS request not handled (method: %s, iface: %s, path: %s)", method, iface, path);
		handled = DBUS_HANDLER_RESULT_HANDLED;
	}
	
	return handled;
}

void dbus_conn_free(void)
{
	if ( (dbus_conn_listen) || (dbus_conn) )
	{
		SAFE_DBUS_CONN_FREE(dbus_conn_listen);
		SAFE_DBUS_CONN_FREE(dbus_conn);
		dbus_shutdown();
	}
}

int dbus_client_init(void)
{
	int ret = -1;
	DBusError dbus_err;

	// initialize the errors
	SAFE_DBUS_ERR_INIT(&dbus_err);

	if ((dbus_conn = dbus_bus_get_private (DBUS_BUS_SYSTEM, &dbus_err)) == NULL)
	{
		DBG_ER_LN("dbus_bus_get_private error !!! (message: %s)", dbus_err.message);
		goto exit_init;
	}

	if (dbus_error_is_set(&dbus_err))
	{
		DBG_ER_LN("dbus_bus_get_private error !!! (message: %s)", dbus_err.message);
		goto exit_init;
	}

	ret = 0;

exit_init:
	SAFE_DBUS_ERR_FREE(&dbus_err);

	return ret;
}

static int dbus_add_match(DBusConnection *dbus_listen, DBusError *err)
{
	int ret = 0;

	if (dbus_add_match_cb)
	{
		ret = dbus_add_match_cb(dbus_listen, err);
	}

	return ret;
}

static void *dbus_thread_handler(void *arg)
{
	DBusError dbus_err;

	// initialize the errors
	if ( dbus_client_init() == -1 )
	{
		goto exit_dbus;
	}

	SAFE_DBUS_ERR_INIT(&dbus_err);
	dbus_conn_listen = dbus_bus_get_private(DBUS_BUS_SYSTEM, &dbus_err);
	if (dbus_error_is_set(&dbus_err))
	{
		DBG_ER_LN("dbus_bus_get_private error !!! (message: %s)", dbus_err.message);
		goto exit_dbus;
	}
	
	if (NULL == dbus_conn_listen)
	{
		DBG_ER_LN("dbus_conn_listen is NULL !!!");
		goto exit_dbus;
	}

	if (!dbus_connection_add_filter(dbus_conn_listen, dbus_filter, NULL, NULL))
	{
		DBG_ER_LN("dbus_connection_add_filter error !!!");
		goto exit_dbus;
	}

	if (dbus_add_match(dbus_conn_listen, &dbus_err) != 0 )
	{
		goto exit_dbus;
	}

	DBG_IF_LN("dbus listen ...");
	while ( dbus_quit() == QUIT_ID_NONE )
	{
		dbus_connection_read_write_dispatch(dbus_conn_listen, 1000);
	}

exit_dbus:
	dbus_conn_free();
	SAFE_DBUS_ERR_FREE(&dbus_err);

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	return NULL;
}

DBusConnection *dbus_conn_get(void)
{
	return dbus_conn;
}

void dbus_path_set(char *path)
{
	SAFE_SPRINTF(dbus_path, "%s", path);
}

char *dbus_path_get(void)
{
	return dbus_path;
}

void dbus_quit_set(QUIT_ID quit)
{
	is_quit = quit;
}

QUIT_ID dbus_quit(void)
{
	return is_quit;
}

READY_ID dbus_ready(void)
{
	int retry = 3;
	while ((dbus_conn_listen==NULL) && (retry>0) && ( dbus_quit() == QUIT_ID_NONE ) )
	{
		retry--;
		sleep(1);
	}

	if (dbus_conn_listen)
	{
		return READY_ID_OK;
	}
	else
	{
		DBG_ER_LN("(retry: %d)", retry);
		return READY_ID_NONE;
	}
}

int dbus_thread_init(dbus_match_fn *match_cb, dbus_filter_fn *filter_cb)
{
	dbus_add_match_cb = match_cb;
	dbus_filter_user_cb = filter_cb;

	if (SAFE_THREAD_CREATE(dbus_tid, NULL, dbus_thread_handler, NULL) != 0)
	{
		DBG_ER_LN("SAFE_THREAD_CREATE error !!!");
		return -1;
	}

	return 0;
}

void dbus_thread_stop(void)
{
	dbus_quit_set(1);
}

void dbus_thread_close(void)
{
	static int is_free = 0;
	if (is_free == 0)
	{
		is_free ++;
		if (dbus_tid != 0)
		{
			dbus_thread_stop();
			pthread_join(dbus_tid, NULL);
			dbus_tid = 0;
		}
		dbus_conn_free();
	}
}

