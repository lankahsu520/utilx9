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

#define USE_TEST_STRING
//#define USE_TEST_COMPRESS
#define USE_TEST_SEC_ENC_AND_DEC
//#define USE_TEST_BIN_CHECK
#define USE_TEST_HOSTNAME
//#define USE_TEST_FILE_LOOKUP
//#define USE_TEST_FILE_PATH
//#define USE_TEST_COPY_FILE
#define USE_TIME_TEST
//#define USE_CURL_TEST
#define USE_REALLOC

int newline_lookupokup_cb(char *newline, void *arg)
{
	int ret = 0;
	DBG_IF_LN("(newline: %s)", newline);

	return ret;
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	//dbg_lvl_set(DBG_LVL_DEBUG);

#ifdef USE_TEST_STRING
	//dbg_lvl_set(DBG_LVL_DEBUG);
	DBG_WN_LN("String testing ...");
	DBG_IF_LN("(1<<3: 0x%08X, 1<<14: 0x%08X, 1<<15: 0x%08X, 1<<16: 0x%08X, 1<<17: 0x%08X)", 1 << 3, 1 << 14, 1 << 15, 1 << 16, 1 << 17);

	char hello[]="Hello World !!!    ";
	DBG_IF_LN("(hello org: %s)", hello);
	char *hello_trim = str_trim(hello);
	DBG_IF_LN("(hello_trim: %s)", hello_trim);

	{
		char topic_pub[LEN_OF_TOPIC]	= "";
		char user[LEN_OF_TOPIC]= "lankahsu520";
		char macid[LEN_OF_TOPIC] = "1234";
		SAFE_STRCAT_EX(topic_pub, user, "/", macid);

		DBG_ER_LN("SAFE_STRCAT_EX - %s", topic_pub);
	}
#endif

#ifdef USE_TEST_COMPRESS
	DBG_X_LN("");
	{
		int hello_org_len = SAFE_STRLEN(hello);

		char hello_enc[LEN_OF_BUF512]="";
		int hello_enc_len = LEN_OF_BUF512;
		compress((Bytef *)hello_enc, (uLongf *)&hello_enc_len, (const Bytef *)hello, hello_org_len);
		DBG_IF_LN("(hello_org_len: %d -> hello_enc_len: %d)", hello_org_len, hello_enc_len);

		char hello_dec[LEN_OF_BUF512]="";
		int hello_dec_len = LEN_OF_BUF512;
		uncompress((Bytef *)hello_dec, (uLongf *)&hello_dec_len, (Bytef *)hello_enc, hello_enc_len);
		DBG_IF_LN("(hello_dec: %s)", hello_dec);
	}
#endif

#ifdef USE_TEST_SEC_ENC_AND_DEC
#ifdef UTIL_EX_SSL
#if (1)
	DBG_X_LN("");
	DBG_WN_LN("BASE64, abc -> abc_enc -> abc_dec");
	char abc[]="rtsp://192.168.50.238:554/live1.sdp";
	int abc_enc_len = 0;
	char *abc_enc = sec_base64_enc(abc, strlen(abc), &abc_enc_len);
	DBG_IF_LN("(sec_base64_enc: %s)", abc_enc);
	int abc_dec_len = 0;
	char *abc_dec = sec_base64_dec(abc_enc, strlen(abc_enc), &abc_dec_len);
	DBG_IF_LN("(sec_base64_dec: %s)", abc_dec);
	SAFE_FREE(abc_enc);
	SAFE_FREE(abc_dec);
#endif

	// plaintext -> plaintext_enc -> plaintext_dec
	//char plaintext[LEN_OF_VAL128] = "Hello World !!!";
	char plaintext[LEN_OF_VAL128] = "123456789012345";
	//char plaintext[LEN_OF_VAL128] = "1234567890abcdef";
	char plaintext_enc[LEN_OF_VAL128] = "";
	char plaintext_dec[LEN_OF_VAL128] = "";
	int pad = 1;
	int in_len = SAFE_STRLEN(plaintext);
	int enc_len = 0;
	int dec_len = 0;

	unsigned char evp_key[EVP_KEY_LEN+1]= "1234567890abcdef";
	unsigned char iv_key[EVP_KEY_LEN+1]= "1234567890abcdef";

	DBG_X_LN("");

	DBG_WN_LN("aes_128_cbc, intlen: %d, plaintext: %s -> plaintext_enc -> plaintext_dec", in_len, plaintext);
	DBG_ER_LN("(evp_key: %s, iv_key: %s)", evp_key, iv_key);
#if (1)
	SAFE_MEMSET(plaintext_enc, 0, sizeof(plaintext_enc));
	SAFE_MEMSET(plaintext_dec, 0, sizeof(plaintext_dec));
	enc_len = sec_aes_cbc_enc(plaintext, in_len, plaintext_enc, evp_key, iv_key);
	DBG_IF_DUMP(plaintext_enc, enc_len, " ", "sec_aes_cbc_enc - plaintext_enc:");
	dec_len = sec_aes_cbc_dec(plaintext_enc, enc_len, plaintext_dec, sizeof(plaintext_dec), evp_key, iv_key);
	DBG_IF_LN("(sec_aes_cbc_dec - plaintext_dec: %s)", plaintext_dec);
#endif

#if (1)
	DBG_X_LN("");
	SAFE_MEMSET(plaintext_enc, 0, sizeof(plaintext_enc));
	SAFE_MEMSET(plaintext_dec, 0, sizeof(plaintext_dec));
	enc_len = sec_aes_cbc_encX(plaintext, SAFE_STRLEN(plaintext), plaintext_enc, evp_key, iv_key, pad);
	DBG_IF_DUMP(plaintext_enc, enc_len, " ", "sec_aes_cbc_encX - enc_len: %d, plaintext_enc:", enc_len);
	dec_len = sec_aes_cbc_decX(plaintext_enc, enc_len, plaintext_dec, evp_key, iv_key, pad);
	DBG_IF_LN("(sec_aes_cbc_decX - dec_len: %d, plaintext_dec: %s)", dec_len, plaintext_dec);
#endif

#endif
#endif

#ifdef USE_TEST_BIN_CHECK
	{
		DBG_X_LN("");
		DBG_WN_LN("bin check ...");
		DBG_IF_LN("(/usr/bin/7z: %d)", file_exe_chk("/usr/bin/7z"));
		DBG_IF_LN("(/bin/7za: %d)", file_exe_chk("/bin/7za"));
	}
#endif

#ifdef USE_TEST_HOSTNAME
	{
		DBG_X_LN("");
		DBG_WN_LN("hostname ...");
		char myhostname[LEN_OF_HOSTNAME]="";
		gethostname(myhostname, sizeof(myhostname));
		DBG_IF_LN("(gethostname: %s)", myhostname);

		char mydomainname[LEN_OF_HOSTNAME]="";
		int res = getdomainname(mydomainname, sizeof(mydomainname));
		DBG_IF_LN("(getdomainname: %s, res: %d)", mydomainname, res);
	}
#endif

#ifdef USE_TEST_FILE_LOOKUP
	file_lookup("/proc/modules", newline_lookupokup_cb, NULL);
#endif

#ifdef USE_TEST_FILE_PATH
	{
		char path[] = "/etc/passwd";
		char actualpath [PATH_MAX+1] = "";
		if ( file_path(path, actualpath) )
		{
			DBG_IF_LN("(actualpath: %s)", actualpath);
		}
		else
		{
			DBG_IF_LN("%s not exist !!!", path);
		}
	}
#endif

#ifdef USE_TEST_COPY_FILE
	char filename[LEN_OF_FULLNAME] ="";
	int i = 0;
	for (i=0; i< 256; i++)
	{
		SAFE_SPRINTF_EX(filename, "./snapshot_%03d.jpg", i);
		file_copy("./snapshot.jpg", filename);
	}
#endif

#ifdef USE_TIME_TEST
	DBG_X_LN("");
	DBG_WN_LN("datetime ...");
	DBG_IF_LN("(time_now_full: %s)", time_now_full(time(NULL)));
#endif

#ifdef USE_CURL_TEST
#ifdef UTIL_EX_CURL
	DBG_X_LN("");
	DBG_WN_LN("http_req ...");
	HttpX_t http_req;
	DBG_IF_LN("(mode: %zd)", sizeof(http_req.mode));
	DBG_IF_LN("(curl: %zd)", sizeof(http_req.curl));
	DBG_IF_LN("(url: %zd)", sizeof(http_req.url));
	DBG_IF_LN("(port: %zd)", sizeof(http_req.port));
	DBG_IF_LN("(user: %zd)", sizeof(http_req.user));
	DBG_IF_LN("(log: %zd)", sizeof(http_req.log));

	DBG_IF_LN("------------");
	DBG_IF_LN("(res_size: %zd)", sizeof(http_req.simple_req.res_size));
	DBG_IF_LN("(response: %zd)", sizeof(http_req.simple_req.response));
	DBG_IF_LN("(method: %zd)", sizeof(http_req.simple_req.method));
	DBG_IF_LN("(curl_slist: %zd)", sizeof(http_req.simple_req.headers));

	DBG_IF_LN("------------");
	DBG_IF_LN("(max_size: %zd)", sizeof(http_req.mjpeg_req.max_size));
	DBG_IF_LN("(filename: %zd)", sizeof(http_req.mjpeg_req.filename));
	DBG_IF_LN("(fp: %zd)", sizeof(http_req.mjpeg_req.fp));
	DBG_IF_LN("(qbuf: %zd)", sizeof(http_req.mjpeg_req.qbuf));
	DBG_IF_LN("(boundary: %zd)", sizeof(http_req.mjpeg_req.boundary));
	DBG_IF_LN("(state: %zd)", sizeof(http_req.mjpeg_req.state));

	DBG_IF_LN("------------");
	RTSPRequest_t rtsp_req;
	DBG_IF_LN("(track: %zd)", sizeof(rtsp_req.track));
	DBG_IF_LN("(track[0]: %zd)", sizeof(rtsp_req.track[0]));
#endif
#endif

#ifdef USE_REALLOC
	char *newp = NULL;
	char *oldp = (char *)malloc(16);
	DBG_IF_LN("(newp: %p, oldp: %p)", newp, oldp);
	newp = (char *)realloc(oldp, 32*1024);
	if (newp==NULL)
	{
		SAFE_FREE(oldp);
		DBG_IF_LN("(newp: %p %zd, oldp: %p %zd)", newp, sizeof(newp), oldp, sizeof(oldp));
	}
	else
	{
		oldp = newp; // warning: pointer ‘oldp’ may be used after ‘realloc’
		DBG_IF_LN("(newp: %p %zd, oldp: %p %zd)", newp, sizeof(newp), oldp, sizeof(oldp));
		SAFE_FREE(newp);
	}
#endif

	exit(0);
}
