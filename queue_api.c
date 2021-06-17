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

void queue_lock(QueueInfo_t *queue)
{
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		threadx_lock(tidx_req);
	}
}

void queue_unlock(QueueInfo_t *queue)
{
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		threadx_unlock(tidx_req);
	}
}

void queue_signal(QueueInfo_t *queue)
{
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		threadx_wakeup(tidx_req);
	}
}

int queue_timewait(QueueInfo_t *queue, int ms)
{
	int ret = EINVAL;

	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		ret = threadx_timewait(tidx_req, ms);
	}

	return ret;
}

void queue_wait(QueueInfo_t *queue)
{
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		threadx_wait(tidx_req);
	}
}

void queue_debug(QueueInfo_t *queue, int dbg_more)
{
	if (queue)
	{
		queue->dbg_more = dbg_more;
	}
}

static void queue_create(QueueInfo_t *queue)
{
#ifdef UTIL_EX_CLIST
	CLIST_STRUCT_INIT(queue, qlist);
#else
	queue->datas = SAFE_CALLOC(queue->queue_size, queue->data_size);
#endif
	queue->data_pop = SAFE_CALLOC(1, queue->data_size);
}

void queue_free(QueueInfo_t *queue)
{
	if (queue)
	{
		queue_lock(queue);

#ifdef UTIL_EX_CLIST
		while (clist_length(queue->qlist) > 0)
		{
			QItem_t *qitem = (QItem_t *)clist_pop(queue->qlist);
			if (qitem)
			{
				if (queue->free_cb)
				{
					queue->free_cb(qitem->data);
				}
				SAFE_FREE(qitem->data);
				SAFE_FREE(qitem);
			}
		}
		clist_free(queue->qlist);
#else
		while ( queue_isempty(queue) != 1 )
		{
			void *datas = (void *)queue->datas;

			queue->head_pos++;
			queue->head_pos %= queue->max_data;

			if (queue->free_cb)
			{
				queue->free_cb( datas + (queue->head_pos*queue->data_size) );
			}
		}
		SAFE_FREE(queue->datas);
#endif
		SAFE_FREE(queue->data_pop);

		queue_unlock(queue);
	}
}

int queue_length(QueueInfo_t *queue)
{
	int ret = 0;
	if (queue)
	{
		queue_lock(queue);
		ret = clist_length(queue->qlist);
		queue_unlock(queue);
	}
	return ret;
}

// 1: full, 0: not full
int queue_isfull(QueueInfo_t *queue)
{
	int ret = 0;
	if (queue)
	{
		queue_lock(queue);
#ifdef UTIL_EX_CLIST
		if (clist_length(queue->qlist) >= queue->max_data)
#else
		if ( ((queue->tail_pos+1)% queue->max_data) == queue->head_pos )
#endif
		{
			DBG_WN_LN("%s is full.", queue->name);
			ret = 1;
		}
		queue_unlock(queue);
	}
	return ret;
}

// 1: empty, 0: not empty
int queue_isempty(QueueInfo_t *queue)
{
	int ret = 0;
	if (queue)
	{
		queue_lock(queue);
#ifdef UTIL_EX_CLIST
		if (clist_length(queue->qlist) <= 0)
#else
		if ( (queue->head_pos % queue->max_data) == (queue->tail_pos % queue->max_data))
#endif
		{
			DBG_TMP_Y("%s is empty.", queue->name);
			ret = 1;
		}
		queue_unlock(queue);
	}
	return ret;
}

int queue_isloop(QueueInfo_t *queue)
{
	int isloop = 0;
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		isloop = threadx_isloop(tidx_req);
	}
	return isloop;
}

int queue_isquit(QueueInfo_t *queue)
{
	int isquit = 0;
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		isquit = threadx_isquit(tidx_req);
	}
	return isquit;
}

// 20 = 2 secs
int queue_isready(QueueInfo_t *queue, int retry)
{
	int isready = 0;
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		isready = threadx_isready(tidx_req, retry);
	}

	return isready;
}

void queue_gosleep(QueueInfo_t *queue)
{
	if (queue==NULL) return;
	if (queue_isloop(queue)==0) return;

	queue_lock(queue);
	queue->ishold = 1;
	queue_unlock(queue);
}

void queue_wakeup(QueueInfo_t *queue)
{
	if (queue==NULL) return;
	if (queue_isloop(queue)==0) return;

	queue_lock(queue);
	queue->ishold = 0;
	queue_signal(queue);
	queue_unlock(queue);
}

void queue_add(QueueInfo_t *queue, void *data_new)
{
	if (queue==NULL) return;
	if (queue_isloop(queue)==0) return;

	queue_lock(queue);
	if ( queue->dbg_more < DBG_LVL_MAX )
	{
		DBG_IF_LN("(name: %s, length: %d/%d, ishold: %d, isloop: %d)", queue->name, clist_length(queue->qlist), queue->max_data, queue->ishold, queue_isloop(queue));
	}

	if ( (queue_isquit(queue)== 0) && ( !queue_isfull(queue) ) )
	{
#ifdef UTIL_EX_CLIST
		QItem_t *qitem = (QItem_t*)SAFE_CALLOC(1, sizeof(QItem_t));
		qitem->data = (void*)SAFE_CALLOC(1, queue->data_size);
		SAFE_MEMCPY(qitem->data, data_new, queue->data_size, queue->data_size);
		clist_add(queue->qlist, qitem);
#else
		// No support !!!
#endif

		DBG_TR_LN("(clist_length: %d)", clist_length(queue->qlist));
		if ( queue->ishold == 0 )
		{
			queue_signal(queue);
		}
	}
	queue_unlock(queue);
}

