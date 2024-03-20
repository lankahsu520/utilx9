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

BackTraceX_t backtraceX_data = {
	.state = NULL,
	.data = NULL
};

void backtraceX_error_cb(void *data, const char *msg, int errnum)
{
	//BackTraceX_t *backtraceX_req = data;
	DBG_ER_LN("(errnum: %d, msg: %s)", errnum, msg);
}

static void backtraceX_syminfo_cb(void *data, uintptr_t pc, const char *symname, uintptr_t symval, uintptr_t symsize)
{
	//struct bt_ctx *ctx = data;
	if (symname)
	{
		printf("%lx %s ??:0\n", (unsigned long)pc, symname);
	}
	else
	{
		printf("%lx ?? ??:0\n", (unsigned long)pc);
	}
}

static int backtraceX_full_cb(void *data, uintptr_t pc, const char *filename, int lineno, const char *function)
{
	BackTraceX_t *backtraceX_req = data;
	if (function)
	{
		printf("%lx %s %s:%d\n", (unsigned long)pc, function, filename?filename:"??", lineno);
	}
	else
	{
		backtrace_syminfo(backtraceX_req->state, pc, backtraceX_syminfo_cb, backtraceX_error_cb, data);
	}
	return 0;
}

static int backtraceX_simple_cb(void *data, uintptr_t pc)
{
	BackTraceX_t *backtraceX_req = data;
	backtrace_pcinfo(backtraceX_req->state, pc, backtraceX_full_cb, backtraceX_error_cb, data);
	return 0;
}

void backtraceX_alert(BackTraceX_t *backtraceX_req)
{
	if (backtraceX_req==NULL)
	{
		backtraceX_req = &backtraceX_data;
	}

	backtrace_print(backtraceX_req->state, 0, stdout);
	backtrace_simple(backtraceX_req->state, 0, backtraceX_simple_cb, backtraceX_error_cb, backtraceX_req);
}

void backtraceX_init(int argc, char **argv)
{
	backtraceX_data.state = backtrace_create_state(argv[0], BACKTRACE_SUPPORTS_THREADS, backtraceX_error_cb, NULL);
}

