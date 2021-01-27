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
#ifndef __BASIC_DEF_H__
#define __BASIC_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


//******************************************************************************
//** define **
//******************************************************************************
#define LEN_OF_USER 16
#define LEN_OF_PASS 16

#define LEN_OF_NAME32 32
#define LEN_OF_NAME64 64

#define LEN_OF_NAME_CPU LEN_OF_NAME32
#define LEN_OF_NAME_PROC LEN_OF_NAME32
#define LEN_OF_NAME_DEV LEN_OF_NAME32
#define LEN_OF_NAME_ONVIF_ACT LEN_OF_NAME64

#define LEN_OF_VAL16 16
#define LEN_OF_VAL32 32
#define LEN_OF_VAL48 48
#define LEN_OF_VAL64 64
#define LEN_OF_VAL80 80

#define LEN_OF_BUF128 128
#define LEN_OF_BUF256 256
#define LEN_OF_BUF512 512
#define LEN_OF_BUF1024 1024

#define LEN_OF_CMDLINE LEN_OF_BUF1024
#define LEN_OF_NEWLINE LEN_OF_BUF1024
#define LEN_OF_RESPONSE LEN_OF_BUF1024

#define LEN_OF_FILENAME256 256
#define LEN_OF_FILENAME512 512

#define MAX_OF_OVERLOAD 3 // Uptime_t
#define MAX_OF_FDSIZE 40 // ProcInfo_t
#define LEN_OF_SLINK 128 // FDInfo_t

#define LEN_OF_IP 30 // fro IPv4 and IPv6
#define LEN_OF_HOSTNAME 32 // must be < 68= 128-30*2
#define LEN_OF_SSID 32

#define LEN_OF_MAC 24
#define LEN_OF_UUID 40

#define LEN_OF_URL128 128
#define LEN_OF_URL256 256
#define LEN_OF_URL512 512
#define LEN_OF_URL1024 1024
#define LEN_OF_URL2048 2048

// HttpCtx_t, NetworkInfo_t, WSList_t
#define LEN_OF_URL LEN_OF_URL2048
// BackupInfo_t
#define LEN_OF_URL_BACKUP LEN_OF_URL
// for onvif
#define LEN_OF_URL_ONVIF LEN_OF_URL

#define LEN_OF_QUERY LEN_OF_URL1024

#define LEN_OF_SSL_BUFFER (16*1024)

#define LEN_OF_LOG (2048+1024) // HttpCtx_t
#define LEN_OF_RESERVE32 32

#define LEN_OF_2BYTES_DEFINE 0xffff
#define LEN_OF_1BYTE_DEFINE 0xff

#ifndef NANOSEC
#define NANOSEC ((uint64_t) 1e9)
#endif

#define A101_UID 0x78CE8AA2
#define A101_UID_UUID_FIRST "78CE8AA2"
#define A101_UUID_PREFIX A101_UID_UUID_FIRST"-7AE4-4875-8175"

#define ONVIF_UID 0xA397A255
#define ONVIF_UUID_FIRST "A397A255"
#define ONVIF_UUID_PREFIX ONVIF_UUID_FIRST"-53BE-41FC-996B"

#define YSTR(x) #x
#define XSTR(x) YSTR(x)

// Check if a bit is 1 or 0
#define CHECK_BIT(var, pos) !!((var) & (1 << (pos)))

#define X_JOIN_E(X,Y) X YSTR(Y)
#define X_JOIN(X,Y) X_JOIN_E(X,Y)

#define COMMAND_DELIMITED_NEWLINE '\n'
#define COMMAND_DELIMITED_RETURN '\r'
#define COMMAND_DELIMITED_NULL '\0'
#define COMMAND_DELIMITED_ALL "\r\n\0"

#define time32_t uint32_t
#define time64_t uint64_t
#define timeX_t time32_t

#define ROUNDING_NUM 0.5

typedef enum
{
	READY_ID_NONE,
	READY_ID_OK,
	READY_ID_MAX,
} READY_ID;

