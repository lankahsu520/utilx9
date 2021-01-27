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

#define DBG_TMP_Y(format,args...) //DBG_DB_LN
#define DBG_TMP_DUMP(ibuf,ilen,delim,format,args...) //DBG_TR_DUMP

static size_t dummy_fp2body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	// my side(fp) -> server
	size_t bytec = size * nmemb;
	bytec = SAFE_FREAD(ptr, 1, (size * nmemb), (FILE *)context);
	return bytec;
}

#if (0)
static size_t dummy_buff2body_cb(void *ptr, size_t size, size_t nmemb, void *context)
{
	// my side(buff) -> server
	HttpCtx_t *http_req = (HttpCtx_t *)context;
	SimpleRequest_t *simple_req = (SimpleRequest_t *)&http_req->simple_req;

	int len = simple_req->req_size - simple_req->req_pos;
	if (len>0)
	{
		if (len > size * nmemb)
		{
			len = size * nmemb;
		}
		//memcpy(ptr, simple_req->request + simple_req->req_pos, len);
		memcpy(ptr, "Hello World!!!", len);
		simple_req->req_pos += len;
	}
	else
	{
		len = 0;
	}
	return len;
}
#endif

#ifdef UTIL_EX_CURL_RTSP
static size_t dummy_header_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	// my side <- server
	size_t bytec = size * nmemb;
	DBG_TMP_Y("(bytec: %zd, ptr: %s)", bytec, str_trim(ptr));
	return bytec;
}

static size_t dummy_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	// my side <- server
	size_t bytec = size * nmemb;
	DBG_TMP_DUMP(ptr, bytec, " ", "(bytec: %zu)", bytec);
	return bytec;
}
#endif

static size_t simple_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	// my side <- server
	size_t bytec = size * nmemb;
	HttpCtx_t *http_req = (HttpCtx_t *)context;
	SimpleRequest_t *simple_req = (SimpleRequest_t *)&http_req->simple_req;

	size_t new_len = simple_req->res_size + bytec + 1;
	char *new_buff = SAFE_REALLOC(simple_req->response, new_len );
	if ( new_buff == NULL )
	{
		DBG_ER_LN("SAFE_REALLOC error !!! (res_size: %zd -> %zd)", simple_req->res_size, new_len);
		return 0;
	}

	simple_req->response = new_buff;
	SAFE_MEMCPY(&(simple_req->response[simple_req->res_size]), ptr, bytec, new_len - simple_req->res_size);
	simple_req->res_size += bytec;
	simple_req->response[simple_req->res_size] = 0;
	return bytec;
}

static size_t soap_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	// my side <- server
	size_t bytec = size * nmemb;
	HttpCtx_t *http_req = (HttpCtx_t *)context;
	SoapRequest_t *soap_req = (SoapRequest_t *)&http_req->soap_req;

	size_t new_len = soap_req->res_size + bytec + 1;
	char *new_buff = SAFE_REALLOC(soap_req->response, new_len );
	if ( new_buff == NULL )
	{
		DBG_ER_LN("SAFE_REALLOC error !!! (size: %zd -> %zd)", soap_req->res_size, new_len);
		return 0;
	}

	soap_req->response = new_buff;
	SAFE_MEMCPY(&(soap_req->response[soap_req->res_size]), ptr, bytec, new_len - soap_req->res_size);
	soap_req->res_size += bytec;
	soap_req->response[soap_req->res_size] = 0;
	return bytec;
}

static size_t uploadfile_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	// my side <- server
	size_t bytec = size * nmemb;
	HttpCtx_t *http_req = (HttpCtx_t *)context;
	FileRequest_t *file_req = (FileRequest_t *)&http_req->file_req;

	size_t new_len = file_req->res_size + bytec + 1;
	char *new_buff = SAFE_REALLOC(file_req->response, new_len );
	if ( new_buff == NULL )
	{
		DBG_ER_LN("SAFE_REALLOC error !!! (size: %zd -> %zd)", file_req->res_size, new_len);
		return 0;
	}

	file_req->response = new_buff;
	SAFE_MEMCPY(&(file_req->response[file_req->res_size]), ptr, bytec, new_len - file_req->res_size);
	file_req->res_size += bytec;
	file_req->response[file_req->res_size] = 0;
	return bytec;
}

static int http_request_simple(HttpCtx_t *http_req)
{
	int ret = -1;
	SimpleRequest_t *simple_req = (SimpleRequest_t *)&http_req->simple_req;

	//DBG_TR_LN("enter (simple_req->method: %d, request: %s)", simple_req->method, simple_req->request);
	DBG_TR_LN("enter (simple_req->method: %d)", simple_req->method);

	if ( strlen(http_req->url) > 0 )
	{
		{
			curl_global_init(CURL_GLOBAL_DEFAULT);
			CURL *curl = curl_easy_init();
			CURLcode curl_res;
			{
				curl_easy_setopt(curl, CURLOPT_URL, http_req->url);
				if (http_req->port!=0)
				{
					curl_easy_setopt(curl, CURLOPT_PORT, http_req->port);
				}
			}
			{
				// ** Auth **
				if (SAFE_STRNCMP( http_req->url, "https", strlen("https") ) == 0)
				{
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
					//curl_easy_setopt(curl, CURLOPT_SSLVERSION, 3);
				}
				if ((http_req->user) && (http_req->password))
				{
					curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
					curl_easy_setopt(curl, CURLOPT_USERNAME, http_req->user);
					curl_easy_setopt(curl, CURLOPT_PASSWORD, http_req->password);
				}
			}

			{
				// ** Debug & Timeout **
				curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_OF_CURL_CONNECTTIMEOUT);
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, MAX_OF_CURL_TIMEOUT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VAL_OF_CURLOPT_VERBOSE);
				// ** redirected **
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			}

			{
				// ** Header **
				if (simple_req->headers)
				{
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, simple_req->headers);
				}
			}

			{
				// ** Body **
				if (simple_req->request)
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, simple_req->request);
				switch (simple_req->method)
				{
					case HTTP_METHOD_ID_POST:
						break;
					case HTTP_METHOD_ID_GET:
						curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET"); 
						break;
					case HTTP_METHOD_ID_PUT:
						curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); 
						break;
					default:
						break;
				}
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, simple_body_cb);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);
			}

			curl_res = curl_easy_perform(curl);
			/* Check for errors */ 
			if(curl_res != CURLE_OK)
			{
				SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "%d %s !!! (url: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url);
			}
			else
			{

				ret = 0;
			}
			/* always cleanup */ 
			curl_easy_cleanup(curl);
			curl_global_cleanup();
		}
	}
	else
	{
		SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "soap_req->request is NULL !!!");
	}
	DBG_TR_LN("ret: %d, %s", ret, http_req->log);
	return ret;
}

