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

void json_dump_simple(json_t *jparent, char *name)
{
	char *dump = JSON_DUMPS_EASY(jparent);
	if(dump)
	{
		DBG_LN_Y("(%s: %s)", name, dump);
	}
	else
	{
		DBG_LN_Y("(%s: %p)", name, dump);
	}
	SAFE_FREE(dump);
}

int json_pass_base64_dec(json_t *jparent, const char *key, char *pass, int len)
{
	int ret = -1;

#ifdef UTIL_EX_SSL
	if((jparent) && (key) && (pass) && (len))
	{
		json_t *jobj = NULL;
		const char *pass_enc = JSON_OBJ_GET_STR(jparent, jobj, key);
		int pass_enc_len = SAFE_STRLEN((char *)pass_enc);

		if((pass_enc) && (pass_enc_len>0))
		{
			int dec_len = 0;
			char *pass_dec = sec_base64_dec((char *)pass_enc, pass_enc_len, &dec_len);
			if(pass_dec)
			{
				SAFE_SNPRINTF(pass, len, "%s", pass_dec);
				ret = 0;
				SAFE_FREE(pass_dec);
			}
		}
	}
#endif

	return ret;
}

int json_pass_base64_enc(json_t *jparent, const char *key, char *pass, int len)
{
	int ret = -1;

#ifdef UTIL_EX_SSL
	if((jparent) && (key) && (pass) && (len))
	{
		int enc_len = 0;
		char *pass_enc = sec_base64_enc(pass, len, &enc_len);

		if(pass_enc)
		{
			JSON_OBJ_SET_STR(jparent, key, pass_enc);
			ret = 0;
			SAFE_FREE(pass_enc);
		}
	}
#endif

	return ret;
}

json_t *json_ary_create(json_t *jparent, const char *key)
{
	if((jparent == NULL) && (JSON_CHECK_OBJ(jparent)))
	{
		return NULL;
	}

	json_t *jary = JSON_OBJ_FIND_REUSE(jparent, key);
	if((jary) || (jary = JSON_ARY_NEW()))
	{
		JSON_OBJ_SET_OBJ(jparent, key, jary);
	}

	return jary;
}

json_t *json_obj_create(json_t *jparent, const char *key)
{
	if((jparent == NULL) && (JSON_CHECK_OBJ(jparent)))
	{
		return NULL;
	}

	json_t *jobj = JSON_OBJ_FIND_REUSE(jparent, key);
	if((jobj) || (jobj = JSON_OBJ_NEW()))
	{
		JSON_OBJ_SET_OBJ(jparent, key, jobj);
	}
	return jobj;
}

// idx_need=-1, to return the last one
json_t *json2topicx(JSON_TopicX_t *topicx_req, int idx_need, JSON_ACTID act)
{
	json_t *jfound = NULL;
	topicx_req->deepth_topic = -1;
	topicx_req->deepth_json = -1;
	SAFE_MEMSET(topicx_req->tokenx_ary, 0, MAX_OF_TOKENX_ARY*sizeof(JSON_TokenX_t));

	if((topicx_req->jroot) && (SAFE_STRLEN(topicx_req->topic) > 0))
	{
		int idx_topic = -1;
		int idx_json = -1;
		json_t *jparent = topicx_req->jroot;

		char topic_walk[LEN_OF_TOPIC] = "";
		char *topic_cpy = NULL;
		SAFE_ASPRINTF(topic_cpy, "%s", topicx_req->topic);
		char *saveptr = NULL;
		char *token = NULL;

		token = SAFE_STRTOK_R(topic_cpy, "/", &saveptr);
		while(token)
		{
			idx_topic ++;
			JSON_TokenX_t *tokenx_req = (JSON_TokenX_t *)&topicx_req->tokenx_ary[idx_topic];
			switch(act)
			{
				case JSON_ACTID_APPEND:
					tokenx_req->jdata = JSON_OBJ_GET_OBJ_EX(jparent, token);
					break;
				case JSON_ACTID_READ:
				case JSON_ACTID_DEL:
				default:
					tokenx_req->jdata = JSON_OBJ_GET_OBJ(jparent, token);
					break;
			}

			SAFE_SPRINTF_EX(tokenx_req->token, "%s", token);
			SAFE_SPRINTF_EX(tokenx_req->topic, "%s%s", topic_walk, token);

			SAFE_STRCAT_EX(topic_walk, token, "/");

			if(tokenx_req->jdata)
			{
				if(idx_need == idx_topic)
				{
					jfound = tokenx_req->jdata;
				}
				else if(idx_need == -1)
				{
					jfound = tokenx_req->jdata;
				}
				idx_json++;
			}
			else
			{
				// Not found in database
			}
			jparent = tokenx_req->jdata;

			if(idx_topic>=MAX_OF_TOKENX_ARY)
			{
				break;
			}
			token = SAFE_STRTOK_R(NULL, "/", &saveptr);
		}

		SAFE_FREE(topic_cpy);

		topicx_req->deepth_topic = idx_topic;
		topicx_req->deepth_json = idx_json;
	}

	if(topicx_req->deepth_topic != topicx_req->deepth_json)
	{
		jfound = NULL;
	}

	if((jfound) && (act==JSON_ACTID_DEL))
	{
		json_t *jparent = topicx_req->jroot;
		int idx = topicx_req->deepth_topic;
		if(idx==0)
		{
			JSON_OBJ_DEL(jparent, topicx_req->tokenx_ary[idx].token);
		}
		else
		{
			jparent = topicx_req->tokenx_ary[idx-1].jdata;
			JSON_OBJ_DEL(jparent, topicx_req->tokenx_ary[idx].token);
		}
		jfound = NULL;
	}

	return jfound;
}

