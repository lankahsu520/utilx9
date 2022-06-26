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

#define DBG_TMP_Y(format,args...) //DBG_LN_Y(format, ## args)
#define DBG_TMP_DUMP(ibuf,len,delim,format,args...) //DBG_TR_DUMP(ibuf,len,delim,format,## args)

#ifdef UTIL_EX_CLIST
typedef struct QItem_Struct
{
	void* next;

	void *data; // queue_api will alloc and free it 
} QItem_t;
#endif

void queuex_lock(QueueX_t *queuex_req)
{
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_lock(tidx_req);
	}
}

void queuex_unlock(QueueX_t *queuex_req)
{
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_unlock(tidx_req);
	}
}

void queuex_signal(QueueX_t *queuex_req)
{
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_wakeup(tidx_req);
	}
}

int queuex_timewait(QueueX_t *queuex_req, int ms)
{
	int ret = EINVAL;

	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		ret = threadx_timewait(tidx_req, ms);
	}

	return ret;
}

void queuex_wait(QueueX_t *queuex_req)
{
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_wait(tidx_req);
	}
}

void queuex_debug(QueueX_t *queuex_req, int dbg_more)
{
	if (queuex_req)
	{
		queuex_req->dbg_more = dbg_more;
	}
}

static void queue_create(QueueX_t *queuex_req)
{
#ifdef UTIL_EX_CLIST
	CLIST_STRUCT_INIT(queuex_req, qlist);
#else
	queuex_req->datas = SAFE_CALLOC(queuex_req->queue_size, queuex_req->data_size);
#endif
	queuex_req->data_pop = SAFE_CALLOC(1, queuex_req->data_size);
}

void queuex_free(QueueX_t *queuex_req)
{
	if (queuex_req)
	{
		queuex_lock(queuex_req);

#ifdef UTIL_EX_CLIST
		while (clist_length(queuex_req->qlist) > 0)
		{
			QItem_t *qitem = (QItem_t *)clist_pop(queuex_req->qlist);
			if (qitem)
			{
				if (queuex_req->free_cb)
				{
					queuex_req->free_cb(qitem->data);
				}
				SAFE_FREE(qitem->data);
				SAFE_FREE(qitem);
			}
		}
		clist_free(queuex_req->qlist);
#else
		while ( queuex_isempty(queuex_req) != 1 )
		{
			void *datas = (void *)queuex_req->datas;

			queuex_req->head_pos++;
			queuex_req->head_pos %= queuex_req->max_data;

			if (queuex_req->free_cb)
			{
				queuex_req->free_cb( datas + (queuex_req->head_pos * queuex_req->data_size) );
			}
		}
		SAFE_FREE(queuex_req->datas);
#endif
		SAFE_FREE(queuex_req->data_pop);

		queuex_unlock(queuex_req);
	}
}

int queuex_length(QueueX_t *queuex_req)
{
	int ret = 0;
	if (queuex_req)
	{
		queuex_lock(queuex_req);
		ret = clist_length(queuex_req->qlist);
		queuex_unlock(queuex_req);
	}
	return ret;
}

// 1: full, 0: not full
int queuex_isfull(QueueX_t *queuex_req)
{
	int ret = 0;
	if (queuex_req)
	{
		queuex_lock(queuex_req);
#ifdef UTIL_EX_CLIST
		if (clist_length(queuex_req->qlist) >= queuex_req->max_data)
#else
		if ( ((queuex_req->tail_pos+1)% queuex_req->max_data) == queuex_req->head_pos )
#endif
		{
			DBG_WN_LN("%s is full.", queuex_req->name);
			ret = 1;
		}
		queuex_unlock(queuex_req);
	}
	return ret;
}

// 1: empty, 0: not empty
int queuex_isempty(QueueX_t *queuex_req)
{
	int ret = 0;
	if (queuex_req)
	{
		queuex_lock(queuex_req);
#ifdef UTIL_EX_CLIST
		if (clist_length(queuex_req->qlist) <= 0)
#else
		if ( (queuex_req->head_pos % queuex_req->max_data) == (queuex_req->tail_pos % queuex_req->max_data))
#endif
		{
			DBG_TMP_Y("%s is empty.", queuex_req->name);
			ret = 1;
		}
		queuex_unlock(queuex_req);
	}
	return ret;
}

