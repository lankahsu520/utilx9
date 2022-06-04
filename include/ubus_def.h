#ifndef __UBUS_DEF_H__
#define __UBUS_DEF_H__

#define UBUS_UNIX_SOCKET_EX "/tmp/IoT/ubus.sock"

#define TIMEOUT_OF_UBUS_REPLY                     5000

#define TIMEOUT_OF_EVENT_200MSEC                  200

//#define SEND_EVENT_DIRECTLY

//******************************************************************************
// echo
//******************************************************************************
// -> echo

typedef enum
{
	UBUS_P_ECHO_ID_MSG,
	UBUS_P_ECHO_ID_MAX,
} UBUS_P_ECHO_ID;

#define UBUS_U_O_ECHO                             "u_o_echo" // unicast
#define UBUS_M_O_ECHO                             "m_o_echo" // multicast
#define UBUS_B_O_ECHO                             "b_o_echo" // broadcast
#define UBUS_M_ECHO                               "m_echo"
#define UBUS_P_ECHO_MSG                           "msg"

#endif