static int http_request_soap(HttpCtx_t *http_req)
{
	int ret = -1;
	SoapRequest_t *soap_req = (SoapRequest_t *)&http_req->soap_req;

	DBG_TR_LN("enter (soap_req->h_action: %s)", soap_req->h_action);

	if (soap_req->request)
	{
		{
			curl_global_init(CURL_GLOBAL_DEFAULT);
			CURL *curl = curl_easy_init();
			CURLcode curl_res;
			{
				curl_easy_setopt(curl, CURLOPT_URL, http_req->url);
				if (http_req->port!=0)
				{
					curl_easy_setopt(curl, CURLOPT_PORT, http_req->port);
				}
			}
			{
				// ** Auth **
				if (SAFE_STRNCMP( http_req->url, "https", strlen("https") ) == 0)
				{
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
					//curl_easy_setopt(curl, CURLOPT_SSLVERSION, 3);
				}
				if ((http_req->user) && (http_req->password))
				{
					curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
					curl_easy_setopt(curl, CURLOPT_USERNAME, http_req->user);
					curl_easy_setopt(curl, CURLOPT_PASSWORD, http_req->password);
				}
			}

			{
				// ** Debug & Timeout **
				curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_OF_CURL_CONNECTTIMEOUT);
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, MAX_OF_CURL_TIMEOUT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VAL_OF_CURLOPT_VERBOSE);
				// ** redirected **
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			}

			{
				// ** Header **
				soap_req->headers = curl_slist_append(soap_req->headers, "Content-Type: application/soap+xml; charset=utf-8");
				soap_req->headers = curl_slist_append(soap_req->headers, "Accept-Encoding: gzip, deflate");
				//headers = curl_slist_append(headers, soap_req->h_action);
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, soap_req->headers);
			}

			{
				// ** Body **
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soap_req->request);

				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, soap_body_cb);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);
			}

			curl_res = curl_easy_perform(curl);
			/* Check for errors */ 
			if(curl_res != CURLE_OK)
			{
				SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "%d %s !!! (url: %s, h_action: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url, soap_req->h_action);
			}
			else
			{

				ret = 0;
			}
			/* always cleanup */ 
			curl_easy_cleanup(curl);
			curl_global_cleanup();
		}
	}
	else
	{
		SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "soap_req->request is NULL !!!");
	}
	DBG_TR_LN("ret: %d, %s", ret, http_req->log);
	return ret;
}

static int http_request_uploadfile(HttpCtx_t *http_req)
{
	int ret = -1;
	FileRequest_t *file_req = (FileRequest_t *)&http_req->file_req;

	DBG_TR_LN("enter (file_req->filename: %s)", file_req->filename);
	
	file_req->fp = SAFE_FOPEN(file_req->filename, "rb"); /* open file to upload */ 
	if(file_req->fp)
	{
		struct stat file_info;
		if(fstat(SAFE_FILENO(file_req->fp), &file_info) != 0)
		{
			SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "fstat error !!! (url: %s, filename: %s)", http_req->url, file_req->filename );
		}
		else
		{
			curl_global_init(CURL_GLOBAL_DEFAULT);
			CURL *curl = curl_easy_init();
			CURLcode curl_res;
			curl_easy_setopt(curl, CURLOPT_URL, http_req->url);

			{
				// ** Auth **
				if (SAFE_STRNCMP( http_req->url, "https", strlen("https") ) == 0)
				{
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
					//curl_easy_setopt(curl, CURLOPT_SSLVERSION, 3);
				}
				if ((http_req->user) && (http_req->password))
				{
					curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
					curl_easy_setopt(curl, CURLOPT_USERNAME, http_req->user);
					curl_easy_setopt(curl, CURLOPT_PASSWORD, http_req->password);
				}
			}

			{
				// ** Debug & Timeout **
				curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_OF_CURL_CONNECTTIMEOUT);
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, MAX_OF_CURL_TIMEOUT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VAL_OF_CURLOPT_VERBOSE);
				// ** redirected **
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			}

			{
				// ** Header **
				file_req->headers = curl_slist_append(file_req->headers, "Content-Type: application/octet-stream");
				//headers = curl_slist_append(headers, "Content-Type: image/jpeg");
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, file_req->headers);
			}

			{
				// ** Body **
				if (file_req->method == HTTP_METHOD_ID_POST)
				{
					curl_easy_setopt(curl, CURLOPT_POST, 1L);
					curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)file_info.st_size);
					curl_easy_setopt(curl, CURLOPT_READFUNCTION, dummy_fp2body_cb);
					curl_easy_setopt(curl, CURLOPT_READDATA, (void *)file_req->fp);

					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, uploadfile_body_cb);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);

				}
				else
				{
					curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
					curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
					curl_easy_setopt(curl, CURLOPT_READDATA, file_req->fp);
				}
			}

			curl_res = curl_easy_perform(curl);
			/* Check for errors */ 
			if(curl_res != CURLE_OK)
			{
				SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "%d %s !!! (url: %s, filename: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url, file_req->filename );
			}
			else
			{
				double size_upload;
				double speed_upload, total_time;
				curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD, &size_upload);
				curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &speed_upload);
				curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);

				SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "Upload Ok !!! (%s, %.0f bytes, %.3f bytes/sec, total: %.3f secs)", file_req->filename, size_upload, speed_upload, total_time );
				ret = 0;
			}
			/* always cleanup */ 
			curl_easy_cleanup(curl);
			curl_global_cleanup();
		}
		SAFE_FCLOSE(file_req->fp);
	}
	else
	{
		SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "SAFE_FOPEN error !!! (url: %s, filename: %s)", http_req->url, file_req->filename );
	}
	DBG_TR_LN("ret: %d, %s", ret, http_req->log);
	return ret;
}

