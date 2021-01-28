#ifndef __ZWAVE_DEF_H__
#define __ZWAVE_DEF_H__

//******************************************************************************
//** define **
//******************************************************************************
//--------------------
//** debug **
//--------------------
#define FIXED_DEBUG_MORE // 8.12|2.81.03,
#define FIXED_DEBUG_CONSOLE "/dev/pts/0" // |2.81.03, console device
#define FIXED_DEBUG_LVL

//--------------------
//** add **
//--------------------
#define SUPPORT_COMMAND_CLASS_ALARM_REPORT // 8.12|
#define SUPPORT_COMMAND_CLASS_BASIC_SET // 8.12|
#define SUPPORT_COMMAND_CLASS_CONFIGURATION_DEFAULT // 8.12|
#define SUPPORT_COMMAND_CLASS_MANUFACTURER_SPECIFIC // 8.12|
#define SUPPORT_COMMAND_CLASS_NO_OPERATION // 8.12|
#define SUPPORT_COMMAND_CLASS_SIMPLE_AV_CONTROL_SET //  8.12|
#define SUPPORT_COMMAND_CLASS_SWITCH_ALL // 8.12|2.81.03, ZW_SendSwitchAll, NW_SWITCH_ALL_ON
#define SUPPORT_COMMAND_CLASS_VERSION // 8.12|
#define SUPPORT_COMMAND_CLASS_WAKE_UP_NOTIFICATION // 8.12|
#define SUPPORT_COMMAND_CLASS_ZWAVEPLUS_INFO // 8.12|
#define SUPPORT_SIMPLE_AV_CONTROL // 8.12|
#define SUPPORT_TTY_WRITE_DIRECTLY // 8.12|2.81.03, ZW_TTY_SEND_FRAME

//--------------------
//** fix **
//--------------------
#define FIXED_DEFAULT_VALUE_SET // |2.81.03, 初始化變數，避免不必要的引用
#define FIXED_STRUCT_PADDING // 8.12|2.81.03, alignment

//#define FIXED_USE_STDIN // |2.81.03, zwave 自己提供的 debug 模式，但是沒有人知道怎麼使用

#define FIXED_SET_SUC_AND_DEFAULT // |2.81.03, 當被指定為 SIS時，必須將key 重新設定

#define FIXED_CFG_TRIM_SPACE // |2.81.03, 只是trim 字串 - zipgateway.cfg
#define FIXED_UNSOLICITED_DESTINATION2 // 8.12|2.81.03, zipgateway 充許2個client 連接，但是 unsolicit 卻只回傳單一client

#define FIXED_NODES_LIST // |2.81.03, 避免 array override

#define FIXED_HANG_AT_EXTRA_CLASSES // |2.81.03, pass 非加密封包 to zware
#define FIXED_UNSOLICITED_SCHEME_SKIP // |2.81.03, check by zware api, 因為有些device 送出未加密的封包，造成zware沒辦法處理，而客戶以為是GW的問題。

#define FIXED_BSEARCH // |2.81.03, to rename bsearch

#define FIXED_PARSE_TO_UNSOLICITED // |2.81.03, to parse this to unsolicited destination

//--------------------
//** nonce, session, static data problem **
//--------------------
#define FIXED_NUM_SESSIONS 64 // |2.81.03, 4, send_data_appl_session_t, send_request_state and udp_tx_session
#define FIXED_NUM_NONCE 32 // |2.81.03, NONCE_TABLE_SIZE 5*3
#define FIXED_NUM_NONCE_TX 3 // |2.81.03, NUM_TX_SESSIONS 2
#define FIXED_NUM_NONCE_RX 3 // |2.81.03, MAX_RXSESSIONS 2
#define FIXED_NONCE_MSG_LEN // |2.81.03, please use META_DATA_MAX_DATA_SIZE
#define FIXED_NONCE_REQUEST_TIMEOUT 3000 // |2.81.03, NONCE_REQUEST_TIMEOUT_MSEC 500, too short

#define FIXED_NONCE_S2 // |2.81.03, 初始化和延長s2 callback 時間

#define FIXED_SEND_DATA_LIST_ALLOC // |2.81.03, global variable 是沒有thread safe的

//--------------------
//** DTLS **
//--------------------
#define FIXED_DTLS_SESSION_ADD // |2.81.03,
#define FIXED_DTLS_HANDSHAKE_TIMEOUT 10 // |2.81.03, DTLS_HANDSHAKE_TIMEOUT 3
// down or sleeping, it takes too much time to create a dtsl connection
#define FIXED_DTLS_SESSION_NAK_TIMEOUT 500 // |2.81.03,

