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

int dbusx_signal_simple(DBusConnection *dbus_conn, char *dbus_path, const char *ifac,char *cmd, int itype, void *arg)
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

int dbusx_signal_str(DbusX_t *dbusx_req, const char *ifac, char *cmd, char *arg)
{
	DBusConnection *dbus_conn = dbusx_conn_get(dbusx_req);
	char *dbus_path = dbusx_path_get(dbusx_req);
	return dbusx_signal_simple(dbus_conn, dbus_path, ifac, cmd, DBUS_TYPE_STRING, (void*)arg);
}

int dbusx_signal_xint2uint(DBusConnection *dbus_conn, char *dbus_path, const char *ifac, char *cmd, int itype, unsigned int *arg)
{
	return dbusx_signal_simple(dbus_conn, dbus_path, ifac, cmd, itype, (void*)arg);
}

char *dbusx_method_key_val(DBusConnection *dbus_conn, char *dbus_path, const char *dest, const char *ifac, char *cmd, char *key, const char *val, int timeout)
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

char *dbusx_method_simple(DBusConnection *dbus_conn, char *dbus_path, const char *dest, const char *ifac, char *cmd, int itype, void *arg, int otype, int timeout)
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

char *dbusx_method_str2str(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, char *arg, int timeout)
{
	DBusConnection *dbus_conn = dbusx_conn_get(dbusx_req);
	char *dbus_path = dbusx_path_get(dbusx_req);
	return dbusx_method_simple(dbus_conn, dbus_path, dest, ifac, cmd, DBUS_TYPE_STRING, (void*)arg, DBUS_TYPE_STRING, timeout);
}

char *dbusx_method_str2int(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, char *arg, int timeout)
{
	DBusConnection *dbus_conn = dbusx_conn_get(dbusx_req);
	char *dbus_path = dbusx_path_get(dbusx_req);
	char *retStr = dbusx_method_simple(dbus_conn, dbus_path, dest, ifac, cmd, DBUS_TYPE_STRING, (void*)arg, DBUS_TYPE_INT32, timeout);
	return retStr;
}

char *dbusx_method_xint2uint(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, int itype, unsigned int *arg, int timeout)
{
	DBusConnection *dbus_conn = dbusx_conn_get(dbusx_req);
	char *dbus_path = dbusx_path_get(dbusx_req);
	return dbusx_method_simple(dbus_conn, dbus_path, dest, ifac, cmd, itype, (void*)arg, DBUS_TYPE_UINT32, timeout);
}

static DBusHandlerResult dbusx_filter(DBusConnection *connection, DBusMessage *message, void *usr_data)
{
	dbus_bool_t handled = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	DbusX_t *dbusx_req = (DbusX_t *)usr_data;
	if (dbusx_req)
	{
		const char *method = dbus_message_get_member(message);
		const char *iface = dbus_message_get_interface(message);
		const char *path = dbus_message_get_path(message);

		if (dbusx_req->filter_user_cb)
		{
			handled = dbusx_req->filter_user_cb(connection, message, usr_data);
		}

		if ( handled != DBUS_HANDLER_RESULT_HANDLED )
		{
			DBG_DB_LN("DBUS request not handled (method: %s, iface: %s, path: %s)", method, iface, path);
			handled = DBUS_HANDLER_RESULT_HANDLED;
		}
	}

	return handled;
}

void dbusx_shutdown(void)
{
	dbus_shutdown();
}

void dbusx_conn_free(DbusX_t *dbusx_req)
{
	if ( (dbusx_req) && ((dbusx_req->dbus_conn_listen) || (dbusx_req->dbus_conn)) )
	{
		SAFE_DBUS_CONN_FREE(dbusx_req->dbus_conn_listen);
		SAFE_DBUS_CONN_FREE(dbusx_req->dbus_conn);

		if (dbusx_req->isgdbus==0)
		{
			dbus_shutdown();
		}
	}
}

