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

ThreadX_t tidx_data;

static void *thread_handler(void *user)
{
	ThreadX_t *tidx_req = (ThreadX_t*)user;

	threadx_detach(tidx_req);

	int count = 0;
	DBG_IF_LN("(count: %d)", count++);

	while (threadx_isquit(tidx_req)==0)
	{
		if (threadx_ispause(tidx_req)==0)
		{
			DBG_IF_LN("(count: %d)", count++);
			if (( count % 10) == 0)
			{
				DBG_IF_LN("wait 3 seconds ...");
				threadx_timewait_simple(tidx_req, 3*1000);
				//break;
			}
		}
		else
		{
			threadx_wait_simple(tidx_req);
		}
	}

	threadx_leave(tidx_req);
	DBG_IF_LN(DBG_TXT_BYE_BYE);

	return NULL;
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	tidx_data.thread_cb = thread_handler;
	tidx_data.data = (void *)&tidx_data;

	threadx_init(&tidx_data, "thread_123");

	while ( (threadx_isquit(&tidx_data)==0) )
	{
		// busy loop
		sleep(1);
	}

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	exit(0);
}