//--------------------
//** disable **
//--------------------
#define FIXED_IPV4_DISABLE // |2.81.03, 不提供IP4
#define FIXED_IPV4_DHCP_DISABLE // |2.81.03, 不提供IP4 DHCP

// virtual node
#define FIXED_PREALLOCATED_VIRTUAL_NODE_RESVERED 3 // |2.81.03, 移除 virtual node
#define FIXED_VIRTUAL_NODE_DISABLE // |2.81.03, 移除 virtual node
// if you turn on -DFIXED_VIRTUAL_NODE_DISABLE, please turn off DFIXED_VIRTUAL_NODE_CB_DISABLE
//#define FIXED_VIRTUAL_NODE_CB_DISABLE

// to fix learn mode in loop when non sis isn't exist
#define FIXED_NON_SIS_NETWORK_AND_SKIP_BRIDGE // |2.81.03,

// to fix learn mode in loop
#define FIXED_NETWORKMANAGEMENT_FRAME_NOTIFY_DISABLE // |2.81.03, 進到learn mode 時，不要再送 NM_EV_FRAME_RECEIVED，避免loop

// to avoid sending WAKE_UP_INTERVAL_SET and ASSIGN_RETURN_ROUTE by zipgateway
#define FIXED_WAKE_UP_INTERVAL_SET_AND_ASSIGN_RETURN_ROUTE_DISABLE // |2.81.03,

#define FIXED_WAKE_UP_PASS_ZWARE // |2.81.03, 讓 zware 來處理 COMMAND_CLASS_WAKE_UP

#define FIXED_MAILBOX_DISABLE // |2.81.03, 關掉zipgateway 的mailbox，因為zware 會處理

//--------------------
//** serial **
//--------------------
#define FIXED_SERIAL_SELECT_TIMEOUT // |2.81.03, 降低存取serial的速度，避免造成zwave chip當掉

//--------------------
//** special case or request **
//--------------------
#define FIXED_ADD_REMOVE_TIMEOUT 6000 // |2.81.03, exclude timeout 時間
#define FIXED_LEARN_TIMEOUT 6000 // |2.81.03, learn timeout 時間
#define FIXED_CHIP_INFO_FILE // |2.81.03, 讀取 zwave chip相關訊息
//#define FIXED_ZIP_RUNPROG // |2.81.03, 讓zipgateway 進到idle 後才執行 zware
#define FIXED_NUM_OF_FIRMWARE 2 // |2.81.03, 在認證申請單，需填入相關的版本號，目前提個2組

//--------------------
//** fix (zware) **
//--------------------
#define FIXED_DTLS_TIMEOUT_MAX 10 // 8.12
#define FIXED_ASSOCIATION_REPORT // 8.12

#define FIXED_ALWAYS_CACHE_CHG // 8.12, 只要device 有更新資料，一定要往上傳，不然使用者會認為失連
#define FIXED_ZWAVEPLUS_INFO_OF_MYSELF // 8.12

#define FIXED_VERSION_REPORT // 8.12

#define FIXED_APPLICATION_TIMEOUT_CB // 8.12, zwif_exec_cb 回傳附上 node_id

#define FIXED_ACK_AS_FAKE_REPORT // 8.12, disable this, we don't want to get a fake report that it is a ack 

#define FIXED_QUEUE_DUP_WRONG // 8.12

//#define FIXED_MAIL_BOX_DISABLE // 8.12, zipgateway will send WAKE_UP_NO_MORE_INFORMATION in mailbox
#define FIXED_WAKE_UP_NO_MORE_INFORMATION_DELAY 2 // 8.12, need to set mail box disable

#define FIXED_REPLICATION_NODE_REMOVE // 8.12

//#define FIXED_INTEL_HEX_LOST_8BYTES // 8.12

#define FIXED_SAVE_NW_DONE // 8.12

#define FIXED_OP_SLEEP_NODE_UPT // 8.12

#define FIXED_RM_FAIL_CB // 8.12
#define FIXED_LEARN_FAIL_CB // 8.12
#define FIXED_LEARN_SM_INTERVIEW_COMPLETED // 8.12, we don't want to get ZWNET_OP_INITIATE (sts: 255 OP_FAILED), and set pMatchAGIGroup->stNodeEpInfo.byNodeID
#define FIXED_LEARN_SILICON_FAIL // 8.12, FUNC_ID_ZW_SET_LEARN_MODE, nms.tmp_node = inf->bSource

