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

#define LEDX_GPIOXX "/sys/class/leds/led"
#define LED1_GPIO43 "/sys/class/leds/led1/brightness"
#define LED2_GPIO41 "/sys/class/leds/led2/brightness"
#define LED3_GPIO39 "/sys/class/leds/led3/brightness"

#define LED_ORDER_ON "on"
#define LED_ORDER_OFF "off"

LedOn_t ledon_normal[MAX_OF_LEDON]=
{
	{LED_ID_1, LED_ACTION_ID_ON, 200},
	{LED_ID_1, LED_ACTION_ID_OFF, 3000},
};

static void led_turn_on_cb(void *usr_data)
{
	LedOn_t *ledon = (LedOn_t *)usr_data;

	DBG_TR_LN("(id: %d, action: %d, duration: %d)", ledon->id, ledon->action, ledon->duration);
	char ledname[LEN_OF_BUF128] = "";
	switch (ledon->id)
	{
		case LED_ID_1:
		case LED_ID_2:
		case LED_ID_3:
			SAFE_SPRINTF(ledname, "%s%d/brightness", LEDX_GPIOXX, ledon->id);

			switch (ledon->action)
			{
				case LED_ACTION_ID_ON:
					file_writer(ledname, LED_VAL_1, SAFE_STRLEN(LED_VAL_1));
					break;
				case LED_ACTION_ID_OFF:
				default:
					file_writer(ledname, LED_VAL_0, SAFE_STRLEN(LED_VAL_0));
					break;
			}
			break;
		default:
			DBG_WN_LN("%s (id: %d)", DBG_TXT_WRONG, ledon->id);
			break;
	}
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	//dbg_lvl_set(DBG_LVL_DEBUG);

	LedOn_t *ledon_ary = (LedOn_t*)&ledon_normal;

	LedOn_t *ledon = NULL;

	ledon = (LedOn_t *)&ledon_ary[0];
	DBG_ER_LN("(action: %d, duration: %d)", ledon->action, ledon->duration);

	ledon = (LedOn_t *)&ledon_ary[1];
	DBG_ER_LN("(action: %d, duration: %d)", ledon->action, ledon->duration);

	LedRequest_t *ledreq_1 = led_thread_init("led1", -1, (LedOn_t*)&ledon_normal, led_turn_on_cb);

	while (1)
	{
		sleep(1);
	}

	SAFE_LED_CLOSE(ledreq_1);

	exit(0);
}
