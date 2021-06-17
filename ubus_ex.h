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
#ifndef __UBUS_EX_H__
#define __UBUS_EX_H__

#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************************
//** include **
//******************************************************************************


//******************************************************************************
//** UTIL_EX_XXX **
//******************************************************************************
//** Linux **
#undef UTIL_EX_UBUS


//******************************************************************************
//** UTIL_EX_UBUS **
//******************************************************************************
#ifdef UTIL_EX_UBUS
#include <libubox/blobmsg_json.h>
#include <libubus.h>

void uloop_timeout_set_ex(void);
int uloop_timerlist_add(uloop_timeout_handler cb, int msecs);
void uloop_end_ex(void);

int ubus_cli_register_event(const char *pattern, ubus_event_handler_t cb);
int ubus_cli_subscribe(char *obj_name, ubus_handler_t cb, ubus_remove_handler_t remove_cb);
int ubus_cli_invoke_ex(char *obj_name, const char *method, struct blob_buf *bbuf, ubus_data_handler_t cb, int timeout);
int ubus_srv_notify_simple(const char *method, struct ubus_object *obj, char *key, char *val);
int ubus_srv_send_event_ex(const char *obj_name, struct blob_buf *bbuf);
int ubus_srv_send_event_simple(const char *obj_name, char *key, char *val);

int ubus_srv_add_object_ex(struct ubus_context *ctx, struct ubus_object *obj);
int ubus_srv_object_subscribe(struct ubus_context *ctx, struct ubus_object *obj, ubus_state_handler_t subscribe_cb);

void ubus_cli_list_register(const char *path, ubus_lookup_handler_t cb);

struct ubus_context *ubus_conn_init(void);
struct ubus_context *ubus_conn_get(void);

struct ubus_context *ubus_srv_init(void);
void ubus_conn_free(void);

void ubus_root_set(char *path);
char *ubus_root_get(void);

void ubus_quit_set(QUIT_ID quit);
QUIT_ID ubus_quit(void);
void ubus_ready_set(READY_ID ready);
READY_ID ubus_ready(void);
void ubus_add_uloop_ex(struct ubus_context *ctx);

int ubus_thread_init(void);
void ubus_thread_stop(void);
void ubus_thread_close(void);

#endif


#ifdef __cplusplus
}
#endif

#endif