int queue_isloop(QueueX_t *queuex_req)
{
	int isloop = 0;
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		isloop = threadx_isloop(tidx_req);
	}
	return isloop;
}

int queue_isquit(QueueX_t *queuex_req)
{
	int isquit = 0;
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		isquit = threadx_isquit(tidx_req);
	}
	return isquit;
}

// 20 = 2 secs
int queuex_isready(QueueX_t *queuex_req, int retry)
{
	int isready = 0;
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		isready = threadx_isready(tidx_req, retry);
	}

	return isready;
}

void queuex_gosleep(QueueX_t *queuex_req)
{
	if (queuex_req==NULL) return;
	if (queue_isloop(queuex_req)==0) return;

	queuex_lock(queuex_req);
	queuex_req->ishold = 1;
	queuex_unlock(queuex_req);
}

void queuex_wakeup(QueueX_t *queuex_req)
{
	if (queuex_req==NULL) return;
	if (queue_isloop(queuex_req)==0) return;

	queuex_lock(queuex_req);
	queuex_req->ishold = 0;
	queuex_signal(queuex_req);
	queuex_unlock(queuex_req);
}

void queuex_add(QueueX_t *queuex_req, void *data_new)
{
	if (queuex_req==NULL) return;
	if (queue_isloop(queuex_req)==0) return;

	queuex_lock(queuex_req);
	if ( queuex_req->dbg_more < DBG_LVL_MAX )
	{
		DBG_IF_LN("(name: %s, length: %d/%d, ishold: %d, isloop: %d)", queuex_req->name, clist_length(queuex_req->qlist), queuex_req->max_data, queuex_req->ishold, queue_isloop(queuex_req));
	}

	if ( (queue_isquit(queuex_req)== 0) && ( !queuex_isfull(queuex_req) ) )
	{
#ifdef UTIL_EX_CLIST
		QItem_t *qitem = (QItem_t*)SAFE_CALLOC(1, sizeof(QItem_t));
		qitem->data = (void*)SAFE_CALLOC(1, queuex_req->data_size);
		SAFE_MEMCPY(qitem->data, data_new, queuex_req->data_size, queuex_req->data_size);
		clist_add(queuex_req->qlist, qitem);
#else
		// No support !!!
#endif

		DBG_TR_LN("(clist_length: %d)", clist_length(queuex_req->qlist));
		if ( queuex_req->ishold == 0 )
		{
			queuex_signal(queuex_req);
		}
	}
	queuex_unlock(queuex_req);
}

void queuex_push(QueueX_t *queuex_req, void *data_new)
{
	if (queuex_req==NULL) return;
	if (queue_isloop(queuex_req)==0) return;

	queuex_lock(queuex_req);
	if ( queuex_req->dbg_more < DBG_LVL_MAX )
	{
		DBG_IF_LN("(name: %s, length: %d/%d, ishold: %d, isloop: %d)", queuex_req->name, clist_length(queuex_req->qlist), queuex_req->max_data, queuex_req->ishold, queue_isloop(queuex_req));
	}

	if ( (queue_isquit(queuex_req)== 0) && ( !queuex_isfull(queuex_req) ) )
	{
#ifdef UTIL_EX_CLIST
		QItem_t *qitem = (QItem_t*)SAFE_CALLOC(1, sizeof(QItem_t));
		qitem->data = (void*)SAFE_CALLOC(1, queuex_req->data_size);
		SAFE_MEMCPY(qitem->data, data_new, queuex_req->data_size, queuex_req->data_size);
		clist_push(queuex_req->qlist, qitem);
#else
		queuex_req->tail_pos++;
		queuex_req->tail_pos %= queuex_req->max_data;

		void *datas = (void *)queuex_req->datas;
		SAFE_MEMSET(datas + (queuex_req->tail_pos*queuex_req->data_size), 0, queuex_req->data_size);
		SAFE_MEMCPY(datas + (queuex_req->tail_pos*queuex_req->data_size), data_new, queuex_req->data_size, queuex_req->data_size);
#endif

		if ( queuex_req->ishold == 0 )
		{
			queuex_signal(queuex_req);
		}
	}
	queuex_unlock(queuex_req);
}

