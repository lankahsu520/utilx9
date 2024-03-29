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
#include <ctype.h>

#ifdef UTIL_EX_BASIC
// https://nachtimwald.com/2017/09/24/hex-encode-and-decode-in-c/
char *bin2hex(const unsigned char *bin, int len)
{
	char * out;
	int i;

	if (bin == NULL || len == 0)
	{
		return NULL;
	}

	out = SAFE_CALLOC(1, len * 2 + 1);
	for (i = 0; i < len; i++)
	{
		out[i * 2] = "0123456789ABCDEF"[bin[i] >> 4];
		out[i * 2 + 1] = "0123456789ABCDEF"[bin[i] &0x0F];
	}

	out[len * 2] = '\0';

	return out;
}

static int hexchr2bin(const char hex, char * out)
{
	if (out == NULL)
	{
		return 0;
	}

	if (hex >= '0' && hex <= '9')
	{
		*out = hex - '0';
	}
	else if (hex >= 'A' && hex <= 'F')
	{
		*out = hex - 'A' + 10;
	}
	else if (hex >= 'a' && hex <= 'f')
	{
		*out = hex - 'a' + 10;
	}
	else
	{
		return 0;
	}

	return 1;
}

int hexs2bin(const char *hex, unsigned char **out)
{
	int len;
	char b1;
	char b2;
	int i;

	if (hex == NULL || *hex == '\0' || out == NULL)
	{
		return 0;
	}

	len = SAFE_STRLEN((char*)hex);
	if (len==0)
	{
		return 0;
	}

	if (len % 2 != 0)
	{
		return 0;
	}
	len /= 2;

	*out = (unsigned char*)SAFE_CALLOC(1, len);
	SAFE_MEMSET(*out, 'A', len);

	for (i = 0; i < len; i++)
	{
		if (!hexchr2bin(hex[i * 2], &b1) || !hexchr2bin(hex[i * 2 + 1], &b2))
		{
			return 0;
		}
		(*out)[i] = (b1 << 4) | b2;
	}

	return len;
}

// https://ivanzz1001.github.io/records/post/cplusplus/2018/03/13/cpluscplus_urlencode
static unsigned char hexchars[] = "0123456789ABCDEF";

/**
 * @brief URLEncode : encode the base64 string "str"
 *
 * @param str:  the base64 encoded string
 * @param strsz:  the str length (exclude the last \0)
 * @param result:  the result buffer
 * @param resultsz: the result buffer size(exclude the last \0)
 *
 * @return: >=0 represent the encoded result length
 *              <0 encode failure
 *
 * Note:
 * 1) to ensure the result buffer has enough space to contain the encoded string, we'd better
 *     to set resultsz to 3*strsz
 *
 * 2) we don't check whether str has really been base64 encoded
 */
int URLEncode(const char *str, const int strsz, char *result, const int resultsz)
{
	int i, j;
	char ch;

	if (strsz < 0 || resultsz < 0)
	{
		return - 1;
	}
	for (i = 0, j = 0; i < strsz && j < resultsz; i++)
	{
		ch = * (str + i);
		if ( (ch >= 'A' && ch <= 'Z')
			|| (ch >= 'a' && ch <= 'z')
			|| (ch >= '0' && ch <= '9')
			|| ch == '.' || ch == '-' || ch == '*' || ch == '_' || ch == '?')
		{
			result[j++] = ch;
		}
		else if (ch == ' ')
		{
			result[j++] = '+';
		}
		else
		{
			if (j + 3 <= resultsz)
			{
				result[j++] = '%';
				result[j++] = hexchars[(unsigned char)ch >> 4];
				result[j++] = hexchars[(unsigned char)ch & 0xF];
			}
			else
			{
				return - 2;
			}
		}
	}
	if (i == 0)
	{
		return 0;
	}
	else if (i == strsz)
	{
		return j;
	}
	return - 2;
}

/**
 * @brief URLDecode : decode the urlencoded str to base64 encoded string
 *
 * @param str:  the urlencoded string
 * @param strsz:  the str length (exclude the last \0)
 * @param result:  the result buffer
 * @param resultsz: the result buffer size(exclude the last \0)
 *
 * @return: >=0 represent the decoded result length
 *              <0 encode failure
 *
 * Note:
 * 1) to ensure the result buffer has enough space to contain the decoded string, we'd better
 *     to set resultsz to strsz
 *
 */
