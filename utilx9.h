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
#ifndef __UTILX9_H__
#define __UTILX9_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define LIBUTILX9_VERSION 0x02000001


//******************************************************************************
//** include **
//******************************************************************************
#include <inttypes.h>
//#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "basic_def.h"
#include <dirent.h> // DIR
#include <errno.h> // EINVAL
#include <sys/time.h>


//******************************************************************************
//** UTIL_EX_XXX **
//******************************************************************************
//** Linux **
#define UTIL_EX_DBG
#define UTIL_EX_SAFE
#define UTIL_EX_BASIC

#define UTIL_EX_CLIST
#define UTIL_EX_SYSTEMINFO
#define UTIL_EX_LED

#define UTIL_EX_CHAINX
#ifdef UTIL_EX_CHAINX
#define UTIL_EX_MCTT
#endif
#define UTIL_EX_PROC_TABLE
#define UTIL_EX_QUEUEX
#define UTIL_EX_STATEX

#define UTIL_EX_SSL

#define UTIL_EX_JSON

#define UTIL_EX_CURL
#ifdef UTIL_EX_CURL
#define UTIL_EX_CURL
#define UTIL_EX_RTP // Makefile?

#undef UTIL_EX_MXML
#ifdef UTIL_EX_MXML
#define UTIL_EX_ONVIF // Makefile?
#define UTIL_EX_SOAP // Makefile?
#define UTIL_EX_WSDISCOVERY
#endif
#endif

#undef UTIL_EX_SSH
#undef UTIL_EX_SWCONFIG
#define UTIL_EX_UV
#define UTIL_EX_DBUS
#define UTIL_EX_USB
#undef UTIL_EX_UCI
#undef UTIL_EX_UBOX
#undef UTIL_EX_FASTCGI
#undef UTIL_EX_YUAREL
#define UTIL_EX_WEBSOCKETS
#define UTIL_EX_MQTT

#define UTIL_EX_CRON


//******************************************************************************
//** UTIL_EX_DBG **
//******************************************************************************
#ifdef UTIL_EX_DBG
extern int dbg_more;

#define DBG_ER_DUMP(ibuf,ilen,delim,format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_DUMP_COLOR(COLORX_RED, ibuf, ilen, delim, format, ## args)
#define DBG_WN_DUMP(ibuf,ilen,delim,format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_DUMP_COLOR(COLORX_PURPLE, ibuf, ilen, delim, format, ## args)
#define DBG_IF_DUMP(ibuf,ilen,delim,format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_DUMP_COLOR(COLORX_YELLOW, ibuf, ilen, delim, format, ## args)
#define DBG_DB_DUMP(ibuf,ilen,delim,format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_DUMP_COLOR(COLORX_WHITE, ibuf, ilen, delim, format, ## args)
#define DBG_TR_DUMP(ibuf,ilen,delim,format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_DUMP_COLOR(COLORX_LIGHT_GRAY, ibuf, ilen, delim, format, ## args)

#define DBG_ER(format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_R(format, ## args)
#define DBG_ER_0(format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_R_0(format, ## args)
#define DBG_WN(format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_P(format, ## args)
#define DBG_WN_0(format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_P_0(format, ## args)
#define DBG_IF(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_Y(format, ## args)
#define DBG_IF_0(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_Y_0(format, ## args)
#define DBG_DB(format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_W(format, ## args)
#define DBG_DB_0(format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_W_0(format, ## args)
#define DBG_TR(format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_LGR(format, ## args)
#define DBG_TR_0(format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_LGR_0(format, ## args)

#define DBG_ER_LN(format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_LN_R(format, ## args)
#define DBG_ER_LN_0(format,args...) if (dbg_more>=DBG_LVL_ERROR) DBG_LN_R_0(format, ## args)
#define DBG_WN_LN(format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_LN_P(format, ## args)
#define DBG_WN_LN_0(format,args...) if (dbg_more>=DBG_LVL_WARN) DBG_LN_P_0(format, ## args)
#define DBG_IF_LN(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_LN_Y(format, ## args)
#define DBG_IF_LN_0(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_LN_Y_0(format, ## args)
#define DBG_IF_LN_G(format,args...) if (dbg_more>=DBG_LVL_INFO) DBG_LN_LG(format, ## args)
#define DBG_DB_LN(format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_LN_W(format, ## args)
#define DBG_DB_LN_0(format,args...) if (dbg_more>=DBG_LVL_DEBUG) DBG_LN_W_0(format, ## args)
#define DBG_TR_LN(format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_LN_LGR(format, ## args)
#define DBG_TR_LN_0(format,args...) if (dbg_more>=DBG_LVL_TRACE) DBG_LN_LGR_0(format, ## args)

#define ARGC_AND_ARGV_ER_DUMP(s1,s2) if (dbg_more>=DBG_LVL_ERROR) ARGC_AND_ARGV_DUMP_COLOR(COLORX_RED,s1,s2)
#define ARGC_AND_ARGV_WN_DUMP(s1,s2) if (dbg_more>=DBG_LVL_WARN) ARGC_AND_ARGV_DUMP_COLOR(COLORX_PURPLE,s1,s2)
#define ARGC_AND_ARGV_IF_DUMP(s1,s2) if (dbg_more>=DBG_LVL_INFO) ARGC_AND_ARGV_DUMP_COLOR(COLORX_YELLOW,s1,s2)
#define ARGC_AND_ARGV_DB_DUMP(s1,s2) if (dbg_more>=DBG_LVL_DEBUG) ARGC_AND_ARGV_DUMP_COLOR(COLORX_WHITE,s1,s2)
#define ARGC_AND_ARGV_TR_DUMP(s1,s2) if (dbg_more>=DBG_LVL_TRACE) ARGC_AND_ARGV_DUMP_COLOR(COLORX_LIGHT_GRAY,s1,s2)

