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

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	//dbg_lvl_set(DBG_LVL_DEBUG);

	DBG_ER_LN("(Version: %s)", version_show());
	time_t run_t = time(NULL);
	time_t expired_t = expiration_date();
	DBG_ER_LN("(Debug LVL: %d, Expiration: %ld=%s, Time Diff: %.2f)", dbg_lvl_get(), expired_t, time_now_short(expired_t), time_diff_days(run_t, expired_t));
	DBG_ER_LN("(Toolchain: %s, Path: %s, Build Path: %s)", PJ_TOOLCHAIN_NAME, PJ_TOOLCHAIN_PATH, PJ_ROOT);
	DBG_ER_LN("(Name: %s, Platform: %s, Save: %s, Work: %s)", PJ_NAME, PJ_PLATFORM, PJ_SAVE_PATH, PJ_WORK_PATH);
	DBG_ER_LN("(ICLOUD: %s:%s-%s, IFACE: %s)", PJ_ICLOUD_HOST, PJ_ICLOUD_PORT, PJ_ICLOUD_SECURITY, PJ_IFACE);
	DBG_ER_LN("(MCTT: %s:%d)", PJ_MCTT_IP, (int)MCTT_PORT);

	exit(0);
}
