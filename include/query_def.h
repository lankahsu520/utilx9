#ifndef __QUERY_DEF_H__
#define __QUERY_DEF_H__

//******************************************************************************
//** FILENAME? **
//******************************************************************************
#define QUERY_FILENAME_COMMAND_XML "command.xml"
#define QUERY_FILENAME_DATAB_XML "datab.xml"
#define QUERY_FILENAME_FLASH "flash"
#define QUERY_FILENAME_INFO_XML "info.xml"
#define QUERY_FILENAME_SCENAR_XML "scenar.xml"
#define QUERY_FILENAME_SERVER_XML "server.xml"
#define QUERY_FILENAME_SYSTEM "system"
#define QUERY_FILENAME_VERSION "version"
#define QUERY_FILENAME_ZIP "zip"
#define QUERY_FILENAME_UNKNOW "unknow"


//******************************************************************************
//** KEY ???= **
//******************************************************************************
#define QUERY_KEY_ACTION "action"
#define QUERY_KEY_ALIVE "alive"
#define QUERY_KEY_EXT1 "ext1"
#define QUERY_KEY_EXT2 "ext2"
#define QUERY_KEY_FAKE "fake"
#define QUERY_KEY_FUNCTION "function"
#define QUERY_KEY_GROUP "group"
#define QUERY_KEY_ID "id"
#define QUERY_KEY_LEVEL "level"
#define QUERY_KEY_LOCALTIME "localtime"
#define QUERY_KEY_ORDER "order"
#define QUERY_KEY_ROOM "room"
#define QUERY_KEY_SCOPE "scope"
#define QUERY_KEY_SETFORSCAN "setforscan" // server.xml?setforscan
#define QUERY_KEY_STATEBOX "statebox" // server.xml?statebox
#define QUERY_KEY_STATUS "status"
#define QUERY_KEY_UID_AP "uid_ap"
#define QUERY_KEY_UNLOCKCODE "unlockcode"
#define QUERY_KEY_USE "use"
#define QUERY_KEY_UID "uid"
#define QUERY_KEY_UUID "uuid"
// for Luffanet only
#define QUERY_KEY_MODULE "module"
#define QUERY_KEY_STATE "state"
#define QUERY_KEY_UNKNOW "unknow"


//******************************************************************************
//** id=??? **
//******************************************************************************
#define QUERY_ID_VAL_PAIR "pair"
#define QUERY_ID_VAL_RESET "reset"


//******************************************************************************
//** action=??? **
//******************************************************************************
#define QUERY_ACTION_VAL_GETP "getp"
#define QUERY_ACTION_VAL_GETSTATUS "getstatus"
#define QUERY_ACTION_VAL_GETVEMERVERSION "getvemerversion"
#define QUERY_ACTION_VAL_IMPORT "import"
#define QUERY_ACTION_VAL_NETWORKTEST "networktest"
#define QUERY_ACTION_VAL_OPENCOM "opencom"
#define QUERY_ACTION_VAL_ORDER "order"
#define QUERY_ACTION_VAL_RAZCPT "razcpt"
#define QUERY_ACTION_VAL_SCAN "scan"
#define QUERY_ACTION_VAL_SERCEM "setcem"
#define QUERY_ACTION_VAL_SETP "setp"
#define QUERY_ACTION_VAL_TESTLK "testlk"
#define QUERY_ACTION_VAL_TIMERPARA "timerpara"
#define QUERY_ACTION_VAL_UPDATETHERMOSTAT "updatethermostat"
#define QUERY_ACTION_VAL_VARX "varX"
#define QUERY_ACTION_VAL_ZONEPARA "zonepara"
// for Luffanet only
#define QUERY_ACTION_VAL_LED "led"
#define QUERY_ACTION_VAL_SYSINFO "sysinfo"
#define QUERY_ACTION_VAL_BUTTON "button"


//******************************************************************************
//** order=??? **
//******************************************************************************
#define QUERY_ORDER_VAL_BABY "baby"
#define QUERY_ORDER_VAL_DEFAULT "default"
#define QUERY_ORDER_VAL_DOWN "down"
#define QUERY_ORDER_VAL_INTC "intc"
#define QUERY_ORDER_VAL_OFF "off"
#define QUERY_ORDER_VAL_ON "on"
#define QUERY_ORDER_VAL_PULSER1 "pulseR1"
#define QUERY_ORDER_VAL_PULSEX "pulseX"
#define QUERY_ORDER_VAL_SETWAY "setway"
#define QUERY_ORDER_VAL_UP "up"

#define QUERY_ORDER_VAL_ADD "add"
#define QUERY_ORDER_VAL_DEACTIVATION "deactivation"
#define QUERY_ORDER_VAL_DELETE "delete"
#define QUERY_ORDER_VAL_DELETE_ALL "delete_all"
#define QUERY_ORDER_VAL_REFRESH "refresh"

#define QUERY_ORDER_VAL_DUMP "dump"

//******************************************************************************
//** state=??? **
//******************************************************************************
#define QUERY_STATE_VAL_IDLE "idle"
#define QUERY_STATE_VAL_NOT_ASSOCIATED "not_associated"
#define QUERY_STATE_VAL_EMPTY_DATABASE "empty_database"
#define QUERY_STATE_VAL_NOT_YOKIS_RADIO_NETOWRK "not_yokis_radio_network"
#define QUERY_STATE_VAL_NOT_YOKIS_CLOUD "not_yokis_cloud"
#define QUERY_STATE_VAL_IP_NETWORK_ERROR "ip_network_error"
#define QUERY_STATE_VAL_NETWORK_CONNECTION_ERROR "network_connection_error"
#define QUERY_STATE_VAL_NETWORK_CABLE_NOT_CONNECTED "network_cable_not_connected"
#define QUERY_STATE_VAL_LEARNING "learning"
#define QUERY_STATE_VAL_MATERIAL_ERROR "material_error"


#endif
