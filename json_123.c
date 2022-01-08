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

static void uuid_test(void)
{
	char guid[LEN_OF_UUID]="";
	os_random_uuid(guid, sizeof(guid));
	DBG_LN_Y("(guid: %s)", guid);
}

int main(int argc, char* argv[])
{
	DBG_LN_Y("enter");

	//dbg_lvl_set(DBG_LVL_DEBUG);
	uuid_test();
	

#ifdef UTIL_EX_JSON
	json_t *jroot = JSON_OBJ_NEW();
	json_t *j1 = JSON_OBJ_NEW();
	json_t *j2 = JSON_OBJ_NEW();
	json_t *j3 = JSON_OBJ_NEW();

	JSON_OBJ_SET_OBJ(jroot, "j1", j1);
	JSON_OBJ_SET_OBJ(j1, "j2", j2);
	JSON_OBJ_SET_OBJ(j2, "j3", j3);
	JSON_OBJ_SET_STR(j3, "logo", "helloworld!!!");

	json_t *jA = JSON_ARY_NEW();
	JSON_OBJ_SET_OBJ(jroot, "jA", jA);
	json_t *jA1 = JSON_OBJ_NEW();
	JSON_ARY_APPEND_OBJ(jA, jA1);
	JSON_OBJ_SET_STR(jA1, "name", "A1");
	JSON_OBJ_SET_INT(jA1, "val", 1);
	json_t *jA2 = JSON_OBJ_NEW();
	JSON_ARY_APPEND_OBJ(jA, jA2);
	JSON_OBJ_SET_STR(jA2, "name", "A2");
	JSON_OBJ_SET_INT(jA2, "val", 2);
	json_t *jA3 = JSON_OBJ_NEW();
	JSON_ARY_APPEND_OBJ(jA, jA3);
	JSON_OBJ_SET_STR(jA3, "name", "A3");
	JSON_OBJ_SET_INT(jA3, "val", 3);

	json_t *jdemo1 = JSON_OBJ_SET_STR(jroot, "demo", "HelloWorld !!!");
	DBG_LN_Y("(jdemo1: %p, refcount: %zd)", jdemo1, jdemo1->refcount);
	json_t *jdemo2 = JSON_OBJ_SET_STR(jroot, "demo", "HelloWorld 1 !!!");
	DBG_LN_Y("(jdemo2: %p, refcount: %zd)", jdemo2, jdemo2->refcount);
	DBG_LN_Y("(jdemo1: %p, refcount: %zd)", jdemo1, jdemo1->refcount);

	json_dump_simple(jroot, "jroot");

	{
		int idx = -1;
		json_ary_find_key_val(jA, "val", JSON_JINT(3), &idx);
		DBG_LN_Y("(idx: %d)", idx);
	}

	json_t *jfound = NULL;
	jfound = JSON_OBJ_FIND_RECURSIVE(jroot, "logo", NULL, JSON_OBJ_FIND_ID_INFINITE, "", NULL);
	if (jfound)
	{
		const char *found = JSON_STR(jfound);
		if (found)
		{
			DBG_LN_Y("(logo: %s)", (char*)found);
		}
	}

	JSON_TopicX_t jtopicx ={
		.jroot = jroot,
	};

	SAFE_SPRINTF_EX(jtopicx.topic, "j1/j2/j4");
	jfound = json2topicx(&jtopicx, -1, JSON_ACTID_READ);
	json_dump_simple(jfound, "Not Found - j1/j2/j4");

	jfound = json2topicx(&jtopicx, -1, JSON_ACTID_APPEND);
	json_dump_simple(jfound, "APPEND - j1/j2/j4");

	SAFE_SPRINTF_EX(jtopicx.topic, "j1/j2/j3");
	jfound = json2topicx(&jtopicx, -1, JSON_ACTID_DEL);
	json_dump_simple(jfound, "DEL - j1/j2/j3");

	SAFE_SPRINTF_EX(jtopicx.topic, "j1/j2");
	jfound = json2topicx(&jtopicx, -1, JSON_ACTID_READ);
	json_dump_simple(jfound, jtopicx.topic);

	JSON_FREE(jroot);

	{
		jroot = JSON_LOADFILE_EASY("./json/urmet.json");
		if (jroot)
		{
			json_t *jfound_ary = JSON_ARY_NEW();
			if (jfound_ary)
			{
				json_t *jval = JSON_JSTR("Battery");
				char topic[LEN_OF_TOPIC] = "";
				//json_t *jfound_val = JSON_OBJ_FIND_RECURSIVE(jroot, "class", jval, -1, topic, NULL);
				//json_dump_simple(jfound_val, "hello");

				jfound = JSON_OBJ_FIND_RECURSIVE(jroot, "class", jval, JSON_OBJ_FIND_ID_INFINITE, topic, jfound_ary);
				json_dump_simple(jfound_ary, "hello");

				JSON_ARY_CLEAR(jfound_ary);
				jfound = JSON_OBJ_FIND_RECURSIVE(jroot, "000980001", NULL, JSON_OBJ_FIND_ID_INFINITE, topic, jfound_ary);
				json_dump_simple(jfound_ary, "hello");

				JSON_FREE(jval);
				JSON_FREE(jfound_ary);
			}
			JSON_FREE(jroot);
		}
	}
#endif

	exit(0);
}
