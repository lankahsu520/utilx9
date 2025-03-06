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
	DBG_IF_LN("(guid: %s)", guid);

	os_random_uuid(guid, sizeof(guid));
	DBG_IF_LN("(guid: %s)", guid);

	os_random_uuid(guid, sizeof(guid));
	DBG_IF_LN("(guid: %s)", guid);
}

int main(int argc, char* argv[])
{
	DBG_IF_LN("enter");

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

#if (1)
	json_dump_simple(jroot, "jroot");

	DBG_WN_LN(">> update j4->j1");
	// update j4->j1
	json_t *j4 = JSON_OBJ_NEW();
	JSON_OBJ_SET_STR(j4, "j4", "child !!!");
	JSON_OBJ_CLEAR(j1);
	JSON_UPDATE(j1, j4);
	JSON_FREE(j4);

	json_dump_simple(jroot, "jroot");
#endif

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

#if (1)
	json_dump_simple(jroot, "jroot");

	// JSON_ARY_DEL
	{
		json_t *jA_new = JSON_ARY_NEW();
		int i = 0;
		json_t *jA_item = NULL;
		// copy all items of jA -> jA_new
		JSON_ARY_FOREACH(jA, i, jA_item) {
			json_t *jA_item_cpy = JSON_COPY(jA_item);
			JSON_ARY_APPEND_OBJ(jA_new, jA_item_cpy);
		}

		// replace "jA": jA_new
		JSON_OBJ_SET_OBJ(jroot, "jA", jA_new);
		jA = JSON_OBJ_GET_OBJ(jroot, "jA");
		DBG_WN_LN(">> (jA: %p, jA_new: %p)", jA, jA_new);
		jA1 = JSON_ARY_GET(jA, 0);
		jA2 = JSON_ARY_GET(jA, 1);
		jA3 = JSON_ARY_GET(jA, 2);
	}

	{
		DBG_WN_LN(">> update jB1->jA1");
		// update jB1->jA1
		json_t *jB1 = JSON_OBJ_NEW();
		JSON_OBJ_SET_STR(jB1, "nameB", "B4");
		JSON_OBJ_SET_INT(jB1, "valB", 4);
		JSON_UPDATE(jA1, jB1);
		json_t *jA1_cpy = JSON_COPY(jA1);
		JSON_ARY_SET_NEW(jA, 0, jA1_cpy);
		JSON_FREE(jB1);
	}

	json_dump_simple(jroot, "jroot");
#endif

	{
		// set "demo" as jdemo1
		json_t *jdemo1 = JSON_OBJ_SET_STR(jroot, "demo", "HelloWorld 1 !!!");
		json_dump_simple(jroot, "jroot");
		DBG_WN_LN(">> set demo as jdemo1 (jdemo1: %p, refcount: %zd)", jdemo1, JSON_REFCOUNT(jdemo1));

		// set "demo" as jdemo2
		json_t *jdemo2 = JSON_OBJ_SET_STR(jroot, "demo", "HelloWorld 2 !!!");
		json_dump_simple(jroot, "jroot");
		DBG_WN_LN(">> set demo as jdemo2; jdemo1 will be free and we can't access jdemo1 !!! !!! (jdemo2: %p, refcount: %zd)", jdemo2, JSON_REFCOUNT(jdemo2));

		//DBG_IF_LN("(jdemo1: %p, refcount: %zd)", jdemo1, JSON_REFCOUNT(jdemo1));
		json_dump_simple(jroot, "jroot");
	}

#if (1)
	{
		int idx = -1;
		json_ary_find_key_val(jA, "val", JSON_JINT(3), &idx);
		DBG_IF_LN("(idx: %d)", idx);
	}
#endif

	json_t *jfound = NULL;
	jfound = JSON_OBJ_FIND_RECURSIVE(jroot, "logo", NULL, JSON_OBJ_FIND_ID_INFINITE, "", NULL);
	if (jfound)
	{
		const char *found = JSON_STR(jfound);
		if (found)
		{
			DBG_IF_LN("(logo: %s)", (char*)found);
		}
	}

	JSON_TopicX_t jtopicx =
	{
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

#if (1)
	{
		jroot = JSON_LOADFILE_EASY("./json/demo.json");
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

#if (1)
	if ( dir_chk("./json") == 0 )
	{
		json_t *jroot_ary = JSON_LOADFILE_EASY_OR_NEW_ARY("./json/demo-ary.json");
		if (jroot_ary)
		{
			int idx =0;
			json_t *jitem = NULL;
			JSON_ARY_FOREACH(jroot_ary, idx, jitem)
			{
				DBG_IF_LN("(idx: %d %s)", idx, JSON_STR(jitem));
			}

			JSON_ARY_APPEND_STR(jroot_ary, time_now_full(time(NULL)));
			JSON_DUMP_FILE_EASY(jroot_ary, "./json/demo-ary.json");
			JSON_FREE(jroot_ary);
		}
	}
	else
	{
		DBG_ER_LN("%s (./json)", DBG_TXT_FOLDER_NOT_FOUND);
	}
#endif

#if (1)
	{
		// {"sunrise":"3:22:56 AM","sunset":"5:10:20 PM","time_utc":1652853043}
		json_t *jsunrise_sunset = JSON_LOADS_EASY("{\"sunrise\":\"3:22:56 AM\",\"sunset\":\"5:10:20 PM\",\"time_utc\":1652853043}");
		if (jsunrise_sunset)
		{
			json_t *jobj = NULL;
			const char *sunrise = JSON_OBJ_GET_STR(jsunrise_sunset, jobj, JKEY_COMM_SUNRISE);
			const char *sunset = JSON_OBJ_GET_STR(jsunrise_sunset, jobj, JKEY_COMM_SUNSET);
			int utc = JSON_OBJ_GET_INT_DEF(jsunrise_sunset, jobj, JKEY_COMM_TIME_UTC, 0);

			DBG_IF_LN("(sunrise: %s)", sunrise);
			DBG_IF_LN("(sunset: %s)", sunset);
			DBG_IF_LN("(utc: %d)", utc);

			JSON_FREE(jsunrise_sunset);
		}
	}
#endif

#if (1)
	{
		// {"sunrise":"3:22:56 AM","sunset":"5:10:20 PM","time_utc":1652853043}
		json_t *jsunrise_sunset = JSON_OBJ_NEW();
		if (jsunrise_sunset)
		{
			JSON_OBJ_SET_STR(jsunrise_sunset, JKEY_COMM_SUNRISE, "3:22:56 AM");
			JSON_OBJ_SET_STR(jsunrise_sunset, JKEY_COMM_SUNSET, "5:10:20 PM");
			JSON_OBJ_SET_INT(jsunrise_sunset, JKEY_COMM_TIME_UTC, 1652853043);

			char *cJson = JSON_DUMPS_EASY(jsunrise_sunset);
			if (cJson)
			{
				DBG_IF_LN("(cJson: %s)", cJson);
				SAFE_FREE(cJson);
			}

			JSON_FREE(jsunrise_sunset);
		}
	}
#endif

#endif

	exit(0);
}
