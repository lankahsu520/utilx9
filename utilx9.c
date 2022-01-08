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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define DBG_TMP_Y(format,args...) //DBG_LN_Y(format, ## args)
#define DBG_TMP_DUMP(ibuf,len,delim,format,args...) //DBG_TR_DUMP(ibuf,len,delim,format,## args)

#ifdef UTIL_EX_DBG 
int dbg_more = DBG_LVL_INFO;//DBG_LVL_INFO;

int dbg_lvl_round(void)
{
	dbg_more++;
	dbg_more %= DBG_LVL_MAX;
	return dbg_more;
}

int dbg_lvl_set(int lvl)
{
	dbg_more = lvl;
	dbg_more %= DBG_LVL_MAX;
	return dbg_more;
}

int dbg_lvl_get(void)
{
	return dbg_more;
}

#else
int dbg_lvl_get(void)
{
	return 0;
}
#endif


#ifdef UTIL_EX_SAFE
#include "util_expiration.h"

time_t expiration_date(void)
{
#ifdef UTIL_EX_EXPIRATION_DATE
	return UTIL_EX_EXPIRATION_DATE;
#else
	return 0;
#endif
}

void* pcheck( void* a )
{
	static double diff_t = 1;
	time_t run_t = time(NULL);
	time_t expired_t = expiration_date();
	if ( expired_t == 0 )
	{
		diff_t++;
		//sleep(diff_t);
		printf("%ld==0",expired_t);
	}
	else if ( run_t > expired_t )
	{
		diff_t = time_diff_days(run_t, expired_t);
		//sleep(diff_t);
		printf("%ld>%ld", run_t, expired_t);
	}
	return a ;
}

int select_ex(int fd, fd_set *fdrset_ptr, fd_set *fdwset_ptr, fd_set *fdeset_ptr, int msec)
{
	int maxfd = fd+1;

	struct timeval *tv_ptr = NULL;
	struct timeval timeout = {0,0};

	SAFE_FD_SET_EX(fd, fdrset_ptr);
	SAFE_FD_SET_EX(fd, fdwset_ptr);
	SAFE_FD_SET_EX(fd, fdeset_ptr);

	if (msec>0)
	{
		timeout.tv_sec = msec /1000;
		timeout.tv_usec = (msec % 1000) * 1000;
		tv_ptr = &timeout;
	}
	else
	{
		// block
	}

	return SAFE_SELECT(maxfd, fdrset_ptr, fdwset_ptr, fdeset_ptr, tv_ptr);
}
#endif

#ifdef UTIL_EX_BASIC 
#include <fcntl.h>

