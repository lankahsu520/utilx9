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

void led_gosleep(LedRequest_t *ledreq)
{
	if (ledreq==NULL) return;

	ThreadX_t *tidx_req = &ledreq->tidx;
	threadx_set_pause(tidx_req, 1);
}

void led_wakeup(LedRequest_t *ledreq)
{
	if (ledreq==NULL) return;

	ThreadX_t *tidx_req = &ledreq->tidx;
	threadx_set_pause(tidx_req, 0);
	threadx_wakeup_simple(tidx_req);
}

static void *led_thread_handler(void *user)
{
	LedRequest_t *ledreq = (LedRequest_t*)user;
	ThreadX_t *tidx_req = &ledreq->tidx;

	threadx_detach(tidx_req);

	if ( ledreq == NULL )
		goto led_exit;
	if ( ledreq->led_on_cb == NULL )
		goto led_exit;
	if ( ledreq->ledon_ary == NULL )
		goto led_exit;

	int idx = 0;
	for (idx = 0; idx < MAX_OF_LEDON; idx++)
	{
		LedOn_t *ledon = (LedOn_t *)&ledreq->ledon_ary[idx];
		if ( ( ledon->id > LED_ID_NONE ) &&  ( ledon->id < LED_ID_MAX ) )
		{
			ledreq->max_led = idx+1;
		}
		else
		{
			break;
		}
	}

	idx = 0;
	while (threadx_isquit(tidx_req)==0)
	{
		if (threadx_ispause(tidx_req)==0)
		{
			LedOn_t *ledon = (LedOn_t *)&ledreq->ledon_ary[idx];
			ledreq->led_on_cb( ledon );

			int hold_next = ledon->duration / TICK_OF_LEDON_10;

			threadx_timewait_simple(tidx_req, hold_next*TICK_OF_LEDON_10);

			if ( (threadx_isquit(tidx_req)==0)  && (threadx_ispause(tidx_req)==0) )
			{
				idx ++;
				idx %= ledreq->max_led;
				if (ledreq->infinite < 0)
				{
					// in loop
				}
				else if ( idx == 0 )
				{
					ledreq->infinite --;
					if (ledreq->infinite == 0)
					{
						// end the thread
						break;
					}
					else
					{
						// go next
					}
				}
			}
		}
		else
		{
			threadx_wait_simple(tidx_req);
		}
	}

led_exit:
	threadx_leave(tidx_req);

	return NULL;
}

static void led_thread_free(LedRequest_t *ledreq)
{
	if (ledreq)
	{
		SAFE_FREE(ledreq);
	}
}

void led_thread_stop(LedRequest_t *ledreq)
{
	if (ledreq)
	{
		threadx_stop(&ledreq->tidx);
	}
}

void led_thread_close(LedRequest_t *ledreq)
{
	if ( (ledreq) && (ledreq->isfree == 0) )
	{
		ledreq->isfree ++;

		threadx_close(&ledreq->tidx);
		led_thread_free(ledreq);
	}
}

LedRequest_t *led_thread_init(char *name, int infinite, LedOn_t *ledon_ary, led_on_fn led_on_cb)
{
	LedRequest_t *ledreq = (LedRequest_t*)SAFE_CALLOC(1, sizeof(LedRequest_t));

	if (ledreq)
	{
		SAFE_SPRINTF(ledreq->name, "%s", name);

		ledreq->infinite = infinite;
		ledreq->ledon_ary = ledon_ary;
		ledreq->led_on_cb = led_on_cb;

		{
			ThreadX_t *tidx_req = &ledreq->tidx;
			tidx_req->thread_cb = led_thread_handler;
			tidx_req->data = ledreq;
			threadx_init(tidx_req);
		}
	}
	return ledreq;
}
