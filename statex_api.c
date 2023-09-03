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

#define MAX_OF_QSTATEX     30

StateXFn_t *statex_fn_last(StateX_t *statex_req)
{
	return statex_req->fn_last;
}

static void statex_free(StateX_t *statex_req, StateXFn_t *fn_curr)
{
	if(fn_curr->init_count)
	{
		if(fn_curr->free_cb)
		{
			fn_curr->free_cb(fn_curr, statex_req->data);
		}
		fn_curr->init_count --;
	}
}

void statex_debug_q(StateX_t *statex_req, int dbg_more)
{
	if(statex_req)
	{
		queuex_debug(statex_req->statex_q, dbg_more);
	}
}

void statex_debug(StateX_t *statex_req, int dbg_more)
{
	if(statex_req)
	{
		statex_req->dbg_more = dbg_more;
	}
}

// curr-init -> last-leave -> curr-enter
static int statex_rotate(StateX_t *statex_req, int run)
{
	int ret = 0;
	StateXFn_t *fn_last = statex_req->fn_last;
	StateXFn_t *fn_links = statex_req->fn_links;
	StateXFn_t *fn_curr = NULL;

	int idx = 0;
	int change = 0;
	while((fn_curr = &fn_links[idx]) && (fn_curr->enter_cb))
	{
		if(fn_curr->action == ACTION_ID_ON)
		{
			if(statex_req->fn_last != fn_curr)
			{
				statex_req->fn_last = fn_curr;
				change = 1;
			}
			else
			{
				// again
				// enter
				//DBG_ER_LN(">>>>>>>>>>>>>> (run: 0x%02X)", run);
				if((run & ACTION_RUN_ID_AGAIN) == ACTION_RUN_ID_AGAIN)
				{
					if(fn_curr->enter_cb)
					{
						fn_curr->enter_cb(fn_curr, statex_req->data);
					}
				}
			}

			if(change == 1)
			{
				// leave
				if(fn_last)
				{
					if(fn_last->leave_cb)
					{
						fn_last->leave_cb(fn_last, statex_req->data);
					}
				}

				// enter
				if(fn_curr->enter_cb)
				{
					fn_curr->enter_cb(fn_curr, statex_req->data);
				}
			}
			goto exit_rotate;
		}
		idx++;
	}

exit_rotate:
	return ret;
}

static void statex_switch(StateX_t *statex_req, int idx, int subitem, ACTION_ID action, int run)
{
	StateXFn_t *fn_links = statex_req->fn_links;
	StateXFn_t *fn_curr = &fn_links[idx];

	if(action == ACTION_ID_ON)
	{
		// init
		if(fn_curr->init_count==0)
		{
			if(fn_curr->init_cb)
			{
				fn_curr->init_cb(fn_curr, statex_req->data);
			}
			fn_curr->init_count ++;
		}
	}
	fn_curr->action = action;
	fn_curr->subitem = subitem;

	statex_rotate(statex_req, run);

	if(action == ACTION_ID_OFF)
	{
		// free
		statex_free(statex_req, fn_curr);
	}
}

static void statex_new(StateXPuck_t *puck_new, StateX_t *statex_req, int idx, int subitem, ACTION_ID action, int run)
{
	puck_new->idx = idx;
	puck_new->subitem = subitem;
	puck_new->action = action;
	puck_new->run = run;
	puck_new->statex_req = statex_req;
}

void statex_add(StateX_t *statex_req, int idx, int subitem, ACTION_ID action, int run)
{
	if((statex_req) && (statex_req->statex_q))
	{
		StateXPuck_t puck_new;

		statex_new(&puck_new, statex_req, idx, subitem, action, run);
		queuex_add(statex_req->statex_q, (void*)&puck_new);
	}
	else
	{
		DBG_ER_LN("statex_add error !!!");
	}
}

void statex_push(StateX_t *statex_req, int idx, int subitem, ACTION_ID action, int run)
{
	if((statex_req) && (statex_req->statex_q))
	{
		StateXPuck_t puck_new;

		statex_new(&puck_new, statex_req, idx, subitem, action, run);
		queuex_push(statex_req->statex_q, (void*)&puck_new);
	}
	else
	{
		DBG_ER_LN("statex_push error !!!");
	}
}

static int statex_q_free_cb(void *arg)
{
	StateXPuck_t *data_pop = (StateXPuck_t *)arg;

	if(data_pop)
	{
	}

	return 0;
}

static int statex_q_exec_cb(void *arg)
{
	StateXPuck_t *data_pop = (StateXPuck_t *)arg;

	if((data_pop) && (data_pop->statex_req))
	{
		StateX_t *statex_req = data_pop->statex_req;
		QueueX_t *statex_q = statex_req->statex_q;

		char *name = statex_q->name;
		int idx = data_pop->idx;
		int subitem = data_pop->subitem;
		ACTION_ID action = data_pop->action;
		int run = data_pop->run;

		if(statex_req->dbg_more < DBG_LVL_MAX)
		{
			DBG_IF_LN("(name: %s, idx: %d, subitem: %d, action: %d, run : %d)", name, idx, subitem, action, run);
		}
		statex_switch(statex_req, idx, subitem, action, run);
	}

	return 0;
}

int statex_open(StateX_t *statex_req, char *name)
{
	int ret = 0;
	statex_req->statex_q = queuex_thread_init(name, MAX_OF_QSTATEX, sizeof(StateXPuck_t), statex_q_exec_cb, statex_q_free_cb);
	if(statex_req->statex_q)
	{
		queuex_isready(statex_req->statex_q, 20);
	}
	else
	{
		ret = -1;
	}

	return ret;
}

void statex_close(StateX_t *statex_req)
{
	{
		queuex_thread_stop(statex_req->statex_q);
		queuex_thread_close(statex_req->statex_q);
	}
	{
		StateXFn_t *fn_links = statex_req->fn_links;
		StateXFn_t *fn_curr = NULL;

		int idx = 0;
		while((fn_curr = &fn_links[idx]) && (fn_curr->enter_cb))
		{
			fn_curr->action = ACTION_ID_OFF;
			statex_free(statex_req, fn_curr);
			idx++;
		}
	}
}