#define FIXED_REPLACE_RM_NODE // 8.12

//--------------------
//** special case or request (zware) **
//--------------------
#define DEVICE_GOTHROUGH_AND_GET // 8.12
#define DEVICE_WAKE_UP_AND_INTERVIEW_BYPASS // 8.12

#define DEVICE_DISABLE_DEVICE_POLLING // 8.12
#define DEVICE_DISABLE_WAKEUP_POLLING // 8.12
#define DEVICE_NODE_STS_PATCH // 8.12

#define DEVICE_DSK_INPUT_TIMEOUT 30 // 8.12

//--------------------
//** interview (zware) **
//--------------------
// some devices's nodeinfo have COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION, but it dose't work !!!
#define DEVICE_INTERVIEW_NOTIFY // 8.12
#define DEVICE_INTERVIEW_TIMEOUT // 8.12
#define DEVICE_INTERVIEW_VERSION // 8.12
#define DEVICE_INTERVIEW_ASSOCIATION_SET_ALLGROUP // 8.12, it will set/get node 1 to all group

#define DEVICE_INTERVIEW_CONFIGURATION_GET // 8.12
#define DEVICE_INTERVIEW_ORDER // 8.12

#define DEVICE_INTERVIEW_USERCODE // 8.12

//--------------------
//** unsecure response (zware) **
//--------------------
#define DEVICE_XXXX_UNSECURE_ACCEPT // 8.12
#define DEVICE_0108_UNSECURE_ACCEPT // 8.12
#define DEVICE_013C_UNSECURE_ACCEPT // 8.12
#define DEVICE_0000_UNSECURE_ACCEPT // 8.12

//--------------------
//** device (zware) **
//--------------------
#define DEVICE_EXT_VER_SHOW // 8.12

#define DEVICE_BASIC_CLASS_SHOW // 8.12
#define DEVICE_ASSOCIATION_SAVE // 8.12, to save into nifxxxxxxxx.dat
#define DEVICE_CONFIGURATION_SAVE // 8.12, to save into nifxxxxxxxx.dat
#define DEVICE_USERCODE_SAVE // 8.12, to save into nifxxxxxxxx.dat

//--------------------
//** certification **
//--------------------
#define CERTIFICATION_CCM_12_2_MANUFACTURER_SPECIFIC_S0_NO_SECURE // |2.81.03,
#define CERTIFICATION_CCM_17_2_APPLICATION_CAPABILITY_REMOVED // |2.81.03,
#define CERTIFICATION_CCT_6_1_SUPERVISION // |2.81.03,
#define CERTIFICATION_CC_105_2_FIRMWARE_VERSION // |2.81.03,
#define CERTIFICATION_CC_33_FIRMWARE_UPDATE_MD_REMOVED // |2.81.03,
#define CERTIFICATION_CC_58_MCA_EPID_0 0 // 8.12
#define CERTIFICATION_CC_59_MULTI_CMD_REMOVED // 8.12
#define CERTIFICATION_CC_XX_VERSION_COMMAND_CLASS_REPORT // |2.81.03,
#define CERTIFICATION_RT_1_22_4_REMOVE_FAILNODE // 8.12
#define CERTIFICATION_SR_2_7_KEX_GET_TIMEOUT 30 // |2.81.03,
#define CERTIFICATION_SR_3_3_1_4_CSA // |2.81.03,
//#define CERTIFICATION_RT_1_13_2_WAKE_UP_NO_MORE_INFORMATION // |2.81.03,

typedef struct
{
	char dsk_key_s[48+4]; // string
	char dsk_key_d[48+4]; // string

	char netkey[32+4];
	char netkey_unauth[32+4];
	char netkey_auth[32+4];
	char netkey_access[32+4];
} KeyData_t;

typedef struct
{
	unsigned char moduleVer; // SERIAL_API_GET_INIT_DATA / ModuleVer
	unsigned char capability; // SERIAL_API_GET_INIT_DATA / Capabilities
	unsigned char chipType; // SERIAL_API_GET_INIT_DATA / ChipType
	unsigned char chipVer; // SERIAL_API_GET_INIT_DATA / ChipVer
	unsigned char nodelist[32]; // SERIAL_API_GET_INIT_DATA / NodeList

	unsigned char cap; // FUNC_ID_ZW_GET_CONTROLLER_CAPABILITIES
	KeyData_t key;
} SerialInitData_t;

#endif
