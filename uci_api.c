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
#include <ctype.h>

int uci_list_free(UCICtx_t *uci_req, const char *u_name, const char *u_key)
{
	return uci_option_del_ex(uci_req, u_name, u_key);
}

int uci_list_del_ex(UCICtx_t *uci_req, const char *u_name, const char *u_key, const char *u_val)
{
	int ret = -1;
	if ( (uci_req->uci_ctx) && (u_name) && (u_key) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			struct uci_ptr ptr = {
				.p = uci_req->uci_pkg,
				.s = u_section,
				.option = u_key,
				.value =u_val,
			};

			if (UCI_OK != uci_del_list(uci_req->uci_ctx, &ptr) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_del_list error !!!");
			}
			else if (UCI_OK != uci_commit(uci_req->uci_ctx, &uci_req->uci_pkg, false) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_commit error !!!");
			}
			else
			{
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("uci_section_get error !!! (u_name: %s)", u_name);
		}
	}
	return ret;
}

int uci_list_add_ex(UCICtx_t *uci_req, const char *u_name, const char *u_key, const char *u_val)
{
	int ret = -1;
	if ( (uci_req->uci_ctx) && (u_name) && (u_key) && (u_val) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			struct uci_option *o_key = uci_lookup_option(uci_req->uci_ctx, u_section, u_key);
			if ((NULL != o_key) && (UCI_TYPE_LIST == o_key->type))
			{
				struct uci_element *u_item;
				UCI_FOREACH_ITEM(&o_key->v.list, u_item)
				{
					//DBG_WN_LN("(key: %s, val: %s)", key, u_item->name);
					if ( SAFE_STRCMP(u_item->name, (char*)u_val) == 0 )
					{
						// Found !!!
						DBG_TR_LN("%s (key: %s, val: %s)", DBG_TXT_FOUND, u_key, u_item->name);
						return 0;
					}
				}
			}

			struct uci_ptr ptr = {
				.p = uci_req->uci_pkg,
				.s = u_section,
				.option = u_key,
				.value = u_val,
			};

			if (UCI_OK != uci_add_list(uci_req->uci_ctx, &ptr) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_set error !!!");
			}
			else if (UCI_OK != uci_commit(uci_req->uci_ctx, &uci_req->uci_pkg, false) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_commit error !!!");
			}
			else
			{
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("uci_section_get error !!! (u_name: %s)", u_name);
		}
	}
	return ret;
}

int uci_option_del_ex(UCICtx_t *uci_req, const char *u_name, const char *u_key)
{
	int ret = -1;
	if ( (uci_req->uci_ctx) && (u_name) && (u_key) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			struct uci_ptr ptr = {
				.p = uci_req->uci_pkg,
				.s = u_section,
				.option = u_key,
			};

			if (UCI_OK != uci_delete(uci_req->uci_ctx, &ptr) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_delete error !!!");
			}
			else if (UCI_OK != uci_commit(uci_req->uci_ctx, &uci_req->uci_pkg, false) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_commit error !!!");
			}
			else
			{
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("uci_section_get error !!! (u_name: %s)", u_name);
		}
	}
	return ret;
}

int uci_option_set_str(UCICtx_t *uci_req, const char *u_name, const char *u_key, const char *u_val)
{
	int ret = -1;
	if ( (uci_req->uci_ctx) && (u_name) && (u_key) && (u_val) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			struct uci_ptr ptr = {
				.p = uci_req->uci_pkg,
				.o = NULL,
				.s = u_section,
				.option = u_key,
				.value = u_val,
			};

			if (UCI_OK != uci_set(uci_req->uci_ctx, &ptr) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_set error !!!");
			}
			else if (UCI_OK != uci_commit(uci_req->uci_ctx, &uci_req->uci_pkg, false) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_commit error !!!");
			}
			else
			{
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("uci_section_get error !!! (u_name: %s)", u_name);
		}
	}
	return ret;
}

