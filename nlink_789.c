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

ChainX_t chainX_n = {
	.mode = CHAINX_MODE_ID_NETLINK,
	.sockfd = -1,
	.status = 0,
	.isfree = 0,

	.security = 0,
	.noblock = 1,

	.retry_hold = TIMEOUT_OF_RETRY_HOLD,
	.select_wait = TIMEOUT_OF_SELECT_1,
	.c_data = NULL,
};

void netlink_recv(ChainX_t *chainX_req, char *ifname, int index, char *status)
{
	DBG_IF_LN("Got !!! (ifname: %s, index: %d, status: %s)", ifname, index, status);
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	dbg_lvl_set(DBG_LVL_TRACE);
	chainX_netlink_register(&chainX_n, netlink_recv);

	chainX_thread_init(&chainX_n); 
	while (1)
	{
		sleep(1);
		if (chainX_linked_check(&chainX_n)==0)
		{
		}
	}

	chainX_thread_stop(&chainX_n);
	chainX_thread_close(&chainX_n);

	exit(0);
}