int dbusx_client_init(DbusX_t *dbusx_req)
{
	int ret = -1;
	DBusError dbus_err;

	// initialize the errors
	SAFE_DBUS_ERR_INIT(&dbus_err);

	if ((dbusx_req->dbus_conn = dbus_bus_get_private (DBUS_BUS_SYSTEM, &dbus_err)) == NULL)
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

static int dbusx_add_match(DBusConnection *dbus_listen, DBusError *err, void *usr_data)
{
	int ret = -1;
	DbusX_t *dbusx_req = (DbusX_t*)usr_data;

	if (dbusx_req)
	{
		if (dbusx_req->add_match_cb)
		{
			ret = dbusx_req->add_match_cb(dbus_listen, err, usr_data);
		}
	}

	return ret;
}

static void *dbusx_thread_handler(void *user)
{
	DbusX_t *dbusx_req = (DbusX_t*)user;

	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_detach(tidx_req);

		DBusError dbus_err;

		if ( dbusx_req_check(dbusx_req) == -1 )
		{
			goto exit_dbus;
		}

		// initialize the errors
		if ( dbusx_client_init(dbusx_req) == -1 )
		{
			goto exit_dbus;
		}

		SAFE_DBUS_ERR_INIT(&dbus_err);
		dbusx_req->dbus_conn_listen = dbus_bus_get_private(DBUS_BUS_SYSTEM, &dbus_err);
		if (dbus_error_is_set(&dbus_err))
		{
			DBG_ER_LN("dbus_bus_get_private error !!! (message: %s)", dbus_err.message);
			goto exit_dbus;
		}
		
		if (NULL == dbusx_req->dbus_conn_listen)
		{
			DBG_ER_LN("dbus_conn_listen is NULL !!!");
			goto exit_dbus;
		}

		if (!dbus_connection_add_filter(dbusx_req->dbus_conn_listen, dbusx_filter, (void *)user, NULL))
		{
			DBG_ER_LN("dbus_connection_add_filter error !!!");
			goto exit_dbus;
		}

		if (dbusx_add_match(dbusx_req->dbus_conn_listen, &dbus_err, (void *)user) != 0 )
		{
			goto exit_dbus;
		}

		DBG_IF_LN("dbus listen ...");
		while (threadx_isquit(tidx_req) == 0)
		{
			dbus_connection_read_write_dispatch(dbusx_req->dbus_conn_listen, 1000);
		}

exit_dbus:
		dbusx_conn_free(dbusx_req);
		SAFE_DBUS_ERR_FREE(&dbus_err);

		threadx_leave(tidx_req);
	}
	DBG_IF_LN(DBG_TXT_BYE_BYE);

	return NULL;
}

DBusConnection *dbusx_listen_get(DbusX_t *dbusx_req)
{
	if (dbusx_req)
		return dbusx_req->dbus_conn_listen;

	return NULL;
}

DBusConnection *dbusx_conn_get(DbusX_t *dbusx_req)
{
	if (dbusx_req)
		return dbusx_req->dbus_conn;

	return NULL;
}

char *dbusx_path_get(DbusX_t *dbusx_req)
{
	if (dbusx_req)
		return dbusx_req->path;

	return NULL;
}

void dbusx_lock(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_lock(tidx_req);
	}
}

void dbusx_unlock(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_unlock(tidx_req);
	}
}

void dbusx_wakeup_simple(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_wakeup_simple(tidx_req);
	}
}

void dbusx_wakeup(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_wakeup(tidx_req);
	}
}

int dbusx_timewait_simple(DbusX_t *dbusx_req, int ms)
{
	int ret = EINVAL;

	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		ret = threadx_timewait_simple(tidx_req, ms);
	}

	return ret;
}

int dbusx_timewait(DbusX_t *dbusx_req, int ms)
{
	int ret = EINVAL;

	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		ret = threadx_timewait(tidx_req, ms);
	}

	return ret;
}

void dbusx_wait_simple(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_wait_simple(tidx_req);
	}
}

void dbusx_wait(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_wait(tidx_req);
	}
}

READY_ID dbusx_ready(DbusX_t *dbusx_req)
{
	ThreadX_t *tidx_req = &dbusx_req->tidx;

	int retry = 3;
	while ((dbusx_req->dbus_conn_listen==NULL) && (retry>0) && ( threadx_isquit(tidx_req) == QUIT_ID_NONE ) )
	{
		retry--;
		sleep(1);
	}

	if (dbusx_req->dbus_conn_listen)
	{
		return READY_ID_OK;
	}
	else
	{
		DBG_ER_LN("(retry: %d)", retry);
		return READY_ID_NONE;
	}
}

void dbusx_req_init(DbusX_t *dbusx_req, char *name, char *path, void *data)
{
	SAFE_MEMSET(dbusx_req, 0, sizeof(DbusX_t));
	SAFE_SPRINTF(dbusx_req->name, "dbusx_%s", name);
	SAFE_SPRINTF(dbusx_req->path, "%s", path);
	dbusx_req->data = data;
}

int dbusx_req_check(DbusX_t *dbusx_req)
{
	int ret = 0;

	if ( SAFE_STRLEN(dbusx_req->path) <= 0 )
	{
		DBG_ER_LN("(path: %s)", dbusx_req->path);
		ret = -1;
	}

	return ret;
}

int dbusx_thread_init(dbusx_match_fn *match_cb, dbusx_filter_fn *filter_cb, DbusX_t *dbusx_req)
{
	dbusx_req->add_match_cb = match_cb;
	dbusx_req->filter_user_cb = filter_cb;

	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		tidx_req->thread_cb = dbusx_thread_handler;
		tidx_req->data = dbusx_req;
		threadx_init(tidx_req, dbusx_req->name);
	}

	return 0;
}

void dbusx_thread_stop(DbusX_t *dbusx_req)
{
	if (dbusx_req)
	{
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_stop(tidx_req);
	}
}

void dbusx_thread_close(DbusX_t *dbusx_req)
{
	if ((dbusx_req) && (dbusx_req->isfree == 0))
	{
		dbusx_req->isfree ++;
	
		ThreadX_t *tidx_req = &dbusx_req->tidx;
		threadx_close(tidx_req);

		dbusx_conn_free(dbusx_req);
	}
}

