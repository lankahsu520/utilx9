#ifndef __REPORT_DEF_H__
#define __REPORT_DEF_H__

#include "stdint.h"

//******************************************************************************
//** define **
//******************************************************************************
#ifndef LEN_OF_MAC
#define LEN_OF_MAC 24
#endif
#ifndef LEN_OF_UUID
#define LEN_OF_UUID 40
#endif

typedef struct Identity_Struct
{
	char c_macid[LEN_OF_MAC]; // LEN_OF_MAC 24
	char c_uuid[LEN_OF_UUID]; // LEN_OF_UUID 40
	char c_nodeid[LEN_OF_UUID];
	uint8_t epid; // 0xFF
} Identity_t;

typedef struct Commander_Struct
{
	uint16_t methodid;
	uint16_t protocolid;
	Identity_t id_frm;
	Identity_t id_to;
} Commander_t;

typedef struct Reporter_Struct
{
	uint16_t methodid;
	uint16_t protocolid;
	Identity_t id_frm;
} Reporter_t;

typedef struct IssueItem_Struct
{
	union
	{
		Reporter_t reporter;
		Commander_t commander;
	};

	uint32_t issueid;
	uint16_t mode;
	uint16_t submode;
	uint16_t category;
	uint32_t timestamp;
	// 71+4+2+2+2+4 = 85

	uint16_t data_len; // to support 0xFF 0xFF
	char data[0xFF]; // 256
} IssueItem_t;

#endif
