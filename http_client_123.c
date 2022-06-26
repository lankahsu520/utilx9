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

#if (0)
char user[LEN_OF_USER] = "admin";
char pass[LEN_OF_PASS] = "888888";
#else
char user[LEN_OF_USER] = "admin"; //"admin";
char pass[LEN_OF_PASS] = "12345678"; //"888888";
#endif

int http_download_mjpeg(char *url, char *prefixname)
{
	int ret = -1;
	if ((url) && strlen(url) && (prefixname) )
	{
		HttpX_t http_req ={
			.mode = HTTP_MODE_ID_DOWNLOAFILE_MJPEG,
			.url = "",
			.log = "",
			.user = user,
			.password = pass,

			.mjpeg_req.max_size = 5*1024*1024, // 5MB
			.mjpeg_req.maxfiles = 5, // 
			.mjpeg_req.prefixname = "",

			.mjpeg_req.fp = NULL,
			.mjpeg_req.num = 0,
		};
		SAFE_SPRINTF_EX(http_req.url, "%s", url);
		SAFE_SPRINTF_EX(http_req.mjpeg_req.prefixname, "%s", prefixname);
		SAFE_MEMSET(http_req.mjpeg_req.boundary, 0, sizeof(http_req.mjpeg_req.boundary));
		SAFE_MEMSET(http_req.mjpeg_req.ctype, 0, sizeof(http_req.mjpeg_req.ctype));
		http_req.mjpeg_req.clength = 0;

		ret = http_request(&http_req);
	}
	return ret;
}

int http_download_rtsp(char *url, char *filename)
{
	int ret = -1;
	if ((url) && strlen(url) && (filename) )
	{
		HttpX_t http_req ={
			.mode = HTTP_MODE_ID_DOWNLOAFILE_RTSP,
			.url = "",
			.log = "",
			.user = user,
			.password = pass,

			.rtsp_req.max_size = 0,
			.rtsp_req.filename = "",
			.rtsp_req.fp = NULL,
			.rtsp_req.duration = 15,
			
			.rtsp_req.rtp_port = rtp_port_get(),
			.rtsp_req.interleaved = 0, // for firewall
			.rtsp_req.stop = 0,

			.rtsp_req.progress = 1,
		};

		SAFE_SPRINTF_EX(http_req.url, "%s", url);
		SAFE_SPRINTF_EX(http_req.rtsp_req.filename, "%s", filename);
		ret = http_request(&http_req);
	}
	return ret;
}

int http_download_normal(char *url, char *filename)
{
	int ret = -1;
	if ((url) && strlen(url) && (filename) )
	{
		HttpX_t http_req ={
			.mode = HTTP_MODE_ID_DOWNLOAFILE_NORMAL,
			.url = "",
			.log = "",
			.file_req.max_filesize = 0,
			.file_req.filename = "",
			.file_req.fp = NULL,
		};
		SAFE_SPRINTF_EX(http_req.url, "%s", url);
		SAFE_SPRINTF_EX(http_req.file_req.filename, "%s", filename);
		ret = http_request(&http_req);
	}
	return ret;
}

void http_response_cb(void *userdata, size_t res_size, char *response)
{
	DBG_ER_LN("%s", response);
}


int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	dbg_lvl_set(DBG_LVL_TRACE);
	//dbg_lvl_set(DBG_LVL_DEBUG);

#if (0)
	struct curl_slist *headers = NULL;
	//headers = curl_slist_append(headers, "Content-Type: image/jpeg");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	char *request = NULL;
	char content_length[LEN_OF_VAL48] ="";
	SAFE_ASPRINTF(request, "%s", "Hello World!!!");
	//SAFE_SPRINTF_EX(content_length, "Content-Length: %d", strlen(request));
	headers = curl_slist_append(headers, content_length);

	//http_simple("http://192.168.50.206:8089/test.jpg", HTTP_METHOD_ID_PUT, headers, strlen(request), request, NULL, http_response_cb);
	http_simple("http://192.168.50.206:8089/test.jpg", HTTP_METHOD_ID_GET, headers, strlen(request), request, NULL, http_response_cb);
#endif

#if (0)
	http_upload("http://192.168.50.206:8089/test.jpg", "./snapshot_770.jpg");
#endif

#if (0)
	//http_upload_with_response("http://192.168.50.206:8089/test.jpg", "./snapshot_770.jpg", NULL, http_response_cb);
	//http_upload_with_response("https://philio-reko.luffanet.com.tw/face/detectFace", "./snapshot_770.jpg", NULL, http_response_cb);

	http_upload_with_response("https://philio-reko.luffanet.com.tw/face/indexFace?uuid=AECDLTRYJKL79HTSMUE1", "./snapshot_770.jpg", NULL, http_response_cb);
#endif

#if (0)
	// mjpeg
	//http_download_mjpeg("http://iris.not.iac.es/axis-cgi/mjpg/video.cgi?resolution=320x240", "./1234");

	// https://en.ipcams.ch/WebCam.aspx?nr=1729
	SAFE_SPRINTF_EX(user, "");
	SAFE_SPRINTF_EX(pass, "");
	http_download_mjpeg("https://webcam1.lpl.org/axis-cgi/mjpg/video.cgi", "./456");

	// single
	SAFE_SPRINTF_EX(user, "admin");
	SAFE_SPRINTF_EX(pass, "888888");
	//http_download_mjpeg("http://192.168.50.170/web/cgi-bin/hi3510/snap.cgi?&-getstream&-snapone", "./170");
	http_download_mjpeg("http://192.168.50.238:80/dms?nowprofileid=1", "./238");

	//http_download_mjpeg("http://d.5857.com/4keu_180119/001.jpg", "./9012");
#endif

#if (1)
	//http_download_rtsp("rtsp://192.168.50.237:554/live1.sdp",  "./video.h264");
	http_download_rtsp("rtsp://192.168.10.195:8554/live",  "./video.h264");
	//http_download_rtsp("rtsp://192.168.50.242/video.pro1",  "./video.h264");

	//http_download_rtsp("rtsp://192.168.50.183:554/11",  "./video.h264");
	//http_download_rtsp("rtsp://192.168.50.109:8000/2.264",  "./video.h264");
#endif
	
#if (0)
#ifdef UTIL_EX_CURL
	HttpX_t http_req ={
		.mode = HTTP_MODE_ID_DOWNLOAFILE_NORMAL,
		.url = "https://curl.haxx.se/download/curl-7.60.0.tar.gz",
		.log = "",
		.file_req.max_filesize = 0,
		.file_req.filename = "/tmp/curl-7.60.0.tar.gz"
	};

	http_request(&http_req);
	DBG_IF_LN("(http_req.log: %s)", http_req.log);
#endif
#endif

	exit(0);
}