#ifdef UTIL_EX_CURL_RTSP
#include <termios.h>
#include <unistd.h>

#define RANGE_OF_RTSP "npt=0.000-" // "0.000-" "npt=0-"

static size_t rtsp_options_header_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	size_t bytec = size * nmemb;
	HttpCtx_t *http_req  = (HttpCtx_t *)context;
	if (http_req)
	{
		if (  SAFE_STRSTR(ptr, "Public:") )
		{
			RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;
			QBUF_t *qoption = &rtsp_req->qoption;
			DBG_TMP_Y("(ptr: %s)", ptr);
			qbuf_write(qoption, ptr, bytec);
		}
	}
	return bytec;
}

// send RTSP OPTIONS request
static CURLcode rtsp_options(HttpCtx_t *http_req, CURL *curl)
{
  CURLcode curl_res = CURLE_OK;
	RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	rtsp_req->CSeq ++;

	qbuf_init(&rtsp_req->qoption, MAX_OF_QBUF_1MB);

	{
		curl_easy_setopt(curl, CURLOPT_RTSP_STREAM_URI, http_req->url);
		curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_OPTIONS);
	}

	{
		// ** Header **
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, rtsp_options_header_cb);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)http_req);
	}

	curl_res = curl_easy_perform(curl);
	if(curl_res != CURLE_OK)
	{
		DBG_ER_LN("%d %s !!! (url: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url );
	}

	DBG_DB_LN("(qoption: %s)", qbuf_buff(&rtsp_req->qoption));
	return curl_res;
}

static size_t rtsp_describe_header_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	HttpCtx_t *http_req = (HttpCtx_t *)context;
	size_t bytec = size * nmemb;
	if (http_req)
	{
		DBG_TMP_Y("(ptr: %s)", ptr);
	}
	return bytec;
}

// scan sdp file for media control attribute
static void rtsp_describe_parse(HttpCtx_t *http_req)
{
	if (http_req)
	{
		RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;
		QBUF_t *qdescribe = &rtsp_req->qdescribe;

		char *saveptr = qbuf_buff(qdescribe);;
		char *token = NULL;

		int mtype = 0; // 0: video, 1: audio
		while ( (token = SAFE_STRTOK_R(NULL, "\r\n", &saveptr)) )
		{
			//DBG_DB_LN(">>>>>>>> (token: %s)", token);
			if (SAFE_STRNCMP(token, "a=control:", strlen("a=control:")) == 0)
			{
				char track[LEN_OF_VAL32] = "";
				SAFE_SSCANF(token, "a=control:%s", track);
				if ( (SAFE_STRCMP(track, "*")==0) )
				{
					// find next
				}
				else if ( (strlen(track)>0) && (rtsp_req->no_of_track<=MAX_OF_RTSP_TRACK) )
				{
					//DBG_DB_LN(">>>>>>>> (mtype: %d, rtsp_req->no_of_track: %d)", mtype, rtsp_req->no_of_track);
					if  (mtype == 0) // video
					{
						SAFE_SNPRINTF(rtsp_req->track[rtsp_req->no_of_track], sizeof(rtsp_req->track[rtsp_req->no_of_track]), "%s", track);
						DBG_DB_LN("(rtsp_req->control: %s)", rtsp_req->track[rtsp_req->no_of_track]);
						rtsp_req->no_of_track ++;						
					}
				}
			}
			else if (SAFE_STRNCMP(token, "m=video", strlen("m=video")) == 0)
			{
				mtype = 0;
				//DBG_DB_LN(">>>>>>>> (mtype: %d)", mtype);
			}
			else if (SAFE_STRNCMP(token, "a=fmtp:", strlen("a=fmtp:")) == 0)
			{
#if (0)
				char pmode_str[LEN_OF_VAL32] = "";
				char *pmode = SAFE_STRSTR(token, "packetization-mode=");
				SAFE_SSCANF(pmode, "packetization-mode=%s;", pmode_str);
				//DBG_DB_LN(">>>>>>>> (pmode: %d)", atoi(pmode_str));

				char plid_str[LEN_OF_VAL32] = "";
				char *plid = SAFE_STRSTR(token, "profile-level-id=");
				SAFE_SSCANF(plid, "profile-level-id=%s;", plid_str);
				//DBG_DB_LN(">>>>>>>> (plid: %d)", atoi(plid_str));
#endif
				char sps_str[LEN_OF_VAL64] = "";
				char *sps = SAFE_STRSTR(token, "sprop-parameter-sets=");

				if (sps)
				{ // h264
					SAFE_SSCANF(sps, "sprop-parameter-sets=%s", sps_str);
					//DBG_DB_LN(">>>>>>>> (sps: %s)", sps_str);

					char *token_sps = NULL;
					char *saveptr_sps = sps_str;
					while ( (token_sps = SAFE_STRTOK_R(NULL, ",", &saveptr_sps)) )
					{
						int sps_dec_len = 0;
						char *sps_dec = sec_base64_dec(token_sps, strlen(token_sps), &sps_dec_len);
						DBG_TMP_Y("(token_sps: %ld %s)", strlen(token_sps), token_sps);
						DBG_TMP_DUMP(sps_dec, sps_dec_len, " ", "(sps_dec_len: %d)", sps_dec_len);

						if (rtsp_req->fp)
						{
							unsigned char nal_header[4] = {0x00, 0x00, 0x00, 0x01};
							SAFE_FWRITE(&nal_header, 1, sizeof(nal_header), rtsp_req->fp);
							SAFE_FWRITE(sps_dec, 1, sps_dec_len, rtsp_req->fp);
						}
						SAFE_FREE(sps_dec);
					}
				}
			}
			else if (SAFE_STRNCMP(token, "m=audio", strlen("m=audio")) == 0)
			{
				mtype = 1;
				//DBG_DB_LN(">>>>>>>> (mtype: %d)", mtype);
			}
		}
		//DBG_DB_LN(">>>>>>>> exit");
	}
}

static size_t rtsp_describe_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	HttpCtx_t *http_req = (HttpCtx_t *)context;
	size_t bytec = size * nmemb;
	if (http_req)
	{
		RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;
		QBUF_t *qdescribe = &rtsp_req->qdescribe;
		qbuf_write(qdescribe, ptr, bytec);
	}
	return bytec;
}