const char *uci_option_get_str(UCICtx_t *uci_req, const char *u_name, const char *u_key)
{
	if ( (uci_req->uci_ctx) && (u_name) && (u_key) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			return uci_lookup_option_string(uci_req->uci_ctx, u_section, u_key);
		}
	}
	return NULL;
}

struct uci_option *uci_option_get_obj(UCICtx_t *uci_req, const char *u_name, const char *u_key)
{
	if ( (uci_req->uci_ctx) && (u_name) && (u_key) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			return uci_lookup_option(uci_req->uci_ctx, u_section, u_key);
	}
	}
	return NULL;
}

static bool uci_validate_str_ex(const char *str, bool is_name, bool is_package)
{
	if (!*str)
		return false;

	for (; *str; str++) {
		unsigned char c = *str;

		if (isalnum(c) || c == '_')
			continue;

		if (c == '-' && is_package)
			continue;

		if (is_name || (c < 33) || (c > 126))
			return false;
	}
	return true;
}

struct uci_section *uci_section_get(UCICtx_t *uci_req, const char *u_name)
{
	if ( (uci_req->uci_ctx) && (uci_req->uci_pkg) )
	{
		return uci_lookup_section(uci_req->uci_ctx, uci_req->uci_pkg, u_name);
	}
	return NULL;
}

int uci_section_del(UCICtx_t *uci_req, const char *u_name)
{
	int ret = -1;
	if ( (uci_req->uci_ctx) && (u_name) )
	{
		struct uci_section *u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			struct uci_ptr ptr = {
				.p = uci_req->uci_pkg,
				.s = u_section,
			};

			if (UCI_OK != uci_delete(uci_req->uci_ctx, &ptr) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_delete error !!!");
			}
			else if (UCI_OK != uci_commit(uci_req->uci_ctx, &uci_req->uci_pkg, false) )
			{
				//uci_perror(uci_req->uci_ctx, NULL);
				DBG_ER_LN("uci_commit error !!!");
			}
			else
			{
				ret = 0;
			}
		}
		else
		{
			DBG_ER_LN("uci_section_get error !!! (u_name: %s)", u_name);
		}
	}
	return ret;
}

struct uci_section *uci_section_set(UCICtx_t *uci_req, const char *u_type, const char *u_name)
{
	struct uci_section *u_section = NULL;

	if ( (u_name) && ( false == uci_validate_str_ex(u_name, true, false) ) )
	{
		return u_section;
	}
	else if ( (uci_req) && (uci_req->uci_ctx) && (uci_req->uci_pkg) && (u_type) && (u_name) )
	{
		u_section = uci_section_get(uci_req, u_name);
		if (u_section)
		{
			DBG_TR_LN("uci_section_get foind !!! (u_name: %s)", u_name);
		}
		else if ( UCI_OK == uci_add_section(uci_req->uci_ctx, uci_req->uci_pkg, u_type, &u_section))
		{
			//DBG_ER_LN("(name: %p)", section->e.name);
			if ( (u_name) && (u_section->e.name) )
			{
				SAFE_FREE(u_section->e.name);
				u_section->e.name = strdup(u_name);
				u_section->anonymous = false;
			}
			if ( UCI_OK == uci_save(uci_req->uci_ctx, uci_req->uci_pkg) )
			{
				uci_commit(uci_req->uci_ctx, &uci_req->uci_pkg, false);
			}
			else
			{
				DBG_ER_LN("uci_save error !!! (u_type: %s)", u_type);
			}
		}
	}
	return u_section;
}

void uci_show_value_ex(struct uci_option *u_option)
{
	char *u_cname = u_option->section->package->e.name;
	char *u_name = u_option->section->e.name;
	char *u_key = u_option->e.name;
	
	switch (u_option->type)
	{
		case UCI_TYPE_STRING:
			{
				char *u_val = u_option->v.string;
				DBG_IF_LN("option (%s/%s, %s=%s)", u_cname, u_name, u_key, u_val);
			}
			break;
		case UCI_TYPE_LIST:
			{
				struct uci_element *u_item;
				UCI_FOREACH_ITEM(&u_option->v.list, u_item)
				{
					char *u_val = u_item->name;
					DBG_IF_LN("list (%s/%s, %s=%s)", u_cname, u_name, u_key, u_val);
				}
			}
			break;
		default:
			DBG_WN_LN("%s (type: %d)", DBG_TXT_NO_SUPPORT, u_option->type);
			break;
	}
}