json_t *json_ary_find_val(json_t *jparent, json_t *jval, int *idx)
{
	if(jparent == NULL)
	{
		return NULL;
	}
	if(jval == NULL)
	{
		return NULL;
	}

	json_t *jobj = NULL;
	json_t *jobj_found = NULL;
	int i = 0;

	JSON_ARY_FOREACH(jparent, i, jobj_found)
	{
		if((jobj_found) && (1 == JSON_EQUAL(jobj_found, jval)))
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
	if(jparent == NULL)
	{
		return NULL;
	}
	if(jval == NULL)
	{
		return NULL;
	}

	json_t *jobj = NULL;
	json_t *jobj_found = NULL;
	int i = 0;

	JSON_ARY_FOREACH(jparent, i, jobj_found)
	{
		json_t *jkey = JSON_OBJ_GET_OBJ(jobj_found, key);
		if((jkey) && (1 == JSON_EQUAL(jkey, jval)))
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
	if(jparent == NULL)
	{
		return NULL;
	}

	json_t *jobj = NULL;
	json_t *jobj_next = jparent;

	char *key_next = NULL;
	SAFE_ASPRINTF(key_next, "%s", keys);

	char *saveptr = NULL;
	char *token = SAFE_STRTOK_R(key_next, "/", &saveptr);
	while((token) && (jobj_next))
	{
		char *token_next = SAFE_STRTOK_R(NULL, "/", &saveptr);

		if((str_isnum(token) == 0) && (JSON_CHECK_ARY(jobj_next)))
		{
			jobj_next = JSON_ARY_GET(jobj_next, atoi(token));
		}
		else
		{
			jobj_next = JSON_OBJ_GET_OBJ(jobj_next, token);
		}

		if(token_next==NULL)
		{
			// last
			jobj = jobj_next;
		}
		token = token_next;
	}

	SAFE_FREE(key_next);
	return jobj;
}

json_t *json_object_lookup(json_t *jparent, const char *key, json_t *jval, int deepth, char *topic_parent, json_t *jfound_ary)
{
	if(jparent == NULL)
	{
		return NULL;
	}
	if(topic_parent == NULL)
	{
		return NULL;
	}

	char topic[LEN_OF_TOPIC] = "";
	json_t *jobj = NULL;
	json_t *jobj_found = NULL;
	int nextth = 0;

	SAFE_SPRINTF_EX(topic, "%s", topic_parent);
	if(deepth<0)
	{
		// infinite
		nextth = deepth;
	}
	else if(deepth==0)
	{
		if(jfound_ary==NULL)
		{
			return jobj;
		}
	}
	else
	{
		nextth = deepth-1;
	}

	if(jparent)
	{
		if(JSON_CHECK_ARY(jparent))
		{
			int idx = 0;
			JSON_ARY_FOREACH(jparent, idx, jobj_found)
			{
				if((JSON_CHECK_OBJ(jobj_found)) && (nextth!=0) && (jobj_found =json_object_lookup(jobj_found, key, jval, nextth, topic, jfound_ary)))
				{
					jobj = jobj_found;
					if(jfound_ary == NULL)
					{
						break;
					}
				}
				else if((JSON_CHECK_ARY(jobj_found)) && (nextth!=0) && (jobj_found =json_object_lookup(jobj_found, key, jval, nextth, topic, jfound_ary)))
				{
					jobj = jobj_found;
					if(jfound_ary == NULL)
					{
						break;
					}
				}
			}
		}
		else if(JSON_CHECK_OBJ(jparent))
		{
			const char *key_found = NULL;
			JSON_OBJ_FOREACH(jparent, key_found, jobj_found)
			{
				char topic_new[LEN_OF_TOPIC] = "";

				if(SAFE_STRLEN(topic) > 0)
				{
					SAFE_SPRINTF_EX(topic_new, "%s/%s", topic, key_found);
				}
				else
				{
					SAFE_SPRINTF_EX(topic_new, "%s", key_found);
				}

				if(SAFE_STRCMP((char*)key_found, (char*)key) ==0)
				{
					if(jval)
					{
						if(1 == JSON_EQUAL(jobj_found, jval))
						{
							jobj = jparent;
						}
					}
					else
					{
						jobj = jobj_found;
					}

					if(jobj)
					{
						if(jfound_ary)
						{
							json_t *jnew = JSON_OBJ_NEW();
							if(jval)
							{
								JSON_OBJ_SET_STR(jnew, JKEY_COMM_TOPIC, topic);
							}
							else
							{
								JSON_OBJ_SET_STR(jnew, JKEY_COMM_TOPIC, topic_new);
							}
							//json_t *jobj_cpy = JSON_COPY(jobj);
							//JSON_OBJ_SET_OBJ(jnew, JKEY_COMM_DATA, jobj_cpy);
							JSON_OBJ_SET_OBJ_LINK(jnew, JKEY_COMM_DATA, jobj);
							JSON_ARY_APPEND_OBJ(jfound_ary, jnew);
						}
						break;
					}
				}
				else if((JSON_CHECK_OBJ(jobj_found)) && (nextth!=0) && (jobj_found = json_object_lookup(jobj_found, key, jval, nextth, topic_new, jfound_ary)))
				{
					jobj = jobj_found;
					if(jfound_ary == NULL)
					{
						break;
					}
				}
				else if((JSON_CHECK_ARY(jobj_found)) && (nextth!=0) && (jobj_found = json_object_lookup(jobj_found, key, jval, nextth, topic_new, jfound_ary)))
				{
					jobj = jobj_found;
					if(jfound_ary == NULL)
					{
						break;
					}
				}
			}
		}
	}

	return jobj;
}

