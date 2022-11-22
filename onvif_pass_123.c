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

char filename[LEN_OF_FULLNAME] = "onvif_pass.sh";

//#define USE_FIXD_DATA
char nonce_rand_default[20] = {0x0E, 0x96, 0xFE, 0xB8, 0x5B, 0x60, 0x4C, 0x01, 0xC5, 0xD9, 0xEB, 0xF1, 0xF3, 0x21, 0xB0, 0x37, 0x62, 0xB3, 0x29, 0x38};
// ./onvif_pass_123 admin
int main(int argc, char* argv[])
{
	char tmpbuf[LEN_OF_BUF256] = "";
	DBG_IF_LN("(argc: %d)", argc);

	if (argc==2)
	{
		char pass[LEN_OF_PASS] = "";

		unlink(filename);

		SAFE_SPRINTF(tmpbuf, "%s", "#!/bin/sh\n\n");
		file_append(filename, tmpbuf, strlen(tmpbuf));

		SAFE_SPRINTF(pass, "%s", argv[1]);

		{
			time_t create_t;
			char create_s[LEN_OF_VAL32] = "";

			time (&create_t);
#ifdef USE_FIXD_DATA
			SAFE_SPRINTF(create_s, "2022-11-22T10:44:48.000Z");
#else
			strftime(create_s, sizeof(create_s), "%Y-%m-%dT%H:%M:%S.000Z", localtime(&create_t));
#endif
			DBG_IF_LN(">> (create_s: %s)", create_s);

			SAFE_SPRINTF(tmpbuf, "export ONVIF_XML_CREATED=%s\n", create_s);
			file_append(filename, tmpbuf, strlen(tmpbuf));

			char *nonce_rand = NULL;
#ifdef USE_FIXD_DATA
			nonce_rand = SAFE_CALLOC(1, 20);
			SAFE_MEMCPY(nonce_rand, nonce_rand_default, 20, 20);
#else
			nonce_rand = os_urandom(20);
			DBG_ER_DUMP(nonce_rand, 20, " ", "nonce_rand:");
#endif
			if (nonce_rand)
			{
				int enc_len = 0;
				char *nonce_b64 = sec_base64_enc(nonce_rand, 20, &enc_len);
				if (nonce_b64)
				{
					DBG_IF_LN("nonce_b64 (enc_len: %d, [%s])", enc_len, nonce_b64);
					SAFE_SPRINTF(tmpbuf, "export ONVIF_XML_NONCE=%s\n", nonce_b64);
					file_append(filename, tmpbuf, strlen(tmpbuf));

					SAFE_FREE(nonce_b64);
				}

				DBG_IF_LN(">> (pass: %s %d)", pass, strlen(pass));
				char *password = onvif_pass_sha1(nonce_rand, 20, create_s, strlen(create_s), pass, strlen(pass));
				if (password)
				{
					int enc_len = 0;
					char *password_b64 = sec_base64_enc(password, 20, &enc_len);
					if (password_b64)
					{
						DBG_IF_LN("password_b64 (enc_len: %d, [%s] -> [%s])", enc_len, pass, password_b64);
						SAFE_SPRINTF(tmpbuf, "export ONVIF_XML_PASSWORD=%s\n", password_b64);
						file_append(filename, tmpbuf, strlen(tmpbuf));

						SAFE_FREE(password_b64);
					}
					SAFE_FREE(password);
				}

				SAFE_FREE(nonce_rand);
			}
		}
	}

	return 0;
}