#define DBG_IF_LLADDR(format, addr, args...) \
		DBG_IF_LN(format, ## args); \
		DBG_IF_LN(" >> (%02x:%02x:%02x:%02x:%02x:%02x)", \
			((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5])

#define DBG_IF_ADDR(format, addr, port, args...) \
		DBG_IF_LN(format, ## args); \
		DBG_IF_LN(" >> (%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d)", \
			((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15], port)

#define DBG_DB_ADDR(format, addr, port, args...) \
	DBG_DB_LN(format, ## args); \
	DBG_DB_LN(" (%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d)", \
		((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15], port)

#define DBG_TR_ADDR(format, addr, port, args...) \
			DBG_TR_LN(format, ## args); \
			DBG_TR_LN(" (%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d)", \
				((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15], port)

#define DBG_IF_ADDR_PLUS(format, addr, port, addr2, port2, args...) \
		DBG_IF_LN(format, ## args); \
		DBG_IF_LN(" >> (%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d -> %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d)", \
			((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15], port, \
			((uint8_t *)addr2)[0], ((uint8_t *)addr2)[1], ((uint8_t *)addr2)[2], ((uint8_t *)addr2)[3], ((uint8_t *)addr2)[4], ((uint8_t *)addr2)[5], ((uint8_t *)addr2)[6], ((uint8_t *)addr2)[7], ((uint8_t *)addr2)[8], ((uint8_t *)addr2)[9], ((uint8_t *)addr2)[10], ((uint8_t *)addr2)[11], ((uint8_t *)addr2)[12], ((uint8_t *)addr2)[13], ((uint8_t *)addr2)[14], ((uint8_t *)addr2)[15], port2)

#define DBG_DB_ADDR_PLUS(format, addr, port, addr2, port2, args...) \
	DBG_DB_LN(format, ## args); \
	DBG_DB_LN(" >> (%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d -> %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d)", \
		((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15], port, \
		((uint8_t *)addr2)[0], ((uint8_t *)addr2)[1], ((uint8_t *)addr2)[2], ((uint8_t *)addr2)[3], ((uint8_t *)addr2)[4], ((uint8_t *)addr2)[5], ((uint8_t *)addr2)[6], ((uint8_t *)addr2)[7], ((uint8_t *)addr2)[8], ((uint8_t *)addr2)[9], ((uint8_t *)addr2)[10], ((uint8_t *)addr2)[11], ((uint8_t *)addr2)[12], ((uint8_t *)addr2)[13], ((uint8_t *)addr2)[14], ((uint8_t *)addr2)[15], port2)

#define DBG_TR_ADDR_PLUS(format, addr, port, addr2, port2, args...) \
	DBG_TR_LN(format, ## args); \
	DBG_TR_LN(" >> (%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d -> %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x %d)", \
		((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15], port, \
		((uint8_t *)addr2)[0], ((uint8_t *)addr2)[1], ((uint8_t *)addr2)[2], ((uint8_t *)addr2)[3], ((uint8_t *)addr2)[4], ((uint8_t *)addr2)[5], ((uint8_t *)addr2)[6], ((uint8_t *)addr2)[7], ((uint8_t *)addr2)[8], ((uint8_t *)addr2)[9], ((uint8_t *)addr2)[10], ((uint8_t *)addr2)[11], ((uint8_t *)addr2)[12], ((uint8_t *)addr2)[13], ((uint8_t *)addr2)[14], ((uint8_t *)addr2)[15], port2)

#define DBG_LN_LN() printf("\n")

int dbg_lvl_round(void);
int dbg_lvl_set(int lvl);
int dbg_lvl_get(void);
#endif


//******************************************************************************
//** UTIL_EX_SAFE **
//******************************************************************************
#ifdef UTIL_EX_SAFE
#include <fcntl.h> // fcntl
#include <sys/ioctl.h> // ioctl

#include <assert.h>
#define ASSERT assert

time_t expiration_date(void);
void* pcheck( void* a );

#define POINTER_CHECK(x) \
		if (x==NULL) { \
			DBG_ER_LN("%s is NULL !!!", XSTR(x) ); \
			return; \
		}

#define SIZE_X size_t

#define SAFE_MIN(x,y) ({ typeof(x) _x = (x); typeof(y) _y = (y); (void) (&_x == &_y); _x < _y ? _x : _y; })
#define SAFE_MAX(x,y) ({ typeof(x) _x = (x); typeof(y) _y = (y); (void) (&_x == &_y); _x > _y ? _x : _y; })

#define SAFE_ARRAY_SIZE(array) (sizeof(array) / sizeof *(array))

#define SAFE_FREE(X) \
	do { if ( (X) != NULL ) {free(X); X=NULL;} } while(0)

#define SAFE_CALLOC(nitems, size) \
	({ void *__ret = NULL; \
		do { \
			__ret = (void *)calloc(nitems, size); \
		} while(0); \
		__ret; \
	})
#define SAFE_MALLOC(size) \
	({ void *__ret = NULL; \
		do { \
			__ret = (void*)malloc(size); \
			if (__ret) memset(__ret, 0, size); \
		} while(0); \
		__ret; \
	})
#define SAFE_REALLOC(ptr, size) \
	({ void *__ret = NULL; \
		do { \
			__ret = (void*)realloc(ptr, size); \
		} while(0); \
		__ret; \
	})

#define SAFE_MEMCPY(dst, src, count, maxcount) \
	({ void *__ret = NULL; do { if ( (pcheck(dst)) && (pcheck(src)) ) { __ret = memcpy(dst, src, SAFE_MIN((SIZE_X)count, (SIZE_X)maxcount)); } } while(0); __ret; })
#define SAFE_MEMSET(s,c,n) \
	({ void *__ret = NULL; do { if (pcheck(s)) { __ret = memset(s, c, n); } } while(0); __ret; })
#define SAFE_MEMCHR(s,c,n) \
	({ char *__ret = NULL; do { if (pcheck(s)) { __ret = memchr(s, c, n); } } while(0); __ret; })
#define SAFE_MEMRCHR(s,c,n) \
	({ char *__ret = NULL; do { if (pcheck(s)) { __ret = memrchr(s, c, n); } } while(0); __ret; })
#define SAFE_MEMMOVE(dst,src,n) \
	({ void *__ret = NULL; do { if ( (pcheck(dst)) && (pcheck(src)) && (n)) { __ret = memmove(dst, src, n); } } while(0); __ret; })
#define SAFE_MEMCMP(s1,s2,n) \
	({ int __ret = -1; do { if ( (pcheck(s1)) && (pcheck(s2)) && (n)) { __ret = memcmp(s1, s2, n); } } while(0); __ret; })
#define SAFE_MEMMEM(s1,n1,s2,n2) \
	({ void *__ret = NULL; do { if ( (pcheck(s1)) && (n1) && (pcheck(s2)) && (n2) && (n1>=n2)) { __ret = memmem(s1, n1, s2, n2); } } while(0); __ret; })

/** string **/
#define SAFE_STRLEN(X) \
	({ size_t __ret =0; do { if (pcheck(X)) __ret = strlen(X); else DBG_ER_LN("%s is NULL !!!", #X); } while(0); __ret; })
#define SAFE_SPRINTF(X, FMT, args...) \
	({ int __ret =0; do { if (pcheck(X)) __ret = sprintf(X, FMT, ## args); else DBG_ER_LN("%s is NULL !!!", #X); } while(0); __ret; })
#define SAFE_SPRINTF_EX(X, FMT, args...) \
	({ int __ret =0; do { if (pcheck(X)) __ret = snprintf(X, sizeof(X), FMT, ## args); else DBG_ER_LN("%s is NULL !!!", #X); } while(0); __ret; })
#define SAFE_SNPRINTF(X, Y, FMT, args...) \
	({ int __ret =0; do { if ((pcheck(X)) && (Y>0)) __ret = snprintf(X, Y, FMT, ## args); else DBG_ER_LN("%s is NULL or Y (%zd <= 0) !!!", #X, (size_t)Y); } while(0); __ret; })

#define SAFE_ASPRINTF(X, FMT, args...) \
	({ int __ret =0; \
		do { \
			__ret = asprintf(&X, FMT, ## args); \
		} while(0); \
		__ret; \
	})

#define SAFE_STRCAT(str1, str2) \
	({ char *__ret = NULL; do { if ( (pcheck(str1)) && (pcheck(str2)) ) { __ret = strcat(str1, str2); } } while(0); __ret; })
#define SAFE_STRCAT_EX(str, args...) \
	({ char *__ret = NULL; do { if (pcheck(str)) { __ret = str_cat_ex(str, ## args, NULL); } } while(0); __ret; })


// #define SAFE_STRTOK(str, delim) strtok(str, delim) // please don't use this, not thread safe
#define SAFE_STRTOK_R(str, delim, saveptr) strtok_r(str, delim, saveptr)
#define SAFE_STRSTR(str1, str2) \
	({ char *__ret = NULL; do { if ((pcheck(str1)) && pcheck(str2)) { __ret = strstr(str1, str2); } } while(0); __ret; })
#define SAFE_STRCASESTR(str1, str2) \
	({ char *__ret = NULL; do { if ((pcheck(str1)) && pcheck(str2)) { __ret = strcasestr(str1, str2); } } while(0); __ret; })

//#define SAFE_STRCASESTR(str1, str2) strcasestr(str1, str2)
#define SAFE_STRCMP(str1, str2) \
	({ int __ret = -1; do { if ((pcheck(str1)) && pcheck(str2)) { __ret = strcmp(str1, str2); } } while(0); __ret; })
#define SAFE_STRNCMP(str1, str2, n) \
	({ int __ret = -1; do { if ((pcheck(str1)) && pcheck(str2) && (n)) { __ret = strncmp(str1, str2, n); } } while(0); __ret; })
#define SAFE_STRRCMP(str1, str2) \
	({ int __ret = -1; do { if ((pcheck(str1)) && pcheck(str2) && (strlen(str1) >= strlen(str2))) { __ret = strcmp(str1+strlen(str1)-strlen(str2), str2); } } while(0); __ret; })

#define SAFE_STRCHR(str, c) \
	({ char *__ret = NULL; do { if (pcheck(str)) { __ret = strchr(str, c); } } while(0); __ret; })
#define SAFE_STRRCHR(str, c) \
	({ char *__ret = NULL; do { if (pcheck(str)) { __ret = strrchr(str, c); } } while(0); __ret; })

#define SAFE_STRSEP(str, delim) \
		({ char *__ret = NULL; do { if (pcheck(str)) { __ret = strsep(&str, delim); } } while(0); __ret; })

#define SAFE_SSCANF(str, args...) \
	({ int __ret =0; do { if (pcheck(str)) { __ret = sscanf(str, ## args); } } while(0); __ret; })
#define SAFE_FSCANF(stream, args...) \
	({ int __ret =0; do { if (stream) { __ret = fscanf(stream, ## args); } } while(0); __ret; })

/** select **/
#define SAFE_FCNTL(s, args...) fcntl(s, ## args)
#define SAFE_IOCTL(s, args...) ioctl(s, ## args)
#define SAFE_FD_CLR(fd, fds_p) FD_CLR(fd, fds_p)
#define SAFE_FD_ISSET(fd, fds_p) FD_ISSET(fd, fds_p)
#define SAFE_FD_SET(fd, fds_p) FD_SET(fd, fds_p)
#define SAFE_FD_ZERO(fds_p) FD_ZERO(fds_p)

#define SAFE_FD_SET_EX(fd, fds_p) \
	do { \
		if (pcheck(fds_p)) \
		{ \
			SAFE_FD_ZERO(fds_p); \
			SAFE_FD_SET(fd, fds_p); \
		} \
	} while(0)

#include <sys/select.h>

#define SAFE_SELECT(nfds, fdrset_p, fdwset_p, fdeset_p, timeout) select(nfds, fdrset_p, fdwset_p, fdeset_p, timeout)
#define SAFE_SELECT_EX(fd, fdrset_p, fdwset_p, fdeset_p, msec) select_ex(fd, fdrset_p, fdwset_p, fdeset_p, msec)

int select_ex(int fd, fd_set *fdrset_p, fd_set *fdwset_p, fd_set *fdeset_p, int msec);

/** read/write **/
#define SAFE_WRITE(fd, buf, count) \
		({ size_t __ret = 0; do { if (pcheck(buf)) { __ret = write(fd, buf, count); } } while(0); __ret; })
#define SAFE_READ(fd, buf, count) \
		({ size_t __ret = 0; do { if (pcheck(buf)) { __ret = read(fd, buf, count); } } while(0); __ret; })

#define SAFE_FWRITE(ptr, count, num, stream) \
	({ size_t __ret = 0; do { if ((stream) && (pcheck(ptr))) { __ret = fwrite(ptr, count, num, stream); } } while(0); __ret; })
#define SAFE_FREAD(ptr, count, num, stream) \
	({ size_t __ret = 0; do { if ((stream) && (pcheck(ptr))) { __ret = fread(ptr, count, num, stream); } } while(0); __ret; })

#define SAFE_FPUTS(ptr, stream) \
	({ int __ret = 0; do { if ((stream) && (pcheck(ptr))) { __ret = fputs(ptr, stream); } } while(0); __ret; })
#define SAFE_FGETS(ptr, size, stream) \
	({ char *__ret = NULL; do { if ((stream) && (pcheck(ptr))) { __ret = fgets(ptr, size, stream); } } while(0); __ret; })

#define SAFE_FSYNC(x) do { if (x>=0) { fsync(x);} } while(0)
#define SAFE_FFLUSH(x) do { if (x>=0) { fflush(x);} } while(0)
#define SAFE_STDOUT_FFLUSH() SAFE_FFLUSH(stdout)
#define SAFE_STDOUT_LINE() do { setvbuf(stdout,NULL,_IOLBF,0); } while(0)
#define SAFE_STDOUT_NONE() do { setvbuf(stdout,NULL,_IONBF,0); } while(0)

/** seek **/
#define SAFE_FTELL(stream) \
	({ long __ret =0; do { if (stream) { __ret = ftell(stream); } } while(0); __ret; })

#define SAFE_FSEEK_SET(stream, offset) \
	({ int __ret =0; do { if (stream) { __ret = fseek(stream, offset, SEEK_SET); } } while(0); __ret; })
#define SAFE_FSEEK_CUR(stream, offset) \
	({ int __ret =0; do { if (stream) { __ret = fseek(stream, offset, SEEK_CUR); } } while(0); __ret; })
#define SAFE_FSEEK_END(stream, offset) \
	({ int __ret =0; do { if (stream) { __ret = fseek(stream, offset, SEEK_END); } } while(0); __ret; })

/** open/close **/
#define SAFE_OPEN(path, args...) \
	({ int __ret =0; do { if (pcheck(path)) { __ret = open(path, ## args); } } while(0); __ret; })
#define SAFE_CLOSE(x) \
	do { if (x>=0) { close(x); x=-1;} } while(0)

#define SAFE_FOPEN(path, mode) \
	({ FILE *__ret = NULL; do { if (pcheck(path)) { __ret = fopen(path, mode); } } while(0); __ret; })
#define SAFE_FCLOSE(x) do { if ((x) != NULL) {fclose(x); x=NULL;} } while(0)

#define SAFE_POPEN(command, mode) \
	({ FILE *__ret = NULL; do { if (pcheck(command)) { __ret = popen(command, mode); } } while(0); __ret; })
#define SAFE_PCLOSE(x) do { if ((x) != NULL) {pclose(x); x=NULL;} } while(0)

#define SAFE_FILENO(fp) \
	({ int __ret =0; do { if (pcheck(fp)) { __ret = fileno(fp); } } while(0); __ret; })

#if (0)
#define SAFE_SYSTEM(FMT, args...) \
	({ int __ret =0; \
		do { \
			char cmdline[LEN_OF_CMDLINE] = ""; \
			snprintf(cmdline, LEN_OF_CMDLINE, FMT, ## args); \
			__ret = system(cmdline); \
		} while(0); \
		__ret; \
	})
#else
#define SAFE_SYSTEM(FMT, args...) system_ex(FMT, ## args)
#endif

#define SAFE_STRTOL(str) \
	({ long  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>2) && (strncasecmp(str, "0x", 2)==0)) { __ret = strtol(str, NULL, 16); } else { __ret=strtol(str, NULL, 10); } } while(0); __ret; })
#define SAFE_STRTOLL(str) \
	({ long long  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>2) && (strncasecmp(str, "0x", 2)==0)) { __ret = strtoll(str, NULL, 16); } else { __ret=strtoll(str, NULL, 10); } } while(0); __ret; })
#define SAFE_STRTOD(str) \
		({ double  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>2) && (strncasecmp(str, "0x", 2)==0)) { __ret = strtod(str, NULL, 16); } else { __ret=strtod(str, NULL, 10); } } while(0); __ret; })

#define SAFE_STRTOL_EX(str, endptr) \
	({ long  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>2) && (strncasecmp(str, "0x", 2)==0)) { __ret = strtol(str, &endptr, 16); } else { __ret=strtol(str, &endptr, 10); } } while(0); __ret; })
#define SAFE_STRTOLL_EX(str, endptr) \
	({ long long  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>2) && (strncasecmp(str, "0x", 2)==0)) { __ret = strtoll(str, &endptr, 16); } else { __ret=strtoll(str, &endptr, 10); } } while(0); __ret; })
#define SAFE_STRTOD_EX(str, endptr) \
	({ double  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>2) && (strncasecmp(str, "0x", 2)==0)) { __ret = strtod(str, &endptr, 16); } else { __ret=strtod(str, &endptr, 10); } } while(0); __ret; })

#define SAFE_ATOI(str) \
	({ int  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>0)) { __ret = atoi(str); } } while(0); __ret; })
#define SAFE_ATOL(str) \
	({ long  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>0)) { __ret = atol(str); } } while(0); __ret; })
#define SAFE_ATOF(str) \
	({ double  __ret =0; do { if ((pcheck(str)) && (strlen((const char *)str)>0)) { __ret = atof(str); } } while(0); __ret; })

//** thread & lock **
#include <pthread.h>
#include <semaphore.h>

#define SAFE_THREAD_LOCK(in_mtx_p) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(in_mtx_p)) \
			{ \
				__ret = pthread_mutex_lock(in_mtx_p); \
				if ( __ret != 0 ) \
				{ \
					DBG_ER_LN("pthread_mutex_lock error !!! (__ret: %d, EINVAL: %d, EBUSY: %d, EAGAIN: %d, EDEADLK: %d, EPERM: %d)", __ret, EINVAL, EBUSY, EAGAIN, EDEADLK, EPERM); \
				} \
			} \
		} while(0); \
		__ret; \
	})
#define SAFE_THREAD_TRYLOCK(in_mtx_p) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(in_mtx_p)) \
			{ \
				__ret = pthread_mutex_trylock(in_mtx_p); \
				if ( __ret != 0 ) \
				{ \
					DBG_ER_LN("pthread_mutex_trylock error !!! (__ret: %d, EINVAL: %d, EBUSY: %d, EAGAIN: %d, EDEADLK: %d, EPERM: %d)", __ret, EINVAL, EBUSY, EAGAIN, EDEADLK, EPERM); \
				} \
			} \
		} while(0); \
		__ret; \
	})
#define SAFE_THREAD_UNLOCK(in_mtx_p) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(in_mtx_p)) \
			{ \
				__ret = pthread_mutex_unlock(in_mtx_p); \
				if ( __ret != 0 ) \
				{ \
					DBG_ER_LN("pthread_mutex_unlock error !!! (__ret: %d, EINVAL: %d, EBUSY: %d, EAGAIN: %d, EDEADLK: %d, EPERM: %d)", __ret, EINVAL, EBUSY, EAGAIN, EDEADLK, EPERM); \
				} \
			} \
		} while(0); \
		__ret; \
	})
#define SAFE_THREAD_SIGNAL(in_cond_p) pthread_cond_signal(in_cond_p)
#define SAFE_THREAD_BROADCAST(in_cond_p) pthread_cond_broadcast(in_cond_p)
#define SAFE_THREAD_DETACH(tid) pthread_detach(tid)
#define SAFE_THREAD_JOIN(tid) \
	({ int __ret = EINVAL; \
		do { \
			if ( tid != 0 ) \
			{ \
				pthread_join(tid, NULL); \
				tid = 0; \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_WAIT(in_cond_p, in_mtx_p) pthread_cond_wait(in_cond_p, in_mtx_p)

#define SAFE_SEMAPHORE_INIT(ptr) sem_init(&ptr->semaphore, 0, 0)
#define SAFE_SEMAPHORE_WAIT(ptr) sem_wait(&ptr->semaphore)
#define SAFE_SEMAPHORE_POST(ptr) sem_post(&ptr->semaphore)
#define SAFE_SEMAPHORE_DESTROY(ptr) sem_destroy(&ptr->semaphore)
#define SAFE_SEMAPHORE_GETVALUE(ptr, val) sem_getvalue(&ptr->semaphore, val)

#define SAFE_MUTEX_DESTROY(in_mtx_p) \
		({ int __ret = EINVAL; \
			do { \
				__ret = pthread_mutex_destroy(in_mtx_p); \
			} while(0); \
			__ret; \
		})

#define SAFE_MUTEX_DESTROY_EX(ptr) SAFE_MUTEX_DESTROY(&ptr->in_mtx)

#ifdef PTHREAD_MUTEX_RECURSIVE_NP
#define PTHREAD_MUTEX_RECURSIVE_X PTHREAD_MUTEX_RECURSIVE_NP
#else
#define PTHREAD_MUTEX_RECURSIVE_X PTHREAD_MUTEX_RECURSIVE
#endif

// we can lock/unlock the mutex more than once at the same thread
#define SAFE_MUTEX_ATTR_RECURSIVE(in_mtx) \
	({ int __ret = EINVAL; \
		do { \
			pthread_mutexattr_t in_attr; \
			int rc = pthread_mutexattr_init(&in_attr); \
			if (rc==0) \
			{ \
				pthread_mutexattr_settype (&in_attr, PTHREAD_MUTEX_RECURSIVE_X); \
				__ret = pthread_mutex_init(&in_mtx, &in_attr); \
				pthread_mutexattr_destroy(&in_attr); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_COND_DESTROY(in_cond_p) \
	({ int __ret = EINVAL; \
		do { \
			__ret = pthread_cond_destroy(in_cond_p); \
		} while(0); \
		__ret; \
	})
	
#define SAFE_COND_DESTROY_EX(ptr) SAFE_COND_DESTROY(&ptr->in_cond)

#define SAFE_COND_ATTR_CLOCK(in_cond) \
	({ int __ret = EINVAL; \
		do { \
			pthread_condattr_t in_attr; \
			int rc = pthread_condattr_init(&in_attr); \
			if (rc==0) \
			{ \
				pthread_condattr_setclock(&in_attr, CLOCK_MONOTONIC); \
				__ret = pthread_cond_init(&in_cond, &in_attr); \
				pthread_condattr_destroy(&in_attr); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_COND_ATTR_NORMAL(in_cond) \
	({ int __ret = EINVAL; \
		do { \
			__ret = pthread_cond_init(&in_cond, NULL); \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_TIMEWAIT(in_cond_p, in_mtx_p, msec) \
	({ int __ret = EINVAL; \
		do { \
			struct timeval now; \
			struct timespec next; \
			gettimeofday(&now, NULL); \
			long long nsec = now.tv_usec * 1000 + (msec % 1000) * 1000 * 1000; \
			next.tv_sec = now.tv_sec + nsec / (1000*1000*1000) + msec / 1000; \
			next.tv_nsec = nsec % (1000*1000*1000); \
			__ret = pthread_cond_timedwait(in_cond_p, in_mtx_p, &next); \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_TIMEWAIT_CLOCK(in_cond_p, in_mtx_p, msec) \
	({ int __ret = EINVAL; \
		do { \
			struct timespec now; \
			struct timespec next; \
			clock_gettime(CLOCK_MONOTONIC, &now); \
			next.tv_sec = now.tv_sec + msec/1000; \
			next.tv_nsec = now.tv_nsec + (msec%1000)*1000000; \
			long tv_sec = (next.tv_nsec/1000000000); \
			if (tv_sec>= 1) \
			{\
				next.tv_sec+=tv_sec; \
				next.tv_nsec%=1000000000; \
			} \
			__ret = pthread_cond_timedwait(in_cond_p, in_mtx_p, &next); \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_CREATE(tid, attr, cb, data) \
	({ int __ret = EINVAL; \
		do { \
			__ret = pthread_create(&tid, attr, cb, data); \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_LOCK_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if ( ptr->tid != 0 ) \
				{ \
					__ret = SAFE_THREAD_LOCK(&ptr->in_mtx); \
					if (__ret!=0) DBG_ER_LN("(name: %s)", ptr->name); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_TRYLOCK_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if ( ptr->tid != 0 ) \
				{ \
					__ret = SAFE_THREAD_TRYLOCK(&ptr->in_mtx); \
					if (__ret!=0) DBG_ER_LN("(name: %s)", ptr->name); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_UNLOCK_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if ( ptr->tid != 0 ) \
				{ \
					__ret = SAFE_THREAD_UNLOCK(&ptr->in_mtx); \
					if (__ret!=0) DBG_ER_LN("(name: %s)", ptr->name); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_SIGNAL_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if ( ptr->tid != 0 ) \
				{ \
					__ret = SAFE_THREAD_SIGNAL(&ptr->in_cond); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_BROADCAST_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if ( ptr->tid != 0 ) \
				{ \
					__ret = SAFE_THREAD_BROADCAST(&ptr->in_cond); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_LEAVE(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if ( 0 == SAFE_THREAD_LOCK_EX(ptr) ) \
				{ \
					ptr->isexit = 1; \
					ptr->isquit = 1; \
					ptr->isloop = 0; \
					SAFE_THREAD_UNLOCK_EX(ptr); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_DETACH_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			ptr->isexit = 0; \
			ptr->isloop = 1; \
			if ( (pcheck(ptr)) && (ptr->in_detach) ) \
			{ \
				__ret = SAFE_THREAD_DETACH( pthread_self() ); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_DETACH_CHECK(ptr) \
	({ int __ret = EINVAL; \
		do { \
			ptr->isexit = 0; \
			ptr->isloop = 1; \
			if ( (pcheck(ptr)) && (ptr->in_detach) ) \
			{ \
				__ret = SAFE_THREAD_DETACH( pthread_self() ); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_JOIN_EX(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if ( (pcheck(ptr)) && (ptr->in_detach==0) ) \
			{ \
				__ret = SAFE_THREAD_JOIN( ptr->tid ); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_JOIN_CHECK(ptr) \
	({ int __ret = EINVAL; \
		do { \
			if (pcheck(ptr)) \
			{ \
				if  (ptr->in_detach==0) \
				{ \
					__ret = SAFE_THREAD_JOIN( ptr->tid ); \
				} \
				else \
				{ \
					int retry = 20; \
					while ( (ptr->isexit==0) && (retry>0) ) \
					{ \
						retry--; \
						usleep(100*1000); \
					} \
				} \
				ptr->tid = 0; \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_THREAD_WAIT_EX(ptr) SAFE_THREAD_WAIT(&ptr->in_cond, &ptr->in_mtx)
#define SAFE_THREAD_TIMEWAIT_EX(ptr, msec) SAFE_THREAD_TIMEWAIT(&ptr->in_cond, &ptr->in_mtx, msec)
#define SAFE_THREAD_TIMEWAIT_CLOCK_EX(ptr, msec) SAFE_THREAD_TIMEWAIT_CLOCK(&ptr->in_cond, &ptr->in_mtx, msec)

#define SAFE_THREAD_CREATE_EX(ptr, attr, cb, data) \
	({ int __ret =0; \
		do { \
		SAFE_THREAD_JOIN(ptr->tid); \
		__ret = SAFE_THREAD_CREATE(ptr->tid, attr, cb, data); \
		} while(0); \
		__ret; \
	})

#define USE_THREAD_CLOCK

typedef void *(*thread_fn) (void *);

typedef struct ThreadX_Struct
{
	char name[LEN_OF_NAME32];

	pthread_t tid;
	pthread_mutex_t in_mtx;
	pthread_cond_t in_cond;

	sem_t semaphore;
	int in_detach;

	int isexit;
	int isfree;
	int isloop;
	int ispause;
	int isquit;

	thread_fn thread_cb;
	void *data;
} ThreadX_t;

void threadx_mutex_init(ThreadX_t *tidx_req);
void threadx_mutex_free(ThreadX_t *tidx_req);

int threadx_isloop(ThreadX_t *tid_req);
int threadx_ispause(ThreadX_t *tid_req);
void threadx_set_pause(ThreadX_t *tidx_req, int flag);
int threadx_isquit(ThreadX_t *tid_req);
void threadx_set_quit(ThreadX_t *tidx_req, int flag);
int threadx_isready(ThreadX_t *tidx_req, int retry);

int threadx_lock(ThreadX_t *tid_req);
int threadx_unlock(ThreadX_t *tid_req);

int threadx_timewait(ThreadX_t *tid_req, int ms);
int threadx_timewait_simple(ThreadX_t *tidx_req, int ms);

int threadx_wait(ThreadX_t *tid_req);
int threadx_wait_simple(ThreadX_t *tidx_req);

void threadx_wakeup(ThreadX_t *tidx_req);
void threadx_wakeup_simple(ThreadX_t *tid_req);

void threadx_leave(ThreadX_t *tidx_req);
int threadx_detach(ThreadX_t *tidx_req);
int threadx_join(ThreadX_t *tidx_req);
void threadx_stop(ThreadX_t *tid_req);
void threadx_close(ThreadX_t *tid_req);
int threadx_init(ThreadX_t *tid_req, char *name);

#endif


//******************************************************************************
//** UTIL_EX_BASIC **
//******************************************************************************
#ifdef UTIL_EX_BASIC
char *version_show(void);

int system_ex(char *fmt, ...);

char *str_cat_ex(char *str, ...);
int str_isnum(const char *str);
char *str_rtrim(char *str);
char *str_ltrim(char *str);
char *str_trim(char *str);
char *str_trim_char(char *str, const char *delim, int delim_len);
void str_toupper(char *str);
void str_tolower(char *str);

uint32_t byte2big_endian(uint8_t size, uint8_t *data);
void big_endian2byte(uint8_t size, uint32_t val, uint8_t *data);

uint32_t byte2little_endian(uint8_t size, uint8_t *data);
void little_endian2byte(uint8_t size, uint32_t val, uint8_t *data);

char *bin2hex(const unsigned char *bin, int len);
int hexs2bin(const char *hex, unsigned char **out);

int URLEncode(const char *str, const int strsz, char *result, const int resultsz);
int URLDecode(const char *str, const int strsz, char *result, const int resultsz, const char **last_pos);

uint8_t buff_crc8_xor(uint8_t *start, uint8_t *buf, int len);

unsigned short buff_crc16_add(unsigned char b, unsigned short acc);
unsigned short buff_crc16(const unsigned char *buf, int len, unsigned short acc);

unsigned long buff_crc32( const void *buf, unsigned long size,unsigned long crc);

#define BB_LITTLE_ENDIAN 1
unsigned short buf_cksum(unsigned short *addr, int nleft);

char *time_now_full(time_t now_t);
char *time_now_short(time_t now_t);
double time_diff_secs(time_t end_t, time_t start_t);
double time_diff_mins(time_t end_t, time_t start_t);
double time_diff_hours(time_t end_t, time_t start_t);
double time_diff_days(time_t end_t, time_t start_t);
double time_diff_weeks(time_t end_t, time_t start_t);

#define SAFE_ACCESS(filename, mode) \
	({ int __ret =0; do { if (pcheck(filename)) { __ret = access(filename, mode); } } while(0); __ret; })

int file_exe_chk(char *filename);
int file_slink(char *filename);
int file_spath(char *filename, char *spath, int length);
char *file_path(char *filename, char *actualpath);
size_t file_append(char *filename, char *buf, int wantsize);
size_t file_writer(char *filename, char *buf, int wantsize);
char *file_reader(char *filename, int *filesize);
int file_copy(const char *from, const char *to);

// 0: get next the new line, others: stop/break
typedef int (*newline_lookup_fn)(char *newline, void *arg);
void file_lookup(char *filename, newline_lookup_fn lookup_cb, void *arg);
void pfile_lookup(char *cmdline, newline_lookup_fn lookup_cb, void *arg);

char *os_random_uuid(char *buf, int buf_len);
char *os_urandom(int byte_count);
#ifdef UTIL_EX_SSL
char *sec_base64_enc(char *input, int length, int *enc_len);
char *sec_base64_dec(char *input, int length, int *dec_len);

int sec_aes_cbc_enc(char *in, char *out, char *aes_key);
char *sec_aes_cbc_enc_ascii(char *in, int in_len, char *aes_key);
char *sec_aes_cbc_enc_base(char *in, int in_len, char *aes_key);
int sec_aes_cbc_dec(char *in, char *out, int out_len, char *aes_key);
int sec_aes_cbc_dec_base(char *in, char *out, int out_len, char *aes_key);
#endif

#define UTIL_EX_BASIC_QBUF

#ifdef UTIL_EX_BASIC_QBUF
#define MAX_OF_QBUF_1KB (1*1024) // 1KB
#define MAX_OF_QBUF_2KB (2*1024) // 2KB
#define MAX_OF_QBUF_1MB (1*1024*1024) // 1MB
#define MAX_OF_QBUF_2MB (2*1024*1024) // 2MB
#define MAX_OF_QBUF_4MB (4*1024*1024) // 4MB
#define MAX_OF_QBUF_8MB (8*1024*1024) // 8MB

typedef struct QBUF_Struct
{
	size_t total;
	size_t max_size;
	char *buff;
} QBUF_t;

void qbuf_init(QBUF_t *qbuf, size_t max_size);
size_t qbuf_total(QBUF_t *qbuf);
char *qbuf_endptr(QBUF_t *qbuf);
char *qbuf_buff(QBUF_t *qbuf);
char *qbuf_jumprchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr);
char *qbuf_jumpchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr);
char *qbuf_memchr(QBUF_t *qbuf, char c, char *jumpptr);
char *qbuf_memmem(QBUF_t *qbuf, char *needle, size_t needlelen, char *jumpptr);
char *qbuf_strstr(QBUF_t *qbuf, char *substr, char *jumpptr);
char *qbuf_pop(QBUF_t *qbuf);
int qbuf_trimrchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr);
int qbuf_trimchr(QBUF_t *qbuf, const char *delim, int delim_len, char *jumpptr);
int qbuf_shiftrstr(QBUF_t *qbuf, char *substr);
int qbuf_shiftstr(QBUF_t *qbuf, char *substr);
int qbuf_read(QBUF_t *qbuf, char *obuff, size_t count);
int qbuf_write(QBUF_t *qbuf, char *ibuff, size_t count);
size_t qbuf_save(QBUF_t *qbuf, char *filename);
void qbuf_free(QBUF_t *qbuf);
#endif

#endif


//******************************************************************************
//** UTIL_EX_CLIST **
//******************************************************************************
#ifdef UTIL_EX_CLIST
// copy from contiki\core\lib\list.c and list.h
// to rename list to clist because list is a popular name
#define CLIST_CONCAT2(s1, s2) s1##s2
#define CLIST_CONCAT(s1, s2) CLIST_CONCAT2(s1, s2)

/**
 * Declare a linked list.
 *
 * This macro declares a linked list with the specified \c type. The
 * type \b must be a structure (\c struct) with its first element
 * being a pointer. This pointer is used by the linked list library to
 * form the linked lists.
 *
 * The list variable is declared as static to make it easy to use in a
 * single C module without unnecessarily exporting the name to other
 * modules.
 *
 * \param name The name of the list.
 */
#define CLIST(name) \
	static void *CLIST_CONCAT(name,_list) = NULL; \
	static clist_t name = (clist_t)&CLIST_CONCAT(name,_list)

/**
 * Declare a linked list inside a structure declaraction.
 *
 * This macro declares a linked list with the specified \c type. The
 * type \b must be a structure (\c struct) with its first element
 * being a pointer. This pointer is used by the linked list library to
 * form the linked lists.
 *
 * Internally, the list is defined as two items: the list itself and a
 * pointer to the list. The pointer has the name of the parameter to
 * the macro and the name of the list is a concatenation of the name
 * and the suffix "_list". The pointer must point to the list for the
 * list to work. Thus the list must be initialized before using.
 *
 * The list is initialized with the LIST_STRUCT_INIT() macro.
 *
 * \param name The name of the list.
 */
#define CLIST_STRUCT(name) \
         void *CLIST_CONCAT(name,_list); \
         clist_t name

/**
 * Initialize a linked list that is part of a structure.
 *
 * This macro sets up the internal pointers in a list that has been
 * defined as part of a struct. This macro must be called before using
 * the list.
 *
 * \param struct_ptr A pointer to the struct
 * \param name The name of the list.
 */
#define CLIST_STRUCT_INIT(struct_ptr, name)                              \
    do {                                                                \
       (struct_ptr)->name = &((struct_ptr)->CLIST_CONCAT(name,_list));   \
       (struct_ptr)->CLIST_CONCAT(name,_list) = NULL;                    \
       clist_init((struct_ptr)->name);                                   \
    } while(0)

/**
 * The linked list type.
 *
 */
typedef void ** clist_t;

void clist_init(clist_t list);
void *clist_head(clist_t list);
void *clist_tail(clist_t list);

void clist_push(clist_t list, void *item);
void clist_add(clist_t list, void *item);

void *clist_chop(clist_t list);
void *clist_pop(clist_t list);

void clist_remove(clist_t list, void *item);

int  clist_length(clist_t list);

void clist_copy(clist_t dest, clist_t src);

void clist_insert(clist_t list, void *previtem, void *newitem);

void *clist_item_next(void *item);

typedef int (*clist_item_filter_fn)(void *item);
int clist_filter_ex(clist_t list, clist_item_filter_fn filter_cb);

int clist_contains(clist_t list, void *item);

typedef void (*clist_item_free_fn)(void *item);

void clist_pop_ex(clist_t list, clist_item_free_fn free_cb);
void clist_free_ex(clist_t list, clist_item_free_fn free_cb);
void clist_free(clist_t list);
#endif


//******************************************************************************
//** UTIL_EX_SYSTEMINFO **
//******************************************************************************
#ifdef UTIL_EX_SYSTEMINFO
#define MIN_PERCENTAGE_OF_FREE_MEMORY 25

// /proc/version
typedef struct Kernel_STRUCT
{
	char release[LEN_OF_VAL1024];
	char builder[LEN_OF_VAL1024];
	char buildtime[LEN_OF_VAL128];
} Kernel_t;


// /proc/uptime
typedef struct Uptime_STRUCT
{
	long bootup_t;
	char bootup_fmt[LEN_OF_VAL32];

	double load[MAX_OF_OVERLOAD];
} Uptime_t;

// /proc/meminfo
typedef struct MemInfo_STRUCT
{
	unsigned int mem_unit;

	unsigned long totalram;
	unsigned long freeram;
#if (0)
	unsigned long Buffers;
	unsigned long Cached;
	int SwapCached;
	int Active;
	int Inactive;
	int Active_anon;
	int Inactive_anon;
	int Active_file;
	int Inactive_file;
	int Unevictable;
	int Mlocked;
	int SwapTotal;
	int SwapFree;
	int Dirty;
	int Writeback;
	int AnonPages;
	int Mapped;
	int Shmem;
	int Slab;
	int SReclaimable;
	int SUnreclaim;
	int KernelStack;
	int PageTables;
	int NFS_Unstable;
	int Bounce;
	int WritebackTmp;
	int CommitLimit;
	int Committed_AS;
	int VmallocTotal;
	int VmallocUsed;
	int VmallocChunk;
#endif
} MemInfo_t;

//
typedef struct SysInfoX_STRUCT
{
	Kernel_t kernelinfo;
	MemInfo_t meminfo;
	Uptime_t uptime;
} SysInfoX_t;

// /proc/stat
typedef struct
{
	char name[LEN_OF_NAME_CPU];

	unsigned long duration;
	unsigned long lasttime;

	unsigned long user;
	unsigned long nice;
	unsigned long system;
	unsigned long idle;
} CPUInfo_t;

typedef struct
{
	int fd;
	char slink[LEN_OF_SLINK];
} FDInfo_t;

// /proc/xxx/statm
// https://my.oschina.net/aiguozhe/blog/125477
typedef struct
{
	char name[LEN_OF_NAME_PROC];

	unsigned long pid;
	float cpu_usage;
	unsigned long size; // VmSize, kB, total program size (same as VmSize in /proc/[pid]/status)
	unsigned long resident; // VmRSS, kB, resident set size (same as VmRSS in /proc/[pid]/status)
	unsigned long shared; // RssFile + RssShmem, kB, shared pages (i.e., backed by a file)
	unsigned long text; // VmExe, kB (code)
	unsigned long lib; // (unused in Linux 2.6)
	unsigned long data; // VmData + VmStk, kB
	unsigned long dt; // (unused in Linux 2.6)

	unsigned long duration;
	unsigned long lasttime;
	unsigned long utime;  //user time
	unsigned long stime;  //kernel time
	unsigned long cutime; //all user time
	unsigned long cstime; //all dead time

	// /proc/18077/status
	unsigned long fdsize; // Number of file descriptor slots currently allocated. 32*n or 64*n
	unsigned long fdcount;
	FDInfo_t fdinfo[MAX_OF_FDSIZE];
}	ProcInfo_t;

void sys_kernel(Kernel_t *kernel_req);

const char *sys_username(void);
const char *sys_homedir(void);

void sys_info_ex(SysInfoX_t *infox_req);
unsigned long sys_cpu_info(CPUInfo_t *cpuinfox_req);
void sys_mem_purge(int freeram_min);

unsigned long proc_cpu_info(ProcInfo_t *procinfo_req);
float proc_cpu_usage(ProcInfo_t *procinfo_req);
void proc_mem_info(ProcInfo_t *procinfo_req);
void proc_fdsize_info(ProcInfo_t *procinfo_req);
void proc_fddetail_info(ProcInfo_t *procinfo_req);
void proc_info_static(ProcInfo_t *procinfo_req);
void proc_info(ProcInfo_t *procinfo_req);

unsigned long pidof(char *name);

#endif


//******************************************************************************
//** UTIL_EX_LED **
//******************************************************************************
#ifdef UTIL_EX_LED

#define MAX_OF_LEDON 40
#define TICK_OF_LEDON_10 10 // 10 m-seconds
#define TICK_OF_LEDON_100 100 // 100 m-seconds

#define LED_VAL_1 "1"
#define LED_VAL_0 "0"

#define SAFE_LED_CLOSE(x) \
	do { \
		led_thread_close(x); \
		x = NULL; \
	} while(0)

typedef enum
{
	LED_ID_NONE = 0,
	LED_ID_1,
	LED_ID_2,
	LED_ID_3,
	LED_ID_4,
	LED_ID_5,
	LED_ID_6,
	LED_ID_7,
	LED_ID_8,
	LED_ID_MAX,
} LED_ID;

typedef enum
{
	LED_ACTION_ID_OFF = 0,
	LED_ACTION_ID_ON,
	LED_ACTION_ID_USB,

	LED_ACTION_ID_UER1,
	LED_ACTION_ID_UER2,
	LED_ACTION_ID_UER3,
	LED_ACTION_ID_UER4,
	LED_ACTION_ID_UER5,
	LED_ACTION_ID_UER6,
	LED_ACTION_ID_UER7,
	LED_ACTION_ID_UER8,
	LED_ACTION_ID_UER9,
	LED_ACTION_ID_UER10,

	LED_ACTION_ID_MAX,
} LED_ACTION_ID;

typedef void (*led_on_fn)(void *usr_data);

typedef struct LedOn_Struct
{
	LED_ID id;
	LED_ACTION_ID action;
	int duration; // m-seconds
} LedOn_t;

typedef struct LedRequest_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isfree;
	int infinite;

	int max_led;
	LedOn_t *ledon_ary;

	led_on_fn led_on_cb;
} LedRequest_t;

void led_gosleep(LedRequest_t *ledreq);
void led_wakeup_simple(LedRequest_t *ledreq);

void led_thread_stop(LedRequest_t *ledreq);
void led_thread_close(LedRequest_t *ledreq);
LedRequest_t *led_thread_init(char *name, int infinite, LedOn_t *ledon_ary, led_on_fn led_on_cb);

#endif


//******************************************************************************
//** UTIL_EX_CURL **
//******************************************************************************
#ifdef UTIL_EX_CURL
#include <curl/curl.h>

#define VAL_OF_CURLOPT_VERBOSE (dbg_more/DBG_LVL_TRACE)

#define MAX_OF_CURL_CONNECTTIMEOUT 20L
#define MAX_OF_CURL_TIMEOUT 300L

typedef enum
{
	HTTP_METHOD_ID_POST = 0,
	HTTP_METHOD_ID_GET,
	HTTP_METHOD_ID_PUT,
	HTTP_METHOD_ID_MAX,
} HTTP_METHOD_ID;

typedef enum
{
	HTTP_MODE_ID_SIMPLE,
	HTTP_MODE_ID_UPLOADFILE,
	HTTP_MODE_ID_DOWNLOAFILE_NORMAL,
	HTTP_MODE_ID_DOWNLOAFILE_MJPEG,
	HTTP_MODE_ID_DOWNLOAFILE_RTSP,
	HTTP_MODE_ID_SOAP,
	HTTP_MODE_ID_MAX,
} HTTP_MODE_ID;

typedef struct HeaderList_STRUCT
{
	void* next;

	const char *value;
} HeaderList;

typedef struct SimpleRequest_STRUCT
{
	size_t res_size;
	char *response;

	HTTP_METHOD_ID method; // 0: POST, 1: GET, 2: PUT
	size_t req_pos;
	size_t req_size;
	char *request; // please alloc
	struct curl_slist *headers;

} SimpleRequest_t;

typedef struct SoapRequest_STRUCT
{
	size_t res_size;
	char *response;

	HTTP_METHOD_ID method; // 0: POST, 1: GET, 2: PUT
	size_t req_pos;
	size_t req_size;
	char *request; // please alloc
	struct curl_slist *headers;

	char *h_action;
} SoapRequest_t;

typedef struct FileRequest_STRUCT
{
	size_t res_size;
	char *response;

	HTTP_METHOD_ID method; // 0: POST, 1: GET, 2: PUT
	size_t req_pos;
	size_t req_size;
	char *request; // please alloc
	struct curl_slist *headers;

	size_t max_filesize;
	char filename[LEN_OF_FULLNAME];
	FILE *fp;

	int progress;
} FileRequest_t;

typedef enum
{
	MJPEG_STATE_ID_BOUNDARY,
	MJPEG_STATE_ID_TYPE,
	MJPEG_STATE_ID_TYPE_0D0A,
	MJPEG_STATE_ID_LENGTH,
	MJPEG_STATE_ID_LENGTH_0D0A,
	MJPEG_STATE_ID_STUPID_0D0A,
	MJPEG_STATE_ID_BODY,
	MJPEG_STATE_ID_MAX,
} MJPEG_STATE_ID;

typedef struct MJPEGRequest_STRUCT
{
	size_t max_size;
	char filename[LEN_OF_FULLNAME];
	FILE *fp;

	char prefixname[LEN_OF_DIRNAME];
	int maxfiles;

	int num;

	QBUF_t qbuf;
	char boundary[LEN_OF_VAL32];
	char ctype[LEN_OF_VAL32];
	int clength;

	char ftype[LEN_OF_VAL32];
	int flength;
	MJPEG_STATE_ID state;
} MJPEGRequest_t;

#define MAX_OF_RTSP_TRACK 2
typedef struct RTSPRequest_STRUCT
{
	size_t max_size;
	char filename[LEN_OF_FULLNAME];
	FILE *fp;
	int duration; // seconds

	int rtp_port; // to get from rtp_port=78700~78798
	int interleaved;
	int stop;

	int progress;
	int CSeq;
	int no_of_track;
	char track[MAX_OF_RTSP_TRACK][LEN_OF_VAL32];
	char session[LEN_OF_VAL32];
	QBUF_t qoption;
	QBUF_t qdescribe;

	void *rtp_req;
} RTSPRequest_t;

typedef struct HttpX_STRUCT
{
	HTTP_MODE_ID mode;
	CURL *curl;
	char url[LEN_OF_URL];
	int port;
	char *user;
	char *password;

	int result;
	char log[LEN_OF_LOG];

	union
	{
		SimpleRequest_t simple_req;
		FileRequest_t file_req;
		SoapRequest_t soap_req;

		MJPEGRequest_t mjpeg_req;
		RTSPRequest_t rtsp_req;
	};
} HttpX_t;

typedef void (*http_response_fn)(void *userdata, size_t res_size, char *response);

void http_connect_timeout_set(HttpX_t *http_req, int timeout);
void http_timeout_set(HttpX_t *http_req, int timeout);
void http_request_stop(HttpX_t *http_req);

void http_request_free(HttpX_t *http_req);
int http_request(HttpX_t *http_req);

int http_upload(const char *url, const char *filename);
int http_upload_with_response(const char *url, const char *filename, void *userdata, http_response_fn cb);

int http_simple(const char *url, HTTP_METHOD_ID method, struct curl_slist *http_simple, size_t req_size, char *request, void *userdata, http_response_fn cb);

#endif


//******************************************************************************
//** UTIL_EX_SOAP **
//******************************************************************************
#ifdef UTIL_EX_SOAP
#include "mxml.h"

#define SOAP_XML_NULL ""

#define ONVIF_XML_BODY "<?xml version='1.0' encoding='utf-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\" xmlns:trt=\"http://www.onvif.org/ver10/media/wsdl\" xmlns:tt=\"http://www.onvif.org/ver10/schema\"><SOAP-ENV:Body/></SOAP-ENV:Envelope>"
//#define ONVIF_XML_GETHOSTNAME "<?xml version='1.0' encoding='utf-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\"><SOAP-ENV:Body><tds:GetHostname/></SOAP-ENV:Body></SOAP-ENV:Envelope>"
#define ONVIF_XML_GETCAPABILITIES "<?xml version='1.0' encoding='utf-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\"><SOAP-ENV:Body><tds:GetCapabilities><tds:Category>All</tds:Category></tds:GetCapabilities></SOAP-ENV:Body></SOAP-ENV:Envelope>"
#define ONVIF_XML_GETSERVICES "<?xml version='1.0' encoding='utf-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\"><SOAP-ENV:Body><tds:GetServices><tds:IncludeCapability>false</tds:IncludeCapability></tds:GetServices></SOAP-ENV:Body></SOAP-ENV:Envelope>"
//#define ONVIF_XML_GETPROFILES "<?xml version='1.0' encoding='utf-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:trt=\"http://www.onvif.org/ver10/media/wsdl\"><SOAP-ENV:Body><trt:GetProfiles/></SOAP-ENV:Body></SOAP-ENV:Envelope>"
#define ONVIF_XML_GETSNAPSHOTURI "<?xml version='1.0' encoding='utf-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:trt=\"http://www.onvif.org/ver10/media/wsdl\"><SOAP-ENV:Body><trt:GetSnapshotUri><trt:ProfileToken>Profile00Token</trt:ProfileToken></trt:GetSnapshotUri></SOAP-ENV:Body></SOAP-ENV:Envelope>"
#define ONVIF_XML_GETSTREAMURI "<?xml version='1.0' encoding='UTF-8'?><SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:tt=\"http://www.onvif.org/ver10/schema\" xmlns:trt=\"http://www.onvif.org/ver10/media/wsdl\"><SOAP-ENV:Body><trt:GetStreamUri><trt:StreamSetup><tt:Stream>RTP-Unicast</tt:Stream><tt:Transport><tt:Protocol>RTSP</tt:Protocol></tt:Transport></trt:StreamSetup><trt:ProfileToken>profile1</trt:ProfileToken></trt:GetStreamUri></SOAP-ENV:Body></SOAP-ENV:Envelope>"

#define WSD_XML_PROBE_DEVICE "<?xml version='1.0' encoding='utf-8'?><s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"><s:Header><a:Action s:mustUnderstand=\"1\">http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</a:Action><a:MessageID>uuid:bd77953d-2069-40b2-82ee-b81a4b007277</a:MessageID><a:ReplyTo><a:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:To s:mustUnderstand=\"1\">urn:schemas-xmlsoap-org:ws:2005:04:discovery</a:To></s:Header><s:Body><Probe xmlns=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\"><d:Types xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\" xmlns:dp0=\"http://www.onvif.org/ver10/device/wsdl\">dp0:Device</d:Types></Probe></s:Body></s:Envelope>"
#define WSD_XML_PROBE_NETWORKVIDEOTRANSMITTER "<?xml version='1.0' encoding='utf-8'?><s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"><s:Header><a:Action s:mustUnderstand=\"1\">http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</a:Action><a:MessageID>uuid:1b897826-55b9-464d-9b34-d36f0a776cb3</a:MessageID><a:ReplyTo><a:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:To s:mustUnderstand=\"1\">urn:schemas-xmlsoap-org:ws:2005:04:discovery</a:To></s:Header><s:Body><Probe xmlns=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\"><d:Types xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\" xmlns:dp0=\"http://www.onvif.org/ver10/network/wsdl\">dp0:NetworkVideoTransmitter</d:Types></Probe></s:Body></s:Envelope>"
#define WSD_XML_PROBE_NETWORKVIDEODISPLAY "<?xml version='1.0' encoding='utf-8'?><s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"><s:Header><a:Action s:mustUnderstand=\"1\">http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</a:Action><a:MessageID>uuid:501fbe60-d3f2-4978-9b41-e8a3bc2acb4f</a:MessageID><a:ReplyTo><a:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:To s:mustUnderstand=\"1\">urn:schemas-xmlsoap-org:ws:2005:04:discovery</a:To></s:Header><s:Body><Probe xmlns=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\"><d:Types xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\" xmlns:dp0=\"http://www.onvif.org/ver10/network/wsdl\">dp0:NetworkVideoDisplay</d:Types></Probe></s:Body></s:Envelope>"

#define soap_node_t mxml_node_t

typedef enum
{
	SOAP_ACTION_ID_GETCOMMON,

	// device
	SOAP_ACTION_ID_DEVICE_GETCAPABILITIES,
	SOAP_ACTION_ID_DEVICE_GETDEVICEINFORMATION,
	SOAP_ACTION_ID_DEVICE_GETHOSTNAME,
	SOAP_ACTION_ID_DEVICE_GETNETWORKINTERFACES,
	SOAP_ACTION_ID_DEVICE_GETSERVICES,
	SOAP_ACTION_ID_DEVICE_GETSCOPES,

	// media
	SOAP_ACTION_ID_MEDIA_GETPROFILES,
	SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI,
	SOAP_ACTION_ID_MEDIA_GETSTREAMURI,

	SOAP_ACTION_ID_PROBE_DEVICE,
	SOAP_ACTION_ID_PROBE_NETWORKVIDEOTRANSMITTER,
	SOAP_ACTION_ID_PROBE_NETWORKVIDEODISPLAY,

	SOAP_ACTION_ID_MAX,
} SOAP_ACTION_ID;

typedef struct SoapX_STRUCT SoapX_t;
typedef void (*soap_parse_fn)(SoapX_t *soap);

typedef struct SoapX_STRUCT
{
	//HttpX_t *http_req;

	soap_node_t *request_node;
	soap_node_t *response_node;
} SoapX_t;

char *soap_element_2string(soap_node_t *parent_node);
void soap_element_dump(soap_node_t *parent_node);
const char *soap_element_name(soap_node_t *parent_node);
void soap_element_print(soap_node_t *curr_node);
void soap_element_save(soap_node_t *parent_node, char *filename);
soap_node_t *soap_element_fetch(soap_node_t *parent_node, const char *ns, const char *element, const char *attr, const char *value);
const char *soap_element_attr(soap_node_t *parent_node, const char  *name);
void soap_element_attr_set(soap_node_t *parent_node, const char *name, const char  *value);
const char *soap_element_text(soap_node_t *parent_node, int *whitespace);
void soap_element_text_new(soap_node_t *parent_node, int whitespace, const char *string);
void soap_element_text_set(soap_node_t *parent_node, int whitespace, const char *string);
soap_node_t *soap_element_next_sibling(soap_node_t *parent_node);
soap_node_t *soap_element_1st_child(soap_node_t *parent_node);

soap_node_t *soap_element_add(soap_node_t *parent_node, const char *name);
void soap_element_remove(soap_node_t *parent_node);
void soap_element_delete(soap_node_t *parent_node);

soap_node_t *soap_load_file(char *filename);
soap_node_t *soap_load_string(char *xmlbuffer);
void soap_load_request(SoapX_t *soap, char *action);

void soap_http_access(SoapX_t *soap, HttpX_t *http_req);
void soap_free(SoapX_t *soap);
SoapX_t *soap_create(char *xmlbuffer);
#endif


//******************************************************************************
//** UTIL_EX_CHAINX **
//******************************************************************************
#ifdef UTIL_EX_CHAINX
//** Linux **
#include <netinet/in.h> // fro struct sockaddr_in
#ifdef UTIL_EX_SSL
#define UTIL_EX_SOCKET_OPENSSL

#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#define SOCKET_SSL_DEBUG(x) ERR_print_errors_fp( stderr );

#define IFACE_NAME_STA "apcli0"
#define IFACE_NAME_AP "ra0"
#define IFACE_NAME_LAN "eth2.2"
#define IFACE_NAME_BR "br0"

#define UTIL_EX_SOCKET_CERT_TXT
//#define UTIL_EX_SOCKET_CERT_FILE
#define UTIL_EX_SOCKET_NOBLOCK
//#define UTIL_EX_SOCKET_BIND_DEV
#define UTIL_EX_TTY

#define TIMEOUT_OF_SOCKET     10
#define TIMEOUT_OF_SSL        2
#define TIMEOUT_OF_RETRY_HOLD 60
#define TIMEOUT_OF_SELECT_10  10
#define TIMEOUT_OF_SELECT_5   5
#define TIMEOUT_OF_SELECT_1   1
#define TIMEOUT_OF_SELECT_0   0

#define MIN_TIMEOUT_OF_SELECT 1
#define MIN_TIMEOUT_OF_RETRY  3
#define RETRY_OF_SSL          5

#define WS_DISCOVERY_IPV6     "FF02::C"
#define WS_DISCOVERY_IPV4     "239.255.255.250"
#define WS_DISCOVERY_PORT     3702

#define SAFE_SOPEN(domain, type, protocol) socket(domain, type, protocol)
//#define SAFE_SCLOSE(x) do { if (x>=0) {shutdown(x, SHUT_RDWR); close(x); x=-1;} } while(0)
#define SAFE_SCLOSE(x) SAFE_CLOSE(x)
#define SAFE_SSETOPT(s, level, optname, opval, optlen) setsockopt(s, level, optname, opval, optlen)
#define SAFE_SGETOPT(s, level, optname, opval, optlen) getsockopt(s, level, optname, opval, optlen)

#define SAFE_CONNECT(s, name, namelen) connect(s, name, namelen)
#define SAFE_BIND(s, name, namelen) bind(s, name, namelen)

#define CHAINX_FDSET_R(x) x->fdrset
#define CHAINX_FDSET_W(x) x->fdwset
#define CHAINX_FDSET_E(x) x->fdeset

#define CHAINX_FD_CLR_R(x) SAFE_FD_CLR(chainX_fd_get(x), &CHAINX_FDSET_R(x))
#define CHAINX_FD_CLR_W(x) SAFE_FD_CLR(chainX_fd_get(x), &CHAINX_FDSET_W(x))
#define CHAINX_FD_CLR_E(x) SAFE_FD_CLR(chainX_fd_get(x), &CHAINX_FDSET_E(x))

#define CHAINX_FD_ISSET_R(x) SAFE_FD_ISSET(chainX_fd_get(x), &CHAINX_FDSET_R(x))
#define CHAINX_FD_ISSET_W(x) SAFE_FD_ISSET(chainX_fd_get(x), &CHAINX_FDSET_W(x))
#define CHAINX_FD_ISSET_E(x) SAFE_FD_ISSET(chainX_fd_get(x), &CHAINX_FDSET_E(x))

typedef enum
{
	CHAINX_MODE_ID_TCP_CLIENT,
	CHAINX_MODE_ID_TCP_SERVER,
	CHAINX_MODE_ID_UDP_CLIENT,
	CHAINX_MODE_ID_UDP_SERVER,
	CHAINX_MODE_ID_MULTI_SENDER,
	CHAINX_MODE_ID_MULTI_RECEIVER,
	CHAINX_MODE_ID_NETLINK,
#ifdef UTIL_EX_TTY
	CHAINX_MODE_ID_TTY,
#endif
	CHAINX_MODE_ID_PING,
	CHAINX_MODE_ID_MAX,
} CHAINX_MODE_ID;

typedef struct ChainX_STRUCT ChainX_t;

typedef void (*chainX_pipe_fn)(ChainX_t *chainX_req, char *buff, int buff_len);
typedef void (*chainX_post_fn)(ChainX_t *chainX_req, char *buff, int buff_len);
#ifdef UTIL_EX_TTY
typedef void (*chainX_serial_fn)(ChainX_t *chainX_req, char *buff, int buff_len);
#endif
typedef void (*chainX_netlink_fn)(ChainX_t *chainX_req, char *ifname, int index, char *status);
typedef void (*chainX_linked_fn)(ChainX_t *chainX_req);

typedef struct Addr_STRUCT
{
	char ipv4[LEN_OF_IP];
	char ipv6[LEN_OF_IP];
	char hostname[LEN_OF_HOSTNAME32];
} Addr_t;

typedef struct NetworkInfo_STRUCT
{
	char uuid[LEN_OF_UUID];
	union
	{
		char url[LEN_OF_URL];
		Addr_t addr;
	};
	int port;
	char user[LEN_OF_USER];
	char pass[LEN_OF_PASS];

	union
	{ // must < 32, for 1.x, it needs to save to flash with the fixed size.
		char reserve[LEN_OF_RESERVE32];
		char reversename[LEN_OF_HOSTNAME32];
	};
} NetworkInfo_t;

#ifdef UTIL_EX_TTY
#include <termios.h>

typedef struct TtyInfo_STRUCT
{
	char ttyname[LEN_OF_NAME_DEV];

	int isset;
	struct termios options;
	struct termios options_bak;

	int speed;
	int databits;
	int stopbits;
	int parity;
} TtyInfo_t;
#endif

typedef struct ChainX_STRUCT
{
	ThreadX_t tidx;

	int isfree;
	int status;

	CHAINX_MODE_ID mode;
	union
	{
		NetworkInfo_t netinfo;
#ifdef UTIL_EX_TTY
		TtyInfo_t ttyinfo;
#endif
	};

	union
	{
		int sockfd;
#ifdef UTIL_EX_TTY
		int ttyfd;
#endif
	};
	fd_set fdrset;
	fd_set fdwset;
	fd_set fdeset;

	int security; // for tcp, 0: normal(default), 1: security
	int noblock; // for tcp, udp

	int retry_hold;
	int select_wait; // seconds

	union
	{
		chainX_pipe_fn pipe_cb; // for tcp client
		chainX_post_fn post_cb;
#ifdef UTIL_EX_TTY
		chainX_serial_fn serial_cb;
#endif
		chainX_netlink_fn netlink_cb; // for netlink
	};
	chainX_linked_fn linked_cb;

#ifdef UTIL_EX_SOCKET_OPENSSL
	SSL_CTX *ctxSSL;
	SSL *cSSL;
#elif defined (UTIL_EX_SOCKET_MBEDTLS)
	mbedtls_net_context server_fd;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_ssl_context ssl;
	mbedtls_ssl_config conf;
	mbedtls_x509_crt cacert;
	mbedtls_x509_crt clicert;
	mbedtls_pk_context pkey;

	int auth;
#endif

#ifdef UTIL_EX_SOCKET_CERT_TXT
	const unsigned char *certificate_txt;
	size_t certificate_txt_size;
	const unsigned char *privatekey_txt;
	size_t privatekey_txt_size;
	const unsigned char *ca_txt;
	size_t ca_txt_size;
#elif defined (UTIL_EX_SOCKET_CERT_FILE)
	char certificate_file[LEN_OF_FULLNAME];
	char privatekey_file[LEN_OF_FULLNAME];
	char ca_file[LEN_OF_FULLNAME];
#endif

	int infinite; // for post, ping
	int recycle; // for post, ping
	int verbose; // for ping

	struct sockaddr_in addr_to;
	struct sockaddr_in addr_frm;

	void *c_data; // for soap or ...
	char session[LEN_OF_VAL48]; // > LEN_OF_UUID
} ChainX_t;

#ifndef IF_NAMESIZE
#define IF_NAMESIZE 16
#endif
void chainX_addr2ipstr(int family, void *sinx_addr, char *ipstr, int len);

int chainX_dns_get(char *dns);

int chainX_if_staticip(char *iface, char *ip, char *netmask, char *gateway);

typedef void (*chainX_if_list_fn)(char *ifa_name, int ifa_flags, int family, char *host, char *netmask);

int chainX_if_list(chainX_if_list_fn list_cb);

int chainX_if_ipaddr(char *iface, char *ip, int ip_len);
int chainX_if_netmask(char *iface, char *netmask, int netmask_len);
int chainX_if_broadcast(char *iface, char *broadcast, int broadcast_len);
int chainX_if_gateway(char *iface, char *gateway, int gateway_len);
int chainX_if_hwaddr(char *iface, char *mac, int mac_len, char *split);
int chainX_if_ssid(char *iface, char *ssid, int ssid_len);

int chainX_fd_get(ChainX_t *chainX_req);

int chainX_port_get(ChainX_t *chainX_req);
int chainX_port_set(ChainX_t *chainX_req, int port);
int chainX_ip_len(ChainX_t * chainX_req);
char *chainX_ip_get(ChainX_t *chainX_req);
void chainX_ip_set(ChainX_t *chainX_req, char *ip);
struct sockaddr_in *chainX_addr_to_get(ChainX_t *chainX_req);
int chainX_addr_to_set_ex(ChainX_t *chainX_req, int ai_family, char *ip_addr, int port);
int chainX_addr_to_set(ChainX_t *chainX_req, char *ipv4, int port);
struct sockaddr_in *chainX_addr_from_get(ChainX_t *chainX_req);
char *chainX_hostname_get(ChainX_t *chainX_req);
void chainX_hostname_set(ChainX_t *chainX_req, char *hostname);

int chainX_reversename_len(ChainX_t *chainX_req);
char *chainX_reversename_get(ChainX_t *chainX_req);
void chainX_reversename_set(ChainX_t *chainX_req, char *hostname);

int chainX_security_get(ChainX_t *chainX_req);
int chainX_security_set(ChainX_t *chainX_req, int mode);

int chainX_recycle_get(ChainX_t *chainX_req);
int chainX_recycle_dec(ChainX_t *chainX_req);
int chainX_recycle_set(ChainX_t *chainX_req, int recycle);

int chainX_infinite_get(ChainX_t *chainX_req);
int chainX_infinite_set(ChainX_t *chainX_req, int infinite);

int chainX_nslookup_ex(char *hostname, int ai_family, char *ipv4_addr, int ipv4_len, char *ipv6_addr, int ipv6_len);
int chainX_nslookup6(char *hostname , char *ip, int ip_len);
int chainX_nslookup(char *hostname , char *ip, int ip_len);
int chainX_nslookup_reverse(char *ip_addr, char *hostname, int hostname_len);

int chainX_quit_check(ChainX_t *chainX_req);
void chainX_quit_set(ChainX_t *chainX_req, int is_quit);

int chainX_linked_check(ChainX_t *chainX_req);

void chainX_wakeup_simple(ChainX_t *chainX_req);
int chainX_timewait_simple(ChainX_t *chainX_req, int ms);

void chainXssl_certificate_file(ChainX_t *chainX_req, char *filename);
void chainXssl_privatekey_file(ChainX_t *chainX_req, char *filename);
void chainXssl_ca_file(ChainX_t *chainX_req, char *filename);
#ifdef UTIL_EX_SOCKET_OPENSSL
SSL *chainXssl_sslfd_get(ChainX_t *chainX_req);
int chainXssl_cert_readbuf(SSL_CTX *ctxSSL, const unsigned char *buff, size_t len );
int chainXssl_key_readbuf(SSL_CTX *ctxSSL, const unsigned char *buff, size_t len );
#elif defined(UTIL_EX_SOCKET_MBEDTLS)
mbedtls_ssl_context *chainXssl_sslfd_get(ChainX_t *chainX_req);
#endif

void chainX_close(ChainX_t *chainX_req);
int chainX_multi_sender(ChainX_t *chainX_req, char *buffer, int nbufs);
int chainX_multi_sender_and_post(ChainX_t *chainX_req, char *buffer, int nbufs);

void chainX_linked_register(ChainX_t *chainX_req, chainX_linked_fn cb);
#ifdef UTIL_EX_TTY
char *chainX_tty_getname(ChainX_t *chainX_req);
void chainX_tty_setname(ChainX_t *chainX_req, char *ttyname);
void chainX_tty_setbaudrate(ChainX_t *chainX_req, int baudrate);
void chainX_tty_setparity(ChainX_t *chainX_req, char parity);
void chainX_tty_setdatabits(ChainX_t *chainX_req, char databits);

void chainX_serial_register(ChainX_t *chainX_req, chainX_serial_fn cb);
#endif
void chainX_post_register(ChainX_t *chainX_req, chainX_post_fn cb);
void chainX_pipe_register(ChainX_t *chainX_req, chainX_pipe_fn cb);
void chainX_netlink_register(ChainX_t *chainX_req, chainX_netlink_fn cb);

void chainX_thread_stop(ChainX_t *chainX_req);
void chainX_thread_close(ChainX_t *chainX_req);
int chainX_thread_init(ChainX_t *chainX_req);

int chainX_ping(ChainX_t *chainX_req);

#ifdef UTIL_EX_SOCKET_OPENSSL
#define SOCKETX_READ(req, wbuff, wlen) \
	({ int __ret = 0; \
		do { \
			if (pcheck(wbuff)) \
				if (chainX_security_get(req) == 1 ) __ret = SSL_read(chainXssl_sslfd_get(req), wbuff, wlen); else __ret = read(chainX_fd_get(req), wbuff, wlen); \
			else \
				__ret = 0; \
		} while(0); \
		__ret; \
	})

#define SOCKETX_WRITE(req, wbuff, wlen)	\
	({ int __ret = 0; \
		do { \
			if (pcheck(wbuff)) \
				if (chainX_security_get(req) == 1 ) __ret = SSL_write(chainXssl_sslfd_get(req), wbuff, wlen); else __ret = write(chainX_fd_get(req), wbuff, wlen); \
			else \
				__ret = 0; \
		} while(0); \
		__ret; \
	})

#elif defined (UTIL_EX_SOCKET_MBEDTLS)

#define SOCKETX_READ(req, wbuff, wlen) \
	({ int __ret = 0; \
		do { \
			if (pcheck(wbuff)) \
				if (chainX_security_get(req) == 1 ) __ret = mbedtls_ssl_read(chainXssl_sslfd_get(req), (unsigned char *)wbuff, wlen); else	 __ret = read(chainX_fd_get(req), wbuff, wlen); \
			else \
				__ret = 0; \
		} while(0); \
		__ret; \
	})

#define SOCKETX_WRITE(req, wbuff, wlen)	\
	({ int __ret = 0; \
		do { \
			if (pcheck(wbuff)) \
				if (chainX_security_get(req) == 1 ) __ret = mbedtls_ssl_write(chainXssl_sslfd_get(req), (const unsigned char *)wbuff, wlen); else __ret = write(chainX_fd_get(req), wbuff, wlen); \
			else \
				__ret = 0; \
		} while(0); \
		__ret; \
	})

#else

#define SOCKETX_READ(req, wbuff, wlen) \
	({ int __ret = 0; \
		do { \
			if (pcheck(wbuff)) \
				__ret = read(chainX_fd_get(req), wbuff, wlen); \
			else __ret = 0; \
		} while(0); \
		__ret; \
	})

#define SOCKETX_WRITE(req, wbuff, wlen)	\
	({ int __ret = 0; \
		do { \
			if (pcheck(wbuff)) \
				__ret = write(chainX_fd_get(req), wbuff, wlen); \
			else __ret = 0; \
		} while(0); \
		__ret; \
	})

#endif

#define SOCKETX_SENDTO(req, wbuff, wlen)	\
	({ int __ret = 0; \
		do { \
			int addr_len=sizeof(struct sockaddr_in); \
			if (pcheck(wbuff)) \
				__ret = sendto(chainX_fd_get(req), wbuff, wlen, 0, (struct sockaddr*)chainX_addr_to_get(req), addr_len); \
			else __ret = 0; \
		} while(0); \
		__ret; \
	})

#define SOCKETX_RECV_FROM(req, wbuff, wlen)	\
	({ int __ret = 0; \
		do { \
			int addr_len=sizeof(struct sockaddr_in); \
			__ret = recvfrom(chainX_fd_get(req), wbuff, wlen, 0, (struct sockaddr*)chainX_addr_from_get(req), (socklen_t *)&addr_len); \
		} while(0); \
		__ret; \
	})

#ifdef UTIL_EX_MCTT
#ifdef PJ_MCTT_PORT
#define MCTT_PORT SAFE_STRTOL(PJ_MCTT_PORT)
#else
#define MCTT_PORT 6288
#endif
#ifdef MCTT_IP
#define MCTT_IP PJ_MCTT_IP
#else
#define MCTT_IP   "229.255.255.250" // 224.0.0.0 ~ 239.255.255.255
#endif
#define MCTT_BOM  0xFCFE

typedef void (*mctt_recv_fn)(void *userdata, unsigned char *payload, int payload_len);

#define MAX_OF_MCTT LEN_OF_BUF2048
typedef struct MCTT_Struct
{
	unsigned short bom;
	unsigned short checksum;

	int payload_len;
	unsigned char payload[MAX_OF_MCTT];
} MCTT_t;

void mctt_publish(ChainX_t *chainX_req, char *payload, int payload_len);
void mctt_thread_close(ChainX_t *chainX_req);
ChainX_t *mctt_thread_init(void *userdata, char *ip, int port, mctt_recv_fn cb);
#endif

#if defined(UTIL_EX_WSDISCOVERY) && defined(UTIL_EX_SOAP)

typedef struct WSList_STRUCT
{
	void* next;

	int mask;
	char url[LEN_OF_URL];
	char types[LEN_OF_VAL64];
	char version[LEN_OF_VAL16];
} WSList_t;

typedef void (*wsdiscovery_response_fn)(ChainX_t *chainX_req, soap_node_t *parent_node);

#define WSDISCOVERY_FILTER_MASK_ONVIF  0x00000001
#define WSDISCOVERY_FILTER_MASK_OTHERS 0x00000002

typedef struct WSDiscoveryX_STRUCT
{
	ChainX_t *chainX_req;

	wsdiscovery_response_fn hello_cb;
	wsdiscovery_response_fn probe_cb;
	wsdiscovery_response_fn probematches_cb;
	wsdiscovery_response_fn others_cb;
} WSDiscoveryX_t;

clist_t ws_list_head(void);
void ws_entry_print(void);
void ws_entry_init(void);
void ws_entry_free(void);
void ws_devices_refresh(void);
void ws_device_add(ChainX_t *chainX_req, soap_node_t *node);

void wsdiscovery_probematches_register(wsdiscovery_response_fn cb);
void wsdiscovery_probe_register(wsdiscovery_response_fn cb);
void wsdiscovery_hello_register(wsdiscovery_response_fn cb);
void wsdiscovery_others_register(wsdiscovery_response_fn cb);
void wsdiscovery_linked_register(chainX_linked_fn cb);

void wsdiscovery_sender(WSDiscoveryX_t *wsd_req, SOAP_ACTION_ID act_id);
void wsdiscovery_probe(chainX_post_fn cb);

WSDiscoveryX_t *wsdiscovery_get(void);
void wsdiscovery_stop(void);
void wsdiscovery_close(void);
WSDiscoveryX_t *wsdiscovery_open(void);

#endif

#endif


//******************************************************************************
//** UTIL_EX_RTP **
//******************************************************************************
#ifdef UTIL_EX_RTP
// RTP Library in C
// https://sourceforge.net/projects/rtp-lib/

/* Enumeration of H.264 NAL unit types */
typedef enum
{
	NAL_TYPE_UNDEFINED = 0,
	NAL_TYPE_SINGLE_NAL_MIN = 1,
	NAL_TYPE_SINGLE_NAL_MAX = 23,
	NAL_TYPE_STAP_A = 24,
	NAL_TYPE_STAP_B = 25,
	NAL_TYPE_MTAP16 = 26,
	NAL_TYPE_MTAP24 = 27,
	NAL_TYPE_FU_A = 28,
	NAL_TYPE_FU_B = 29,
} NAL_TYPE;

typedef struct
{
	unsigned char flags; /* Version(2),Padding(1), Ext(1), Cc(4) */
	unsigned char mk_pt; /* Marker(1), PlayLoad Type(7) */
	unsigned short sq_nb; /* Sequence Number */
	unsigned long ts; /* Timestamp */
	unsigned long ssrc; /* SSRC */
	unsigned long *csrc; /* CSRC's table */
} rtp_hdr;

/**
 ** RTP header extension
 **/
typedef struct
{
	unsigned short ext_type; /* Extension profile */
	unsigned short ext_len; /* Number of extensions */
	unsigned long *hd_ext; /* Extension's table */
} rtp_ext;

/**
 ** RTP Context body
 **/
typedef struct
{
	int context_num; /* Context number - send/receive */
	unsigned int my_ssrc; /* SSRC number - send/receive */
	unsigned int sending_pkt_count;	/* Number of packets sent - send/receive */
	unsigned int sending_octet_count;	/* Number of bytes sent - send/receive */
	unsigned char version; /* Version - receive */
	unsigned char marker; /* Marker flag - receive */
	unsigned char padding; /* Padding length - receive */
	unsigned char CSRClen; /* CSRC length - send/receive */
	unsigned char pt; /* Payload type - send/receive */
	unsigned int *CSRCList; /* CSRC list - send/receive */
	unsigned int my_previous_ssrc;	/* actually unused */
	unsigned int init_RTP_timestamp; /* First value of timestamp - send/receive */
	unsigned int RTP_timestamp; /* current value of timestamp - receive */
	unsigned int time_elapsed; /* Time elapsed since the beginning - send/receive */
	unsigned short init_seq_no; /* First sequence number - send/receive */
	unsigned short seq_no; /* Current sequence number - send/receive */
	rtp_ext *hdr_extension; /* Extension header - send/receive */
	void *conx_data; /* Network data */
} sess_context_t;

/**
 ** RTP Packet
 **/
typedef struct
{
	rtp_hdr *RTP_header; /* Header RTP */
	rtp_ext *RTP_extension; /* extension of the header if exist */

	char *payload; /* payload portion of RTP packet */
	unsigned int payload_len; /* The length of the payload */

	sess_context_t *sess_req;
} rtp_pkt;

typedef struct RTPX_STRUCT
{
	size_t max_size;
	size_t total;
	HttpX_t *http_req;

	sess_context_t sess_data;
} RTPX_t;

int rtp_port_get(void);
void rtp_context_print(sess_context_t *sess_req);
int dummy_write(RTPX_t *rtp_req, void *buf, size_t count);
void rtp_body_parse(RTPX_t *rtp_req, char *buff, int buff_len);
void rtp_free(RTPX_t *rtp_req);
RTPX_t *rtp_init(int port, int interleaved);
#endif


//******************************************************************************
//** UTIL_EX_ONVIF **
//******************************************************************************
#ifdef UTIL_EX_ONVIF

#define ONVIF_STRUCT_VER 2
#define ONVIF_VER "0.1.0"

typedef enum
{
	NET_PROTOCOL_ID_COMMON,
	NET_PROTOCOL_ID_ONVIF,
	NET_PROTOCOL_ID_SMIL,
	NET_PROTOCOL_ID_MAX,
} NET_PROTOCOL_ID;

typedef struct OnvifDevice_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
	char hostname[LEN_OF_HOSTNAME]; // GetHostname
} OnvifDevice_t;

typedef struct OnvifMedia_STRUCT
{
	char uri[LEN_OF_URL_ONVIF]; // GetCapabilities
	char profiletoken[LEN_OF_VAL32]; // GetProfiles - 1st, for GetSnapshotUri
} OnvifMedia_t;

typedef struct OnvifAnalytics_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifAnalytics_t;

typedef struct OnvifEvents_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifEvents_t;

typedef struct OnvifImaging_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifImaging_t;

typedef struct OnvifPTZ_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifPTZ_t;

typedef struct OnvifDeviceIO_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifDeviceIO_t;

typedef struct OnvifDisplay_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifDisplay_t;

typedef struct OnvifRecording_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifRecording_t;

typedef struct OnvifSearch_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifSearch_t;

typedef struct OnvifReplay_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifReplay_t;

typedef struct OnvifReceiver_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifReceiver_t;

typedef struct OnvifAnalyticsDevice_STRUCT
{
	char uri[LEN_OF_URL_ONVIF];  // GetCapabilities
} OnvifAnalyticsDevice_t;

typedef struct OnvifServices_STRUCT
{
	int ver;
	NET_PROTOCOL_ID prot_id;

	OnvifDevice_t device;
	OnvifMedia_t media;
	OnvifAnalytics_t analytics;
	OnvifEvents_t events;
	OnvifImaging_t imaging;
	OnvifPTZ_t ptz;
	OnvifDeviceIO_t deviceio;
	OnvifRecording_t recording;
	OnvifSearch_t search;
	OnvifReplay_t replay;
	OnvifReceiver_t receiver;
	OnvifAnalyticsDevice_t analyticsdevice;
} OnvifServices_t;

typedef struct CommonServices_STRUCT
{
	int ver;
	NET_PROTOCOL_ID prot_id;
} CommonServices_t;

typedef struct ConnectionInfo_STRUCT
{
	NetworkInfo_t netinfo;

	union
	{
		CommonServices_t common_service;
		OnvifServices_t onvif_service;
	};
} ConnectionInfo_t;

typedef struct OnvifX_STRUCT
{
	SOAP_ACTION_ID act_id;
	char act_ns[LEN_OF_NAME_ONVIF_ACT];
	char act_name[LEN_OF_NAME_ONVIF_ACT];

	NetworkInfo_t netinfo;

	int http_auth;

	void *request;
} OnvifX_t;

typedef void (*onvif_resuest_fn)(SoapX_t *soap, OnvifX_t *onvif_req);

char *onvif_pass_sha1(char *nonce, int nonce_len, char *created, int create_len, char *password, int password_len);
void onvif_auth(OnvifX_t *onvif_req, SoapX_t *soap);
soap_node_t *onvif_open(OnvifX_t *onvif_req, onvif_resuest_fn request_cb);

soap_node_t *onvif_GetCommon(OnvifX_t *onvif_req);
//** device **

//** media **

int onvif_GetVideoClip(OnvifX_t *onvif_req, char *videoclip_uri, char *filename, int duration);
int onvif_GetSnapshot(OnvifX_t *onvif_req, char *snapshot_uri, char *prefixname);
#endif


//******************************************************************************
//** UTIL_EX_PROC_TABLE **
//******************************************************************************
#ifdef UTIL_EX_PROC_TABLE

typedef struct ProcList_STRUCT
{
	void* next;

	const char *name;
	ProcInfo_t procinfo;
} ProcList_t;

ProcList_t *proc_entry_push(clist_t head, const char *name);
void proc_entry_del(clist_t head, ProcList_t *proc_entry);
void proc_entry_reset(clist_t head);
void proc_entry_scan(clist_t head);

void proc_entry_print_ex(clist_t head, int fdlist);
clist_t proc_table_head(void);

void proc_entry_print(int fdlist);
void proc_table_free(clist_t head);
void proc_table_open(void);
void proc_table_refresh(void);
void proc_table_close(void);
#endif


//******************************************************************************
//** UTIL_EX_QUEUEX **
//******************************************************************************
#ifdef UTIL_EX_QUEUEX
typedef int (*queuex_fn)(void *arg);

typedef struct QueueX_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isfree;
	int ishold;

	int dbg_more;

#ifdef UTIL_EX_CLIST
	CLIST_STRUCT(qlist);
	void *data_pop;
	int data_size;
	int max_data;
#else
	void *datas;
	void *data_pop;
	int data_size;

	int head_pos;
	int tail_pos;
	int max_data;
#endif

	queuex_fn exec_cb;
	queuex_fn free_cb; // for un-processed data
} QueueX_t;

void queuex_lock(QueueX_t *queuex_req);
void queuex_unlock(QueueX_t *queuex_req);
void queuex_signal(QueueX_t *queuex_req);
int queuex_timewait(QueueX_t *queuex_req, int ms);
void queuex_wait(QueueX_t *queuex_req);

void queuex_debug(QueueX_t *queuex_req, int dbg_more);
void queuex_free(QueueX_t *queuex_req);
int queuex_length(QueueX_t *queuex_req);
int queuex_isfull(QueueX_t *queuex_req);
int queuex_isempty(QueueX_t *queuex_req);
int queuex_isready(QueueX_t *queuex_req, int retry);

void queuex_gosleep(QueueX_t *queuex_req);
void queuex_wakeup(QueueX_t *queuex_req);
void queuex_add(QueueX_t *queuex_req, void *data_new);
void queuex_push(QueueX_t *queuex_req, void *data_new);

void queuex_thread_stop(QueueX_t *queuex_req);
void queuex_thread_close(QueueX_t *queuex_req);
QueueX_t *queuex_thread_init(char *name, int queue_size, int data_size, queuex_fn exec_cb, queuex_fn free_cb);
#endif


//******************************************************************************
//** UTIL_EX_STATEX **
//******************************************************************************
#ifdef UTIL_EX_STATEX
typedef enum
{
	ACTION_ID_OFF = 0,
	ACTION_ID_ON = 1,
	ACTION_ID_MAX,
} ACTION_ID;

typedef enum
{
	SUBITEM_ID_NONE = 0,
	SUBITEM_ID_1 = 1,
	SUBITEM_ID_2 = 2,
	SUBITEM_ID_3 = 3,
	SUBITEM_ID_4 = 4,
	SUBITEM_ID_5 = 5,
	SUBITEM_ID_6 = 6,
	SUBITEM_ID_7 = 7,
	SUBITEM_ID_8 = 8,
	SUBITEM_ID_9 = 9,
	SUBITEM_ID_10 = 10,
	SUBITEM_ID_11 = 11,
	SUBITEM_ID_12 = 12,
	SUBITEM_ID_13 = 13,
	SUBITEM_ID_14 = 14,
	SUBITEM_ID_15 = 15,

	SUBITEM_ID_MAX,
} SUBITEM_ID;

#define ACTION_RUN_ID_MASK 0xFFFF
#define ACTION_RUN_ID_INSTANTLY 0x0001
#define ACTION_RUN_ID_AGAIN 0x0002
#define ACTION_RUN_ID_NORMAL ACTION_RUN_ID_INSTANTLY
#define ACTION_RUN_ID_FULL (ACTION_RUN_ID_AGAIN | ACTION_RUN_ID_INSTANTLY)

typedef struct StateXFn_STRUCT StateXFn_t;

typedef void (*statex_init_fn)(StateXFn_t *fn_link, void *data);
typedef void (*statex_free_fn)(StateXFn_t *fn_link, void *data);
typedef void (*statex_leave_fn)(StateXFn_t *fn_link, void *data);
typedef void (*statex_enter_fn)(StateXFn_t *fn_link, void *data);

typedef struct StateXFn_STRUCT
{
	int id;
	int subitem;
	ACTION_ID action;

	statex_init_fn init_cb;
	statex_free_fn free_cb;
	statex_leave_fn leave_cb;
	statex_enter_fn enter_cb;

	int init_count;
} StateXFn_t;

typedef struct StateX_STRUCT StateX_t;

typedef struct StateXPuck_Struct
{
	StateX_t *statex_req;
	int idx;
	int subitem;
	ACTION_ID action;
	int run;
} StateXPuck_t;

typedef struct StateX_STRUCT
{
	QueueX_t *statex_q;

	StateXFn_t *fn_last;
	StateXFn_t *fn_links;

	int dbg_more;
	void *data;
} StateX_t;

StateXFn_t *statex_fn_last(StateX_t *statex_req);

void statex_debug_q(StateX_t *statex_req, int dbg_more);
void statex_debug(StateX_t *statex_req, int dbg_more);
void statex_add(StateX_t *statex_req, int idx, int subitem, ACTION_ID action, int run);
void statex_push(StateX_t *statex_req, int idx, int subitem, ACTION_ID action, int run);
int statex_open(StateX_t *statex_req, char *name);
void statex_close(StateX_t *statex_req);

#endif


//******************************************************************************
//** UTIL_EX_JSON **
//******************************************************************************
#ifdef UTIL_EX_JSON
#include <jansson.h>

typedef enum
{
	JSON_ACTID_READ = 0,
	JSON_ACTID_APPEND,
	JSON_ACTID_DEL,
} JSON_ACTID;

typedef struct JSON_TokenX_STRUCT
{
	char token[LEN_OF_TOPIC_TOKEN];
	char topic[LEN_OF_TOPIC];
	json_t *jdata;
} JSON_TokenX_t;

#define MAX_OF_TOKENX_ARY 0xFF
typedef struct JSON_TopicX_STRUCT
{
	char topic[LEN_OF_TOPIC];
	json_t *jroot;

	int deepth_topic;
	int deepth_json;
	JSON_TokenX_t tokenx_ary[MAX_OF_TOKENX_ARY];
} JSON_TopicX_t;

#define JSON_UTF8(X) \
	({ json_t *__jobj = NULL; \
		if (X) __jobj = json_stringn(X, strlen(X)); \
		__jobj; \
	})

#define JSON_REFCOUNT(X) \
		({ long int ret = -1; \
			if (X) { \
				ret = X->refcount;  \
			} \
			ret; \
		})

#define JSON_FREE(X) \
	do { \
		if ( (X) != NULL ) { \
			if (X->refcount==1) { json_decref(X); X=NULL;} \
			else { DBG_ER_LN("JSON_FREE fail !!! (%s->refcount: %zd != 1)", #X, X->refcount); } \
		} \
	} while(0)

#define JSON_COPY(jroot) \
	({ json_t *__jobj = NULL; \
		if (jroot) __jobj = json_deep_copy(jroot); \
		__jobj; \
	})

#define JSON_UPDATE(x,y) json_object_update(x,y)
#define JSON_UPDATE_EXISTING(x,y) json_object_update_existing(x,y)
#define JSON_UPDATE_MISSING(x,y) json_object_update_missing(x,y)
#define JSON_EQUAL(x,y) json_equal(x,y)

#define JSON_CHECK_OBJ(jroot) json_is_object(jroot)
#define JSON_CHECK_ARY(jroot) json_is_array(jroot)
#define JSON_CHECK_STR(jroot) json_is_string(jroot)
#define JSON_CHECK_INT(jroot) json_is_integer(jroot)
#define JSON_CHECK_REAL(jroot) json_is_real(jroot)

#define JSON_OBJ_NEW() json_object()

#define JSON_OBJ_FOREACH(jroot, key, jobj) json_object_foreach(jroot, key, jobj)

// json_object_set_new will replace the old one
#define JSON_OBJ_SET_OBJ(jroot, key, jval) \
	({ int __ret = -1; \
		do { \
			if (jroot) \
			{ \
				__ret = json_object_set_new(jroot, key, jval ); \
			} \
			else \
			{ \
				JSON_FREE(jval); \
				DBG_ER_LN("%s is NULL !!!", #jroot);\
			} \
		} while(0); \
		__ret; \
	})

#define JSON_OBJ_SET_OBJ_LINK(jroot, key, jval) \
		({ int __ret = -1; \
			do { \
				if (jroot) \
				{ \
					__ret = json_object_set(jroot, key, jval ); \
				} \
				else \
				{ \
					JSON_FREE(jval); \
					DBG_ER_LN("%s is NULL !!!", #jroot);\
				} \
			} while(0); \
			__ret; \
		})

#define JSON_OBJ_GET_OBJ(jroot, key) \
	({ json_t *__jobj = NULL; \
		if ( (jroot) && (JSON_CHECK_OBJ(jroot)) ) __jobj = json_object_get(jroot, key); \
		__jobj; \
	})

#define JSON_OBJ_GET_ARY_EX(jroot, key) \
		({ json_t *__jobj = NULL; \
			if (jroot) __jobj = json_ary_create(jroot, key); \
			__jobj; \
		})

#define JSON_OBJ_GET_OBJ_EX(jroot, key) \
	({ json_t *__jobj = NULL; \
		if ( (jroot) && (JSON_CHECK_OBJ(jroot)) ) __jobj = json_obj_create(jroot, key); \
		__jobj; \
	})

#define JSON_OBJ_FIND_ID_INFINITE -1
#define JSON_OBJ_FIND_RECURSIVE(jroot, key, jval, deepth, topic_parent, jfound_ary) json_object_lookup(jroot, key, jval, deepth, topic_parent, jfound_ary)
#define JSON_OBJ_FIND_REUSE(jroot, key) \
	({ json_t *__ret = NULL; \
		do { if ( (JSON_CHECK_OBJ(jroot)) && ((__ret=JSON_OBJ_GET_OBJ(jroot, key))) ) json_incref(__ret);} while(0); \
		__ret; \
	})

#define JSON_OBJ_FIND_KEYS(jroot, keys) json_object_find_with_keys(jroot, keys);

#define JSON_OBJ_DEL(jroot, key) \
	({ int __ret = 0; \
		if ( (jroot) && (JSON_CHECK_OBJ(jroot)) ) \
			__ret = json_object_del(jroot, key); \
		__ret; \
	})

#define JSON_OBJ_CLEAR(jroot) json_object_clear(jroot)

#define JSON_JSTR(val) json_string(val)
#define JSON_JINT(val) json_integer(val)
#define JSON_JREAL(val) json_real(val)

//#define JSON_OBJ_SET_STR(jroot, key, val) JSON_OBJ_SET_OBJ(jroot, key, JSON_JSTR(val))
//#define JSON_OBJ_SET_INT(jroot, key, val) JSON_OBJ_SET_OBJ(jroot, key, JSON_JINT(val))
//#define JSON_OBJ_SET_REAL(jroot, key, val) JSON_OBJ_SET_OBJ(jroot, key, JSON_JREAL(val))
#define JSON_OBJ_SET_STR(jroot, key, val) ({json_t *__jval = JSON_JSTR(val); JSON_OBJ_SET_OBJ(jroot, key, __jval); __jval;})
#define JSON_OBJ_SET_INT(jroot, key, val) ({json_t *__jval = JSON_JINT(val); JSON_OBJ_SET_OBJ(jroot, key, __jval); __jval;})
#define JSON_OBJ_SET_REAL(jroot, key, val) ({json_t *__jval = JSON_JREAL(val); JSON_OBJ_SET_OBJ(jroot, key, __jval); __jval;})

#define JSON_OBJ_FILL_STR(jroot, key, val) \
	({json_t *__jval = JSON_OBJ_GET_OBJ(jroot, key); \
		if ( (__jval==NULL) && (__jval=JSON_JSTR(val)) ) \
			JSON_OBJ_SET_OBJ(jroot, key, __jval); \
		__jval; \
	})

#define JSON_STR(jobj) \
	({ const char *__ret = NULL; \
		if ( (jobj) && (JSON_CHECK_STR(jobj)) ) \
			__ret = json_string_value(jobj); \
		__ret; \
	})

#define JSON_OBJ_GET_STR(jroot, jobj, key) \
	({ const char *__ret = NULL; \
		if ( ( jobj = JSON_OBJ_GET_OBJ(jroot, key) ) ) \
			__ret = JSON_STR(jobj); \
		__ret; \
	})

#define JSON_OBJ_GET_ASTR(jroot, jobj, key, buf) \
	({ int __ret =0; \
		do { \
			const char *val = NULL; \
			if ( ( jobj = JSON_OBJ_GET_OBJ(jroot, key) ) && ( val = JSON_STR(jobj) ) ) \
				__ret = asprintf(&buf, "%s", val); \
			else \
				__ret = asprintf(&buf, "\n"); \
		} while(0); \
		__ret; \
	})

#define JSON_INT(jobj, val) \
	({ json_int_t __ret = val; \
		if ( (jobj) && (JSON_CHECK_INT(jobj)) ) \
			__ret = json_integer_value(jobj); \
		__ret; \
	})

#define JSON_OBJ_GET_INT_DEF(jroot, jobj, key, val) \
	({ json_int_t __ret = val; \
		if ( ( jobj = JSON_OBJ_GET_OBJ(jroot, key) ) ) \
			__ret = JSON_INT(jobj, val); \
		__ret; \
	})

#define JSON_REAL(jobj, val) \
	({ double __ret = val; \
		if ( (jobj) && (JSON_CHECK_REAL(jobj)) ) \
			__ret = json_real_value(jobj); \
		__ret; \
	})

#define JSON_OBJ_GET_REAL_DEF(jroot, jobj, key, val) \
	({ double __ret = val; \
		if ( ( jobj = JSON_OBJ_GET_OBJ(jroot, key) ) ) \
			__ret = JSON_REAL(jobj, val); \
		__ret; \
	})

#define JSON_ITER(jroot) json_object_iter(jroot)
#define JSON_ITER_NEXT(jroot, jiter) json_object_iter_next(jroot, jiter)
#define JSON_ITER_VAL(jiter) json_object_iter_value(jiter)
#define JSON_ITER_KEY(jiter) json_object_iter_key(jiter)

#define JSON_OBJ_SIZE(jobj) json_object_size(jobj)

#define JSON_ARY_NEW() json_array()

#define JSON_ARY_SIZE(jary) json_array_size(jary)
#define JSON_ARY_GET(jary, idx) json_array_get(jary, idx)
#define JSON_ARY_DEL(jary, idx) json_array_remove(jary, idx)
#define JSON_ARY_CLEAR(jary) json_array_clear(jary)

#define JSON_ARY_FOREACH(jary, idx, jval) json_array_foreach(jary, idx, jval)

#define JSON_ARY_APPEND_OBJ(jary, jval) \
	({ int __ret = -1; \
		do { if ((jary) && (jval)) __ret = json_array_append_new(jary, jval ); else DBG_ER_LN("%p or %p is NULL !!!", jary, jval); } while(0); \
		__ret; \
	})

#define JSON_ARY_APPEND_STR(jary, val) JSON_ARY_APPEND_OBJ(jary, JSON_JSTR(val))
#define JSON_ARY_APPEND_INT(jary, val) JSON_ARY_APPEND_OBJ(jary, JSON_JINT(val))
#define JSON_ARY_APPEND_REAL(jary, val) JSON_ARY_APPEND_OBJ(jary, JSON_JREAL(val))

#define JSON_ARY_SET_NEW(jary, idx, jval) json_array_set_new(jary, idx, jval)

#define JSON_FLAGS_VIEW JSON_INDENT(2)|JSON_ENSURE_ASCII|JSON_PRESERVE_ORDER
#define JSON_FLAGS_WITHOUT_SORT_KEY JSON_COMPACT|JSON_ENSURE_ASCII|JSON_PRESERVE_ORDER
#define JSON_FLAGS_EASY JSON_COMPACT|JSON_ENSURE_ASCII|JSON_SORT_KEYS|JSON_PRESERVE_ORDER

#define JSON_DUMP_FILE_FLAGS(x, filename, y) \
		({ int __ret = 0; \
			do { \
				if ( (x) && (pcheck(filename)) && (strlen(filename)>0) ) __ret = json_dump_file(x, filename, y); \
			} while(0); \
			__ret; \
		})

#define JSON_DUMP_FILE_EASY(x, filename) \
	({ int __ret = 0; \
		do { \
			if ( (x) && (pcheck(filename)) && (strlen(filename)>0) ) __ret = json_dump_file(x, filename, JSON_FLAGS_EASY); \
		} while(0); \
		__ret; \
	})

#define JSON_DUMPS_FLAGS(x,y) \
		({ char *__ret = NULL; \
			do { \
				if (x) __ret = json_dumps( x, y ); \
			} while(0); \
			__ret; \
		})

#define JSON_DUMPS_EASY(x) \
	({ char *__ret = NULL; \
		do { \
			if (x) __ret = json_dumps( x, JSON_FLAGS_EASY ); \
		} while(0); \
		__ret; \
	})

#define JSON_LOADFILE_EASY(filename) \
	({ json_t *__ret = NULL; \
		do { \
			json_error_t jerror = {0}; \
			if ( (pcheck(filename)) && (strlen(filename)>0) ) __ret = json_load_file(filename, 0, &jerror); \
			else DBG_ER_LN("json_load_file error !!! (error: %d %s)", jerror.line, jerror.text); \
		} while(0); \
		__ret; \
	})

#define JSON_LOADFILE_EASY_OR_NEW(filename) \
	({ json_t *__ret = NULL; \
		do { \
			json_error_t jerror = {0}; \
			if ( ( (pcheck(filename)) && (strlen(filename)>0) && (__ret = json_load_file(filename, 0, &jerror))) || (__ret = JSON_OBJ_NEW()) ) {} \
			else DBG_ER_LN("json_load_file error !!! (error: %d %s)", jerror.line, jerror.text); \
		} while(0); \
		__ret; \
	})

#define JSON_LOADS_EASY(x) \
	({ json_t *__ret = NULL; \
		do { \
			json_error_t jerror = {0}; \
			if (pcheck(x)) __ret = json_loads(x, JSON_DISABLE_EOF_CHECK, &jerror); \
			else DBG_ER_LN("json_loads error !!! (error: %d %s)", jerror.line, jerror.text); \
		} while(0); \
		__ret; \
	})

#define JSON_LOADS_EASY_OR_NEW(x) \
	({ json_t *__ret = NULL; \
		do { \
			json_error_t jerror = {0}; \
			if ( ((pcheck(x)) && (__ret = json_loads(x, JSON_DISABLE_EOF_CHECK, &jerror))) || (__ret = JSON_OBJ_NEW()) ) {} \
			else DBG_ER_LN("json_loads error !!! (error: %d %s)", jerror.line, jerror.text); \
		} while(0); \
		__ret; \
	})

void json_dump_simple(json_t *jparent, char *name);

int json_pass_base64_dec(json_t *jparent, const char *key, char *pass, int len);
int json_pass_base64_enc(json_t *jparent, const char *key, char *pass, int len);

json_t *json_ary_create(json_t *jparent, const char *key);
json_t *json_obj_create(json_t *jparent, const char *key);

json_t *json2topicx(JSON_TopicX_t *topicx_req, int idx_need, JSON_ACTID act);

json_t *json_ary_find_val(json_t *jparent, json_t *jval, int *idx);
json_t *json_ary_find_key_val(json_t *jparent, const char *key, json_t *jval, int *idx);

// key like dongle/1/device/0/uid
json_t *json_object_find_with_keys(json_t *jparent, const char *keys);
json_t *json_object_lookup(json_t *jparent, const char *key, json_t *jval, int deepth, char *topic_parent, json_t *jfound_ary);

#endif


//******************************************************************************
//** UTIL_EX_SSH **
//******************************************************************************
#ifdef UTIL_EX_SSH
#include <libssh/callbacks.h>
#include <libssh/libssh.h>

typedef enum
{
	TUNNEL_MODE_ID_SSH,
	TUNNEL_MODE_ID_SSH_FAKE,
	TUNNEL_MODE_ID_STDINOUT,
	TUNNEL_MODE_ID_MAX,
} TUNNEL_MODE_ID;

typedef struct SSH_STRUCT
{
	char server_ip[LEN_OF_IP];
	int server_port;
	char server_user[LEN_OF_USER];
	char server_pass_enc[LEN_OF_PASS];
	char server_pass_dec[LEN_OF_PASS];
	
	ssh_session session;
	ssh_channel channel;

	char prompt[LEN_OF_BUF256];

	int cols;
	int rows;

	int verbosity;
} SSH_t;

typedef struct Tunnel_STRUCT
{
	SSH_t ssh_req;

	int open_port;

	TUNNEL_MODE_ID mode;
	int timeout;
	int foreground;

	int retry;
	int isquit;
} Tunnel_t;

int sshX_open_shell(SSH_t *ssh_req);
int sshX_request_pty(SSH_t *ssh_req);
int sshX_request_shell(SSH_t *ssh_req);

void sshX_stream_copy(ssh_channel channel_frm, ssh_channel channel_to);

void sshX_select_loop_with_tunnel(SSH_t *ssh_req, SSH_t *ssh_req_frm);
void sshX_select_loop_with_fd(SSH_t *ssh_req, socket_t in_fd, socket_t out_fd, socket_t err_fd);
ssh_channel sshX_open_channel(SSH_t *ssh_req);
int sshX_interactive(SSH_t *ssh_req);

int sshX_authenticate(SSH_t *ssh_req);

void sshX_close_channel(SSH_t *ssh_req);
void sshX_close_session(SSH_t *ssh_req);
void sshX_stop(SSH_t *ssh_req);

ssh_session sshX_client(SSH_t *ssh_req);

#endif


//******************************************************************************
//** UTIL_EX_SWCONFIG **
//******************************************************************************
#ifdef UTIL_EX_SWCONFIG
#ifndef IFNAMSIZ
#define IFNAMSIZ 16
#endif
#include <swlib.h>

typedef enum
{
	SWLINK_CMD_ID_NONE,
	SWLINK_CMD_ID_GET,
	SWLINK_CMD_ID_SET,
	SWLINK_CMD_ID_LOAD,
	SWLINK_CMD_ID_HELP,
	SWLINK_CMD_ID_SHOW,
	SWLINK_CMD_ID_PORTMAP,
	SWLINK_CMD_ID_MAX,
} SWLINK_CMD_ID;

typedef struct SWLinkX_STRUCT
{
	char cdev[LEN_OF_VAL32];
	struct switch_dev *dev;
	struct switch_attr *attr;
	struct switch_val val;

	int port;
	SWLINK_CMD_ID cmd; 
	char ckey[LEN_OF_VAL32];

} SWLinkX_t;

#endif

//******************************************************************************
//** UTIL_EX_UV **
//******************************************************************************
#ifdef UTIL_EX_UV
#include <uv.h>

#define SAFE_UV_LOOP_RUN(loop) \
		do { \
			if (pcheck(loop)) \
			{ \
				uv_run((uv_loop_t*)loop, UV_RUN_DEFAULT); \
			} \
		} while(0)

#define SAFE_UV_LOOP_INIT(loop) do { if (loop==NULL) {loop=uv_default_loop();} } while(0)

#define SAFE_UV_LOOP_CLOSE(loop) \
	do { \
		if (pcheck(loop)) \
		{ \
			uv_stop((uv_loop_t*)loop); \
			uv_loop_close((uv_loop_t*)loop); \
			loop=NULL; \
		} \
	} while(0)

#define SAFE_UV_READ_STOP(stream) \
		({ int __ret = 0;\
			do { \
				__ret = uv_read_stop((uv_stream_t*)stream); \
			} while(0); \
			__ret; \
		})

#define SAFE_UV_CLOSE(handle, close_cb) \
	({ int __ret = 0;\
		do { \
				if ( (uv_is_active((uv_handle_t*)handle)) && ( uv_is_closing((uv_handle_t*)handle) == 0 ) ) \
			{ \
				uv_close((uv_handle_t*)handle, close_cb); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_CANCEL(req) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(req)) ) \
			{ \
				__ret = uv_cancel((uv_req_t*)req); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_UNREF(handle) \
	do { \
		if (pcheck(handle)) \
		{ \
			uv_unref((uv_handle_t*)handle); \
		} \
	} while(0)


//** process **
#define SAFE_UV_PROCESS_KILL(process, signum) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(process)) ) \
			{ \
				__ret = uv_process_kill((uv_process_t*)process, signum); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_KILL(pid, signum) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(process)) ) \
			{ \
				__ret = uv_kill(pid, signum); \
			} \
		} while(0); \
		__ret; \
	})

//** idle **
#define SAFE_UV_IDLE_INIT(loop, idle) \
	({ int __ret = 0;\
		do { \
			if ((pcheck(loop)) && (pcheck(idle))) \
			{ \
				__ret = uv_idle_init(loop, (uv_idle_t*)idle); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_IDLE_START(idle, cb) \
	({ int __ret = 0;\
		do { \
			if (pcheck(idle)) \
			{ \
				__ret = uv_idle_start((uv_idle_t*)idle, cb); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_IDLE_STOP(idle) \
	({ int __ret = 0;\
		do { \
			if (pcheck(idle)) \
			{ \
				__ret = uv_idle_stop((uv_idle_t*)idle); \
			} \
		} while(0); \
		__ret; \
	})

//** file **
#define SAFE_UV_FS_OPEN(loop, req, path, flags, mode, cb) \
	({ int __ret = 0;\
		do { \
			if ((pcheck(loop)) && (pcheck(path))) \
			{ \
				__ret = uv_fs_open(loop, req, path, flags, mode, cb); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_FS_CLOSE(loop, req, file, cb) \
		({ int __ret = 0;\
			do { \
				if (pcheck(loop)) \
				{ \
					__ret = uv_fs_close(loop, req, file, cb); \
				} \
			} while(0); \
			__ret; \
		})

#define SAFE_UV_FS_READ(loop, req, file, bufs, nbufs, off, cb) \
	({ int __ret = 0;\
		do { \
			if (pcheck(loop)) \
			{ \
				__ret = uv_fs_read(loop, req, file, bufs, nbufs, off, cb); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_FS_WRITE(loop, req, file, bufs, nbufs, off, cb) \
	({ int __ret = 0;\
		do { \
			if (pcheck(loop)) \
			{ \
				__ret = uv_fs_write(loop, req, file, bufs, nbufs, off, cb); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_FS_REQ_CLEANUP(req) \
	do { \
		uv_fs_req_cleanup((uv_fs_t*)req); \
	} while(0);

//** timer **
#define SAFE_UV_TIMER_INIT(loop, handle) do { if ((pcheck(loop)) && (pcheck(handle))) {uv_timer_init((uv_loop_t*)loop, (uv_timer_t* )handle);} } while(0)
#define SAFE_UV_TIMER_START(handle, cb, first, next) do { if (pcheck(handle)) {uv_timer_start((uv_timer_t*)handle, cb, first, next);} } while(0)
#define SAFE_UV_TIMER_AGAIN(handle) \
	({ int  __ret = 0;\
		do { \
			if (pcheck(handle)) \
			{ \
				__ret = uv_timer_again((uv_timer_t*)handle); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_TIMER_SET_REPEAT(handle, repeat) do { if (pcheck(handle)) {uv_timer_set_repeat((const uv_timer_t*)handle, repeat);} } while(0)
#define SAFE_UV_TIMER_GET_REPEAT(handle) \
	({ uint64_t  __ret = 0;\
		do { \
			if (pcheck(handle)) \
			{ \
				__ret = uv_timer_get_repeat((const uv_timer_t*)handle); \
			} \
		} while(0); \
		__ret; \
	})
#define SAFE_UV_TIMER_GET_DUE_IN(handle) \
		({ uint64_t  __ret = 0;\
			do { \
				if (pcheck(handle)) \
				{ \
					__ret = uv_timer_get_due_in((const uv_timer_t*)handle); \
				} \
			} while(0); \
			__ret; \
		})

#define SAFE_UV_TIMER_STOP(handle) \
	({ int __ret = 0;\
		do { \
			if (pcheck(handle)) \
			{ \
				uv_timer_stop((uv_timer_t*)handle); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_TIMER_CLOSE(handle, cb) \
	({ int __ret = 0;\
		do { \
			SAFE_UV_TIMER_STOP(handle); \
			SAFE_UV_CLOSE(handle, cb); \
		} while(0); \
		__ret; \
	})

//** async **
#define SAFE_UV_ASYNC(async) \
	do { \
		if ( uv_is_active((uv_handle_t*)async) ) \
		{ \
			uv_async_send((uv_async_t*)async); \
		} \
	} while(0);

#define SAFE_UV_ASYNC_EX(ptr) SAFE_UV_ASYNC(&ptr->uv_async_fd)
#define SAFE_UV_ASYNC_INIT(loop, async, async_cb) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(loop)) && (pcheck(async)) ) \
			{ \
				__ret = uv_async_init((uv_loop_t*)loop, (uv_async_t*)async, async_cb); \
			} \
		} while(0); \
		__ret; \
	})

//** tty **
#define SAFE_UV_TTY_INIT(loop, handle, fd, unused) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(loop)) && (pcheck(handle))  ) \
			{ \
				__ret = uv_tty_init((uv_loop_t*)loop, (uv_tty_t*)handle, fd, unused); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_TTY_SET_MODE(handle, mode) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(handle))  ) \
			{ \
				__ret = uv_tty_set_mode((uv_tty_t*)handle, mode); \
			} \
		} while(0); \
		__ret; \
	})

//** buffer **
#define SAFE_UV_BUF_INIT(base, len) \
	({ uv_buf_t __ret = 0;\
		do { \
			if ( (pcheck(base)) && (len>0)  ) \
			{ \
				__ret = uv_buf_init((char*)base, len); \
			} \
		} while(0); \
		__ret; \
	})

//** stream **
#define SAFE_UV_PIPE_INIT(loop, handle, ipc) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(loop)) && (pcheck(handle))  ) \
			{ \
				__ret = uv_pipe_init((uv_loop_t*)loop, (uv_pipe_t*)handle, ipc); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_PIPE_OPEN(handle, file) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(handle)) ) \
			{ \
				__ret = uv_pipe_open((uv_pipe_t*)handle, file); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_READ_START(stream, alloc_cb, read_cb) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(stream)) ) \
			{ \
				__ret = uv_read_start((uv_stream_t*)stream, alloc_cb, read_cb); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_SET_BLOCKING(stream, blocking) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(stream)) ) \
			{ \
				__ret = uv_stream_set_blocking((uv_stream_t*)stream, blocking); \
			} \
		} while(0); \
		__ret; \
	})

//** queue **
#define SAFE_UV_QUEUE_WORK(loop, req, cb, cb_fin) \
	({ int __ret = 0;\
		do { \
			if ( (pcheck(loop)) && (pcheck(req))) \
			{ \
				__ret = uv_queue_work((uv_loop_t*)loop, (uv_work_t*)req, cb, cb_fin); \
			} \
		} while(0); \
		__ret; \
	})

//** thread & lock **
#define SAFE_UV_THREAD_CREATE(tid, entry, arg) \
	({ int __ret = 0;\
		do { \
			if (pcheck(tid)) \
			{ \
				__ret = uv_thread_create((uv_thread_t *)tid, entry, arg); \
			} \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_MUTEX_INIT(x) uv_mutex_init_recursive(x)
#define SAFE_UV_MUTEX_DESTROY(x) uv_mutex_destroy(x)
#define SAFE_UV_COND_INIT(x) uv_cond_init(x)
#define SAFE_UV_COND_DESTROY(x) uv_cond_destroy(x)

#define SAFE_UV_LOCK(x) uv_mutex_trylock(x)
#define SAFE_UV_UNLOCK(x) uv_mutex_unlock(x)
#define SAFE_UV_SIGNAL(x) uv_cond_signal(x)
#define SAFE_UV_BROADCAST(x) uv_cond_broadcast(x)
#define SAFE_UV_WAIT(in_cond, in_mtx) \
	do { \
		uv_cond_wait(in_cond, in_mtx); \
	} while(0);

#define SAFE_UV_TIMEWAIT(in_cond, in_mtx, msec) \
	({ int __ret = 0;\
		do { \
			__ret = uv_cond_timedwait(in_cond, in_mtx, msec*(NANOSEC/1000)); \
		} while(0); \
		__ret; \
	})

#define SAFE_UV_MUTEX_INIT_EX(ptr) SAFE_UV_MUTEX_INIT(&ptr->uv_mtx)
#define SAFE_UV_MUTEX_DESTROY_EX(ptr) SAFE_UV_MUTEX_DESTROY(&ptr->uv_mtx)
#define SAFE_UV_COND_INIT_EX(ptr) SAFE_UV_COND_INIT(&ptr->uv_cond)
#define SAFE_UV_COND_DESTROY_EX(ptr) SAFE_UV_COND_DESTROY(&ptr->uv_cond)
#define SAFE_UV_LOCK_EX(ptr) SAFE_UV_LOCK(&ptr->uv_mtx)
#define SAFE_UV_UNLOCK_EX(ptr) SAFE_UV_UNLOCK(&ptr->uv_mtx)
#define SAFE_UV_SIGNAL_EX(ptr) SAFE_UV_SIGNAL(&ptr->uv_cond);
#define SAFE_UV_BROADCAST_EX(ptr) SAFE_UV_BROADCAST(&ptr->uv_cond);
#define SAFE_UV_WAIT_EX(ptr, msec) SAFE_UV_WAIT(&ptr->uv_cond, &ptr->uv_mtx)
#define SAFE_UV_TIMEWAIT_EX(ptr, msec) SAFE_UV_TIMEWAIT(&ptr->uv_cond, &ptr->uv_mtx, msec)

#define SAFE_UV_THREAD_JOIN_EX(x) uv_thread_join(x)

//** error **
#define SAFE_UV_STRERROR(err) \
	({ const char* __ret = 0;\
		do { \
			__ret = uv_strerror(err); \
		} while(0); \
		__ret; \
	})

typedef struct UvWriteEx_STRUCT
{
	uv_write_t req;
	uv_buf_t buf;
	uv_write_cb cb;
} UvWriteEx_t;

#define MAX_OF_SPAWN_ARGS 10

typedef struct
{
	char name[LEN_OF_CMDLINE];
	int quit;

	uv_loop_t *loop;
	uv_process_t child_req;

	int argc;
	char *args[MAX_OF_SPAWN_ARGS];

	uv_stdio_container_t stdio[3];

	uv_pipe_t pipe_in;
	uv_pipe_t pipe_out;
	uv_read_cb pipe_out_cb;

	unsigned int flags;
	uv_process_options_t options;
	uv_exit_cb exit_cb;
} SpawnX_t;

typedef struct
{
	char name[LEN_OF_NAME32];
	char filename[LEN_OF_FULLNAME];
	int isquit;

	uv_loop_t *loop;
	uv_fs_event_t req;

	unsigned int flags; // UV_FS_EVENT_WATCH_ENTRY, UV_FS_EVENT_STAT, UV_FS_EVENT_RECURSIVE 
	uv_fs_event_cb detect_cb;
} UvEvent_t;

void uv_loop_close_ex(uv_loop_t *loop);
void uv_write_ex(uv_stream_t *dest, size_t size, char *buf, uv_write_cb cb);

void uv_spawn_close_ex(SpawnX_t *spawn_req);
void uv_spawn_open_ex(SpawnX_t *spawn_req);
void uv_spawn_simple_detached(SpawnX_t *spawn_req, int num, ...);

void uv_event_close_ex(UvEvent_t *event_req);
void uv_event_open_ex(UvEvent_t *event_req);

#endif


//******************************************************************************
//** UTIL_EX_DBUS **
//******************************************************************************
#ifdef UTIL_EX_DBUS
#include <dbus/dbus.h>

#ifndef TIMEOUT_OF_DBUS_REPLY
#define TIMEOUT_OF_DBUS_REPLY                     5000
#endif

#define SAFE_DBUS_MSG_FREE(X) \
	do { if ( (X) != NULL ) {dbus_message_unref(X); X=NULL;} } while(0)
#define SAFE_DBUS_CONN_FREE(X) \
	do { if ( (X) != NULL ) {dbus_connection_close(X); dbus_connection_unref(X); X=NULL;} } while(0)
#define SAFE_DBUS_ERR_INIT(X) \
	do { dbus_error_init(X); } while(0)
#define SAFE_DBUS_ERR_FREE(X) \
	do { dbus_error_free(X); } while(0)

typedef int dbusx_match_fn(DBusConnection *dbus_listen, DBusError *err, void *usr_data);
typedef DBusHandlerResult dbusx_filter_fn(DBusConnection *connection, DBusMessage *message, void *usr_data);

typedef struct DbusX_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isfree;
	int isinit;
	int isgdbus; // DbusX & gdbus run at the same time.

	char path[LEN_OF_NAME64];
	DBusConnection *dbus_conn;
	DBusConnection *dbus_conn_listen;
	
	dbusx_match_fn *add_match_cb;
	dbusx_filter_fn *filter_user_cb;

	void *data;
} DbusX_t;

DBusHandlerResult demo_signal_cb(DBusConnection *connection, DBusMessage *message, void *usr_data);
DBusHandlerResult demo_signal_name_cb(DBusConnection *connection, DBusMessage *message, const char *signal_name, void *usr_data);

int dbusx_signal_simple(DBusConnection *dbus_conn, char *dbus_path, const char *ifac,char *cmd, int itype, void *arg);
int dbusx_signal_str(DbusX_t *dbusx_req, const char *ifac, char *cmd, char *arg);
int dbusx_signal_helper(DbusX_t *dbusx_req, const char *ifac, char *cmd, int itype, void *arg);

DBusHandlerResult dbusx_method_echo_cb(DBusConnection *connection, DBusMessage *message, void *usr_data);
char *dbusx_method_key_val(DBusConnection *dbus_conn, char *dbus_path, const char *dest, const char *ifac, char *cmd, char *key, const char *val, int timeout);
char *dbusx_method_simple(DBusConnection *dbus_conn, char *dbus_path, const char *dest, const char *ifac, char *cmd, int itype, void *arg, int otype, int timeout);
char *dbusx_method_str2str(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, char *arg, int timeout);
char *dbusx_method_str2int(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, char *arg, int timeout);
char *dbusx_method_xint2uint(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, int itype, unsigned int *arg, int timeout);
void dbusx_method_str2null(DbusX_t *dbusx_req, const char *dest, const char *ifac, char *cmd, char *arg, int timeout);

void dbusx_shutdown(void);
void dbusx_conn_free(DbusX_t *dbusx_req);
int dbusx_client_init(DbusX_t *dbusx_req);

DBusConnection *dbusx_listen_get(DbusX_t *dbusx_req);
DBusConnection *dbusx_conn_get(DbusX_t *dbusx_req);
char *dbusx_path_get(DbusX_t *dbusx_req);

void dbusx_lock(DbusX_t *dbusx_req);
void dbusx_unlock(DbusX_t *dbusx_req);
void dbusx_wakeup_simple(DbusX_t *dbusx_req);
void dbusx_wakeup(DbusX_t *dbusx_req);
int dbusx_timewait_simple(DbusX_t *dbusx_req, int ms);
int dbusx_timewait(DbusX_t *dbusx_req, int ms);
void dbusx_wait_simple(DbusX_t *dbusx_req);
void dbusx_wait(DbusX_t *dbusx_req);

READY_ID dbusx_ready(DbusX_t *dbusx_req);
void dbusx_req_init(DbusX_t *dbusx_req, char *name, char *path, void *data);
int dbusx_req_check(DbusX_t *dbusx_req);

int dbusx_thread_init(dbusx_match_fn *match_cb, dbusx_filter_fn *filter_cb, DbusX_t *dbusx_req);
void dbusx_thread_stop(DbusX_t *dbusx_req);
void dbusx_thread_close(DbusX_t *dbusx_req);

#endif


//******************************************************************************
//** UTIL_EX_USB **
//******************************************************************************
#ifdef UTIL_EX_USB
#include <libusb-1.0/libusb.h>

#define RETRY_OF_ACCESS_USBX 3
#define DELAY_OF_WAIT_USBX (200) // ms
#define RETRY_OF_WAIT_USBX (10) // 0.2 * 10 s
#define USE_USBX_THREAD_CLOCK
#define LEN_OF_USB_BUFFER LEN_OF_BUF512

typedef struct UsbX_STRUCT
{
	ThreadX_t tidx;

	int usb_isfree;

	libusb_context *usb_req;
	libusb_device_handle *usb_dev_handle;
	struct libusb_transfer *usb_dev_transfer;

	ssize_t usb_cnt;
	libusb_device **usb_list;

	int vendor_id;
	int product_id;

	libusb_hotplug_callback_handle usb_hotplug_handle;
	libusb_hotplug_callback_fn usb_hotplug_fn;

	uint8_t usb_reset;

	uint8_t usb_iface_idx;
	int usb_claim;
	char usb_path[LEN_OF_VAL32];
	uint8_t usb_endpoint;

	uint8_t bmAttributes;
	uint8_t wMaxPacketSize;

	size_t res_size;
	unsigned char response[LEN_OF_USB_BUFFER];
	size_t req_size;
	unsigned char request[LEN_OF_USB_BUFFER];

	unsigned int usb_timeout;

	int dbg_lvl;

	void *user_data;
} UsbX_t;

void usbX_dev_print_endpoint(const struct libusb_endpoint_descriptor *usb_endpoint);
void usbX_dev_print_iface_desc(const struct libusb_interface_descriptor *usb_altsetting);
void usbX_dev_print_iface(const struct libusb_interface *usb_interface);
void usbX_dev_print_cfg(struct libusb_config_descriptor *usb_config);
void usbX_dev_print_handle(libusb_device_handle *usb_dev_handle);
void usbX_dev_print_ex(UsbX_t *usbX_req);

void usbX_dev_transfer_free(UsbX_t *usbX_req);
void usbX_dev_read_poll_free(UsbX_t *usbX_req);
int usbX_dev_read_poll(UsbX_t *usbX_req, libusb_transfer_cb_fn callback);

void usbX_dev_response_reset(UsbX_t *usbX_req);
int usbX_dev_read(UsbX_t *usbX_req, unsigned int usb_timeout);
int usbX_dev_write(UsbX_t *usbX_req, int *nwrite, unsigned int usb_timeout);

void usbX_dev_path(struct libusb_device *usb_dev, char *usb_path, int len);
int usbX_dev_open(UsbX_t *usbX_req, struct libusb_device *usb_dev);
void usbX_dev_close(UsbX_t *usbX_req);

int usbX_hotplug_register(UsbX_t *usbX_req);

void usbX_lock(UsbX_t *usbX_req);
void usbX_unlock(UsbX_t *usbX_req);
void usbX_signal(UsbX_t *usbX_req);
int usbX_timewait(UsbX_t *usbX_req, int ms);
void usbX_wait(UsbX_t *usbX_req);
int usbX_timewait_simple(UsbX_t *usbX_req, int ms);
void usbX_wakeup_simple(UsbX_t *usbX_req);

int usbX_thread_isloop(UsbX_t *usbX_req);

void usbX_listen_close(UsbX_t *usbX_req);
int usbX_listen_open(UsbX_t *usbX_req, void *user_data);

void usbX_close(UsbX_t *usbX_req);
int usbX_browse(UsbX_t *usbX_req, void *user_data);

#endif


//******************************************************************************
//** UTIL_EX_UCI **
//******************************************************************************
#ifdef UTIL_EX_UCI
#include <uci.h>

#define UCI_CFG_WIRELESS "/etc/config/wireless"
#define UCI_CFG_DEMO "/etc/config/demo"

#define UCI_PKG_FREE(ctx, pkg) \
	do { \
		if ( (ctx) && (pkg) ) { \
			uci_unload(ctx, pkg); \
			pkg=NULL;\
		} \
	} while(0)

#define uci_req_FREE(X) \
	do { \
		if ( (X) != NULL ) { \
			uci_free_context(X); \
			X=NULL;\
		} \
	} while(0)

#define UCI_LOAD(filename, pkg) \
	({ struct uci_context *__ret = NULL; \
		do { \
			__ret = uci_alloc_context(); \
			if (__ret) \
			{ \
				if (UCI_OK != uci_load(__ret, filename, &pkg)) \
				{ \
					uci_req_FREE(__ret); \
					DBG_ER_LN("uci_load error !!! (uci_filename: %s, uci_pkg: %p)", filename, pkg); \
				} \
			} \
		} while(0); \
		__ret; \
	})

typedef struct UCIX_STRUCT
{
	char *uci_filename;
	struct uci_context *uci_req; 
	struct uci_package *uci_pkg;

} UCIX_t;

#define UCI_FOREACH_ITEM(_list, _ptr) uci_foreach_element(_list, _ptr)

#define UCI_LIST_FREE(u_req, u_name, u_key) \
	({ int __ret = -1; \
		__ret = uci_list_free(u_req, u_name, u_key); \
		__ret; \
	})

#define UCI_LIST_DEL(u_req, u_name, u_key, u_val) \
	({ int __ret = -1; \
		__ret = uci_list_del_ex(u_req, u_name, u_key, u_val); \
		__ret; \
	})

#define UCI_LIST_ADD(u_req, u_name, u_key, u_val) \
	({ int __ret = -1; \
		__ret = uci_list_add_ex(u_req, u_name, u_key, u_val); \
		__ret; \
	})

#define UCI_OPTION_DEL(u_req, u_name, u_key) \
	({ int __ret = -1; \
		__ret = uci_option_del_ex(u_req, u_name, u_key); \
		__ret; \
	})

#define UCI_OPTION_SET_STR(u_req, u_name, u_key, u_val) \
	({ int __ret = -1; \
		__ret = uci_option_set_str(u_req, u_name, u_key, u_val); \
		__ret; \
	})

#define UCI_OPTION_GET_STR(u_req, u_name, u_key) \
	({ const char *__ret = NULL; \
		__ret = uci_option_get_str(u_req, u_name, u_key); \
		__ret; \
	})

#define UCI_OPTION_GET_ASTR(u_req, u_name, u_key, buf) \
	({ int __ret =0; \
		do { \
			const char *u_val = NULL; \
			if ( ( u_val = UCI_OPTION_GET_STR(u_req, u_name, u_key) ) ) \
				__ret = asprintf(&buf, "%s", u_val); \
			else \
				__ret = asprintf(&buf, "\n"); \
		} while(0); \
		__ret; \
	})

#define UCI_SESSION_DEL(u_req, u_name) \
	({ int __ret = -1; \
		__ret = uci_section_del(u_req, u_name); \
		__ret; \
	})

#define UCI_SESSION_GET(u_req, u_name) \
	({ struct uci_section *__ret = NULL; \
		__ret = uci_section_get(u_req, u_name); \
		__ret; \
	})

#define UCI_SESSION_SET(u_req, u_type, u_name) \
	({ struct uci_section *__ret = NULL; \
		__ret = uci_section_set(u_req, u_type, u_name); \
		__ret; \
	})

#define UCI_CLOSE(u_req) uci_close(u_req)
#define UCI_OPEN(u_req) \
	({ int __ret = -1; \
		__ret = uci_open(u_req); \
		__ret; \
	})

int uci_list_free(UCIX_t *uci_req, const char *u_name, const char *u_key);
int uci_list_del_ex(UCIX_t *uci_req, const char *u_name, const char *u_key, const char *u_val);
int uci_list_add_ex(UCIX_t *uci_req, const char *u_name, const char *u_key, const char *u_val);

int uci_option_del_ex(UCIX_t *uci_req, const char *u_name, const char *u_key);
int uci_option_set_str(UCIX_t *uci_req, const char *u_name, const char *u_key, const char *u_val);
const char *uci_option_get_str(UCIX_t *uci_req, const char *u_name, const char *u_key);
struct uci_option *uci_option_get_obj(UCIX_t *uci_req, const char *u_name, const char *u_key);

struct uci_section *uci_section_get(UCIX_t *uci_req, const char *u_name);
int uci_section_del(UCIX_t *uci_req, const char *u_name);
struct uci_section *uci_section_set(UCIX_t *uci_req, const char *u_type, const char *u_name);

void uci_show_value_ex(struct uci_option *u_option);
void uci_show_section_ex(struct uci_section *u_section);
int uci_show_what_ex(UCIX_t *uci_req, char *u_config);
int uci_show_configs_ex(UCIX_t *uci_req);

void uci_close(UCIX_t *uci_req);
int uci_open(UCIX_t *uci_req);

#endif


//******************************************************************************
//** UTIL_EX_UBOX **
//******************************************************************************
#ifdef UTIL_EX_UBOX
#include <libubox/ulog.h>

// ULOG_KMSG -> /dev/kmsg
// ULOG_SYSLOG -> vsyslog()
// ULOG_STDIO -> stderr
#define ULOG_OPEN(ch, fac, id) ulog_open(ch, fac, id)
#define ULOG_OPEN_SUSER(id) ULOG_OPEN(ULOG_SYSLOG, LOG_USER, id)

#define ULOG_LVL_SET(x) ulog_threshold(x)

#define ULOG_ER_LN(fmt, ...) ULOG_ERR(COLORX_RED "[%02ld/%u] %s:%d - " fmt "" COLORX_NONE "\n", (long) getpid(), (unsigned int)gettidv1_ex(), __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define ULOG_ER(fmt, ...) ULOG_ERR(fmt, ## __VA_ARGS__)
#define ULOG_WN_LN(fmt, ...) ULOG_WARN(COLORX_PURPLE "[%02ld/%u] %s:%d - " fmt "" COLORX_NONE "\n", (long) getpid(), (unsigned int)gettidv1_ex(), __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define ULOG_WN(fmt, ...) ULOG_WARN(fmt, ## __VA_ARGS__)
#define ULOG_IF_LN(fmt, ...) ULOG_NOTE(COLORX_YELLOW "[%02ld/%u] %s:%d - " fmt "" COLORX_NONE "\n", (long) getpid(), (unsigned int)gettidv1_ex(), __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define ULOG_IF(fmt, ...) ULOG_NOTE(fmt, ## __VA_ARGS__)
#define ULOG_DB_LN(fmt, ...) ULOG_INFO(COLORX_WHITE "[%02ld/%u] %s:%d - " fmt "" COLORX_NONE "\n", (long) getpid(), (unsigned int)gettidv1_ex(), __FUNCTION__, __LINE__, ## __VA_ARGS__)
#define ULOG_DB(fmt, ...) ULOG_INFO(fmt, ## __VA_ARGS__)

#define ULOG_CLOSE() ulog_close()
#else
#define ULOG_OPEN(ch, fac, id)
#define ULOG_OPEN_SUSER(id)

#define ULOG_LVL_SET(x)

#define ULOG_ER_LN(fmt, ...)
#define ULOG_ER(fmt, ...)
#define ULOG_WN_LN(fmt, ...)
#define ULOG_WN(fmt, ...)
#define ULOG_IF_LN(fmt, ...)
#define ULOG_IF(fmt, ...)
#define ULOG_DB_LN(fmt, ...)
#define ULOG_DB(fmt, ...)

#define ULOG_CLOSE()
#endif


//******************************************************************************
//** UTIL_EX_FASTCGI **
//******************************************************************************
#ifdef UTIL_EX_FASTCGI

char *fastcgi_path_get(char *filename, int port);

#endif


//******************************************************************************
//** UTIL_EX_YUAREL **
//******************************************************************************
#ifdef UTIL_EX_YUAREL
#include <yuarel.h>

#define MAX_OF_QUERY_PARAM 10

typedef struct yuarel_param yuarel_param_t;

typedef struct QueryParam_Struct
{
	int count;
	char query[LEN_OF_QUERY];
	char query_parse[LEN_OF_QUERY];
	yuarel_param_t params[MAX_OF_QUERY_PARAM];
} QueryParam_t;

char *query_uri_get(QueryParam_t *q_params_req);
int query_count_get(QueryParam_t *q_params_req);
yuarel_param_t *query_params_get(QueryParam_t *q_params_req);
yuarel_param_t *query_parser(char *query, QueryParam_t *q_params_req);

#endif


//******************************************************************************
//** UTIL_EX_WEBSOCKETS **
//******************************************************************************
#ifdef UTIL_EX_WEBSOCKETS
#include <libwebsockets.h>

#define WEBSOCKETS_OVER_MQTT_PORT_7680 7680
#define WEBSOCKETS_PORT_7681 7681
#define WEBSOCKETS_URMET_PORT_7682 7682

#define LEN_OF_WEBSOCKET LEN_OF_BUF_2MB
#define LEN_OF_LWS (LWS_SEND_BUFFER_PRE_PADDING + LEN_OF_WEBSOCKET + LWS_SEND_BUFFER_POST_PADDING)
#define MAX_OF_RING 8
#define MAX_OF_SESSION 8

#define LWS_SUB_PROTOCOL_HTTP "http"
//#define LWS_SUB_PROTOCOL_EXAMPLE "lws_example"

typedef enum
{
	LWS_PROTO_ID_HTTP,
	//LWS_PROTO_ID_EXAMPLE,
	LWS_PROTO_ID_MAX,
} LWS_PROTO_ID;

typedef enum
{
	LWS_WSI_ID_CLIENT,
	LWS_WSI_ID_SERVER,
	LWS_WSI_ID_MAX,
} LWS_WSI_ID;

typedef struct LWSMsg_Struct
{
	void* next;

	char *payload;
	int payload_len;
} LWSMsg_t;

typedef struct LWSSession_Struct
{
	void* next;

	int use_foreign_loops;
	struct lws *wsi;
	//pthread_mutex_t in_mtx;
	CLIST_STRUCT(msg_list);
} LWSSession_t;

typedef struct LWSX_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isfree;
	int dbg_more;

	int isecho;
	LWS_WSI_ID wsi_id;

	int security;
	char certificate_file[LEN_OF_FULLNAME];
	char privatekey_file[LEN_OF_FULLNAME];

	struct lws_context_creation_info cinfo;
	struct lws_context *context;
	int timeout_ms;

	struct lws_client_connect_info ccinfo;
	char hostname[LEN_OF_HOSTNAME];

	lws_callback_function *callback;

	CLIST_STRUCT(session_list);

	char tx[LEN_OF_LWS];
	int tx_size;
	char rx[LEN_OF_LWS];
	int rx_size;
} LWSX_t;

#define SAFE_LWS_MEMCPY(dst, src, count, maxcount) \
	SAFE_MEMCPY(dst+LWS_SEND_BUFFER_PRE_PADDING, src, count, maxcount)

#define SAFE_LWS_WRITE(wsi, buf, len, wp) \
	lws_write(wsi, (unsigned char *)buf+LWS_SEND_BUFFER_PRE_PADDING, len, wp)

#if (0)
#define LWS_TX_PRINT(x) \
	if (pcheck(x)) \
	{ \
		LWSX_t *ctx = x; \
		char *body = ctx->tx + LWS_SEND_BUFFER_PRE_PADDING; \
		if (ctx->dbg_more<DBG_LVL_MAX) DBG_IF_LN("(tx_size: %d, body: %s)", ctx->tx_size, body); \
	}

#define LWS_RX_PRINT(x) \
	if (pcheck(x)) \
	{ \
		LWSX_t *ctx = x; \
		char *body = ctx->rx + LWS_SEND_BUFFER_PRE_PADDING; \
		if (ctx->dbg_more<DBG_LVL_MAX) DBG_IF_LN("(rx_size: %d, body: %s)", ctx->rx_size, body); \
	}
#endif

char* translate_lws_cb(enum lws_callback_reasons reason);

LWSX_t *lws2_protocol_user(struct lws *wsi);

void lws2_session_lock(LWSSession_t *session);
void lws2_session_unlock(LWSSession_t *session);
void lws2_session_pop(LWSX_t *lws_req, LWSSession_t *session);

void lws2_session_write(LWSSession_t *session);
void lws2_session_write_q_push(LWSSession_t *session, char *payload, int payload_len);
void lws2_session_write_q_broadcast(LWSX_t *lws_req, char *payload, int payload_len);
int lws2_session_count(LWSX_t *lws_req);

void lws2_lock(LWSX_t *lws_req);
void lws2_unlock(LWSX_t *lws_req);

void lws2_cli_init(LWSX_t *lws_req, struct lws_protocols *protocols, unsigned int options, uv_loop_t *loop);
void lws2_cli_open(LWSX_t *lws_req, char *address, int port, char *filename);
//void lws2_cli_close(LWSX_t *lws_req);

void lws2_srv_init(LWSX_t *lws_req, int port, struct lws_protocols *protocols, unsigned int options, uv_loop_t *loop);

void lws2_thread_stop(LWSX_t *lws_req);
void lws2_thread_close(LWSX_t *lws_req);
void lws2_thread_init(LWSX_t *lws_req);

#endif


//******************************************************************************
//** UTIL_EX_MQTT **
//******************************************************************************
#ifdef UTIL_EX_MQTT
#include <mosquitto.h>

#define LEN_OF_CLIENT_ID LEN_OF_VAL32
#define MAX_OF_QPUB     30
#define MAX_OF_QSUB     30

// methodid/c_macid/c_uuid/c_nodeid/epid/issue
#define MQTT_TOPIC_SUB_ROOT_MASK "%s%s+/#"

#define MQTT_TOPIC_SUB_ROOT_MASK_METHODID "%s%s%d/#"
#define MQTT_TOPIC_SUB_ROOT_MASK_METHODID_MACID "%s%s%d/%s/#"
#define MQTT_TOPIC_SUB_ROOT_MASK_METHODID_MACID_NODEID_EPID_ISSUEID "%s%s%d/%s/%s/%d/%d/%08X"

typedef void mqtt_log_fn(struct mosquitto *mosq, void *userdata, int level, const char *str);
typedef void mqtt_connect_fn(struct mosquitto *mosq, void *userdata, int result);
typedef void mqtt_disconnect_fn(struct mosquitto *mosq, void *userdata, int result);
typedef void mqtt_message_fn(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);

typedef enum
{
	MQTT_TOPIC_ID_NONE,
	MQTT_TOPIC_ID_USER,
	MQTT_TOPIC_ID_CLIENTID,
	MQTT_TOPIC_ID_MAX,
} MQTT_TOPIC_ID;

typedef struct MQTTSub_Struct
{
	void* next;

	char topic[LEN_OF_TOPIC];
	mqtt_message_fn *message_cb;
} MQTTSub_t;

typedef struct MQTTSession_Struct
{
	void *mqtt_req;
	struct mosquitto *mosq;
	char macid[LEN_OF_MAC];

	char hostname[LEN_OF_HOSTNAME];
	int port;
	int keepalive;
	char topic_root[LEN_OF_TOPIC];
	MQTT_TOPIC_ID topic_id;

	bool clean_session;
	char clientid[LEN_OF_CLIENT_ID];

	char user[LEN_OF_USER];
	char pass[LEN_OF_PASS];

	char tls_version[LEN_OF_VAL16];
	char certificate_file[LEN_OF_FULLNAME];
	char privatekey_file[LEN_OF_FULLNAME];
	char ca_file[LEN_OF_FULLNAME];

	int isconnect;
	int count;

	QueueX_t *qpub;
	QueueX_t *qsub;

	CLIST_STRUCT(sub_list);

	mqtt_log_fn *log_cb;
	mqtt_connect_fn *connect_cb;
	mqtt_disconnect_fn *disconnect_cb;

	mqtt_message_fn *root_subscribe_cb;

	void *sub_subscribe; // for libhoneyx
	void *mixture; // for libhoneyx

	void *data;
} MQTTSession_t;

typedef void mqtt_topic_fn(MQTTSession_t *session, char *topic, char *msg);

typedef struct MQTTTopic_Struct
{
	MQTTSession_t *session;
	char *topic;
	char *msg;
	mqtt_topic_fn *topic_cb;
} MQTTTopic_t;

typedef struct MQTTX_Struct
{
	char name[LEN_OF_NAME32];

	ThreadX_t tidx;

	int isfree;
	int isinit;
	int dbg_more;

	MQTTSession_t *session;
} MQTTX_t;

int mqtt_session_isconnect(MQTTX_t *mqtt_req);
MQTTSession_t *mqtt_session_get(MQTTX_t *mqtt_req);

int mqtt_publish(MQTTSession_t *session, char *topic, char *msg);

void mqtt_subscribe_add(MQTTSession_t *session, char *topic, mqtt_message_fn *message_cb);

void mqtt_qsub_add(MQTTSession_t *session, char *topic, char *msg, mqtt_topic_fn *topic_cb);
void mqtt_qpub_add(MQTTSession_t *session, char *topic, char *msg, mqtt_topic_fn *topic_cb);
void mqtt_queue_wakeup(MQTTSession_t *session);
void mqtt_queue_gosleep(MQTTSession_t *session);

void mqtt_srv_subscribe(MQTTSession_t *session);

void mqtt_lock(MQTTX_t *mqtt_req);
void mqtt_unlock(MQTTX_t *mqtt_req);
void mqtt_signal(MQTTX_t *mqtt_req);
int mqtt_timewait(MQTTX_t *mqtt_req, int ms);
void mqtt_wait(MQTTX_t *mqtt_req);
void mqtt_wakeup(MQTTX_t *mqtt_req);

int mqtt_isquit(MQTTX_t *mqtt_req);

void mqtt_thread_stop(MQTTX_t *mqtt_req);
void mqtt_thread_close(MQTTX_t *mqtt_req);
void mqtt_thread_init(MQTTX_t *mqtt_req);

#endif

#ifdef UTIL_EX_CRON

typedef enum
{
	CRON_ID_MINUTE = 0,
	CRON_ID_HOUR,
	CRON_ID_MDAY,
	CRON_ID_MONTH,
	CRON_ID_WDAY,
	CRON_ID_YEAR,
	CRON_ID_MAX,
} CRON_ID;

#define CRON_YEAR_START_2020 2020
#define CRON_YEAR_END_2120 2120
#define MAX_OF_CRON_RANGE 200 // > (CRON_YEAR_END_2020-CRON_YEAR_START_2020)
int cronx_validate(char *cron_txt, struct tm *kick_tm);

#endif

//******************************************************************************
//** END **
//******************************************************************************

#ifdef __cplusplus
}
#endif

#endif