static CURLcode rtsp_describe(HttpCtx_t *http_req, CURL *curl)
{
	CURLcode curl_res = CURLE_OK;
	RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	rtsp_req->CSeq ++;

	qbuf_init(&rtsp_req->qdescribe, MAX_OF_QBUF_1MB);

	{
		curl_easy_setopt(curl, CURLOPT_RTSP_STREAM_URI, http_req->url);
		curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_DESCRIBE);
	}

	{
		// ** Header **
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, rtsp_describe_header_cb);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)http_req);
		//curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
		//curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)NULL);
	}

	{
		// ** Body **
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, rtsp_describe_body_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);
	}

	curl_res = curl_easy_perform(curl);
	if(curl_res != CURLE_OK)
	{
		DBG_ER_LN("%d %s !!! (url: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url );
	}

	DBG_DB_LN("(qdescribe: %s)", qbuf_buff(&rtsp_req->qdescribe));
	return curl_res;
}


static size_t rtsp_setup_header_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	HttpCtx_t *http_req = (HttpCtx_t *)context;
  size_t bytec = size * nmemb;
	DBG_TMP_Y("(bytec: %zd, ptr: %s)", bytec, str_trim(ptr));

	char *session = NULL;
	if ( (session = SAFE_STRSTR(ptr, "Session:")) )
	{
		session += strlen("Session:");
			
		char *saveptr = NULL;
		char *first = SAFE_STRTOK_R(session, ";", &saveptr);
		SAFE_SNPRINTF(http_req->rtsp_req.session, sizeof(http_req->rtsp_req.session), "%s", first);
		str_trim(http_req->rtsp_req.session);

		//char *second = SAFE_STRTOK_R(NULL, ";", &saveptr);
		//DBG_DB_LN(">>>>>>> (session: %s)", http_req->rtsp_req.session);
	}
	
  return bytec;
}

static CURLcode rtsp_setup(HttpCtx_t *http_req, CURL *curl, int track_id)
{
	CURLcode curl_res = CURLE_OK;
	RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	rtsp_req->CSeq ++;

	{
		char *url= NULL;
		char transport[LEN_OF_VAL64] = "";
		SAFE_ASPRINTF(url, "%s/%s", http_req->url, rtsp_req->track[track_id]);
		if (url)
		{
			if (rtsp_req->interleaved == 0)
			{ // use udp port
				SAFE_SNPRINTF(transport, sizeof(transport), "RTP/AVP;unicast;client_port=%d-%d", rtsp_req->rtp_port+track_id*2, rtsp_req->rtp_port+track_id*2+1);
			}
			else
			{ // use the same session
				SAFE_SNPRINTF(transport, sizeof(transport), "RTP/AVP/TCP;unicast;interleaved=0-1");
			}

			DBG_DB_LN("(url: %s, %s)", url, transport);
			curl_easy_setopt(curl, CURLOPT_RTSP_STREAM_URI, url);
			curl_easy_setopt(curl, CURLOPT_RTSP_TRANSPORT, transport);
			curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_SETUP);
			if (strlen(rtsp_req->session))
			{
				curl_easy_setopt(curl, CURLOPT_RTSP_SESSION_ID, rtsp_req->session);
			}
			SAFE_FREE(url);
		}
	}

	{
		// ** Header **
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, rtsp_setup_header_cb);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)http_req);
		//curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
		//curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)NULL);
	}

	{
		// ** Body **
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dummy_body_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);
	}

	curl_res = curl_easy_perform(curl);
	if(curl_res != CURLE_OK)
	{
		DBG_ER_LN("%d %s !!! (url: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url );
	}
	return curl_res;
}

static size_t rtsp_play_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
	size_t bytec = size * nmemb;
	//DBG_TMP_DUMP(ptr, bytec, " ", "(bytec: %ld)", bytec);

	HttpCtx_t *http_req  = (HttpCtx_t *)context;
	if (http_req)
	{
		//unsigned char magic = ptr[0];
		unsigned char channel = ptr[1];
		unsigned long length = byte2big_endian(2, (unsigned char*)ptr+2);

		if (channel==0)
		{
			RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;
			RTPCtx_t *rtp_req = (RTPCtx_t*)rtsp_req->rtp_req;
			
			rtp_body_parse(rtp_req, ptr+4, length);
		}
	}
	return bytec;
}

static CURLcode rtsp_play(HttpCtx_t *http_req, CURL *curl)
{
  CURLcode curl_res = CURLE_OK;
	RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	rtsp_req->CSeq ++;

	{
		char *url = NULL;
		SAFE_ASPRINTF(url, "%s", http_req->url);
		if (url)
		{
			curl_easy_setopt(curl, CURLOPT_RTSP_STREAM_URI, url);
			curl_easy_setopt(curl, CURLOPT_RANGE, RANGE_OF_RTSP);
			curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_PLAY);
			SAFE_FREE(url);
		}
	}

	{
		// ** Header **
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, dummy_header_cb);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)http_req);
	}

	{
		// ** Body **
	  //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dummy_body_cb);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);
	  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)NULL);

		if (rtsp_req->interleaved != 0)
		{
			//curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
			curl_easy_setopt(curl, CURLOPT_INTERLEAVEFUNCTION, rtsp_play_body_cb);
			curl_easy_setopt(curl, CURLOPT_INTERLEAVEDATA, (void *)http_req);
		}
	}

	curl_res = curl_easy_perform(curl);
	if(curl_res != CURLE_OK)
	{
		DBG_ER_LN("%d %s !!! (url: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url );
	}

	curl_easy_setopt(curl, CURLOPT_RANGE, NULL);
	return curl_res;
}

static CURLcode rtsp_receive(HttpCtx_t *http_req, CURL *curl)
{
	CURLcode curl_res = CURLE_OK;
	RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	if (rtsp_req->interleaved != 0)
	{
		curl_res = curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_RECEIVE);
		curl_res = curl_easy_perform(curl);
		//DBG_ER_LN("%d %s", res, curl_easy_strerror(res));
	}
	sleep(1);

	return curl_res;
}

