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
#include "zlib.h" // for compress and uncompress

#define USE_TEST_COMPRESS
#define USE_TEST_SEC_ENC_AND_DEC
#define USE_TEST_BIN_CHECK
#define USE_TEST_HOSTNAME
#define USE_TEST_FILE_LOOKUP
#define USE_TEST_FILE_PATH
#define USE_TEST_COPY_FILE
#define USE_TIME_TEST

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
	DBG_IF_LN("(1<<3: 0x%08X, 1<<14: 0x%08X, 1<<15: 0x%08X, 1<<16: 0x%08X, 1<<17: 0x%08X)", 1 << 3, 1 << 14, 1 << 15, 1 << 16, 1 << 17);

	char hello[]="Hello World !!!    ";
	DBG_IF_LN("(hello_trim: %s)", hello);
	
	char *hello_trim = str_trim(hello);
	DBG_IF_LN("(hello_trim: %s)", hello_trim);

	{
		char topic_pub[LEN_OF_TOPIC]	= "";
		char user[LEN_OF_TOPIC]= "luffanet";
		char macid[LEN_OF_TOPIC] = "1234";
		SAFE_STRCAT_EX(topic_pub, user, "/", macid);

		DBG_ER_LN("SAFE_STRCAT_EX - %s", topic_pub);
	}

	DBG_LN_LN();

#ifdef USE_TEST_COMPRESS
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
	char abc[]="rtsp://192.168.50.238:554/live1.sdp";
	int abc_enc_len = 0;
	char *abc_enc = sec_base64_enc(abc, strlen(abc), &abc_enc_len);
	DBG_IF_LN("(abc_enc: %s)", abc_enc);
	int abc_dec_len = 0;
	char *abc_dec = sec_base64_dec(abc_enc, strlen(abc_enc), &abc_dec_len);
	DBG_IF_LN("(abc_dec: %s)", abc_dec);
	SAFE_FREE(abc_enc);
	SAFE_FREE(abc_dec);

	char aes[LEN_OF_PASS] = "123456789";
	char aes_enc[LEN_OF_PASS] = "";
	sec_aes_cbc_enc(aes, aes_enc, "888888");
	DBG_IF_LN("(aes_enc: %s)", aes_enc);
	char aes_dec[LEN_OF_PASS] = "";
	sec_aes_cbc_dec(aes_enc, aes_dec, LEN_OF_PASS, "888888");
	DBG_IF_LN("(aes_dec: %s)", aes_dec);
#endif
#endif

#ifdef USE_TEST_BIN_CHECK
	{
		DBG_IF_LN("(/usr/bin/7z: %d)", file_exe_chk("/usr/bin/7z"));
		DBG_IF_LN("(/bin/7za: %d)", file_exe_chk("/bin/7za"));
	}
#endif

#ifdef USE_TEST_HOSTNAME
	{
		char myhostname[LEN_OF_HOSTNAME]="";
		gethostname(myhostname, LEN_OF_HOSTNAME);
		DBG_IF_LN("(gethostname: %s)", myhostname);

		char mydomainname[LEN_OF_HOSTNAME]="";
		int res = getdomainname(mydomainname, LEN_OF_HOSTNAME);
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
		if( file_path(path, actualpath) )
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
	char filename[LEN_OF_FILENAME256] ="";
	int i = 0;
	for (i=0; i< 256; i++)
	{
		SAFE_SPRINTF(filename, "./snapshot_%03d.jpg", i);
		file_copy("./snapshot.jpg", filename);
	}
#endif

#ifdef USE_TIME_TEST
	DBG_IF_LN("(time_now_full: %s)", time_now_full(time(NULL)));
#endif

	exit(0);
}
