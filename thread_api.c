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

void threadx_mutex_init(ThreadX_t *tidx_req)
{
	if (tidx_req==NULL) return;

	int rc = SAFE_MUTEX_ATTR_RECURSIVE(tidx_req->in_mtx);
	if (rc == 0)
	{
#ifdef USE_THREAD_CLOCK
		SAFE_COND_ATTR_CLOCK(tidx_req->in_cond);
#else
		SAFE_COND_ATTR_NORMAL(tidx_req->in_cond);
#endif
	}
}

void threadx_mutex_free(ThreadX_t *tidx_req)
{
	SAFE_MUTEX_DESTROY_EX(tidx_req);
	SAFE_COND_DESTROY_EX(tidx_req);
}

int threadx_isloop(ThreadX_t *tidx_req)
{
	int isloop = 0;
	threadx_lock(tidx_req);
	isloop = tidx_req->isloop;
	threadx_unlock(tidx_req);
	return isloop;
}

int threadx_ispause(ThreadX_t *tidx_req)
{
	int ispause = 0;
	threadx_lock(tidx_req);
	ispause = tidx_req->ispause;
	threadx_unlock(tidx_req);
	return ispause;
}

void threadx_set_pause(ThreadX_t *tidx_req, int flag)
{
	threadx_lock(tidx_req);
	tidx_req->ispause = flag;
	threadx_unlock(tidx_req);
}

int threadx_isquit(ThreadX_t *tidx_req)
{
	int isquit = 0;
	threadx_lock(tidx_req);
	isquit = tidx_req->isquit;
	threadx_unlock(tidx_req);
	return isquit;
}

void threadx_set_quit(ThreadX_t *tidx_req, int flag)
{
	threadx_lock(tidx_req);
	tidx_req->isquit = flag;
	threadx_unlock(tidx_req);
}

// 20 = 2 secs
int threadx_isready(ThreadX_t *tidx_req, int retry)
{
	if (retry<0) retry = 10;

	while (retry>0)
	{
		if (tidx_req->isloop==1) break;
		if (tidx_req->isquit==1) break;
		if (tidx_req->isexit==1) break;

		retry--;
		usleep(100*1000);
	}

	return tidx_req->isloop;
}

int threadx_lock(ThreadX_t *tidx_req)
{
	return SAFE_THREAD_LOCK_EX(tidx_req);
}

int threadx_unlock(ThreadX_t *tidx_req)
{
	return SAFE_THREAD_UNLOCK_EX(tidx_req);
}

int threadx_timewait(ThreadX_t *tidx_req, int ms)
{
	if ( threadx_isquit(tidx_req) ) return EINVAL;

	int ret = EINVAL;

#ifdef USE_THREAD_CLOCK
	ret = SAFE_THREAD_TIMEWAIT_CLOCK_EX(tidx_req, ms);
#else
	ret = SAFE_THREAD_TIMEWAIT_EX(tidx_req, ms);
#endif

	return ret;
}

int threadx_timewait_simple(ThreadX_t *tidx_req, int ms)
{
	if ( threadx_isquit(tidx_req) ) return EINVAL;

	int ret = EINVAL;

	threadx_lock(tidx_req);
	ret = threadx_timewait(tidx_req, ms);
	threadx_unlock(tidx_req);

	return ret;
}

int threadx_wait(ThreadX_t *tidx_req)
{
	if ( threadx_isquit(tidx_req) ) return EINVAL;

	return SAFE_THREAD_WAIT_EX(tidx_req);
}

int threadx_wait_simple(ThreadX_t *tidx_req)
{
	if ( threadx_isquit(tidx_req) ) return EINVAL;

	int __ret = EINVAL;
	threadx_lock(tidx_req);
	__ret = SAFE_THREAD_WAIT_EX(tidx_req);
	threadx_unlock(tidx_req);

	return __ret;
}

void threadx_wakeup(ThreadX_t *tidx_req)
{
	SAFE_THREAD_BROADCAST_EX(tidx_req);
}

void threadx_wakeup_simple(ThreadX_t *tidx_req)
{
	threadx_lock(tidx_req);
	SAFE_THREAD_BROADCAST_EX(tidx_req);
	threadx_unlock(tidx_req);
}

void threadx_leave(ThreadX_t *tidx_req)
{
	SAFE_THREAD_LEAVE(tidx_req);
}

int threadx_detach(ThreadX_t *tidx_req)
{
	//return SAFE_THREAD_DETACH_EX(tidx_req);
	return SAFE_THREAD_DETACH_CHECK(tidx_req);
}

int threadx_join(ThreadX_t *tidx_req)
{
	//return SAFE_THREAD_JOIN_EX(tidx_req);
	return SAFE_THREAD_JOIN_CHECK(tidx_req);
}

void threadx_stop(ThreadX_t *tidx_req)
{
	if (tidx_req)
	{
		threadx_set_quit(tidx_req, 1);
		threadx_wakeup_simple(tidx_req);
	}
}

void threadx_close(ThreadX_t *tidx_req)
{
	if ( (tidx_req) && (tidx_req->isfree == 0) )
	{
		tidx_req->isfree++;

		threadx_stop(tidx_req);

		threadx_join(tidx_req);

		threadx_mutex_free(tidx_req);
	}
}

int threadx_init(ThreadX_t *tidx_req)
{
	int ret = 0;

	if (tidx_req)
	{
	
		tidx_req->isexit = 0;
		tidx_req->isfree = 0;
		tidx_req->isloop = 0;
		tidx_req->ispause = 0;
		tidx_req->isquit = 0;

		threadx_mutex_init(tidx_req);

		if (SAFE_THREAD_CREATE(tidx_req->tid, NULL, tidx_req->thread_cb, (void*)tidx_req->data) != 0)
		{
			DBG_ER_LN("SAFE_THREAD_CREATE error !!!");
			ret = -1;
		}
	}
	else
	{
		ret = -1;
	}

	return ret;
}