static CURLcode rtsp_teardown(HttpCtx_t *http_req, CURL *curl)
{
	CURLcode curl_res = CURLE_OK;
	//RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	{
		curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_TEARDOWN);
	}

	{
		// ** Header **
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)stdout);
	}

	curl_res = curl_easy_perform(curl);
	if(curl_res != CURLE_OK)
	{
		DBG_ER_LN("%d %s !!! (url: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url );
	}
	return curl_res;
}

static int _getch(void)
{
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

static int http_request_downloadfile_rtsp(HttpCtx_t *http_req)
{
	int ret = -1;
	RTSPRequest_t *rtsp_req = (RTSPRequest_t *)&http_req->rtsp_req;

	DBG_TR_LN("enter (rtsp_req->filename: %s)", rtsp_req->filename);

	rtsp_req->fp = SAFE_FOPEN(rtsp_req->filename, "wb"); /* open file to download */ 
	if(rtsp_req->fp)
	{
		struct stat file_info;
		if(fstat(SAFE_FILENO(rtsp_req->fp), &file_info) != 0)
		{
			SAFE_SNPRINTF(http_req->log, sizeof(http_req->log), "fstat error !!! (url: %s, filename: %s)", http_req->url, rtsp_req->filename );
		}
		else
		{
			curl_global_init(CURL_GLOBAL_ALL);
			CURL *curl = curl_easy_init();
			CURLcode curl_res;
			curl_easy_setopt(curl, CURLOPT_URL, http_req->url);
			//curl_easy_setopt(curl, CURLOPT_PROTOCOLS, (long)CURLPROTO_RTSP);
			//curl_easy_setopt(curl, CURLOPT_USERAGENT, "LIVE555 Streaming Media v2013.02.11");
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "LibVLC/3.0.4 (LIVE555 Streaming Media v2016.11.28)");
			{
				// ** Auth **
				if ((http_req->user) && (strlen(http_req->user) >0) && (http_req->password) && (strlen(http_req->password) >0))
				{
					//curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC|CURLAUTH_DIGEST);
					curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
					curl_easy_setopt(curl, CURLOPT_USERNAME, http_req->user);
					curl_easy_setopt(curl, CURLOPT_PASSWORD, http_req->password);
				}
			}

			{
				// ** Debug & Timeout **
				//curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_OF_CURL_CONNECTTIMEOUT);
				//curl_easy_setopt(curl, CURLOPT_TIMEOUT, MAX_OF_CURL_TIMEOUT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VAL_OF_CURLOPT_VERBOSE);
				// ** redirected **
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			}

			{
				// ** Header **
			}

			{
				// ** Body **
				rtsp_req->CSeq = 0;

				// request server options
				curl_res = rtsp_options(http_req, curl);

				// request session description and write response to sdp buffer
				curl_res = rtsp_describe(http_req, curl);

				rtsp_req->no_of_track = 0;
				// get media control attribute from sdp buffer
				rtsp_describe_parse(http_req);

				int i =0;
				for (i=0; i < rtsp_req->no_of_track; i++)
				{
					// setup media stream
					curl_res = rtsp_setup(http_req, curl, i);
				}

				// to setup RTP
				RTPCtx_t *rtp_req = rtp_init(rtsp_req->rtp_port, rtsp_req->interleaved);
				rtp_req->http_req = http_req;

				rtsp_req->rtp_req = rtp_req;

				// start playing media stream
				curl_res = rtsp_play(http_req, curl);

				if (rtsp_req->max_size)
				{
					while ( (rtsp_req->stop==0) && 
									(rtp_req->total <= rtsp_req->max_size)
								)
					{
						rtsp_receive(http_req, curl);
					}
				}
				else if (rtsp_req->duration)
				{
					time_t start_t = time(NULL);
					int duration = 0;
					while ( (rtsp_req->stop==0) && 
									( duration <= rtsp_req->duration)
								)
					{
						rtsp_receive(http_req, curl);
						duration = (int)difftime(time(NULL), start_t );
						if ( (rtsp_req->progress) &&  ( (duration%5)==0) )
						{
							DBG_DB_LN("(duration: %d/%d)", duration,rtsp_req->duration );
							//rtp_context_print( &rtp_req->sess_data);
						}
					}
				}
				else
				{
					_getch();
				}

				// teardown session
				curl_res = rtsp_teardown(http_req, curl);

				rtp_free(rtp_req);
			}

			if(curl_res != CURLE_OK)
			{
				SAFE_SPRINTF(http_req->log, "%d %s !!! (url: %s, filename: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url, rtsp_req->filename );
			}
			else
			{
				ret = 0;
			}

			/* always cleanup */ 
			curl_easy_cleanup(curl);
			curl_global_cleanup();

			qbuf_free(&rtsp_req->qoption);
			qbuf_free(&rtsp_req->qdescribe);
		}
		SAFE_FCLOSE(rtsp_req->fp);
	}
	else
	{
		SAFE_SPRINTF(http_req->log, "SAFE_FOPEN error !!! (url: %s, filename: %s)", http_req->url, rtsp_req->filename );
	}
	DBG_TR_LN("ret: %d, %s", ret, http_req->log);
	return ret;
}
#endif

static int http_request_downloadfile_normal(HttpCtx_t *http_req)
{
	int ret = -1;
	FileRequest_t *file_req = (FileRequest_t *)&http_req->file_req;

	DBG_TR_LN("enter (file_req->filename: %s)", file_req->filename);

	file_req->fp = SAFE_FOPEN(file_req->filename, "wb"); /* open file to download */ 
	if(file_req->fp)
	{
		struct stat file_info;
		if(fstat(SAFE_FILENO(file_req->fp), &file_info) != 0)
		{
			SAFE_SPRINTF(http_req->log, "fstat error !!! (url: %s, filename: %s)", http_req->url, file_req->filename );
		}
		else
		{
			curl_global_init(CURL_GLOBAL_DEFAULT);
			CURL *curl = curl_easy_init();
			CURLcode curl_res;
			curl_easy_setopt(curl, CURLOPT_URL, http_req->url);

			{
				// ** Auth **
				if (SAFE_STRNCMP( http_req->url, "https", strlen("https") ) == 0)
				{
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
					//curl_easy_setopt(curl, CURLOPT_SSLVERSION, 3);
				}
				if ((http_req->user) && (strlen(http_req->user) >0) && (http_req->password) && (strlen(http_req->password) >0))
				{
					curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
					curl_easy_setopt(curl, CURLOPT_USERNAME, http_req->user);
					curl_easy_setopt(curl, CURLOPT_PASSWORD, http_req->password);
				}
			}

			{
				// ** Debug & Timeout **
				curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_OF_CURL_CONNECTTIMEOUT);
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, MAX_OF_CURL_TIMEOUT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VAL_OF_CURLOPT_VERBOSE);
				// ** redirected **
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			}

			{
				// ** Header **
			}

			{
				// ** Body **
			  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
			  curl_easy_setopt(curl, CURLOPT_WRITEDATA, file_req->fp);

				if (http_req->file_req.max_filesize > 0)
				{
				  curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, http_req->file_req.max_filesize);
				}
			}

			curl_res = curl_easy_perform(curl);
			/* Check for errors */ 
			if(curl_res != CURLE_OK)
			{
				SAFE_SPRINTF(http_req->log, "%d %s !!! (url: %s, filename: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url, file_req->filename );
			}
			else
			{
				double size_download;
				double speed_download, total_time;
				curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &size_download);
				curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &speed_download);
				curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);

				SAFE_SPRINTF(http_req->log, "Download Ok !!! (%s, %.0f bytes, %.3f bytes/sec, total: %.3f secs)", file_req->filename, size_download, speed_download, total_time);
				ret = 0;
			}
			/* always cleanup */ 
			curl_easy_cleanup(curl);
			curl_global_cleanup();
		}
		SAFE_FCLOSE(file_req->fp);
	}
	else
	{
		SAFE_SPRINTF(http_req->log, "SAFE_FOPEN error !!! (url: %s, filename: %s)", http_req->url, file_req->filename );
	}
	DBG_TR_LN("ret: %d, %s", ret, http_req->log);
	return ret;
}