typedef enum
{
	QUIT_ID_NONE,
	QUIT_ID_NOW,
	QUIT_ID_MAX,
} QUIT_ID;


//******************************************************************************
//** DBG **
//******************************************************************************
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define gettidv1_ex() syscall(__NR_gettid)
#define gettidv2_ex() syscall(SYS_gettid)

#define DBG_TXT_BUSY "Busy!!!"
#define DBG_TXT_ENTER "__________ Enter __________"
#define DBG_TXT_BYE_BYE "Bye-Bye !!!"
#define DBG_TXT_CRC_ERROR "CRC error !!!"
#define DBG_TXT_FOUND "Found !!!"
#define DBG_TXT_GOT "Got !!!"
#define DBG_TXT_LAUNCH_THREAD "Launch a new thread !!!"
#define DBG_TXT_HELLO_WORLD "Hello world !!!"
#define DBG_TXT_LINKED "Linked !!!"
#define DBG_TXT_NO_SUPPORT "No support !!!"
#define DBG_TXT_NON_IMPLEMENT "Non-implement !!!"
#define DBG_TXT_START "Start !!!"
#define DBG_TXT_UTF8_ERROR "UTF-8 error !!!"
#define DBG_TXT_WRONG "Wrong !!!"

//** debug **
#define COLOR_NONE "\033[0m"
#define COLOR_RED "\033[0;32;31m"
#define COLOR_LIGHT_RED "\033[1;31m"
#define COLOR_GREEN "\033[0;32;32m"
#define COLOR_LIGHT_GREEN "\033[1;32m"
#define COLOR_BLUE "\033[0;32;34m"
#define COLOR_LIGHT_BLUE "\033[1;34m"
#define COLOR_DARY_GRAY "\033[1;30m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_LIGHT_CYAN "\033[1;36m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_LIGHT_PURPLE "\033[1;35m"
#define COLOR_BROWN "\033[0;33m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_LIGHT_GRAY "\033[0;37m"
#define COLOR_WHITE "\033[1;37m"

#define DBG_LVL_ERROR        0
#define DBG_LVL_WARN         1
#define DBG_LVL_INFO         2
#define DBG_LVL_DEBUG        3
#define DBG_LVL_TRACE        4
#define DBG_LVL_MAX          5

#define DBG_LN_COLOR(color, format, args...) printf(color"[%02ld/%u] %s:%d - "format""COLOR_NONE"\n",  (long) getpid(), (unsigned int)gettidv1_ex(), __FUNCTION__, __LINE__, ## args)
#define DBG_LN_COLOR_0(color, format, args...) printf(color""format""COLOR_NONE"", ## args)