int URLDecode(const char *str, const int strsz, char *result, const int resultsz, const char **last_pos)
{
	int i = 0, j = 0;
	char ch;
	char a;

	*last_pos = str;
	if (strsz < 0 || resultsz < 0)
	{
		return - 1;
	}
	while ( (i < strsz) && (j < resultsz) )
	{
		ch = * (str + i);
		if (ch == '+')
		{
			result[j] = ' ';
			i += 1;
			j ++;
		}
		else if (ch == '%')
		{
			if (i + 3 <= strsz)
			{
				ch = * (str + i + 1);
				if (ch >= 'A' && ch <= 'F')
				{
					a = (ch - 'A') + 10;
				}
				else if (ch >= '0' && ch <= '9')
				{
					a = ch - '0';
				}
				else if (ch >= 'a' && ch <= 'f')
				{
					a = (ch - 'a') + 10;
				}
				else
				{
					return - 2;
				}
				a <<= 4;
				ch = * (str + i + 2);
				if (ch >= 'A' && ch <= 'F')
				{
					a |= (ch - 'A') + 10;
				}
				else if (ch >= '0' && ch <= '9')
				{
					a |= (ch - '0');
				}
				else if (ch >= 'a' && ch <= 'f')
				{
					a |= (ch - 'a') + 10;
				}
				else
				{
					return - 2;
				}

				if ( (a == '"') || (a == '\'') )
				{
					// to remove " or ' from the uri
				}
				else
				{
					result[j] = a;
					j ++;
				}
				i += 3;
			}
			else
			{
				break;
			}
		}
		else if (ch == '"')
		{
			if (i + 1 <= strsz)
			{
				ch = * (str + i + 1);
				if (ch == '"')
				{
					result[j] = ch;
					j ++;
					i += 1;
				}
			}
			i += 1;
		}
#if (1)
		else if (isascii(ch))
#else
		else if ( (ch >= 'A' && ch <= 'Z')
			|| (ch >= 'a' && ch <= 'z')
			|| (ch >= '0' && ch <= '9')
			|| ch == '.' || ch == '-' || ch == '*' || ch == '_' || ch == '?' || ch == '=' || ch == '&' || ch == '[' || ch == ']')
#endif
		{
			result[j] = ch;
			j ++;
			i += 1;
		}
		else
		{
			return - 2;
		}
	}
	*last_pos = str + i;
	return j;
}
#endif

#ifdef UTIL_EX_SSL
// https://devenix.wordpress.com/2008/01/18/howto-base64-encode-and-decode-with-c-and-openssl-2/
char *sec_base64_enc(char *input, int length, int *enc_len)
{
	//int ret = 0;
	BIO *bmem, *b64;
	BUF_MEM *bptr;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	bmem = BIO_push(b64, bmem);

	BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);
	(void)BIO_set_close(bmem, BIO_CLOSE);
	BIO_write(bmem, (const void *)input, length);
	(void)BIO_flush(bmem);
	BIO_get_mem_ptr(bmem, &bptr);

	*enc_len = bptr->length;

	char *buff = SAFE_CALLOC(1, bptr->length+1);
	SAFE_MEMCPY(buff, bptr->data, bptr->length, bptr->length);
	//buff[bptr->length-1] = 0;

	BIO_free_all(bmem);

	return buff;
}

char *sec_base64_dec(char *input, int length, int *dec_len)
{
	BIO *b64, *bmem;

	char *buffer = SAFE_CALLOC(1, length+1);
	SAFE_MEMSET(buffer, 0, length);

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf(input, length);
	bmem = BIO_push(b64, bmem);

	BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);
	(void)BIO_set_close(bmem, BIO_CLOSE);
	*dec_len = BIO_read(bmem, buffer, length);
	//buffer[*dec_len] = '\0';

	BIO_free_all(bmem);

	return buffer;
}
#endif

// https://www.gnu.org/software/libc/manual/html_node/Backtraces.html
void backtrace_alert(void)
{
	void* array[10];
	size_t size;
	char** strings;
	size_t i;

	size = backtrace(array, 10);
	strings = backtrace_symbols(array, size);

	if (NULL == strings)
	{
		exit(EXIT_FAILURE);
	}

	DBG_ER_LN("===== Obtained %02zd stack frames =====", size);

	for (i = 0; i < size; i++)
	{
		DBG_X_LN("%s", strings[i]);
	}

	DBG_ER_LN("====================================");

	SAFE_FREE(strings);
}