static size_t mjpeg_header_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
  size_t bytec = size * nmemb;
	HttpCtx_t *http_req  = (HttpCtx_t *)context;
	char *multi_ptr = NULL;
	char *ctype = NULL;
	char *clength = NULL;
	char *boundary = NULL;
	if (http_req)
	{
		MJPEGRequest_t *mjpeg_req = (MJPEGRequest_t *)&http_req->mjpeg_req;
		if ( (ctype = SAFE_STRSTR(ptr, "Content-Type:")) )
		{
			SAFE_MEMSET(mjpeg_req->boundary, 0, sizeof(mjpeg_req->boundary));
			SAFE_SNPRINTF(mjpeg_req->ctype, (int)sizeof(mjpeg_req->ctype), "%s", ctype);
			if ( (multi_ptr = SAFE_STRSTR(ctype, "multipart/x-mixed-replace")) &&
						(boundary = SAFE_STRSTR(ctype, "boundary="))
				)
			{
				// No support
				char *boundary = SAFE_STRSTR(ctype, "boundary=");
				SAFE_SSCANF(boundary, "boundary=%s", mjpeg_req->boundary);
				str_trim(mjpeg_req->boundary);
				DBG_TR_LN("(boundary: %s)", mjpeg_req->boundary);
				mjpeg_req->state = MJPEG_STATE_ID_BOUNDARY;
				qbuf_init(&mjpeg_req->qbuf, MAX_OF_QBUF_1MB);
			}
			
		}
		else if ( (clength = SAFE_STRSTR(ptr, "Content-Length:")) ) 
		{
			mjpeg_req->clength = atoi(clength);
		}
	}
  return bytec;
}

