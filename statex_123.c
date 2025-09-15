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

void sys_init2_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_free2_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_leave2_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_enter2_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}

void sys_init1_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_free1_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_leave1_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_enter1_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}

void sys_init0_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_free0_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_leave0_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}
void sys_enter0_cb(StateXFn_t *fn_link, void *data)
{
	DBG_ER_LN(DBG_TXT_ENTER);
}

StateXFn_t sys_fn_links[] =
{
	// action, init_cb, free_cb, leave_cb, enter_cb
	{0, -1, ACTION_ID_OFF, sys_init0_cb, sys_free0_cb, sys_leave0_cb, sys_enter0_cb},
	{1, -1, ACTION_ID_OFF, sys_init1_cb, sys_free1_cb, sys_leave1_cb, sys_enter1_cb},
	{2, -1, ACTION_ID_OFF, sys_init2_cb, sys_free2_cb, sys_leave2_cb, sys_enter2_cb},
	{3, -1, ACTION_ID_OFF, NULL, NULL, NULL, NULL}, /* terminator */
};

StateX_t statex_sys =
{
	.fn_last = NULL,
	.fn_links = sys_fn_links,

	.dbg_more = DBG_LVL_MAX,
};

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	statex_open(&statex_sys, "sys");
	statex_push(&statex_sys, 2, SUBITEM_ID_NONE, ACTION_ID_ON, ACTION_RUN_ID_NORMAL);
	statex_push(&statex_sys, 0, SUBITEM_ID_NONE, ACTION_ID_ON, ACTION_RUN_ID_NORMAL);
	statex_push(&statex_sys, 1, SUBITEM_ID_NONE, ACTION_ID_ON, ACTION_RUN_ID_NORMAL);
	//statex_add(&statex_sys, 0, SUBITEM_ID_NONE, ACTION_ID_OFF, ACTION_RUN_ID_NORMAL);
	//statex_add(&statex_sys, 1, SUBITEM_ID_NONE, ACTION_ID_OFF, ACTION_RUN_ID_NORMAL);
	int retry = 4;
	while (retry>0)
	{
		sleep(1);
		retry--;
	}
	statex_close(&statex_sys);

	exit(0);
}
