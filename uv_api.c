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

void on_uv_close(uv_handle_t *handle)
{
	if (handle != NULL)
	{
	}
}

void on_uv_walk(uv_handle_t *handle, void *arg)
{
	SAFE_UV_CLOSE(handle, on_uv_close);
}

void uv_loop_close_ex(uv_loop_t *loop)
{
	uv_stop(loop);
	int result = uv_loop_close(loop);
	if (result == UV_EBUSY)
	{
		uv_walk(loop, on_uv_walk, NULL);
	}
}

static void uv_write_ex_cb(uv_write_t *req, int status)
{
	UvWriteEx_t *wreq = (UvWriteEx_t *)req;

	if (wreq->cb)
	{
		wreq->cb(req, status);
	}
	SAFE_FREE(wreq->buf.base);
	SAFE_FREE(wreq);
}

void uv_write_ex(uv_stream_t *dest, size_t size, char *buf, uv_write_cb cb)
{
	UvWriteEx_t *wreq = (UvWriteEx_t *)SAFE_CALLOC(1, sizeof(UvWriteEx_t));
	{
		wreq->buf = uv_buf_init((char *)SAFE_CALLOC(1, size), size);
		{
			SAFE_MEMCPY(wreq->buf.base, buf, size, size);
		}
	}

	wreq->cb = cb;
	uv_write((uv_write_t *)wreq, (uv_stream_t *)dest, &wreq->buf, 1, uv_write_ex_cb);
}

static void uv_spawn_exit_cb(uv_process_t *process, int64_t exit_status, int term_signal)
{
	if (process)
	{
		SpawnCtx_t *spawn_req = (SpawnCtx_t *)process->data;

		if (spawn_req)
		{
			SAFE_UV_CLOSE((uv_handle_t*)&spawn_req->pipe_in, NULL);
			SAFE_UV_CLOSE((uv_handle_t*)&spawn_req->pipe_out, NULL);
		}
		SAFE_UV_CLOSE((uv_handle_t*)process, NULL);
		spawn_req->quit = 1;
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, spawn_req->name);
	}
}

static void uv_spawn_pipe_init(SpawnCtx_t *spawn_req)
{
	spawn_req->stdio[0].flags = UV_CREATE_PIPE | UV_READABLE_PIPE;
	spawn_req->stdio[0].data.stream = (uv_stream_t *) &spawn_req->pipe_in;
	//spawn_req->stdio[0].flags = UV_IGNORE;
	spawn_req->stdio[1].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
	spawn_req->stdio[1].data.stream = (uv_stream_t *) &spawn_req->pipe_out;
	spawn_req->stdio[2].flags = UV_IGNORE;
	spawn_req->options.stdio_count = 3;
	spawn_req->options.stdio = spawn_req->stdio;

	SAFE_UV_PIPE_INIT(spawn_req->loop, &spawn_req->pipe_in, 0);
	SAFE_UV_PIPE_INIT(spawn_req->loop, &spawn_req->pipe_out, 0);
}

static void uv_alloc_ex_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	*buf = uv_buf_init((char*) SAFE_MALLOC(suggested_size), suggested_size);
}

static void uv_spawn_pipe_stdout_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
	if (nread < 0)
	{
		//DBG_ER_LN("%s (nread: %d)", DBG_TXT_WRONG, nread);
		SAFE_UV_CLOSE(stream, NULL);
	}
	else if (nread > 0)
	{
		SpawnCtx_t *spawn_req = (SpawnCtx_t *)stream->data;
		if ( (spawn_req) && (spawn_req->pipe_out_cb) )
		{
			spawn_req->pipe_out_cb(stream, nread, buf);
		}
		else
		{
			DBG_IF_LN("(buf->base: %s)", buf->base);
		}
	}

	// OK to free buffer as write_data copies it.
	if (buf->base)
	{
		free(buf->base);
	}
}

void uv_spawn_close_ex(SpawnCtx_t *spawn_req)
{
	if ( (spawn_req) && (spawn_req->quit==0) )
	{
		SAFE_UV_PROCESS_KILL(&spawn_req->child_req, SIGTERM);
		//SAFE_UV_PROCESS_KILL(&spawn_req->child_req, SIGQUIT);
		//SAFE_UV_KILL(spawn_req->child_req.pid, SIGTERM);

		if ( (spawn_req->options.flags & UV_PROCESS_DETACHED) == UV_PROCESS_DETACHED )
		{
			SAFE_UV_UNREF(&spawn_req->child_req);
		}
	}
}

