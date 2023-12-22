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

typedef struct DemoList_STRUCT
{
	void* next;

	int num;
} DemoList_t;

CLIST(demo_list);

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");
	//dbg_lvl_set(DBG_LVL_DEBUG);

	int idx = 0;
	clist_init(demo_list);
	DemoList_t *item = NULL;

	while ( idx < 10 )
	{
		item = (DemoList_t*)SAFE_CALLOC(1, sizeof(DemoList_t));
		item->num = idx++;

		if (item->num%4==0)
		{
			clist_add(demo_list, item);
		}
		else
		{
			clist_push(demo_list, item);
		}
	}

	while ( clist_length(demo_list) > 0 )
	{
		item = (DemoList_t*)clist_pop(demo_list);
		DBG_IF_LN("(num: %d)", item->num);
	}

	clist_free(demo_list);
	exit(0);
}
