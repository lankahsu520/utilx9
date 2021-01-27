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

json_t *json_ary_create(json_t *jparent, const char *key)
{
	if ( jparent == NULL ) return NULL;

	json_t *jary = JSON_OBJ_FIND_REUSE(jparent, key);
	if ( (jary) || (jary = JSON_ARY_NEW()) )
	{
		JSON_OBJ_SET_OBJ(jparent , key, jary);
	}

	return jary;
}

json_t *json_obj_create(json_t *jparent, const char *key)
{
	if ( jparent == NULL ) return NULL;

	json_t *jobj = JSON_OBJ_FIND_REUSE(jparent, key);
	if ( (jobj) || (jobj = JSON_OBJ_NEW()) )
	{
		JSON_OBJ_SET_OBJ(jparent , key, jobj);
	}
	return jobj;
}

json_t *json_ary_find_val(json_t *jparent, json_t *jval, int *idx)
{
	if ( jparent == NULL ) return NULL;
	if ( jval == NULL ) return NULL;

	json_t *jobj = NULL;
	json_t *jobj_found = NULL;
	int i = 0;

	JSON_ARY_FOREACH(jparent, i, jobj_found) {
		if ( (jobj_found) && ( 1 == JSON_EQUAL(jobj_found, jval) ) )
		{
			// found !!!
			*idx = i;
			jobj = jobj_found;
			break;
		}
	}

	JSON_FREE(jval);

	return jobj;
}


json_t *json_ary_find_key_val(json_t *jparent, const char *key, json_t *jval, int *idx)
{
	if ( jparent == NULL ) return NULL;
	if ( jval == NULL ) return NULL;

	json_t *jobj = NULL;
	json_t *jobj_found = NULL;
	int i = 0;

	JSON_ARY_FOREACH(jparent, i, jobj_found) {
		json_t *jkey = JSON_OBJ_GET_OBJ(jobj_found, key);
		if ( (jkey) && ( 1 == JSON_EQUAL(jkey, jval) ) )
		{
			// found !!!
			*idx = i;
			jobj = jobj_found;
			break;
		}
	}

	JSON_FREE(jval);

	return jobj;
}

// key like dongle/1/device/0/uid
json_t *json_object_find_with_keys(json_t *jparent, const char *keys)
{
	if ( jparent == NULL ) return NULL;

	json_t *jobj = NULL;
	json_t *jobj_next = jparent;

	char *key_next = NULL;
	SAFE_ASPRINTF(key_next, "%s", keys);

	char *saveptr = NULL;
	char *token = SAFE_STRTOK_R(key_next, "/", &saveptr);
	while ( (token) && (jobj_next) )
	{
		char *token_next = SAFE_STRTOK_R(NULL, "/", &saveptr);

		if ( ( str_isnum(token) == 0 ) && (JSON_CHECK_ARY(jobj_next)) )
		{
			jobj_next = JSON_ARY_GET(jobj_next, atoi(token));
		}
		else
		{
			jobj_next = JSON_OBJ_GET_OBJ(jobj_next, token);
		}

		if (token_next==NULL)
		{
			// last
			jobj = jobj_next;
		}
		token = token_next;
	}

	SAFE_FREE(key_next);
	return jobj;
}

json_t *json_object_lookup(json_t *jparent, const char *key, int deepth)
{
	if ( jparent == NULL ) return NULL;

	json_t *jobj = NULL;
	json_t *jobj_found = NULL;
	int nextth = 0;

	if (deepth<0)
	{
		// infinite
		nextth = deepth;
	}
	else if (deepth==0)
	{
		return jobj;
	}
	else
	{
		nextth = deepth-1;
	}

	if (jparent)
	{
		if (JSON_CHECK_ARY(jparent))
		{
			int idx = 0;
			JSON_ARY_FOREACH(jparent, idx, jobj_found) {
				if ( (JSON_CHECK_OBJ(jobj_found)) && (nextth!=0) && (jobj_found = json_object_lookup(jobj_found, key, nextth)) )
				{
					// found !!!
					jobj = jobj_found;
					break;
				}
				else if ( (JSON_CHECK_ARY(jobj_found)) && (nextth!=0) && (jobj_found = json_object_lookup(jobj_found, key, nextth)) )
				{
					// found !!!
					jobj = jobj_found;
					break;
				}
			}
		}
		else if ( JSON_CHECK_OBJ(jparent) )
		{
			const char *key_found = NULL;
			JSON_OBJ_FOREACH(jparent, key_found, jobj_found) {
				if (SAFE_STRCMP((char*)key_found, (char*)key) ==0)
				{
					// found !!!
					jobj = jobj_found;
					break;
				}
				else if ( (JSON_CHECK_OBJ(jobj_found)) && (nextth!=0) && (jobj_found = json_object_lookup(jobj_found, key, nextth)) )
				{
					// found !!!
					jobj = jobj_found;
					break;
				}
				else if ( (JSON_CHECK_ARY(jobj_found)) && (nextth!=0) && (jobj_found = json_object_lookup(jobj_found, key, nextth)) )
				{
					// found !!!
					jobj = jobj_found;
					break;
				}
			}
		}
	}

	return jobj;
}