#if (0)
int str_isspace(char *str)
{
	char *s=" \n\t\r";
	if ( SAFE_STRCHR(s,str) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}
#endif

char *version_show(void)
{
	static char buff[LEN_OF_VAL64] = "";
	if ( SAFE_STRLEN(buff) == 0 )
	{
		time_t bootup_t = time(NULL);
		SAFE_SPRINTF_EX(buff, "%s, %s, %s, %s, %ld", PJ_VERSION, PJ_REVISION, PJ_BUILDNO, PJ_BUILDER, bootup_t);
	}

	return buff;
}

int system_ex(char *fmt, ...)
{
	va_list vargs;
	char *cmd = NULL;
	int rc = 0;
	int ret = -1;

	va_start(vargs, fmt);
	ret = vasprintf(&cmd, fmt, vargs);
	va_end(vargs);

	if (ret<0) DBG_ER_LN("vasprintf error !!!");
	if (cmd)
	{
		DBG_DB_LN("(cmd: %s)", cmd);
		rc = system(cmd);
		SAFE_FREE(cmd);
	}
	return rc;
}

char *str_cat_ex(char *str, ...)
{
	if (str)
	{
		va_list vargs;
		va_start(vargs, str);
		char *s = va_arg(vargs, char*);
		while (s)
		{
			strcat(str, s);
			s = va_arg(vargs, char*);
		}
		va_end(vargs);
	}

	return str;
}

// 0: is number. -1: fail
int str_isnum(const char *str)
{
	int ret = -1;

	while (*str != '\0')
	{
		if ( (*str < '0') || (*str > '9') )
		{
			return ret;
		}
		str++;
	}

	return 0;
}

char *str_rtrim(char *str)
{
	if ( (str == NULL) || (*str == '\0') )
	{
		return str;
	}

	int len = strlen(str);
	char *p = str + len - 1;
	while ( (p >= str) && (isspace(*p)) )
	{
		*p = '\0';
		--p;
	}

	return str;
}

char *str_ltrim(char *str)
{
	if ( (str == NULL) || (*str == '\0') )
	{
		return str;
	}

	int len = 0;
	char *p = str;
	while ( (*p != '\0') && (isspace(*p)) )
	{
		++p;
		++len;
	}

	if (len>0)
	{
		SAFE_MEMMOVE(str, p, strlen(str) - len + 1);
	}
	return str;
}

char *str_trim(char *str)
{
	str = str_rtrim(str);
	str = str_ltrim(str);

	return str;
}

char *str_trim_char(char *str, const char *delim, int delim_len)
{
	if ( (str == NULL) || (*str == '\0') )
	{
		return str;
	}

	char *p = str;
	while (*p != '\0')
	{
		//if (*p == trim)
		if ( SAFE_MEMCHR((char*)delim, *p, delim_len) )
		{
			char *endp = NULL;
			endp = p+strlen(p+1);
			SAFE_MEMMOVE(p, p+1, strlen(p+1));
			*endp = '\0';
		}
		else
		{
			p++;
		}
	}

	return str;
}

void str_toupper(char *str)
{
	if (str)
	{
		int c = 0;

		while (str[c] != '\0')
		{
			if (str[c] >= 'a' && str[c] <= 'z')
			{
				str[c] = str[c] - 32;
			}
			c++;
		}
	}
}

void str_tolower(char *str)
{
	if (str)
	{
		int c = 0;

		while (str[c] != '\0')
		{
			if (str[c] >= 'A' && str[c] <= 'Z')
			{
				str[c] = str[c] + 32;
			}
			c++;
		}
	}
}

uint32_t byte2big_endian(uint8_t size, uint8_t *data)
{
	uint32_t val =0;
	switch (size)
	{
		case 1:
			//cmd[4] = cfg_param_rec->param_val & 0xFF;
			val = data[0];
			break;

		case 2:
			//cmd[4] = (cfg_param_rec->param_val >> 8) & 0xFF;
			//cmd[5] = cfg_param_rec->param_val & 0xFF;
			val = ((unsigned int)data[0] << 8) | data[1];
			break;

		case 4:
			//cmd[4] = (cfg_param_rec->param_val >> 24) & 0xFF;
			//cmd[5] = (cfg_param_rec->param_val >> 16) & 0xFF;
			//cmd[6] = (cfg_param_rec->param_val >> 8) & 0xFF;
			//cmd[7] = cfg_param_rec->param_val & 0xFF;
			val = ((unsigned int)data[0] << 24) | ((unsigned int)data[1] << 16) | ((unsigned int)data[2] << 8) | data[3];
			break;

		default:
			break;
	}
	return val;
}

void big_endian2byte(uint8_t size, uint32_t val, uint8_t *data)
{
	switch (size)
	{
		case 1:
			data[0] = val & 0xFF;
			break;

		case 2:
			data[0] = (val >> 8) & 0xFF;
			data[1] = val & 0xFF;
			break;

		case 4:
			data[0] = (val >> 24) & 0xFF;
			data[1] = (val >> 16) & 0xFF;
			data[2] = (val >> 8) & 0xFF;
			data[3] = val & 0xFF;
			break;

		default:
			break;
	}
}

uint32_t byte2little_endian(uint8_t size, uint8_t *data)
{
	uint32_t val =0;
	switch (size)
	{
		case 1:
			//cmd[4] = cfg_param_rec->param_val & 0xFF;
			val = data[0];
			break;

		case 2:
			//cmd[4] = (cfg_param_rec->param_val >> 8) & 0xFF;
			//cmd[5] = cfg_param_rec->param_val & 0xFF;
			val = ((unsigned int)data[1] << 8) | data[0];
			break;

		case 4:
			//cmd[4] = (cfg_param_rec->param_val >> 24) & 0xFF;
			//cmd[5] = (cfg_param_rec->param_val >> 16) & 0xFF;
			//cmd[6] = (cfg_param_rec->param_val >> 8) & 0xFF;
			//cmd[7] = cfg_param_rec->param_val & 0xFF;
			val = ((unsigned int)data[3] << 24) | ((unsigned int)data[2] << 16) | ((unsigned int)data[1] << 8) | data[0];
			break;

		default:
			break;
	}
	return val;
}

void little_endian2byte(uint8_t size, uint32_t val, uint8_t *data)
{
	switch (size)
	{
		case 1:
			data[0] = val & 0xFF;
			break;

		case 2:
			data[1] = (val >> 8) & 0xFF;
			data[0] = val & 0xFF;
			break;

		case 4:
			data[3] = (val >> 24) & 0xFF;
			data[2] = (val >> 16) & 0xFF;
			data[1] = (val >> 8) & 0xFF;
			data[0] = val & 0xFF;
			break;

		default:
			break;
	}
}

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
				result[j++] = hexchars[(unsigned char)
				ch >> 4];
				result[j++] = hexchars[(unsigned char)
				ch & 0xF];
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

				if ( (a == '"') || (a == '\''))
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

uint8_t buff_crc8_xor(uint8_t *start, uint8_t *buf, int len)
{
	int i = 0;
	int idx = 0;
	uint8_t crc = 0;

	if (start)
	{
		idx = 0;
		crc = start[0];
	}
	else
	{
		idx = 1;
		crc = buf[0];
	}

	for (i = idx; i < len; i++) {
			crc ^= buf[i];
	}
	return crc;
}

// copy from contiki\core\lib\Crc16.c  and Crc16.h
unsigned short buff_crc16_add(unsigned char b, unsigned short acc)
{
	/*
		acc  = (unsigned char)(acc >> 8) | (acc << 8);
		acc ^= b;
		acc ^= (unsigned char)(acc & 0xff) >> 4;
		acc ^= (acc << 8) << 4;
		acc ^= ((acc & 0xff) << 4) << 1;
	*/

	acc ^= b;
	acc  = (acc >> 8) | (acc << 8);
	acc ^= (acc & 0xff00) << 4;
	acc ^= (acc >> 8) >> 4;
	acc ^= (acc & 0xff00) >> 5;
	return acc;
}

unsigned short buff_crc16(const unsigned char *buf, int len, unsigned short acc)
{
	int i;

	for(i = 0; i < len; ++i)
	{
		acc = buff_crc16_add(*buf, acc);
		++buf;
	}
	return acc;
}

static unsigned long buff_crc32_tab[] = 
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

unsigned long buff_crc32( const void *buf, unsigned long size,unsigned long crc)
{
	const unsigned char *p;

	p = buf;
	crc = crc ^ ~0U;

	while (size--)
		crc = buff_crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

	return crc ^ ~0U;
}

#define BB_LITTLE_ENDIAN 1
unsigned short buf_cksum(unsigned short *addr, int nleft)
{
	/*
	 * Our algorithm is simple, using a 32 bit accumulator,
	 * we add sequential 16 bit words to it, and at the end, fold
	 * back all the carry bits from the top 16 bits into the lower
	 * 16 bits.
	 */
	unsigned sum = 0;
	while (nleft > 1) {
		sum += *addr++;
		nleft -= 2;
	}

	/* Mop up an odd byte, if necessary */
	if (nleft == 1) {
		if (BB_LITTLE_ENDIAN)
			sum += *(unsigned char*)addr;
		else
			sum += *(unsigned char*)addr << 8;
	}

	/* Add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
	sum += (sum >> 16);                     /* add carry */

	return (unsigned short)~sum;
}

static void time_sec2day(int duration, int *day, int *hrs, int *min, int *sec)
{
	*day = (duration / 86400);
	duration = (duration % 86400);
	*hrs = (duration / 3600);
	duration = (duration % 3600);
	*min = (duration / 60);
	*sec = (duration % 60);
}

char *time_now_full(time_t now_t) // output: 2020-03-06 15:01:47
{
	static char buff[LEN_OF_VAL128] = "";
	//time_t now_t = time(NULL);
	struct tm *timeinfo  = localtime (&now_t);
	SAFE_SPRINTF_EX(buff, "%04d-%02d-%02d %02d:%02d:%02d",
			timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	return buff;
}

char *time_now_short(time_t now_t) // output: 20200306 150147
{
	static char buff[LEN_OF_VAL128] = "";
	//time_t now_t = time(NULL);
	struct tm *timeinfo  = localtime (&now_t);
	SAFE_SPRINTF_EX(buff, "%04d%02d%02d %02d%02d%02d",
			timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	return buff;
}

double time_diff_secs(time_t end_t, time_t start_t)
{
	double  diff_t = difftime(end_t, start_t);
	return diff_t;
}

double time_diff_mins(time_t end_t, time_t start_t)
{
	double  diff_t = difftime(end_t, start_t);
	diff_t = diff_t/60; //60
	return diff_t;
}

double time_diff_hours(time_t end_t, time_t start_t)
{
	double  diff_t = difftime(end_t, start_t);
	diff_t = diff_t/3600; //60*60
	return diff_t;
}

double time_diff_days(time_t end_t, time_t start_t)
{
	double  diff_t = difftime(end_t, start_t);
	diff_t = diff_t/86400; //60*60*24
	return diff_t;
}

double time_diff_weeks(time_t end_t, time_t start_t)
{
	double  diff_t = difftime(end_t, start_t);
	diff_t = diff_t/604800; //60*60*24*7
	return diff_t;
}

#include <libgen.h>

int file_exe_chk(char *filename)
{
	int ret = -1;
	struct stat sb;
	if ( (stat(filename, &sb) == 0) && (sb.st_mode & S_IXUSR) ) 
	{
		ret = 0;
	}
	return ret;
}

// 1: soft link
int file_slink(char *filename)
{
	struct stat file_stat= {0};

	if (lstat(filename, &file_stat) == -1)
	{
		return 0;
	}

	return S_ISLNK(file_stat.st_mode) ? 1 : 0;
}

int file_spath(char *filename, char *spath, int length)
{
	int ret = -1;
	if ( file_slink(filename) )
	{
		DBG_DB_LN("S_ISLNK !!!(filename: %s)", filename);
		ret = readlink(filename, spath, length);
	}
	else
	{
		DBG_DB_LN("S_ISLNK not !!! (filename: %s)", filename);
	}

	return ret;
}

char *file_path(char *filename, char *actualpath)
{
#if (0)
	char *dirc, *basec, *bname, *dname;
	//char path[128] = "";//"/etc/passwd";
	//SAFE_SPRINTF_EX(path, "/etc/%s", "../etc/passwd");

	dirc = strdup(filename);
	basec = strdup(filename);
	dname = dirname(dirc);
	bname = basename(basec);
	DBG_IF_LN("(filename: %s, dirname: %s, basename: %s)", filename, dname, bname);
	SAFE_FREE(dirc);
	SAFE_FREE(basec);
#endif

	char *ptr = realpath(filename, actualpath);
	if ( ptr )
	{
		DBG_IF_LN("(actualpath: %s)", actualpath);
	}
	else
	{
		DBG_IF_LN("%s not exist !!!", filename);
	}
	return ptr;
}

size_t file_append(char *filename, char *buf, int wantsize)
{
	FILE *fp;
	size_t writesize = 0;
	//time_t t;

	fp = SAFE_FOPEN(filename, "a+");
	if ( fp == NULL ) {
		DBG_ER_LN("return, SAFE_FOPEN error !!! (%s, errno: %d %s)", filename, errno, strerror(errno));
		return 0;
	}

	SAFE_FSEEK_END(fp, 0);

	writesize = SAFE_FWRITE(buf, 1, wantsize, fp);
	if ( writesize <= 0 ) {
		DBG_ER_LN("SAFE_FWRITE error !!! (writesize: %zd, wantsize: %d)", writesize, wantsize );
	}

	SAFE_FCLOSE(fp);

	return writesize;
}

size_t file_writer(char *filename, char *buf, int wantsize)
{
	FILE *fp;
	size_t writesize = 0;
	//time_t t;

	fp = SAFE_FOPEN(filename, "w");
	if ( fp == NULL ) {
		DBG_ER_LN("return, SAFE_FOPEN error !!! (%s, errno: %d %s)", filename, errno, strerror(errno));
		return 0;
	}

	writesize = SAFE_FWRITE(buf, 1, wantsize, fp);
	if ( writesize <= 0 ) {
		DBG_ER_LN("SAFE_FWRITE error !!! (writesize: %zd, wantsize: %d)", writesize, wantsize );
	}

	SAFE_FCLOSE(fp);

	return writesize;
}

char *file_reader(char *filename, int *filesize)
{
	FILE *fp;
	int size = 0;
	char *buf = NULL;

	if ( access(filename, F_OK) == -1 )
	{
		DBG_ER_LN("return, %s not exist !!!", filename);
		return NULL;
	}

	fp = SAFE_FOPEN(filename, "r");
	if ( fp == NULL )
	{
		DBG_ER_LN("return, SAFE_FOPEN error !!! (%s, errno: %d %s)", filename, errno, strerror(errno));
		return NULL;
	}

	SAFE_FSEEK_END(fp, 0);
	size = SAFE_FTELL(fp);
	SAFE_FSEEK_SET(fp, 0);

	if ( size > 0 )
	{
		buf = SAFE_CALLOC(1, size);
		*filesize = SAFE_FREAD(buf, 1, size, fp);
	}

	SAFE_FCLOSE(fp);

	return buf;
}

int file_copy(const char *file_from, const char *file_to)
{
	int ret = 0;

	int fd_to = -1;
	int fd_from = -1;
	char buf[4096];
	ssize_t nread;
	//int saved_errno;

	if ( ( file_to == NULL ) || ( file_from == NULL ) )
	{
		DBG_ER_LN("file_to or file_from is NULL !!!");
		ret = -1;
		goto cp_exit;
	}
	DBG_IF_LN("(%s -> %s)", file_from, file_to);

	SAFE_MEMSET(buf, 0, sizeof(buf));
	fd_from = SAFE_OPEN((char *)file_from, O_RDONLY);
	if (fd_from < 0)
	{
		DBG_ER_LN("SAFE_OPEN error !!! (%s)", file_from);
		ret = -1;
		goto cp_exit;
	}
	
	fd_to = SAFE_OPEN((char *)file_to, O_WRONLY | O_CREAT , 0666);
	if (fd_to < 0)
	{
		DBG_ER_LN("SAFE_OPEN error !!! (%s)", file_to);
		ret = -1;
		goto cp_exit;
	}
	
	while ( (nread = read(fd_from, buf, sizeof(buf) )) > 0)
	{
		char *out_ptr = buf;
		ssize_t nwritten;

		do
		{
			nwritten = write(fd_to, out_ptr, nread);

			if (nwritten >= 0)
			{
				nread -= nwritten;
				out_ptr += nwritten;
			}
			else if (errno != EINTR)
			{
				ret = -1;
				goto cp_exit;
			}
		} while (nread > 0);
	}

cp_exit:
	SAFE_FSYNC(fd_to);
	SAFE_FSYNC(fd_from);

	SAFE_CLOSE(fd_from);
	SAFE_CLOSE(fd_to);
	return ret;
}

void file_lookup(char *filename, newline_lookup_fn lookup_cb, void *arg)
{
	if ( (lookup_cb) && (filename) && (access(filename, F_OK) != -1) )
	{
		char newline[LEN_OF_NEWLINE];

		DBG_TR_LN("enter (%s)", filename);

		FILE *fp = SAFE_FOPEN(filename, "r");
		if (fp)
		{
			while (SAFE_FGETS(newline, sizeof(newline), fp)!= NULL)
			{
				if ( lookup_cb(newline, arg) != 0 )
					break;
			}
			SAFE_FCLOSE(fp);
		}
		else
		{
			DBG_ER_LN("SAFE_FOPEN error !!! (%s, errno: %d %s)", filename, errno, strerror(errno));
		}
	}
	else
	{
		DBG_ER_LN("filename or lookup_cb is NULL !!!");
	}
}

void pfile_lookup(char *cmdline, newline_lookup_fn lookup_cb, void *arg)
{
	if ( (lookup_cb) && (cmdline) && (strlen(cmdline) > 0) )
	{
		char newline[LEN_OF_NEWLINE];

		DBG_TR_LN("enter (%s)", cmdline);

		FILE *fp = SAFE_POPEN(cmdline, "r");
		if (fp)
		{
			while (SAFE_FGETS(newline, sizeof(newline), fp)!= NULL)
			{
				if ( lookup_cb(newline, arg) != 0 )
					break;
			}
			SAFE_PCLOSE(arg);
		}
		else
		{
			DBG_ER_LN("SAFE_POPEN error !!! (%s)", cmdline );
		}
	}
	else
	{
		DBG_ER_LN("cmdline or lookup_cb is NULL !!!");
	}
}

char *os_random_uuid(char *buf, int buf_len)
{
	if ( (buf) && (buf_len>=LEN_OF_UUID) )
	{
		const char *c = "89ab";
		char *p = buf;
		int n;

		srand(time(NULL));

		for( n = 0; n < 16; ++n )
		{
			int b = rand()%255;
			switch( n )
			{
				case 6:
					SAFE_SPRINTF(p, "4%X", b%15 );
					break;
				case 8:
					SAFE_SPRINTF(p, "%c%X", c[rand()%strlen(c)], b%15 );
					break;
				default:
					SAFE_SPRINTF(p, "%02X", b);
					break;
			}

			p += 2;
			switch( n )
			{
				case 3:
				case 5:
				case 7:
				case 9:
					*p++ = '-';
					break;
			}
		}
		*p = 0;
	}
	else
	{
		DBG_ER_LN("%s (buf: %p, buf_len: %d < %d)", DBG_TXT_WRONG, buf, buf_len, LEN_OF_UUID);
	}
	return buf;
}

char *os_urandom(int byte_count)
{
	char *data = SAFE_CALLOC(1, byte_count);

	FILE *fp = SAFE_FOPEN("/dev/urandom", "r");
	if ( (data) && (fp) )
	{
		if (SAFE_FREAD(data, 1, byte_count, fp) > 0)
		{
			// got !!!
		}
	}

	SAFE_FCLOSE(fp);
	return data;
}

#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#include <openssl/aes.h>
//#include <openssl/cmac.h>
//#include <openssl/err.h>
//#include <openssl/ssl.h>


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
	BIO_set_close(bmem, BIO_CLOSE);
	BIO_write(bmem, (const void *)input, length);
	BIO_flush(bmem);
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
	BIO_set_close(bmem, BIO_CLOSE);
	*dec_len = BIO_read(bmem, buffer, length);
	//buffer[*dec_len] = '\0';

	BIO_free_all(bmem);

	return buffer;
}

int sec_aes_cbc_enc(char *in, char *out, char *aes_key)
{
	int ret = 0;
	AES_KEY aes;
	int out_len;
	unsigned char iv[AES_BLOCK_SIZE];

	if(!in || !out) return 0;

	memcpy(iv, aes_key, AES_BLOCK_SIZE);

	if ( AES_set_encrypt_key((unsigned char*)iv, 128, &aes) < 0 ) {
		return -1;
	}
	out_len = ((strlen(in)/AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE; //strlen(in);

	AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, out_len, &aes, iv, AES_ENCRYPT);
	return ret;
}

char *sec_aes_cbc_enc_ascii(char *in, int in_len, char *aes_key)
{
	int enc_len = ((in_len/AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
	char *in_enc = SAFE_CALLOC(1, enc_len + 1);
	sec_aes_cbc_enc(in, in_enc, aes_key);

	char *out_ascii = bin2hex((const unsigned char *)in_enc, enc_len);
	SAFE_FREE(in_enc);

	return out_ascii;
}

char *sec_aes_cbc_enc_base(char *in, int in_len, char *aes_key)
{
	int enc_len = ((in_len/AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
	char *in_enc = SAFE_CALLOC(1, enc_len + 1);
	sec_aes_cbc_enc(in, in_enc, aes_key);

	int out_base_len = 0;
	char *out_base = sec_base64_enc(in_enc, enc_len, &out_base_len);
	DBG_DB_LN("(out_base: %s, out_base_len: %d)", out_base, out_base_len);
	SAFE_FREE(in_enc);

	return out_base;
}


int sec_aes_cbc_dec(char *in, char *out, int out_len, char *aes_key)
{
	int ret = 0;
	AES_KEY aes;
	unsigned char iv[AES_BLOCK_SIZE];

	if(!in || !out) return 0;

	memcpy(iv, aes_key, AES_BLOCK_SIZE);

	if(AES_set_decrypt_key((unsigned char*)iv, 128, &aes) < 0) {
		return -1;
	}

	AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, out_len, &aes, iv, AES_DECRYPT);
	return ret;
}

int sec_aes_cbc_dec_base(char *in, char *out, int out_len, char *aes_key)
{
	int ret = 0;
	int in_base_len = 0;
	char *in_base = sec_base64_dec(in, strlen(in), &in_base_len);

	if (sec_aes_cbc_dec((char*)in_base, out, out_len, aes_key) < 0 )
	{
		ret = -1;
	}
	SAFE_FREE(in_base);
	return ret;
}
#endif

#ifdef UTIL_EX_BASIC_QBUF
void qbuf_init(QBUF_t *qbuf, size_t max_size)
{
	if ( qbuf )
	{
		memset(qbuf, 0, sizeof(QBUF_t));
		qbuf->max_size = max_size;
	}
}

size_t qbuf_total(QBUF_t *qbuf)
{
	if (qbuf)
	{
		return qbuf->total;
	}
	return 0;
}

char *qbuf_endptr(QBUF_t *qbuf)
{
	if (qbuf)
	{
		return qbuf->buff + qbuf->total;
	}
	return NULL;
}

char *qbuf_buff(QBUF_t *qbuf)
{
	if (qbuf)
	{
		return qbuf->buff;
	}
	return NULL;
}

static char *qbuf_jumpjump(QBUF_t *qbuf, char *jumpptr, size_t *jumplen)
{
	int skiplen = 0;
	char *startptr = qbuf_buff(qbuf);
	if ( ( jumpptr ) && ( jumpptr > startptr ) )
	{
		skiplen = jumpptr - startptr;
		if ( (skiplen + 1) < qbuf_total(qbuf) )
		{
			startptr = jumpptr;
		}
	}

	if (jumplen)
	{
		*jumplen = skiplen;
	}
	return startptr;
}

char *qbuf_jumprchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr)
{
	if ( (qbuf) && ( qbuf_total(qbuf) > 0 ) )
	{
		size_t jumplen = 0;
		char *startptr = qbuf_jumpjump(qbuf, jumpptr, &jumplen);

		if (startptr)
		{
			size_t n = qbuf_total(qbuf) - jumplen;
			size_t idx = n-1;
			while (idx > 0 )
			{
				if ( SAFE_MEMCHR((char*)delim, startptr[idx], delim_len) )
				{
					// Found !!!
					idx --;
				}
				else
				{
					break;
				}
			}
			if (idx != (n-1)) return startptr+idx+1;
		}
	}
	return NULL;
}

char *qbuf_jumpchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr)
{
	if ( (qbuf) && ( qbuf_total(qbuf) > 0 ) )
	{
		size_t jumplen = 0;
		char *startptr = qbuf_jumpjump(qbuf, jumpptr, &jumplen);

		if (startptr)
		{
			int n = qbuf_total(qbuf) - jumplen;
			int idx = 0;
			while (idx < n)
			{
				if ( SAFE_MEMCHR((char*)delim, startptr[idx], delim_len) )
				{
					// Found !!!
					idx ++;
				}
				else
				{
					break;
				}
			}
			if (idx) return startptr+idx-1;
		}
	}
	return NULL;
}

char *qbuf_memchr(QBUF_t *qbuf, char c, char *jumpptr)
{
	if ( (qbuf) && ( qbuf_total(qbuf) > 0 ) )
	{
		size_t jumplen = 0;
		char *startptr = qbuf_jumpjump(qbuf, jumpptr, &jumplen);

		int n = qbuf_total(qbuf) - jumplen;
		
		return SAFE_MEMCHR(startptr, c, n);
	}
	return NULL;
}

char *qbuf_memmem(QBUF_t *qbuf, char *needle, size_t needlelen, char *jumpptr)
{
	if ( (qbuf) && (needle) && (needlelen) && ( qbuf_total(qbuf) > 0 ) )
	{
		size_t jumplen = 0;
		char *startptr = qbuf_jumpjump(qbuf, jumpptr, &jumplen);
		char *endptr = qbuf_endptr(qbuf);
		size_t leftlen = endptr - startptr;
		return SAFE_MEMMEM(startptr, leftlen, needle, needlelen);
	}
	return NULL;
}

char *qbuf_strstr(QBUF_t *qbuf, char *substr, char *jumpptr)
{
	if ( (qbuf) && (substr) && ( qbuf_total(qbuf) > 0 ) )
	{
		size_t jumplen = 0;
		char *startptr = qbuf_jumpjump(qbuf, jumpptr, &jumplen);

		return SAFE_STRSTR(startptr, substr);
	}
	return NULL;
}

char *qbuf_pop(QBUF_t *qbuf)
{
	char *buff = NULL;
	if ( (qbuf) && ( qbuf_total(qbuf) > 0 ) )
	{
		buff = qbuf_buff(qbuf);

		qbuf->buff = NULL;
		qbuf->total = 0;
	}
	return buff;
}

// count: ok
// -1: fail
int qbuf_read(QBUF_t *qbuf, char *obuff, size_t count)
{
	int ret = -1;

	if ( (qbuf) && ( qbuf_total(qbuf) > 0 ) )
	{
		int nread = SAFE_MIN((SIZE_X)count, (SIZE_X)qbuf_total(qbuf) );

		//DBG_TR_LN("(buff: %s, total: %d, count: %d)", qbuf->buff, qbuf->total, count);
		if (obuff)
		{
			SAFE_MEMCPY(obuff, qbuf->buff, nread, nread);
		}

		size_t new_len = qbuf->total - nread;
		SAFE_MEMMOVE(qbuf->buff, qbuf->buff+nread, new_len);
		char *new_buff = SAFE_REALLOC(qbuf->buff, new_len+1);
		if ( new_buff == NULL )
		{
			// out of memory
			// qbuf->buff will be free outside
			DBG_ER_LN("SAFE_REALLOC error !!! (total: %zd -> %zd)", qbuf->total, new_len);
			ret = -1;
		}
		else
		{
			new_buff[new_len] = '\0'; 

			qbuf->buff = new_buff;
			qbuf->total = new_len;
			ret = nread;
		}
	}
	return ret;
}

int qbuf_trimrchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr)
{
	int ret = qbuf_total(qbuf);
	char *breakptr = NULL;
	if ((ret) && 
			(breakptr = qbuf_jumprchr(qbuf, delim, delim_len, jumpptr)) )
	{
		char *endptr = qbuf_endptr(qbuf);

		size_t trim_num = (endptr-breakptr);
		if (trim_num < qbuf->total)
		{
			qbuf->total -= trim_num;
			SAFE_MEMSET(breakptr, 0, trim_num);
		}
		ret = qbuf_total(qbuf);
	}
	return ret;
}

int qbuf_trimchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr)
{
	int ret = qbuf_total(qbuf);
	char *breakptr = NULL;
	if ((ret) && 
			(breakptr = qbuf_jumpchr(qbuf, delim, delim_len, jumpptr)) )
	{
		char *pbuff = qbuf_buff(qbuf);
		qbuf_read(qbuf, NULL, (breakptr - pbuff));
		ret = qbuf_total(qbuf);
	}
	return ret;
}

int qbuf_shiftrstr(QBUF_t *qbuf, char *substr)
{
	int ret = -1;
	char *breakptr = NULL;

	if ( (qbuf) && (substr) && ( (breakptr = qbuf_memmem(qbuf, substr, SAFE_STRLEN(substr), NULL)) > 0 ))
	{
		char *endptr = qbuf_endptr(qbuf);
		size_t trim_num = (endptr-breakptr);
		if (trim_num < qbuf_total(qbuf))
		{
			qbuf->total -= trim_num;
			SAFE_MEMSET(breakptr, 0, trim_num);
		}
		ret = 0;
	}
	return ret;
}

int qbuf_shiftstr(QBUF_t *qbuf, char *substr)
{
	int ret = -1;
	char *breakptr = NULL;

	if ( (qbuf) && (substr) && ( (breakptr = qbuf_memmem(qbuf, substr, SAFE_STRLEN(substr), NULL)) > 0 ))
	{
		int slen = strlen(substr);
		int mlen = breakptr - qbuf_buff(qbuf) + slen;
		if ( qbuf_read(qbuf, NULL, breakptr - qbuf_buff(qbuf) + slen) == mlen)
		{
			ret = 0;
		}
	}
	return ret;
}

// count: ok
// -1: fail
int qbuf_write(QBUF_t *qbuf, char *ibuff, size_t count)
{
	int ret = -1;
	//DBG_DB_LN("(buff: %s, count: %d)", buff, count);
	if ( (qbuf) && (ibuff) && (count>0) )
	{
		size_t new_total = qbuf->total + count;

		if (new_total > qbuf->max_size)
		{
			DBG_ER_LN("No free memory !!! (new_total: %zd -> %zd)", new_total, qbuf->max_size);
		}
		else
		{
			char *new_buff = SAFE_REALLOC(qbuf->buff, new_total+1);
			if (new_buff == NULL)
			{
				// out of memory
				// qbuf->buff will be free outside
				DBG_ER_LN("SAFE_REALLOC error !!! (total: %zd -> %zd)", qbuf->total, new_total);
				ret = -1;
			}
			else
			{
				new_buff[new_total] = '\0';

				qbuf->buff = new_buff;
				SAFE_MEMCPY( qbuf->buff + qbuf->total, ibuff, count, count);
				qbuf->total = new_total;
				ret = count;
				//DBG_DB_LN("(buff: %s, total: %d, count: %d)", qbuf->buff, qbuf->total, count);
			}
		}
	}
	return ret;
}

size_t qbuf_save(QBUF_t *qbuf, char *filename)
{
	size_t ret = 0;
	if (qbuf)
	{
		ret = file_writer(filename, qbuf_buff(qbuf), qbuf_total(qbuf));
	}
	return ret;
}

void qbuf_free(QBUF_t *qbuf)
{
	if (qbuf)
	{
		SAFE_FREE(qbuf->buff);
		qbuf->total = 0;
	}
}
#endif

#endif


#ifdef UTIL_EX_SYSTEMINFO

#include <sys/utsname.h>
void sys_kernel(Kernel_t *kernel_ctx)
{
	struct utsname uname_ctx;
	uname(&uname_ctx);

	SAFE_SNPRINTF(kernel_ctx->release, (int)sizeof(kernel_ctx->release), "%s version %s", uname_ctx.sysname, uname_ctx.release);
	SAFE_SNPRINTF(kernel_ctx->buildtime, (int)sizeof(kernel_ctx->buildtime), "%s", uname_ctx.version);

	char cmdline[LEN_OF_CMDLINE] = "cat /proc/version";
	char newline[LEN_OF_NEWLINE];

	DBG_TR_LN("enter (%s)", cmdline);

	FILE *fp = SAFE_POPEN(cmdline, "r");
	if (fp)
	{
		if ( SAFE_FGETS(newline, sizeof(newline), fp)!= NULL )
		{
			char *str_b = SAFE_STRCHR(newline,'(');
			char *str_e = SAFE_STRCHR(newline,')');

			if ((str_b) && (str_e) && (str_e >str_b))
			{
				SAFE_SNPRINTF( kernel_ctx->builder, (int)(str_e-str_b), "%s", str_b+1 );
			}
		}
		else
		{
			DBG_ER_LN("SAFE_FGETS error !!! (%s)", cmdline );
		}
		SAFE_PCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_POPEN error !!! (%s)", cmdline );
	}

	DBG_TMP_Y("(release: %s, builder: %s, buildtime: %s)", kernel_ctx->release, kernel_ctx->builder, kernel_ctx->buildtime);
}

#include <sys/types.h>
#include <pwd.h>

const char *sys_username(void)
{
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw)
	{
		return pw->pw_name;
	}

	return "";
}

const char *sys_homedir(void)
{
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if (pw)
	{
		return pw->pw_dir;
	}

	return "";
}

#include <sys/sysinfo.h> // for struct sysinfo 

void sys_info_ex(SysInfoEx_t *info_ctx)
{
	sys_kernel(&info_ctx->kernelinfo);

	{
		struct sysinfo info;
		sysinfo(&info);
		info_ctx->uptime.bootup_t = info.uptime;
		{
			int day, hrs, min, sec;
			time_sec2day(info_ctx->uptime.bootup_t, &day, &hrs, &min, &sec);
			SAFE_SPRINTF_EX(info_ctx->uptime.bootup_fmt, "%02d:%02d:%02d:%02d", day, hrs, min, sec);
		}
		info_ctx->meminfo.mem_unit = info.mem_unit;
		info_ctx->meminfo.totalram = info.totalram;
		info_ctx->meminfo.freeram = info.freeram;	

#ifdef __UCLIBC__
		{
			DBG_ER_LN("(Load average: %f %f %f)", info_ctx->uptime.load[0], info_ctx->uptime.load[1], info_ctx->uptime.load[2]);
		}
#else
		if (getloadavg(info_ctx->uptime.load, 3) != -1)
		{
			DBG_TMP_Y("(Load average: %f %f %f)", info_ctx->uptime.load[0], info_ctx->uptime.load[1], info_ctx->uptime.load[2]);
		}
#endif
	}
}

unsigned long sys_cpu_info(CPUInfo_t *cpuinfo_ctx)
{
	char cmdline[LEN_OF_CMDLINE] = "cat /proc/stat";
	char newline[LEN_OF_NEWLINE];

	DBG_TR_LN("enter (%s)", cmdline);

	FILE *fp = SAFE_POPEN(cmdline, "r");
	if (fp)
	{
		if (SAFE_FGETS(newline, sizeof(newline), fp) != NULL)
		{
			SAFE_SSCANF(newline, "%s %ld %ld %ld %ld", cpuinfo_ctx->name, &cpuinfo_ctx->user, &cpuinfo_ctx->nice, &cpuinfo_ctx->system, &cpuinfo_ctx->idle);
		}
		else
		{
			DBG_ER_LN("SAFE_FGETS error !!! (%s)", cmdline );
		}
		SAFE_PCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_POPEN error !!! (%s)", cmdline );
	}

	unsigned long lasttime = (cpuinfo_ctx->user + cpuinfo_ctx->nice + cpuinfo_ctx->system + cpuinfo_ctx->idle);
	if (cpuinfo_ctx->lasttime == 0)
	{
		cpuinfo_ctx->lasttime = lasttime;
		cpuinfo_ctx->duration = 0;
	}
	else
	{
		cpuinfo_ctx->duration = lasttime - cpuinfo_ctx->lasttime;
	}
	cpuinfo_ctx->lasttime = lasttime;
	return (cpuinfo_ctx->user + cpuinfo_ctx->nice + cpuinfo_ctx->system + cpuinfo_ctx->idle);
}

void sys_mem_purge(int freeram_min)
{
	struct sysinfo sinfo;
	sysinfo(&sinfo);
	
	int freeram_low = ((double)sinfo.freeram/sinfo.totalram) *100;
	if (freeram_low > freeram_min)
	{
		// nothing
		DBG_IF_LN("safe !!! (freeram_percent: %d > %d, %ld, %ld)", freeram_low, freeram_min, sinfo.freeram, sinfo.totalram);
	}
	else
	{
		DBG_IF_LN("purging ... (freeram_percent: %d <= %d, %ld, %ld)", freeram_low, freeram_min, sinfo.freeram, sinfo.totalram);
		SAFE_SYSTEM("sync; echo 3 > /proc/sys/vm/drop_caches");
	}
}

#define PROCESS_ITEM 14
static const char* get_items(const char*buffer ,unsigned int item)
{
	int i = 0;
	const char *p =buffer;

	int len = strlen(buffer);
	int count = 0;
	
	for (i=0; i<len;i++)
	{
		if (' ' == *p)
		{
			count ++;
			if(count == item -1)
			{
				p++;
				break;
			}
		}
		p++;
	}

	return p;
}

unsigned long proc_cpu_info(ProcInfo_t *procinfo_ctx)
{
	char filename[LEN_OF_FULLNAME]="";
	char newline[LEN_OF_NEWLINE];

	if (procinfo_ctx->pid == 0)
	{
		DBG_ER_LN("procinfo_ctx->pid == 0 !!!");
		return 0;
	}

	SAFE_SPRINTF_EX(filename,"/proc/%ld/stat", procinfo_ctx->pid);
	DBG_TR_LN("enter (%s)", filename);

	FILE *fp = SAFE_FOPEN(filename, "r");
	if (fp)
	{
		if ( SAFE_FGETS(newline, sizeof(newline), fp) != NULL )
		{
			const char *q =get_items(newline, PROCESS_ITEM);
			SAFE_SSCANF((char *)q,"%ld %ld %ld %ld", &procinfo_ctx->utime, &procinfo_ctx->stime, &procinfo_ctx->cutime, &procinfo_ctx->cstime);
		}
		else
		{
			DBG_ER_LN("SAFE_FGETS error !!! (file_name: %s)", filename );
		}
		SAFE_FCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_FOPEN error !!! (%s, errno: %d %s)", filename, errno, strerror(errno));
	}

	unsigned long lasttime = (procinfo_ctx->utime + procinfo_ctx->stime + procinfo_ctx->cutime + procinfo_ctx->cstime);
	if (procinfo_ctx->lasttime == 0)
	{
		procinfo_ctx->lasttime = lasttime;
		procinfo_ctx->duration = 0;
	}
	else
	{
		procinfo_ctx->duration = lasttime - procinfo_ctx->lasttime;
	}
	procinfo_ctx->lasttime = lasttime;
	return lasttime;
}

float proc_cpu_usage(ProcInfo_t *procinfo_ctx)
{
	CPUInfo_t cpuinfo;

	memset(&cpuinfo, 0, sizeof(CPUInfo_t));
	sys_cpu_info(&cpuinfo);
	proc_cpu_info(procinfo_ctx);

	usleep(200000);

	sys_cpu_info(&cpuinfo);
	proc_cpu_info(procinfo_ctx);

	procinfo_ctx->cpu_usage = 0.0;
	if ( 0 != cpuinfo.duration)
	{ 
		procinfo_ctx->cpu_usage = 100.0 * (procinfo_ctx->duration)/(cpuinfo.duration);
	}

	return procinfo_ctx->cpu_usage ;
}

void proc_mem_info(ProcInfo_t *procinfo_ctx)
{
	char filename[LEN_OF_FULLNAME]="";
	char newline[LEN_OF_NEWLINE];

	if (procinfo_ctx->pid == 0)
	{
		DBG_ER_LN("procinfo_ctx->pid == 0 !!!");
		return;
	}

	SAFE_SPRINTF_EX(filename, "/proc/%ld/statm", procinfo_ctx->pid);
	DBG_TR_LN("enter (%s)", filename);

	FILE *fp = SAFE_FOPEN(filename, "r");
	if (fp)
	{
		if (SAFE_FGETS(newline, sizeof(newline), fp)!= NULL)
		{
			SAFE_SSCANF(newline, "%ld %ld %ld %ld %ld %ld %ld", &procinfo_ctx->size, &procinfo_ctx->resident, &procinfo_ctx->shared, &procinfo_ctx->text, &procinfo_ctx->lib, &procinfo_ctx->data, &procinfo_ctx->dt);
			procinfo_ctx->size *= 4;
			procinfo_ctx->resident *= 4;
			procinfo_ctx->text *= 4;
			procinfo_ctx->data *= 4;
		}
		else
		{
			DBG_ER_LN("SAFE_FGETS error !!!" );
		}
		SAFE_FCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_FOPEN error !!! (%s, errno: %d %s)", filename, errno, strerror(errno));
	}
}

void proc_fdsize_info(ProcInfo_t *procinfo_ctx)
{
	char cmdline[LEN_OF_CMDLINE] = "";
	char newline[LEN_OF_NEWLINE];

	if (procinfo_ctx->pid == 0)
	{
		DBG_ER_LN("procinfo_ctx->pid == 0 !!!");
		return;
	}

	SAFE_SPRINTF_EX(cmdline,"cat /proc/%ld/status | grep 'Name\\|FDSize'", procinfo_ctx->pid);
	DBG_TR_LN("enter (%s)", cmdline);

	FILE *fp = SAFE_POPEN(cmdline, "r");
	if (fp)
	{
		while((SAFE_FGETS(newline, sizeof(newline), fp)) != NULL)
		{
			char key[32]="";
			char vals[32]="";

			SAFE_SSCANF(newline,"%s %s", key, vals);
			if (key[strlen(key)-1]==':') key[strlen(key)-1] ='\0';
			DBG_TR_LN("(key: %s, vals: %s)", key, vals);

			if (SAFE_STRCMP(key, "Name") ==0)
			{
				SAFE_SPRINTF_EX(procinfo_ctx->name, "%s", vals);
			}
			else if (SAFE_STRCMP(key, "FDSize") ==0)
			{
				procinfo_ctx->fdsize = atol(vals);
			}
			else
			{
				break;
			}
		}
		SAFE_PCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_POPEN error !!! (%s)", cmdline );
	}
}

void proc_fddetail_info(ProcInfo_t *procinfo_ctx)
{
	char cmdline[LEN_OF_CMDLINE] = "";
	char newline[LEN_OF_NEWLINE];

	if (procinfo_ctx->pid == 0)
	{
		DBG_ER_LN("procinfo_ctx->pid == 0 !!! (name: %s)", procinfo_ctx->name);
		return;
	}

	SAFE_SPRINTF_EX(cmdline,"ls -l /proc/%ld/fd", procinfo_ctx->pid);
	DBG_TR_LN("enter (%s)", cmdline);

	FILE *fp = SAFE_POPEN(cmdline, "r");
	if (fp)
	{
		procinfo_ctx->fdcount = 0;
		while((SAFE_FGETS(newline, sizeof(newline), fp)) != NULL)
		{
			DBG_TMP_Y("(newline: %s, %d)", newline, strlen(newline));
			if (strlen(newline)>=56)
			{
				int idx = procinfo_ctx->fdcount;
				SAFE_SSCANF(newline+56,"%d -> %s", &procinfo_ctx->fdinfo[idx].fd, procinfo_ctx->fdinfo[idx].slink);

				DBG_TMP_Y("(newline: %s)", newline+56);
				DBG_TMP_Y("(fd: %d, slink: %s)", procinfo_ctx->fdinfo[idx].fd, procinfo_ctx->fdinfo[idx].slink);
				procinfo_ctx->fdcount ++;
				if (procinfo_ctx->fdcount>=MAX_OF_FDSIZE)
				{
					DBG_ER_LN("procinfo_ctx->fdcount: %ld > MAX_OF_FDSIZE: %d !!!", procinfo_ctx->fdcount, MAX_OF_FDSIZE );
					break;
				}
			}
		}
		SAFE_PCLOSE(fp);
	}
	else
	{
		DBG_ER_LN("SAFE_POPEN error !!! (%s)", cmdline );
	}
}

void proc_info_static(ProcInfo_t *procinfo_ctx)
{
	proc_mem_info(procinfo_ctx);
	proc_fdsize_info(procinfo_ctx);
	proc_fddetail_info(procinfo_ctx);
}

void proc_info(ProcInfo_t *procinfo_ctx)
{
	proc_info_static(procinfo_ctx);
	proc_cpu_usage(procinfo_ctx);
}

unsigned long pidof(char *name)
{
	unsigned long ret = 0;
	DIR* dir;
	struct dirent* ent;
	char* endptr;

	if (!(dir = opendir("/proc")))
	{
		DBG_ER_LN("opendir error !!! (/proc)");
		return ret;
	}

	while ( (ret == 0) && ((ent = readdir(dir)) != NULL) )
	{
		// if endptr is not a null character, the directory is not entirely numeric, so ignore it
		char cmdline[LEN_OF_CMDLINE] = "";
		unsigned long pid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != '\0')
		{
			continue;
		}

		/* try to open the cmdline file */
		SAFE_SNPRINTF(cmdline, (int)sizeof(cmdline), "/proc/%ld/cmdline", pid);
		//DBG_ER_LN(">>>>>>>>> (cmdline: %s)", cmdline);
		FILE* fp = SAFE_FOPEN(cmdline, "r");
		if (fp) 
		{
			if (SAFE_FGETS(cmdline, sizeof(cmdline), fp) != NULL)
			{
				//DBG_ER_LN(">>>>>>>>> (cmdline: %s)", cmdline);
				// check the first token in the file, the program name
				char *saveptr = NULL;
				char *first = SAFE_STRTOK_R(cmdline, " ", &saveptr);

				if ( SAFE_STRRCMP(first, name) == 0 )
				{
					ret = pid;
				}
			}
			SAFE_FCLOSE(fp);
		}
	}

	return ret;
}

#endif

#ifdef UTIL_EX_FASTCGI
char *fastcgi_path_get(char *filename, int port)
{
	static char path[LEN_OF_URL] = "";

	SAFE_MEMSET(path, 0, sizeof(path));
	SAFE_SPRINTF_EX(path, "localhost:%d/%s", port, filename);

	return path;
}
#endif