void queue_push(QueueInfo_t *queue, void *data_new)
{
	if (queue==NULL) return;
	if (queue_isloop(queue)==0) return;

	queue_lock(queue);
	if ( queue->dbg_more < DBG_LVL_MAX )
	{
		DBG_IF_LN("(name: %s, length: %d/%d, ishold: %d, isloop: %d)", queue->name, clist_length(queue->qlist), queue->max_data, queue->ishold, queue_isloop(queue));
	}

	if ( (queue_isquit(queue)== 0) && ( !queue_isfull(queue) ) )
	{
#ifdef UTIL_EX_CLIST
		QItem_t *qitem = (QItem_t*)SAFE_CALLOC(1, sizeof(QItem_t));
		qitem->data = (void*)SAFE_CALLOC(1, queue->data_size);
		SAFE_MEMCPY(qitem->data, data_new, queue->data_size, queue->data_size);
		clist_push(queue->qlist, qitem);
#else
		queue->tail_pos++;
		queue->tail_pos %= queue->max_data;

		void *datas = (void *)queue->datas;
		SAFE_MEMSET(datas + (queue->tail_pos*queue->data_size), 0, queue->data_size);
		SAFE_MEMCPY(datas + (queue->tail_pos*queue->data_size), data_new, queue->data_size, queue->data_size);
#endif

		if ( queue->ishold == 0 )
		{
			queue_signal(queue);
		}
	}
	queue_unlock(queue);
}

static void queue_pop(QueueInfo_t *queue)
{
	int exec = 0;
	if (queue==NULL) return;

	void *data_pop = (void *)queue->data_pop;

	//int old = clist_length(queue->qlist);
	queue_lock(queue);
	if ( queue->dbg_more < DBG_LVL_MAX )
	{
		DBG_IF_LN("(name: %s, length: %d/%d, ishold: %d, isloop: %d)", queue->name, clist_length(queue->qlist), queue->max_data, queue->ishold, queue_isloop(queue));
	}

	if ( ( queue_isquit(queue) == 0 ) && ( queue->ishold == 0 ) && (queue_isempty(queue) != 1) )
	{
		SAFE_MEMSET(data_pop, 0, queue->data_size);

#ifdef UTIL_EX_CLIST
		QItem_t *qitem = (QItem_t *)clist_pop(queue->qlist);
		SAFE_MEMCPY(data_pop, qitem->data, queue->data_size, queue->data_size);
		SAFE_FREE(qitem->data);
		SAFE_FREE(qitem);
#else
		void *datas = (void *)queue->datas;

		queue->head_pos++;
		queue->head_pos %= queue->max_data;

		SAFE_MEMCPY(data_pop, datas + (queue->head_pos*queue->data_size), queue->data_size, queue->data_size);
		SAFE_MEMSET(datas + (queue->head_pos*queue->data_size), 0, queue->data_size);
#endif

		exec = 1;
	}
	else if ( queue_isquit(queue) == 0 )
	{
		queue_wait(queue);
	}
	queue_unlock(queue);

	if (exec)
	{
		if (queue->exec_cb)
		{
			queue->exec_cb(data_pop);
		}
		if (queue->free_cb)
		{
			queue->free_cb(data_pop);
		}
	}
	//int new = clist_length(queue->qlist);
}

static void *queue_thread_handler( void *user )
{
	QueueInfo_t *queue = (QueueInfo_t*)user;

	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		threadx_detach(tidx_req);

		queue_create(queue);

		while (threadx_isquit(tidx_req) == 0)
		{
			queue_pop(queue);
		}

		queue_free(queue);

		threadx_leave(tidx_req);
	}

	return NULL;
}

void queue_thread_stop(QueueInfo_t *queue)
{
	if (queue)
	{
		ThreadX_t *tidx_req = &queue->tidx;
		threadx_stop(tidx_req);
	}
}

void queue_thread_close(QueueInfo_t *queue)
{
	if ((queue) && (queue->isfree == 0))
	{
		queue->isfree ++;

		ThreadX_t *tidx_req = &queue->tidx;
		threadx_close(tidx_req);

		SAFE_FREE(queue);
	}
}

QueueInfo_t *queue_thread_init(char *name, int queue_size, int data_size, queue_fn exec_cb, queue_fn free_cb)
{
	QueueInfo_t *queue = (QueueInfo_t*)SAFE_CALLOC(1, sizeof(QueueInfo_t));

	if (queue)
	{
		SAFE_SPRINTF(queue->name, "%s", name);
		//queue->in_mtx = PTHREAD_MUTEX_INITIALIZER;
		//queue->in_cond = PTHREAD_COND_INITIALIZER;

		queue->data_size = data_size;
		queue->max_data = queue_size;
		queue->exec_cb = exec_cb;
		queue->free_cb = free_cb;
		queue->dbg_more = DBG_LVL_MAX;

		{
			ThreadX_t *tidx_req = &queue->tidx;
			tidx_req->thread_cb = queue_thread_handler;
			tidx_req->data = queue;
			threadx_init(tidx_req);
		}
	}
	return queue;
}


