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

//#define SAFE_SWAP_INC(x,y) ({ typeof(x) _x = SAFE_MIN(x,y); typeof(y) _y = SAFE_MAX(x,y); x = _x; y = _y})

static void cronx_item2range(char *cron_sub, char *range_ary, int start, int min, int max)
{
	{
		char *cron_line = NULL;
		//DBG_DB_LN("saveptr: [%s]", saveptr);
		SAFE_ASPRINTF(cron_line, "%s", cron_sub);

		char *saveptr = cron_line;
		char *token = NULL;
		while ((token = SAFE_STRTOK_R(NULL, ",", &saveptr)))
		{
			int i = SAFE_ATOI(token);
			if (SAFE_STRCHR(token, '-'))
			{
				int idx_b = 0;
				int idx_e = -1;
				if (SAFE_SSCANF(token, "%d-%d", &idx_b, &idx_e) >= 2)
				{
					idx_b -= start;
					idx_e -= start;
					DBG_TR_LN("(cron_sub: %s, token: %s, idx_b: %d, idx_e: %d)", cron_sub, token, idx_b, idx_e);
					for (i = idx_b; i <= idx_e && i <= max; i++)
					{
						range_ary[i] = 1;
					}
				}
			}
			else if (SAFE_STRCHR(token, '/'))
			{
				int interval = 0;
				if (SAFE_SSCANF(token, "*/%d", &interval) >= 1)
				{
					int idx_b = min;
					int idx_e = max;
					DBG_TR_LN("(cron_sub: %s, token: %s, interval: %d)", cron_sub, token, interval);
					for (i = idx_b; i <= idx_e; i+=interval)
					{
						range_ary[i] = 1;
					}
				}
			}
			else if (SAFE_STRCMP(token, "*") == 0)
			{
				int idx_b = min;
				int idx_e = max;
				for (i = idx_b; i <= idx_e; i++)
				{
					range_ary[i] = 1;
				}
			}
			else
			{
				DBG_TR_LN("(cron_sub: %s, token: %s, i: %d)", cron_sub, token, i);
				i -= start;
				range_ary[i] = 1;
			}
		}
		SAFE_FREE(cron_line);
	}
}


// minute (0-59)
// hour (0-23)
// day of month (1-31)
// month (1-12)
// day of week (0-6, Sunday=0)
// * * * * *
// 1 2 3 4 5
int cronx_validate(char *cron_txt, struct tm *kick_tm)
{
	int fit = 0;

	int tm_min = kick_tm->tm_min;
	int tm_hour = kick_tm->tm_hour;
	int tm_mday = kick_tm->tm_mday;
	int tm_mon = kick_tm->tm_mon;
	int tm_wday = kick_tm->tm_wday;
	int tm_year = kick_tm->tm_year+1900;
	DBG_DB_LN("(cron_txt: [%s], [%d %d %d %d %d %d])", cron_txt, tm_min, tm_hour, tm_mday, tm_mon, tm_wday, tm_year);
	{
		int idx = 0;
		char *cron_line = NULL;
		//DBG_DB_LN("saveptr: [%s]", saveptr);
		SAFE_ASPRINTF(cron_line, "%s", cron_txt);

		char *saveptr = cron_line;
		char *token = NULL;
		while ((token = SAFE_STRTOK_R(NULL, " ", &saveptr)))
		{
			char range_ary[MAX_OF_CRON_RANGE]= {0};
			switch (idx)
			{
				case CRON_ID_MINUTE:
					cronx_item2range(token, range_ary, 0, 0, 59);
					DBG_TR_DUMP(range_ary, 60, " ", "range_ary (%s):", token);
					if (range_ary[tm_min] == 1)
					{
						// fit
						fit ++;
					}
					else
					{
						fit = -1;
						goto exit_parser;
					}
					break;
				case CRON_ID_HOUR:
					cronx_item2range(token, range_ary, 0, 0, 23);
					DBG_TR_DUMP(range_ary, 24, " ", "range_ary (%s):", token);
					if (range_ary[tm_hour] == 1)
					{
						// fit
						fit ++;
					}
					else
					{
						fit = -1;
						goto exit_parser;
					}
					break;
				case CRON_ID_MDAY:
					cronx_item2range(token, range_ary, 0, 1, 31);
					DBG_TR_DUMP(range_ary, 32, " ", "range_ary (%s):", token);
					if (range_ary[tm_mday] == 1)
					{
						// fit
						fit ++;
					}
					else
					{
						fit = -1;
						goto exit_parser;
					}
					break;
				case CRON_ID_MONTH:
					cronx_item2range(token, range_ary, 0, 1, 12);
					DBG_TR_DUMP(range_ary, 13, " ", "range_ary (%s):", token);
					if (range_ary[tm_mon] == 1)
					{
						// fit
						fit ++;
					}
					else
					{
						fit = -1;
						goto exit_parser;
					}
					break;
				case CRON_ID_WDAY:
					cronx_item2range(token, range_ary, 0, 0, 6);
					DBG_TR_DUMP(range_ary, 7, " ", "range_ary (%s):", token);
					if (range_ary[tm_wday] == 1)
					{
						// fit
						fit ++;
					}
					else
					{
						fit = -1;
						goto exit_parser;
					}
					break;
				case CRON_ID_YEAR:
				{
					cronx_item2range(token, range_ary, CRON_YEAR_START_2020, CRON_YEAR_START_2020-CRON_YEAR_START_2020, CRON_YEAR_END_2120-CRON_YEAR_START_2020);
					DBG_TR_DUMP(range_ary, CRON_YEAR_END_2120-CRON_YEAR_START_2020+1, " ", "range_ary (%s):", token);
					if (tm_year>CRON_YEAR_START_2020)
					{
						tm_year -= CRON_YEAR_START_2020;
						if (range_ary[tm_year] == 1)
						{
							// fit
							fit ++;
						}
						else
						{
							fit = -1;
							goto exit_parser;
						}
					}
					else
					{
						fit = -1;
						goto exit_parser;
					}
				}
				break;
				default:
					break;
			}
			idx++;
			//DBG_ER_LN(">>>>>>>> (token: %s)", token);
		}

exit_parser:
		SAFE_FREE(cron_line);
		if (fit>0)
		{
			DBG_IF_LN("%s (cron_txt: [%s], [%d %d %d %d %d %d], fit: %d)", DBG_TXT_GOT, cron_txt, tm_min, tm_hour, tm_mday, tm_mon, tm_wday, tm_year, fit);
		}
	}

	return fit;
}
