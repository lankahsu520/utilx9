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

ThreadX_t tidx_data_A;
ThreadX_t tidx_data_B;
#define MAX_OF_A 5
#define MAX_OF_B 15

static void *thread_handler(void *user)
{
	ThreadX_t *tidx_req = (ThreadX_t*)user;

	threadx_detach(tidx_req);

	int count = 0;
	DBG_IF_LN("%s (name: %s, count: %d)", DBG_TXT_RUN_LOOP, tidx_req->name, count);

	while (threadx_isquit(tidx_req)==0)
	{
		if (threadx_ispause(tidx_req)==0)
		{
			if (tidx_req == &tidx_data_A)
			{
				DBG_IF_LN("(name: %s, count: %d/%d)", tidx_req->name, count++, MAX_OF_A);
				if (count > MAX_OF_A)
				{
					DBG_IF_LN("(tidx_req: %p, &tidx_data_A: %p)", tidx_req, &tidx_data_A);
					break;
				}
			}
			else if (tidx_req == &tidx_data_B)
			{
				DBG_IF_LN("(name: %s, count: %d/%d)", tidx_req->name, count++, MAX_OF_B);
				if (count > MAX_OF_B)
				{
					DBG_IF_LN("(tidx_req: %p, &tidx_data_B: %p)", tidx_req, &tidx_data_B);
					break;
				}
			}

			//if ((count % 3) == 0)
			{
				//DBG_IF_LN("wait 3 seconds ...");
				threadx_timewait_simple(tidx_req, 1*1000);
				//break;
			}
		}
		else
		{
			threadx_wait_simple(tidx_req);
		}
	}

	threadx_leave(tidx_req);
	DBG_IF_LN("%s (name: %s)", DBG_TXT_BYE_BYE, tidx_req->name);

	return NULL;
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	tidx_data_A.thread_cb = thread_handler;
	tidx_data_A.data = (void *)&tidx_data_A;

	threadx_init(&tidx_data_A, "thread_A");

	tidx_data_B.thread_cb = thread_handler;
	tidx_data_B.data = (void *)&tidx_data_B;

	threadx_init(&tidx_data_B, "thread_B");

	while ((threadx_isquit(&tidx_data_A)==0) || (threadx_isquit(&tidx_data_B)==0))
	{
		// busy loop
		sleep(1);
	}

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	exit(0);
}
