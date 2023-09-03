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


int main(int argc, char* argv[])
{
	DBG_IF_LN(DBG_TXT_ENTER);


	ULOG_OPEN_SUSER(NULL);
	ULOG_LVL_SET(LOG_INFO);
	ULOG_IF_LN(DBG_TXT_ENTER);

	ULOG_IF_LN(DBG_TXT_BYE_BYE);
	ULOG_CLOSE();

	DBG_IF_LN(DBG_TXT_BYE_BYE);
	exit(0);
}
