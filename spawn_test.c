#if (0)
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_loop_t *loop;
uv_process_t child_req;
uv_process_options_t options;
int main() {
    loop = uv_default_loop();

    char* args[5];
    args[0] = "mkdir";
    args[1] = "-p";
    args[2] = "test-dir";
    args[3] = NULL;

    options.exit_cb = on_exit;
    options.file = "mkdir";
    options.args = args;

    int r;
    if ((r = uv_spawn(loop, &child_req, &options))) {
        fprintf(stderr, "%s\n", uv_strerror(r));
        return 1;
    } else {
        fprintf(stderr, "Launched process with ID %d\n", child_req.pid);
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
#else
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_loop_t *loop;
uv_process_t child_req;
uv_process_options_t options;
uv_pipe_t pipe_in;
uv_pipe_t pipe_out;

void on_child_exit(uv_process_t *req, int64_t exit_status, int term_signal) {
    fprintf(stderr, "Process exited with status %ld, signal %d\n", exit_status, term_signal);
    uv_close((uv_handle_t*) req, NULL);
    uv_close((uv_handle_t*) &pipe_out, NULL);
    uv_close((uv_handle_t*) &pipe_in, NULL);
}

void pipe_alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	printf("alloc_buffer called, requesting a %lu byte buffer\n", suggested_size);
	*buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void pipe_out_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
	if (nread > 0)
	{
		printf("(nread: %ld, len: %ld, %s)", nread, buf->len, buf->base);
	}

	if (buf->base)
	{
		free(buf->base);
	}
}

static char exepath[1024];
static size_t exepath_size = 1024;
static uv_stdio_container_t child_stdio[3];

int main(int argc, char *argv[]) {
    printf("spawn_test\n");
    loop = uv_default_loop();

    int r = 0;
    //r = uv_exepath(exepath, &exepath_size);
    exepath[exepath_size] = '\0';

    char* args[3];
    args[0] = "./dummy";
    args[1] = NULL;
    args[2] = NULL;

    uv_pipe_init(loop, &pipe_in, 0);
    uv_pipe_init(loop, &pipe_out, 0);
    //uv_pipe_open(&pipe_out, 0);

    child_stdio[0].flags = UV_CREATE_PIPE | UV_READABLE_PIPE;
    child_stdio[0].data.stream = (uv_stream_t*) &pipe_in;
    child_stdio[1].flags = UV_CREATE_PIPE | UV_WRITABLE_PIPE;
    child_stdio[1].data.stream = (uv_stream_t *) &pipe_out;
    child_stdio[2].flags = UV_IGNORE;
    options.stdio = child_stdio;
    options.stdio_count = 3;

    options.exit_cb = on_child_exit;
    options.file = args[0];
    options.args = args;

    r = uv_spawn(loop, &child_req, &options);
    if (r!=0) {
        fprintf(stderr, "%d %s\n", r, uv_strerror(r));
        return 1;
    }
    uv_read_start((uv_stream_t*)&pipe_out, pipe_alloc_buffer, pipe_out_read);

    return uv_run(loop, UV_RUN_DEFAULT);
}
#endif