void uv_spawn_open_ex(SpawnCtx_t *spawn_req)
{
	if (spawn_req)
	{
		uv_spawn_pipe_init(spawn_req);

		spawn_req->options.exit_cb = uv_spawn_exit_cb;
		spawn_req->options.file = spawn_req->args[0];
		spawn_req->options.args = spawn_req->args;
		spawn_req->options.flags = spawn_req->flags; //UV_PROCESS_DETACHED;

		spawn_req->child_req.data = (void *)spawn_req;
		int r = uv_spawn(spawn_req->loop, &spawn_req->child_req, &spawn_req->options);
		if ( r == 0 )
		{
			spawn_req->pipe_out.data = (void *)spawn_req;
			SAFE_UV_READ_START((uv_stream_t*)&spawn_req->pipe_out, uv_alloc_ex_cb, uv_spawn_pipe_stdout_cb);
			
			DBG_WN_LN("%s (spawn_req: %p, pid: %d)", DBG_TXT_LAUNCH_THREAD, spawn_req, spawn_req->child_req.pid);
		}
		else
		{
			DBG_ER_LN("%s - %s (%s)", DBG_TXT_WRONG, uv_strerror(r), spawn_req->args[0]);
		}
	}
	else
	{
		DBG_IF_LN("spawn_req is NULL !!!");
	}
}

void uv_spawn_on_exit(uv_process_t *req, int64_t exit_status, int term_signal)
{
	DBG_DB_LN("(exit_status: %d, term_signal: %d)", exit_status, term_signal);
	SAFE_FREE(req->data);

	uv_close((uv_handle_t*) req, NULL);
}

void uv_spawn_simple_detached(SpawnCtx_t *spawn_req, int num, ...)
{
	if ( (spawn_req) && (spawn_req->loop) && (num < MAX_OF_SPAWN_ARGS) )
	{
		int i = 0;

		va_list args;
		va_start(args, num);
		for (i = 0; i < num; i++)
		{
			spawn_req->args[i] = va_arg(args, char*);
		}
		spawn_req->args[num] = NULL;
		va_end(args);

		if (spawn_req->options.exit_cb == NULL)
		{
			spawn_req->options.exit_cb = uv_spawn_on_exit;
		}
		spawn_req->options.file = spawn_req->args[0];
		spawn_req->options.args = spawn_req->args;
		spawn_req->options.flags |= UV_PROCESS_DETACHED;

		int r;
		if ((r = uv_spawn(spawn_req->loop, &spawn_req->child_req, &spawn_req->options)))
		{
			DBG_IF_LN("uv_spawn error !!! (%s)", uv_strerror(r));
		}
		else
		{
			DBG_IF_LN("uv_spawn ... (child_args[0]: %s)", spawn_req->args[0]);
		}
		uv_unref((uv_handle_t*) &spawn_req->child_req);
	}
	else
	{
		DBG_ER_LN("error !!! (spawn_req: %p, uv_loop: %p, num %d >= 20)", spawn_req, spawn_req->loop, num);
	}
}

static void uv_event_cb(uv_fs_event_t *handle, const char *filename, int events, int status)
{
	if (handle)
	{
		UvEventCtx_t *event_req = (UvEventCtx_t *)handle->data;
		if (event_req)
		{
			if (event_req->detect_cb)
			{
				event_req->detect_cb(handle, filename, events, status);
			}
			else
			{
				DBG_IF_LN("(filename: %s, events: %d, status: %d)", filename, events, status);
			}
		}
	}
}

void uv_event_close_ex(UvEventCtx_t *event_req)
{
	if ( (event_req) && (event_req->isquit==0) )
	{
		event_req->isquit = 1;
		uv_fs_event_stop(&event_req->req);
		DBG_WN_LN("%s (%s)", DBG_TXT_BYE_BYE, event_req->name);
	}
}

void uv_event_open_ex(UvEventCtx_t *event_req)
{
	if ( (event_req) && (event_req->loop) )
	{
		event_req->req.data = (void *)event_req;
		uv_fs_event_init(event_req->loop, &event_req->req);
		uv_fs_event_start(&event_req->req, uv_event_cb, event_req->filename, event_req->flags);
	}
}
