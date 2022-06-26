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

int sshX_open_shell(SSH_t *ssh_req)
{
	int rc;

	rc = ssh_channel_open_session(ssh_req->channel);
	if (rc != SSH_OK)
	{
		DBG_ER_LN("ssh_channel_open_session error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
		return rc;
	}

	return rc;
}

int sshX_request_pty(SSH_t *ssh_req)
{
	int rc;

	rc = ssh_channel_request_pty(ssh_req->channel);
	if (rc != SSH_OK)
	{
		DBG_ER_LN("ssh_channel_request_pty error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
		return rc;
	}

	if ( (ssh_req->cols != 0 ) && (ssh_req->rows != 0 ) )
	{
		rc = ssh_channel_change_pty_size(ssh_req->channel, ssh_req->cols, ssh_req->rows);
		if (rc != SSH_OK)
		{
			DBG_ER_LN("ssh_channel_change_pty_size error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
			return rc;
		}
	}

	return rc;
}

int sshX_request_shell(SSH_t *ssh_req)
{
	int rc;

	rc = ssh_channel_request_shell(ssh_req->channel);
	if (rc != SSH_OK)
	{
		DBG_ER_LN("ssh_channel_request_shell error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
		return rc;
	}

	return rc;
}

void sshX_stream_copy(ssh_channel channel_frm, ssh_channel channel_to)
{
	int nbytes = 0;
	char buffer[LEN_OF_BUF1024];
	memset(buffer, 0, sizeof(buffer));

	while ( (nbytes = ssh_channel_read_timeout(channel_frm, buffer, sizeof(buffer), 0, 100)) > 0)
	{
		nbytes = ssh_channel_write(channel_to, buffer, sizeof(buffer));
		memset(buffer, 0, sizeof(buffer));
	}
}

void sshX_select_loop_with_tunnel(SSH_t *ssh_req, SSH_t *ssh_req_frm)
{
	ssh_session session = ssh_req->session;
	ssh_channel channel = ssh_req->channel;

	ssh_channel channel_frm = ssh_req_frm->channel;

	ssh_connector connector_in, connector_out, connector_err;
	int rc;

	ssh_event event = ssh_event_new();

	/* stdin */
	connector_in = ssh_connector_new(session);
	ssh_connector_set_out_channel(connector_in, channel, SSH_CONNECTOR_STDINOUT);
	ssh_connector_set_in_channel(connector_in, channel_frm, SSH_CONNECTOR_STDINOUT);
	ssh_event_add_connector(event, connector_in);

	/* stdout */
	connector_out = ssh_connector_new(session);
	ssh_connector_set_out_channel(connector_out, channel_frm, SSH_CONNECTOR_STDINOUT);
	ssh_connector_set_in_channel(connector_out, channel, SSH_CONNECTOR_STDINOUT);
	ssh_event_add_connector(event, connector_out);

	/* stderr */
	connector_err = ssh_connector_new(session);
	ssh_connector_set_out_channel(connector_err, channel_frm, SSH_CONNECTOR_STDINOUT);
	ssh_connector_set_in_channel(connector_err, channel, SSH_CONNECTOR_STDERR);
	ssh_event_add_connector(event, connector_err);

	while (ssh_channel_is_open(channel) && (ssh_channel_is_eof(channel) == 0) &&
					ssh_channel_is_open(channel_frm) && (ssh_channel_is_eof(channel_frm) == 0) )
	{
		//if (signal_delayed) {
		//	sizechanged();
		//}
		rc = ssh_event_dopoll(event, 60000);
		if (rc == SSH_ERROR)
		{
			DBG_ER_LN("ssh_event_dopoll error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(session), ssh_get_error(session));
			break;
		}
	}

	if (connector_in)
	{
		ssh_event_remove_connector(event, connector_in);
		ssh_connector_free(connector_in);
	}
	if (connector_out)
	{
		ssh_event_remove_connector(event, connector_out);
		ssh_connector_free(connector_out);
	}
	if (connector_err)
	{
		ssh_event_remove_connector(event, connector_err);
		ssh_connector_free(connector_err);
	}

	ssh_event_free(event);
}

void sshX_select_loop_with_fd(SSH_t *ssh_req, socket_t in_fd, socket_t out_fd, socket_t err_fd)
{
	ssh_session session = ssh_req->session;
	ssh_channel channel = ssh_req->channel;

	ssh_connector connector_in, connector_out, connector_err;
	int rc;

	ssh_event event = ssh_event_new();

	/* stdin */
	connector_in = ssh_connector_new(session);
	ssh_connector_set_out_channel(connector_in, channel, SSH_CONNECTOR_STDINOUT);
	ssh_connector_set_in_fd(connector_in, in_fd);
	ssh_event_add_connector(event, connector_in);

	/* stdout */
	connector_out = ssh_connector_new(session);
	ssh_connector_set_out_fd(connector_out, out_fd);
	ssh_connector_set_in_channel(connector_out, channel, SSH_CONNECTOR_STDINOUT);
	ssh_event_add_connector(event, connector_out);

	/* stderr */
	connector_err = ssh_connector_new(session);
	ssh_connector_set_out_fd(connector_err, err_fd);
	ssh_connector_set_in_channel(connector_err, channel, SSH_CONNECTOR_STDERR);
	ssh_event_add_connector(event, connector_err);

	while (ssh_channel_is_open(channel))
	{
		//if (signal_delayed) {
		//	sizechanged();
		//}
		rc = ssh_event_dopoll(event, 60000);
		if (rc == SSH_ERROR)
		{
			DBG_ER_LN("ssh_event_dopoll error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(session), ssh_get_error(session));
			break;
		}
	}
	if (connector_in)
	{
		ssh_event_remove_connector(event, connector_in);
		ssh_connector_free(connector_in);
	}
	if (connector_out)
	{
		ssh_event_remove_connector(event, connector_out);
		ssh_connector_free(connector_out);
	}
	if (connector_err)
	{
		ssh_event_remove_connector(event, connector_err);
		ssh_connector_free(connector_err);
	}

	ssh_event_free(event);
}

ssh_channel sshX_open_channel(SSH_t *ssh_req)
{
	ssh_req->channel = ssh_channel_new(ssh_req->session);
	return ssh_req->channel;
}

int sshX_interactive(SSH_t *ssh_req)
{
	int ret = 0;

	if ( sshX_open_channel(ssh_req) )
	{
		struct termios terminal;
		struct termios terminal_local;
		int interactive=isatty(0);

		if (interactive)
		{
			tcgetattr(0, &terminal_local);
			memcpy(&terminal, &terminal_local, sizeof(struct termios));
		}

		sshX_open_shell(ssh_req);
		sshX_request_pty(ssh_req);
		sshX_request_shell(ssh_req);

		if (interactive)
		{
			cfmakeraw(&terminal_local);
			tcsetattr(0, TCSANOW, &terminal_local);
			//setsignal();
		}

		sshX_select_loop_with_fd(ssh_req, 0, 1, 2);

		tcsetattr(0, TCSANOW, &terminal);
	}

	return ret;
}

int sshX_authenticate(SSH_t *ssh_req)
{
	int rc = SSH_AUTH_SUCCESS;

	DBG_TR_LN("call ssh_userauth_none ...");
	rc = ssh_userauth_none(ssh_req->session, NULL);
	if (rc == SSH_AUTH_ERROR)
	{
		return rc;
	}

	char *banner = ssh_get_issue_banner(ssh_req->session);
	if (banner)
	{
		printf("%s\n",banner);
		SSH_STRING_FREE_CHAR(banner);
	}

	int method = ssh_userauth_list(ssh_req->session, NULL);
	DBG_DB_LN("(method: %d)", method);

	while (rc != SSH_AUTH_SUCCESS)
	{
		if ( method & SSH_AUTH_METHOD_GSSAPI_MIC )
		{
			rc = ssh_userauth_gssapi(ssh_req->session);
			if(rc == SSH_AUTH_ERROR)
			{
				DBG_ER_LN("ssh_userauth_gssapi error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
				return rc;
			}
			else if (rc == SSH_AUTH_SUCCESS)
			{
				break;
			}
		}

		if ( method & SSH_AUTH_METHOD_PUBLICKEY )
		{
			rc = ssh_userauth_publickey_auto(ssh_req->session, NULL, NULL);
			if (rc == SSH_AUTH_ERROR)
			{
				DBG_ER_LN("ssh_userauth_publickey_auto error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
				return rc;
			}
			else if (rc == SSH_AUTH_SUCCESS)
			{
				break;
			}
		}

		if ( method & SSH_AUTH_METHOD_PASSWORD )
		{
			char *password = NULL;
			if ( strlen(ssh_req->server_pass_dec) > 0 )
			{
				SAFE_ASPRINTF(password, "%s",  ssh_req->server_pass_dec);
			}
			else if ( strlen(ssh_req->server_pass_enc) <= 0 )
			{
				char prompt[LEN_OF_BUF256] = "";
				SAFE_SNPRINTF(prompt, sizeof(prompt), "%s@%s's passowrd: ", ssh_req->server_user, ssh_req->server_ip);

				password = SAFE_CALLOC(1, LEN_OF_PASS);
				memset(password, 0, LEN_OF_PASS);
				if (ssh_getpass(prompt, password, LEN_OF_PASS, 0, 0) < 0)
				{
					return SSH_AUTH_ERROR;
				}
			}
			else
			{
				int server_pass_dec_len = 0;
				password = sec_base64_dec(ssh_req->server_pass_enc, strlen(ssh_req->server_pass_enc), &server_pass_dec_len);
			}

			if (password)
			{
				//DBG_ER_LN("(password: %s)", password);
				rc = ssh_userauth_password(ssh_req->session, NULL, password);
				switch (rc)
				{
					case SSH_AUTH_SUCCESS:
						break;
					case SSH_AUTH_DENIED:
						DBG_WN_LN("Permission denied, please try again !!!");
						break;
					default:
						DBG_ER_LN("ssh_userauth_password error !!! (rc: %d, %d %s)", rc, ssh_get_error_code(ssh_req->session), ssh_get_error(ssh_req->session));
						break;
				}
				SAFE_FREE(password);
			}
		}
	}
	return rc;
}

void sshX_close_channel(SSH_t *ssh_req)
{
	if (ssh_req->channel)
	{
		ssh_channel_send_eof(ssh_req->channel);
		ssh_channel_close(ssh_req->channel);
		ssh_channel_free(ssh_req->channel);

		ssh_req->channel = NULL;
	}
}

void sshX_close_session(SSH_t *ssh_req)
{
	if (ssh_req->session )
	{
		if (ssh_is_connected(ssh_req->session ))
		{
			ssh_disconnect(ssh_req->session );
		}

		ssh_free(ssh_req->session );
		ssh_req->session  = NULL;
	}
}

void sshX_stop(SSH_t *ssh_req)
{
	sshX_close_channel(ssh_req);
	sshX_close_session(ssh_req);
}

ssh_session sshX_client(SSH_t *ssh_req)
{
	//int rc;
	//ssh_init();

	ssh_req->session = ssh_new();
	if (ssh_req->session == NULL)
	{
		DBG_ER_LN("ssh_new error !!!");
		goto exit_connect;
	}

#if (0)
	ssh_callbacks_init(&cb);
	ssh_set_callbacks(ssh_req->session,&cb);
#endif

	{
		// connect
		ssh_options_set(ssh_req->session, SSH_OPTIONS_LOG_VERBOSITY, &ssh_req->verbosity);
		ssh_options_set(ssh_req->session, SSH_OPTIONS_HOST, ssh_req->server_ip); 
		if ( strlen(ssh_req->server_user) > 0 )
		{
			DBG_TR_LN("(ssh_req->server_user: %s)", ssh_req->server_user);
			ssh_options_set(ssh_req->session, SSH_OPTIONS_USER, ssh_req->server_user);
		}
		if (ssh_req->server_port > 0)
			ssh_options_set(ssh_req->session, SSH_OPTIONS_PORT, &ssh_req->server_port);

		int process_config = 0;
		ssh_options_set(ssh_req->session , SSH_OPTIONS_PROCESS_CONFIG, &process_config);

		ssh_options_parse_config(ssh_req->session, NULL);

		DBG_TR_LN("call ssh_connect ...");
		if ( ssh_connect(ssh_req->session) )
		{
			DBG_ER_LN("ssh_new error !!! (%s)", ssh_get_error(ssh_req->session));
			goto exit_connect;
		}

		char *banner = ssh_get_issue_banner(ssh_req->session);
		if (banner)
		{
			DBG_DB_LN("(banner: %s)", banner);
			SAFE_FREE(banner);
		}

		if ( SSH_AUTH_SUCCESS != sshX_authenticate(ssh_req) )
			goto exit_connect;
	}
	return ssh_req->session ;

exit_connect:
	sshX_close_session(ssh_req);
	//ssh_finalize();

	return ssh_req->session ;
}

