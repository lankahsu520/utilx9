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

static pthread_t tid = 0;

int thread_exit = 0;

static void *thread_handler(void *arg)
{
	int i = 10;
	while (i>0)
	{
		i--;
		DBG_DB_LN("thread_handler - %d", i);
		sleep(1);
	}

	thread_exit = 1;
	DBG_DB_LN("thread_handler exit - %d", i);
	return NULL;
}

int thread_init(void)
{
	int ret = 0;
	if (pthread_create(&tid, NULL, thread_handler, NULL) != 0)
	{
		DBG_ER_LN("pthread_create error !!!");
		return -1;
	}
	return ret;
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	thread_init();

	while (thread_exit==0)
	{
		// busy loop
		sleep(1);
	}

	DBG_TR_LN(DBG_TXT_BYE_BYE);
	exit(0);
}