void uci_show_option_ex(struct uci_option *u_option)
{
#if (1)
	char *u_cname = u_option->section->package->e.name;
	char *u_name = u_option->section->e.name;
	char *u_key = u_option->e.name;

	DBG_TR_LN("(u_cname: %s, u_name: %s, u_key: %s)", u_cname, u_name, u_key);
#endif
	uci_show_value_ex(u_option);
}

void uci_show_section_ex(struct uci_section *u_section)
{
#if (1)
	char *u_cname = u_section->package->e.name;
	char *u_name = u_section->e.name;
	char *u_type = u_section->type;

	DBG_TR_LN("(u_cname: %s, u_type: %s, u_name: %s)", u_cname, u_type, u_name);
#endif
	struct uci_element *u_item;
	UCI_FOREACH_ITEM(&u_section->options, u_item) {
		uci_show_option_ex(uci_to_option(u_item));
	}
}


int uci_show_package_ex(struct uci_package *u_ptr)
{
	int ret = -1;
	struct uci_element *u_item;

	UCI_FOREACH_ITEM( &u_ptr->sections, u_item)
	{
		struct uci_section *u_section = uci_to_section(u_item);
		uci_show_section_ex(u_section);
	}

	ret = 0;
	goto exit_package;
exit_package:
	return ret;
}

int uci_show_what_ex(UCICtx_t *uci_req, char *u_what)
{
	int ret = -1;
	struct uci_ptr u_ptr;
	if (uci_lookup_ptr(uci_req->uci_ctx, &u_ptr, u_what, true) != UCI_OK)
	{
		goto exit_what;
	}

	struct uci_element *u_item = u_ptr.last;
	DBG_IF_LN_0("_________________________________________________________________________________\n");
	DBG_TR_LN("(u_what: %s, u_item->type: %d)", u_what, u_item->type);
	switch (u_item->type)
	{
		case UCI_TYPE_PACKAGE:
			uci_show_package_ex(u_ptr.p);
			break;
	
		case UCI_TYPE_SECTION:
			//uci_show_section(ptr.s);
			break;
	
		case UCI_TYPE_OPTION:
			//uci_show_option(ptr.o, true);
			break;
		default:
			/* should not happen */
			goto exit_what;
	}
	
	ret = 0;
exit_what:
	return ret;
}

int uci_show_configs_ex(UCICtx_t *uci_req)
{
	int ret = -1;
	char **u_configs = NULL;
	char **u_config;

	if ((uci_list_configs(uci_req->uci_ctx, &u_configs) != UCI_OK) || !u_configs)
	{
		goto exit_config;
	}

	DBG_IF_LN_0("_________________________________________________________________________________\n");
	for (u_config = u_configs; *u_config; u_config++)
	{
		DBG_IF_LN("(u_config: %s)", *u_config);
	}

	ret = 0;
exit_config:
	SAFE_FREE(u_configs);
	return ret;
}

void uci_close(UCICtx_t *uci_req)
{
	UCI_PKG_FREE(uci_req->uci_ctx, uci_req->uci_pkg);
	UCI_CTX_FREE(uci_req->uci_ctx);
}

int uci_open(UCICtx_t *uci_req)
{
	int ret = 0;
	uci_req->uci_ctx = UCI_LOAD(uci_req->uci_filename, uci_req->uci_pkg);
	if (uci_req->uci_ctx == NULL)
	{
		ret = -1;
		goto cleanup;
	}

	return ret; 

cleanup:
	uci_close(uci_req);
	return ret;
}