static size_t mjpeg_body_cb(char *ptr, size_t size, size_t nmemb, void *context)
{
  size_t bytec = size * nmemb;
	HttpCtx_t *http_req = (HttpCtx_t *)context;

	//DBG_DB_LN("(ptr: %s)", ptr);
	if (http_req)
	{
		MJPEGRequest_t *mjpeg_req = (MJPEGRequest_t *)&http_req->mjpeg_req;

		if (strlen(mjpeg_req->boundary) > 0)
		{
			QBUF_t *qbuf = &mjpeg_req->qbuf;
			qbuf_write(qbuf, ptr, bytec);

mjpeg_parse:
			{
				//DBG_TR_LN("(size: %d, nmemb: %d)", size, nmemb);
				char *startptr = qbuf_buff(qbuf);
				char *saveptr = NULL;
				size_t total = qbuf_total(qbuf);

				//DBG_TR_LN("(startptr: %s, size: %d, nmemb: %d)", startptr, size, nmemb);
				// multi
				switch (mjpeg_req->state)
				{
					case MJPEG_STATE_ID_BOUNDARY:
						//DBG_TR_LN("(startptr: %s, size: %d, nmemb: %d)", startptr, size, nmemb);
						{
							char boundary[LEN_OF_VAL48] = "";
							//DBG_TR_LN("(ptr: %s, size: %d, nmemb: %d)", ptr, size, nmemb);
							if (SAFE_MEMCMP(mjpeg_req->boundary, "--", 2) == 0)
							{
								SAFE_SNPRINTF(boundary, (int)sizeof(boundary), "%s\r\n", http_req->mjpeg_req.boundary);
							}
							else
							{
								SAFE_SNPRINTF(boundary, (int)sizeof(boundary), "--%s\r\n", http_req->mjpeg_req.boundary);
							}

							if (qbuf_shiftstr(qbuf, boundary) == 0)
							{
								// found !!!
								if (mjpeg_req->fp == NULL)
								{
									// create a new file
									SAFE_SNPRINTF(mjpeg_req->filename, sizeof(mjpeg_req->filename), "%s_%02d.jpg", mjpeg_req->prefixname, mjpeg_req->num);
									mjpeg_req->fp = SAFE_FOPEN(mjpeg_req->filename, "wb");
								}

								if (mjpeg_req->fp)
								{
									mjpeg_req->state ++;
								}

								goto mjpeg_parse;
							}
						}
						break;
					case MJPEG_STATE_ID_TYPE:
						if (qbuf_shiftstr(qbuf, "Content-Type:") == 0)
						{
							mjpeg_req->state ++;

							goto mjpeg_parse;
						}
						break;
					case MJPEG_STATE_ID_TYPE_0D0A:
						if ( (saveptr = qbuf_strstr(qbuf, "\r\n", NULL)) )
						{
							SAFE_SNPRINTF(mjpeg_req->ftype, (int)(saveptr-startptr)+1, "%s", startptr);

							{
								DBG_TR_LN("(filename[%d]: %s, ftype: %s)", mjpeg_req->num, mjpeg_req->filename, mjpeg_req->ftype);
								mjpeg_req->state ++;
								qbuf_read(qbuf, NULL, (saveptr-startptr+1) + strlen("\r\n") - 1);
							}

							goto mjpeg_parse;
						}
						break;
					case MJPEG_STATE_ID_LENGTH:
						if (qbuf_shiftstr(qbuf, "Content-Length:") == 0)
						{
							mjpeg_req->state ++;

							goto mjpeg_parse;
						}
						break;
					case MJPEG_STATE_ID_LENGTH_0D0A:
						if ( (saveptr = qbuf_strstr(qbuf, "\r\n", NULL)) )
						{
							char flength[LEN_OF_VAL16] = "";
							SAFE_SNPRINTF(flength, (int)(saveptr-startptr)+1, "%s", startptr);
							mjpeg_req->flength = atoi(flength);

							if (mjpeg_req->flength)
							{
								DBG_TR_LN("(filename[%d]: %s, flength: %d)", mjpeg_req->num, mjpeg_req->filename, mjpeg_req->flength);
								mjpeg_req->state ++;
								qbuf_read(qbuf, NULL, (saveptr-startptr+1) + strlen("\r\n") - 1);
							}

							goto mjpeg_parse;
						}
						break;
					case MJPEG_STATE_ID_STUPID_0D0A:
						if (qbuf_total(qbuf) > 2)
						{
							if (SAFE_MEMCMP(qbuf_buff(qbuf), "\r\n", 2) == 0)
							{
								// found !!!
								qbuf_read(qbuf, NULL, 2);
							}

							mjpeg_req->state ++;
							goto mjpeg_parse;
						}
						break;
					case MJPEG_STATE_ID_BODY:
						if (mjpeg_req->flength <= total)
						{
							nmemb = mjpeg_req->flength;
							size = 1;
						}
						else
						{
							nmemb = total;
							size = 1;
						}
						{
							size_t written = SAFE_FWRITE(startptr, size, nmemb, mjpeg_req->fp);
							qbuf_read(qbuf, NULL, size*nmemb);
							
							//DBG_TR_LN("(size: %d, nmemb: %d, flength: %d, written: %d)", size, nmemb, mjpeg_req->flength, written);
							mjpeg_req->flength -= written;
							if (mjpeg_req->flength<=0)
							{
								SAFE_FCLOSE(mjpeg_req->fp);
								DBG_DB_LN("(filename[%d]: %s, ftype: %s)", mjpeg_req->num, mjpeg_req->filename, mjpeg_req->ftype);

								mjpeg_req->state ++; mjpeg_req->state %= MJPEG_STATE_ID_MAX;
								mjpeg_req->num++;

								if ( (mjpeg_req->maxfiles) && (mjpeg_req->num >= mjpeg_req->maxfiles))
								{
									// finish !!!
									DBG_DB_LN("(num: %d >= maxfiles: %d)", mjpeg_req->num, mjpeg_req->maxfiles);
									bytec = 0;
								}
								else
								{
									goto mjpeg_parse;
								}
							}
						}
						break;
					default:
						break;
				}
			}
		}
		else
		{
			// single
			SAFE_FWRITE(ptr, size, nmemb, mjpeg_req->fp);
		}
	}
	else
	{
		DBG_ER_LN("http_req is NULL !!!");
	}
	return bytec;
}

static int http_request_downloadfile_mjpeg(HttpCtx_t *http_req)
{
	int ret = -1;
	MJPEGRequest_t *mjpeg_req = (MJPEGRequest_t *)&http_req->mjpeg_req;
	int fnlen = strlen(mjpeg_req->filename);

	if (fnlen >0 )
	{
		char *ptr = NULL;
		if ((fnlen>4) && ((ptr=SAFE_STRSTR(mjpeg_req->filename+fnlen-5, ".jpg")) || (ptr=SAFE_STRSTR(mjpeg_req->filename+fnlen-5, ".jpeg") ) ))
		{
			SAFE_SNPRINTF(mjpeg_req->prefixname, (int)(ptr - mjpeg_req->filename), "%s", mjpeg_req->filename);
		}
	}
	else if (strlen(mjpeg_req->prefixname) >0 )
	{
		DBG_TR_LN("enter (mjpeg_req->prefixname: %s)", mjpeg_req->prefixname);

		SAFE_SNPRINTF(mjpeg_req->filename, sizeof(mjpeg_req->filename), "%s.jpg", mjpeg_req->prefixname);
	}
	else
	{
		return ret;
	}

	mjpeg_req->fp = SAFE_FOPEN(mjpeg_req->filename, "wb"); /* open file to download */ 
	if(mjpeg_req->fp)
	{
		struct stat file_info;
		if(fstat(SAFE_FILENO(mjpeg_req->fp), &file_info) != 0)
		{
			SAFE_SPRINTF(http_req->log, "fstat error !!! (url: %s, filename: %s)", http_req->url, mjpeg_req->filename );
		}
		else
		{
			curl_global_init(CURL_GLOBAL_DEFAULT);
			CURL *curl = curl_easy_init();
			CURLcode curl_res;
			curl_easy_setopt(curl, CURLOPT_URL, http_req->url);

			{
				// ** Auth **
				if (SAFE_STRNCMP( http_req->url, "https", strlen("https") ) == 0)
				{
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
					//curl_easy_setopt(curl, CURLOPT_SSLVERSION, 3);
				}
				if ((http_req->user) && (strlen(http_req->user) >0) && (http_req->password) && (strlen(http_req->password) >0))
				{
					curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
					curl_easy_setopt(curl, CURLOPT_USERNAME, http_req->user);
					curl_easy_setopt(curl, CURLOPT_PASSWORD, http_req->password);
				}
			}

			{
				// ** Debug & Timeout **
				curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, MAX_OF_CURL_CONNECTTIMEOUT);
				curl_easy_setopt(curl, CURLOPT_TIMEOUT, MAX_OF_CURL_TIMEOUT);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, VAL_OF_CURLOPT_VERBOSE);
				// ** redirected **
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			}

			{
				// ** Header **
			  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, mjpeg_header_cb);
			  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)http_req);
			}

			{
				// ** Body **
			  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mjpeg_body_cb);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)http_req);

				if (http_req->mjpeg_req.max_size> 0)
				{
				  curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, http_req->mjpeg_req.max_size);
				}
			}

			curl_res = curl_easy_perform(curl);
			/* Check for errors */ 
			if ( (curl_res != CURLE_OK) && (mjpeg_req->num==0) )
			{
				SAFE_SPRINTF(http_req->log, "%d %s !!! (url: %s, filename: %s)", curl_res, curl_easy_strerror(curl_res), http_req->url, mjpeg_req->filename );
			}
			else
			{
				double size_download;
				double speed_download, total_time;
				curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &size_download);
				curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &speed_download);
				curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);

				SAFE_SPRINTF(http_req->log, "Download Ok !!! (%s, %.0f bytes, %.3f bytes/sec, total: %.3f secs)", mjpeg_req->filename, size_download, speed_download, total_time);
				ret = 0;
			}
			/* always cleanup */ 
			curl_easy_cleanup(curl);
			curl_global_cleanup();
		}
		SAFE_FCLOSE(mjpeg_req->fp);
		qbuf_free(&mjpeg_req->qbuf);
	}
	else
	{
		SAFE_SPRINTF(http_req->log, "SAFE_FOPEN error !!! (url: %s, filename: %s)", http_req->url, mjpeg_req->filename );
	}
	DBG_TR_LN("ret: %d, %s", ret, http_req->log);
	return ret;
}

