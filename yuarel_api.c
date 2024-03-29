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

char *query_uri_get(QueryParam_t *q_params_req)
{
	return q_params_req->query;
}

int query_count_get(QueryParam_t *q_params_req)
{
	return q_params_req->count;
}

yuarel_param_t *query_params_get(QueryParam_t *q_params_req)
{
	return q_params_req->params;
}

yuarel_param_t *query_parser(char *query, QueryParam_t *q_params_req)
{
	SAFE_SNPRINTF(q_params_req->query, sizeof(q_params_req->query), "%s", query);
	SAFE_SNPRINTF(q_params_req->query_parse, sizeof(q_params_req->query_parse), "%s", query);
	q_params_req->count = yuarel_parse_query(q_params_req->query_parse, '&', q_params_req->params, MAX_OF_QUERY_PARAM);

	return q_params_req->params;
}