static void queue_pop(QueueX_t *queuex_req)
{
	int exec = 0;
	if (queuex_req==NULL) return;

	void *data_pop = (void *)queuex_req->data_pop;

	//int old = clist_length(queuex_req->qlist);
	queuex_lock(queuex_req);
	if ( queuex_req->dbg_more < DBG_LVL_MAX )
	{
		DBG_IF_LN("(name: %s, length: %d/%d, ishold: %d, isloop: %d)", queuex_req->name, clist_length(queuex_req->qlist), queuex_req->max_data, queuex_req->ishold, queue_isloop(queuex_req));
	}

	if ( ( queue_isquit(queuex_req) == 0 ) && ( queuex_req->ishold == 0 ) && (queuex_isempty(queuex_req) != 1) )
	{
		SAFE_MEMSET(data_pop, 0, queuex_req->data_size);

#ifdef UTIL_EX_CLIST
		QItem_t *qitem = (QItem_t *)clist_pop(queuex_req->qlist);
		SAFE_MEMCPY(data_pop, qitem->data, queuex_req->data_size, queuex_req->data_size);
		SAFE_FREE(qitem->data);
		SAFE_FREE(qitem);
#else
		void *datas = (void *)queuex_req->datas;

		queuex_req->head_pos++;
		queuex_req->head_pos %= queuex_req->max_data;

		SAFE_MEMCPY(data_pop, datas + (queuex_req->head_pos*queuex_req->data_size), queuex_req->data_size, queuex_req->data_size);
		SAFE_MEMSET(datas + (queuex_req->head_pos*queuex_req->data_size), 0, queuex_req->data_size);
#endif

		exec = 1;
	}
	else if ( queue_isquit(queuex_req) == 0 )
	{
		queuex_wait(queuex_req);
	}
	queuex_unlock(queuex_req);

	if (exec)
	{
		if (queuex_req->exec_cb)
		{
			queuex_req->exec_cb(data_pop);
		}
		if (queuex_req->free_cb)
		{
			queuex_req->free_cb(data_pop);
		}
	}
	//int new = clist_length(queuex_req->qlist);
}

static void *queue_thread_handler( void *user )
{
	QueueX_t *queuex_req = (QueueX_t*)user;

	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_detach(tidx_req);

		queue_create(queuex_req);

		while (threadx_isquit(tidx_req) == 0)
		{
			queue_pop(queuex_req);
		}

		queuex_free(queuex_req);

		threadx_leave(tidx_req);
	}

	return NULL;
}

void queuex_thread_stop(QueueX_t *queuex_req)
{
	if (queuex_req)
	{
		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_stop(tidx_req);
	}
}

void queuex_thread_close(QueueX_t *queuex_req)
{
	if ((queuex_req) && (queuex_req->isfree == 0))
	{
		queuex_req->isfree ++;

		ThreadX_t *tidx_req = &queuex_req->tidx;
		threadx_close(tidx_req);

		SAFE_FREE(queuex_req);
	}
}

QueueX_t *queuex_thread_init(char *name, int queue_size, int data_size, queuex_fn exec_cb, queuex_fn free_cb)
{
	QueueX_t *queuex_req = (QueueX_t*)SAFE_CALLOC(1, sizeof(QueueX_t));

	if (queuex_req)
	{
		SAFE_SPRINTF_EX(queuex_req->name, "%s", name);
		//queuex_req->in_mtx = PTHREAD_MUTEX_INITIALIZER;
		//queuex_req->in_cond = PTHREAD_COND_INITIALIZER;

		queuex_req->data_size = data_size;
		queuex_req->max_data = queue_size;
		queuex_req->exec_cb = exec_cb;
		queuex_req->free_cb = free_cb;
		queuex_req->dbg_more = DBG_LVL_MAX;

		{
			ThreadX_t *tidx_req = &queuex_req->tidx;
			tidx_req->thread_cb = queue_thread_handler;
			tidx_req->data = queuex_req;
			threadx_init(tidx_req, queuex_req->name);
		}
	}
	return queuex_req;
}