void http_request_free(HttpCtx_t *http_req)
{
	if (http_req)
	{
		switch (http_req->mode)
		{
			case HTTP_MODE_ID_SOAP:
				SAFE_FREE(http_req->soap_req.request);
				SAFE_FREE(http_req->soap_req.response);
				curl_slist_free_all(http_req->soap_req.headers);
				break;
			case HTTP_MODE_ID_SIMPLE:
				SAFE_FREE(http_req->simple_req.request);
				SAFE_FREE(http_req->simple_req.response);
				curl_slist_free_all(http_req->simple_req.headers);
				break;
			case HTTP_MODE_ID_UPLOADFILE:
				SAFE_FREE(http_req->file_req.request);
				SAFE_FREE(http_req->file_req.response);
				curl_slist_free_all(http_req->file_req.headers);
				break;
			default:
				break;
		}
	}
}

int http_request(HttpCtx_t *http_req)
{
	int ret = -1;
	http_req->result = 0;
	if ( (http_req->url) && (strlen(http_req->url) >= 7) ) // "http://" or "https://"
	{
		switch (http_req->mode)
		{
			case HTTP_MODE_ID_SIMPLE:
				ret = http_request_simple(http_req);
				break;
			case HTTP_MODE_ID_UPLOADFILE:
				ret = http_request_uploadfile(http_req);
				break;
			case HTTP_MODE_ID_DOWNLOAFILE_NORMAL:
				ret = http_request_downloadfile_normal(http_req);
				break;
			case HTTP_MODE_ID_DOWNLOAFILE_MJPEG:
				ret = http_request_downloadfile_mjpeg(http_req);
				break;				
			case HTTP_MODE_ID_DOWNLOAFILE_RTSP:
#ifdef UTIL_EX_CURL_RTSP				
				ret = http_request_downloadfile_rtsp(http_req);
#else
				DBG_ER_LN("%s (HTTP_MODE_ID_DOWNLOAFILE_RTSP)", DBG_TXT_NO_SUPPORT);
				ret = -1;
#endif
				break;				
			case HTTP_MODE_ID_SOAP:
				ret = http_request_soap(http_req);
				break;
			default:
				break;
		}
	}
	return ret;
}

int http_upload(const char *url, const char *filename)
{
	int ret = -1;
	if ((url) && strlen(url) && (filename) && (access(filename, R_OK ) == 0) )
	{
		HttpCtx_t http_req ={
			.mode = HTTP_MODE_ID_UPLOADFILE,
			.url = "",
			.log = "",
			.file_req.filename = "",
			.file_req.fp = NULL,
			.file_req.method = HTTP_METHOD_ID_PUT,
		};
		SAFE_SPRINTF(http_req.url, "%s", url);
		SAFE_SPRINTF(http_req.file_req.filename, "%s", filename);
		ret = http_request(&http_req);

		http_request_free(&http_req);
	}
	return ret;
}

int http_upload_with_response(const char *url, const char *filename, void *userdata, http_response_fn cb)
{
	int ret = -1;
	if ((url) && strlen(url) && (filename) && (access(filename, R_OK ) == 0) )
	{
		HttpCtx_t http_req ={
			.mode = HTTP_MODE_ID_UPLOADFILE,
			.url = "",
			.log = "",
			.file_req.filename = "",
			.file_req.fp = NULL,
			.file_req.method = HTTP_METHOD_ID_POST,
		};
		SAFE_SPRINTF(http_req.url, "%s", url);
		SAFE_SPRINTF(http_req.file_req.filename, "%s", filename);
		ret = http_request(&http_req);

		//FileRequest_t *file_req = (FileRequest_t *)&http_req.file_req;

		if (cb)
		{
			cb(userdata, http_req.simple_req.res_size, http_req.simple_req.response);
		}
		http_request_free(&http_req);
	}
	return ret;
}

int http_simple(const char *url, HTTP_METHOD_ID method, struct curl_slist *headers, size_t req_size, char *request, void *userdata, http_response_fn cb)
{
	int ret = -1;
	if ((url) && strlen(url) )
	{
		HttpCtx_t http_req ={
			.mode = HTTP_MODE_ID_SIMPLE,
			.url = "",
			.log = "",
			.simple_req.method = method,
			.simple_req.headers = headers,
			.simple_req.req_size = req_size,
			.simple_req.req_pos = 0,
			.simple_req.request = request,
		};
		//DBG_ER_LN("(request: %s)", http_req.simple_req.request);
		SAFE_SPRINTF(http_req.url, "%s", url);
		ret = http_request(&http_req);

		if (cb)
		{
			cb(userdata, http_req.simple_req.res_size, http_req.simple_req.response);
		}
		http_request_free(&http_req);
	}
	return ret;
}