#define DBG_LN_R(format,args...) DBG_LN_COLOR(COLOR_RED, format, ## args)
#define DBG_LN_R_0(format,args...) DBG_LN_COLOR_0(COLOR_RED, format, ## args)
#define DBG_LN_LR(format,args...) DBG_LN_COLOR(COLOR_LIGHT_RED, format, ## args)
#define DBG_LN_LR_0(format,args...) DBG_LN_COLOR_0(COLOR_LIGHT_RED, format, ## args)
#define DBG_LN_G(format,args...) DBG_LN_COLOR(COLOR_GREEN, format, ## args)
#define DBG_LN_G_0(format,args...) DBG_LN_COLOR_0(COLOR_GREEN, format, ## args)
#define DBG_LN_LG(format,args...) DBG_LN_COLOR(COLOR_LIGHT_GREEN, format, ## args)
#define DBG_LN_LG_0(format,args...) DBG_LN_COLOR_0(COLOR_LIGHT_GREEN, format, ## args)
#define DBG_LN_B(format,args...) DBG_LN_COLOR(COLOR_BLUE, format, , ## args)
#define DBG_LN_B_0(format,args...) DBG_LN_COLOR_0(COLOR_BLUE, format, ## args)
#define DBG_LN_LB(format,args...) DBG_LN_COLOR(COLOR_LIGHT_BLUE, format, ## args)
#define DBG_LN_LB_0(format,args...) DBG_LN_COLOR_0(COLOR_LIGHT_BLUE, format, ## args)
#define DBG_LN_DGR(format,args...) DBG_LN_COLOR(COLOR_DARY_GRAY, format, ## args)
#define DBG_LN_C(format,args...) DBG_LN_COLOR(COLOR_CYAN, format, ## args)
#define DBG_LN_C_0(format,args...) DBG_LN_COLOR_0(COLOR_CYAN, format, ## args)
#define DBG_LN_LC(format,args...) DBG_LN_COLOR(COLOR_LIGHT_CYAN, format, ## args)
#define DBG_LN_LC_0(format,args...) DBG_LN_COLOR_0(COLOR_LIGHT_CYAN, format, ## args)
#define DBG_LN_P(format,args...) DBG_LN_COLOR(COLOR_PURPLE, format, ## args)
#define DBG_LN_P_0(format,args...) DBG_LN_COLOR_0(COLOR_PURPLE, format, ## args)
#define DBG_LN_LP(format,args...) DBG_LN_COLOR(COLOR_LIGHT_PURPLE, format, ## args)
#define DBG_LN_LP_0(format,args...) DBG_LN_COLOR_0(COLOR_PURPLE, format, ## args)
#define DBG_LN_BR(format,args...) DBG_LN_COLOR(COLOR_BROWN, format, ## args)
#define DBG_LN_Y(format,args...) DBG_LN_COLOR(COLOR_YELLOW, format, ## args)
#define DBG_LN_Y_0(format,args...) DBG_LN_COLOR_0(COLOR_YELLOW, format, ## args)
#define DBG_LN_LGR(format,args...) DBG_LN_COLOR(COLOR_LIGHT_GRAY, format, ## args)
#define DBG_LN_LGR_0(format,args...) DBG_LN_COLOR_0(COLOR_LIGHT_GRAY, format, ## args)
#define DBG_LN_W(format,args...) DBG_LN_COLOR(COLOR_WHITE, format, ## args)
#define DBG_LN_W_0(format,args...) DBG_LN_COLOR_0(COLOR_WHITE, format, ## args)

#define BUFF_DUMP_BUFF(ibuf, ilen, delim, prefix, obuf, olen) \
	({ int __ret = 0; \
		do { \
			if ( (pcheck(ibuf)) && (pcheck(obuf)) ) \
			{ \
				int k =0; \
				for (k = 0; k < ilen; k++) \
				{ \
					if (k>0) __ret += snprintf(obuf + __ret, olen-__ret, delim""prefix"%02X", (0xff & (char)ibuf[k]) ); \
					else __ret += snprintf(obuf + __ret, olen-__ret, prefix"%02X", (0xff & (char)ibuf[k]) ); \
				} \
			} \
		} while(0); \
		__ret; \
	})

#define BUFF_DUMP_FP(fp, ibuf, ilen) \
	{ int k =0; \
		for (k = 0; k < ilen; k++) \
		{ \
			fprintf(fp,"%02X", ibuf[k]); \
		} \
	}

#define DBG_DUMP_COLOR(color, ibuf, ilen, delim, format, args...) \
	{ int k =0; \
		char* dbuf = (char* )ibuf; \
		printf(color"[%02ld/%u] %s:%d - "format" {", (long) getpid(), (unsigned int)gettidv1_ex(),  __FUNCTION__, __LINE__, ## args); \
		for (k=0; k<ilen; k++) \
		{ \
			if ((k%16) ==0) printf("\n    %02X", (0xff & (char)dbuf[k]) ); \
			else printf(delim"%02X", (0xff & (char)dbuf[k]) ); \
		} \
			printf("\n}\n"COLOR_NONE); \
	}


#ifdef __cplusplus
}
#endif

#endif
