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

UCIX_t uci_wireless_req =
{
	.uci_filename = UCI_CFG_WIRELESS,

	.uci_req = NULL,
	.uci_pkg = NULL,
};

UCIX_t uci_demo_req =
{
	//.uci_filename = "demo",
	.uci_filename = UCI_CFG_DEMO,

	.uci_req = NULL,
	.uci_pkg = NULL,
};

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	{
		UCIX_t *uci_req = &uci_wireless_req;
		if (0 == UCI_OPEN(uci_req))
		{
			DBG_IF_LN("(ssid: %s)", UCI_OPTION_GET_STR(uci_req, "ap", "ssid"));
			UCI_CLOSE(uci_req);
		}
	}

	{
		UCIX_t *uci_req = &uci_demo_req;
		if (0 == UCI_OPEN(uci_req))
		{
#if (1)
			//DBG_IF_LN("(uci_pkg: %p)", uci_req->uci_pkg);
			int s_num = 0;

			char u_type[LEN_OF_BUF128] = "";
			char u_name[LEN_OF_BUF128] = "";

			for (s_num = 0; s_num < 5; s_num++)
			{
				SAFE_SPRINTF_EX(u_type, "type_%02d", s_num);
				SAFE_SPRINTF_EX(u_name, "name_%02d", s_num);
				struct uci_section *usection = UCI_SESSION_SET(uci_req, u_type, u_name);
				DBG_IF_LN("(type: %s, name: %s, usection: %p)", usection->type, usection->e.name, usection);

				{
					int idx = 0;
					char u_key[LEN_OF_BUF128] = "";
					char u_val[LEN_OF_BUF128] = "";
					for (idx = 0; idx < s_num+1; idx++)
					{
						SAFE_SPRINTF_EX(u_key, "key_%02d", idx);
						SAFE_SPRINTF_EX(u_val, "%02d", idx);
						int ret = UCI_OPTION_SET_STR(uci_req, u_name, u_key, u_val);
						DBG_IF_LN("(%s/%s: %s, ret: %d)", u_name, u_key, UCI_OPTION_GET_STR(uci_req, u_name, u_key), ret);
					}
				}
			}

			UCI_OPTION_DEL(uci_req, "name_04", "key_02");
			UCI_OPTION_DEL(uci_req, "name_04", "key_03");
			UCI_OPTION_SET_STR(uci_req, "name_04", "key_04", "999");
			UCI_SESSION_DEL(uci_req, "name_02");
#endif

#if (1)
			{
				char u_name[LEN_OF_BUF128] = "";
				char u_type[LEN_OF_BUF128] = "";
				SAFE_SPRINTF_EX(u_type, "type_%02d", 4);
				SAFE_SPRINTF_EX(u_name, "name_%02d", 4);
				//struct uci_section *u_section = UCI_SESSION_SET(uci_req, u_type, u_name);

				int idx = 0;
				char u_key[LEN_OF_BUF128] = "";
				char u_val[LEN_OF_BUF128] = "";
				SAFE_SPRINTF_EX(u_key, "key_%02d", 1);
				for (idx = 0; idx < 5; idx++)
				{
					SAFE_SPRINTF_EX(u_val, "%02d", idx);
					UCI_LIST_ADD(uci_req, "name_04", "list_01", u_val);
				}
				for (idx = 0; idx < 5; idx++)
				{
					SAFE_SPRINTF_EX(u_val, "%02d", idx);
					UCI_LIST_ADD(uci_req, "name_04", "list_02", u_val);
				}
			}
			UCI_LIST_FREE(uci_req, "name_04", "list_01");
			UCI_LIST_DEL(uci_req, "name_04", "list_02", "03");
#endif

			uci_show_configs_ex(uci_req);
			uci_show_what_ex(uci_req, "demo");

			UCI_CLOSE(uci_req);
		}
	}

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	exit(0);
}
