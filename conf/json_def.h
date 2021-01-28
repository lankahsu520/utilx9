#ifndef __JSON_DEF_H__
#define __JSON_DEF_H__

//******************************************************************************
//** FILE **
//******************************************************************************
#define JSON_CONFIG_DIR                           "/mnt/PhilioData" // for PJ_HAS_PHILIO_SDK_V2/USE_ONVIF_MODULE_V2


//******************************************************************************
//** ROOT **
//******************************************************************************
#define JKEY_ROOT_ACTIONS                         "actions"
#define JKEY_ROOT_CHAINS                          "chains"
#define JKEY_ROOT_CONTROL                         "control"
#define JKEY_ROOT_DATA                            "data"
#define JKEY_ROOT_DEVICE                          "device"
#define JKEY_ROOT_DONGLE                          "dongle"
#define JKEY_ROOT_EQUIPMENT                       "equipment"
#define JKEY_ROOT_EVENT                           "event"
#define JKEY_ROOT_FIRMWARE                        "firmware"
#define JKEY_ROOT_GROUPS                          "groups"
#define JKEY_ROOT_HW                              "hw"
#define JKEY_ROOT_INTERFACE                       "iface"
#define JKEY_ROOT_JSON                            "json"
#define JKEY_ROOT_MODULES                         "modules"
#define JKEY_ROOT_NETWORK                         "network"
#define JKEY_ROOT_NOTIFICATION                    "notification"
#define JKEY_ROOT_PAYLOAD                         "payload"
#define JKEY_ROOT_REMOTES                         "remotes"
#define JKEY_ROOT_RESULT                          "result"
#define JKEY_ROOT_SCANS                           "scans"
#define JKEY_ROOT_SCENARIOS                       "scenarios"
#define JKEY_ROOT_SCENARS                         "scenars"
#define JKEY_ROOT_SUBNET                          "subnet"
#define JKEY_ROOT_SUPPORT_INFO                    "supportInfo"
#define JKEY_ROOT_TRIGGERS                        "triggers"


//******************************************************************************
//** INTERFACE **
//******************************************************************************
#define JKEY_INTERFACE_CAPABILITY                 "capability"
#define JKEY_INTERFACE_CHIPTYPE                   "chiptype"
#define JKEY_INTERFACE_CHIPVER                    "chipver"
#define JKEY_INTERFACE_DEVNAME                    "devname"
#define JKEY_INTERFACE_ISBRIDGE                   "isbridge"
#define JKEY_INTERFACE_ISEXISTSIS                 "isexistsis"
#define JKEY_INTERFACE_ISONOTHERNETWORK           "isonothernetwork"
#define JKEY_INTERFACE_ISREALPRIMARY              "isrealprimary"
#define JKEY_INTERFACE_ISRFBUSY                   "isrfbusy"
#define JKEY_INTERFACE_ISSECONDARY                "issecondary"
#define JKEY_INTERFACE_ISSUC                      "issuc"
#define JKEY_INTERFACE_MODULEVER                  "modulever"
#define JKEY_INTERFACE_PROTOCOL                   "protocol"
#define JKEY_INTERFACE_SUCID                      "sucid"
#define JKEY_INTERFACE_ZWAVE                      "zwave"


//******************************************************************************
//** DEVICE **
//******************************************************************************
#define JKEY_DEVICE_BATTERY                       "battery"
#define JKEY_DEVICE_CHANNEL                       "channel"
#define JKEY_DEVICE_LAST_TAMPER_TIME_UTC          "lasttampertime_utc"
#define JKEY_DEVICE_LAST_TAMPER_TIME              "lasttampertime"

// ***** (v1) *****
#define JKEY_DEVICE_APPLICATION_SUBVERSION        "Application_Subversion"
#define JKEY_DEVICE_APPLICATION_VERSION           "Application_Version"
#define JKEY_DEVICE_MANUFACTURE_ID                "Manufacture_ID"
#define JKEY_DEVICE_PRODUCT_TYPE                  "Product_type"
#define JKEY_DEVICE_PROTOCOL_SUBVERSION           "Protocol_Subversion"
#define JKEY_DEVICE_PROTOCOL_VERSION              "Protocol_Version"
#define JKEY_DEVICE_PRODUCT_ID                    "Product_ID"

#define JKEY_DEVICE_TX_STATUS                     "tx_status"

// ***** (v2) *****
#define JKEY_DEVICE_PAN27_INFO                    "pan27_info"
#define JKEY_DEVICE_ZIGBEE_INFO                   "zigbee_info"
#define JKEY_DEVICE_ZWAVE_INFO                    "zwave_info"

// ***** (s2) *****
#define JKEY_DEVICE_SLEEPING                      "sleeping"
#define JKEY_COMM_DSK                             "dsk"
#define JKEY_COMM_PIN                             "pin"

#define JKEY_DEVICE_ZWPLUS_VER                    "zwplus_ver"
#define JKEY_DEVICE_NODE_TYPE                     "node_type"
#define JKEY_DEVICE_ROLE_TYPE                     "role_type"
#define JKEY_DEVICE_INSTR_ICON                    "instr_icon"
#define JKEY_DEVICE_USR_ICON                      "usr_icon"

// ***** onvif (v2) *****
#define JKEY_DEVICE_MEDIA                         "media"
#define JKEY_DEVICE_ONVIF_INFO                    "onvif_info"


//******************************************************************************
//** CHANNEL **
//******************************************************************************
#define JKEY_CHANNEL_CTRL_TYPE                    "ctrltype"
#define JKEY_CHANNEL_FUNC_TYPE                    "functype"

#define JKEY_CHANNEL_METER                        "meter"
#define JKEY_CHANNEL_CURTAIN_LOGIC                "curtain_logic"
#define JKEY_CHANNEL_SENSOR_VALUE                 "sensorvalue"
#define JKEY_CHANNEL_SENSOR_UNIT                  "sensorunit"
#define JKEY_CHANNEL_SENSOR_STATE                 "sensorstate"

#define JKEY_CHANNEL_SWITCH_COLOR                 "switch_color"

#define JKEY_CHANNEL_WAKEUP                       "wakeup"

#define JKEY_CHANNEL_ZIGBEE_SWITCH_COLOR          "zigbee_switch_color"
#define JKEY_CHANNEL_ZIGBEE_SWITCH_COLOR_CLOUD    "switchcolor"
#define JKEY_CHANNEL_ZWAVE_SWITCH_COLOR_CLOUD     "switchcolor"


//******************************************************************************
//** COMM **
//******************************************************************************
#define JKEY_COMM_ACTION                          "action"
#define JKEY_COMM_AP_SSID                         "AP_SSID"
#define JKEY_COMM_ASSOCIATE_GROUP                 "associategroup"
#define JKEY_COMM_ASSOCIATE_UID                   "assciateuid"
#define JKEY_COMM_BASIC_VALUE                     "basicvalue"
#define JKEY_COMM_BOOTUP                          "bootup"
#define JKEY_COMM_BRANCH                          "branch"
#define JKEY_COMM_BUILDER                         "builder"
#define JKEY_COMM_BUILDNO                         "buildno"
#define JKEY_COMM_BUILDTIME                       "buildtime"
#define JKEY_COMM_CDT                             "cdt"
#define JKEY_COMM_CFGS                            "cfgs"
#define JKEY_COMM_CHANNEL                         "channel"
#define JKEY_COMM_CHECKSUM                        "checksum"
#define JKEY_COMM_CHID                            "chid"
#define JKEY_COMM_CLOUD_BACKUP                    "cloud_backup"
#define JKEY_COMM_CMD                             "cmd"
#define JKEY_COMM_CODE                            "code"
#define JKEY_COMM_CODE1                           "code1"
#define JKEY_COMM_CODE10                          "code10"
#define JKEY_COMM_CODE2                           "code2"
#define JKEY_COMM_CODE3                           "code3"
#define JKEY_COMM_CODE4                           "code4"
#define JKEY_COMM_CODE5                           "code5"
#define JKEY_COMM_CODE6                           "code6"
#define JKEY_COMM_CODE7                           "code7"
#define JKEY_COMM_CODE8                           "code8"
#define JKEY_COMM_CODE9                           "code9"
#define JKEY_COMM_CODE_NUM                        "codenum"
#define JKEY_COMM_CPU_USAGE                       "cpu_usage"
#define JKEY_COMM_DAYM                            "daym"
#define JKEY_COMM_DAYW                            "dayw"
#define JKEY_COMM_DATA1                           "data1"
#define JKEY_COMM_DATA10                          "data10"
#define JKEY_COMM_DATA2                           "data2"
#define JKEY_COMM_DATA3                           "data3"
#define JKEY_COMM_DATA4                           "data4"
#define JKEY_COMM_DATA5                           "data5"
#define JKEY_COMM_DATA6                           "data6"
#define JKEY_COMM_DATA7                           "data7"
#define JKEY_COMM_DATA8                           "data8"
#define JKEY_COMM_DATA9                           "data9"
#define JKEY_COMM_DATAS                           "datas"
#define JKEY_COMM_DEV_EUI64                       "dev_eui64"
#define JKEY_COMM_DIM_ON_VALUE                    "Dim_ON_Value"
#define JKEY_COMM_DURATION                        "duration"
#define JKEY_COMM_ERRORCODE                       "ErrorCode"
#define JKEY_COMM_ERROR_CODE                      "error_code"
#define JKEY_COMM_EVENT                           "event"
#define JKEY_COMM_EVENTCODE                       "eventCode"
#define JKEY_COMM_EVT                             "evt"
#define JKEY_COMM_EXT1                            "ext1"
#define JKEY_COMM_EXT2                            "ext2"
#define JKEY_COMM_FAIL                            "fail"
#define JKEY_COMM_FDCOUNT                         "fdcount"
#define JKEY_COMM_FDSIZE                          "fdsize"
#define JKEY_COMM_FIRMWARE                        "firmware"
#define JKEY_COMM_FIRMWARE_DATE                   "firmware_date"
#define JKEY_COMM_FILENAME                        "filename"
#define JKEY_COMM_FLAGS                           "flags"
#define JKEY_COMM_FREERAM                         "freeram"
#define JKEY_COMM_FUNCTION                        "function"
#define JKEY_COMM_GENERIC                         "generic"
#define JKEY_COMM_GROUP                           "group"
#define JKEY_COMM_HOMEID                          "homeid"
#define JKEY_COMM_HOSTNAME                        "hostname"
#define JKEY_COMM_HR                              "hr"
#define JKEY_COMM_ID                              "id"
#define JKEY_COMM_IDENTIFIER                      "identifier"
#define JKEY_COMM_IMPORT                          "import"
#define JKEY_COMM_INDEX                           "index"
#define JKEY_COMM_IP                              "ip"
#define JKEY_COMM_ISCEN                           "iscen"
#define JKEY_COMM_JSONGETUSERDATA_NUMBER          "jsongetuserdata_number"
#define JKEY_COMM_JSONSETALL_NUMBER               "jsonsetall_number"
#define JKEY_COMM_KERNEL                          "kernel"
#define JKEY_COMM_KEY                             "key"
#define JKEY_COMM_LANGUAGE                        "language"
#define JKEY_COMM_LAST_BEAT_TIME                  "lastbeattime"
#define JKEY_COMM_LAST_BEAT_TIME_UTC              "lastbeattime_utc"
#define JKEY_COMM_LED                             "led"
#define JKEY_COMM_LEDS                            "leds"
#define JKEY_COMM_LEVEL                           "level"
#define JKEY_COMM_LINKS                           "links"
#define JKEY_COMM_LOAD0                           "load0"
#define JKEY_COMM_LOAD1                           "load1"
#define JKEY_COMM_LOAD2                           "load2"
#define JKEY_COMM_MAC                             "mac"
#define JKEY_COMM_MAP                             "map"
#define JKEY_COMM_MAXNUMBER                       "maxnumber"
#define JKEY_COMM_MAX_ADDR                        "maxaddr"
#define JKEY_COMM_MEM                             "mem"
#define JKEY_COMM_MIN                             "min"
#define JKEY_COMM_MODEL                           "model"
#define JKEY_COMM_MODULE                          "module"
#define JKEY_COMM_MODULES_UIDS                    "modulesUids"
#define JKEY_COMM_MSG                             "msg"
#define JKEY_COMM_MTH                             "mth"
#define JKEY_COMM_NAME                            "name"
#define JKEY_COMM_NODEID                          "nodeid"
#define JKEY_COMM_NOSAVE                          "nosave"
#define JKEY_COMM_NOW_TIMESTAMP                   "Now_timeStamp"
#define JKEY_COMM_NUMERO                          "numero"
#define JKEY_COMM_ROOT                            "root"
#define JKEY_COMM_OFFSET                          "offset"
#define JKEY_COMM_ORDER                           "order"
#define JKEY_COMM_ORBWEB_UUID                     "Orbweb_UUID"
#define JKEY_COMM_PANID                           "panid"
#define JKEY_COMM_PASS                            "pass"
#define JKEY_COMM_PORT                            "port"
#define JKEY_COMM_PRODUCT_TYPE                    "product_type"
#define JKEY_COMM_PRODUCT_UID                     "productUid"
#define JKEY_COMM_PROFILETOKEN                    "profiletoken"
#define JKEY_COMM_RELEASE                         "release"
#define JKEY_COMM_REMOTE                          "remote"
#define JKEY_COMM_RES                             "res"
#define JKEY_COMM_RESIDENT                        "resident"
#define JKEY_COMM_RESP_TIME                       "response_time"
#define JKEY_COMM_REVISION                        "revision"
#define JKEY_COMM_ROOM                            "room"
#define JKEY_COMM_SAN                             "san"
#define JKEY_COMM_SAVETO                          "saveto"
#define JKEY_COMM_SCENARIO                        "scenario"
#define JKEY_COMM_SECOND                          "sec"
#define JKEY_COMM_SECONDE                         "seconde"
#define JKEY_COMM_SECURITY                        "security"
#define JKEY_COMM_SEQ                             "seq"
#define JKEY_COMM_SETASTCLOCK_LAT                 "setastclock_lat"
#define JKEY_COMM_SETASTCLOCK_LON                 "setastclock_lon"
#define JKEY_COMM_SIGN                            "sign"
#define JKEY_COMM_SET_CHECKBOX                    "jsonsetcheckbox"
#define JKEY_COMM_SET_ENABLELOCK                  "enablelock"
#define JKEY_COMM_SET_SUpwd                       "SU_PASSWORD"
#define JKEY_COMM_SIZE                            "size"
#define JKEY_COMM_SPECIFIC                        "specific"
#define JKEY_COMM_STATE                           "state"
#define JKEY_COMM_STATUSFLAG                      "status_flag"
#define JKEY_COMM_STA_SSID                        "STA_SSID"
#define JKEY_COMM_STEAL                           "steal"
#define JKEY_COMM_SUNRISE                         "sunrise"
#define JKEY_COMM_SUNSET                          "sunset"
#define JKEY_COMM_SWVERSION                       "swversion"
#define JKEY_COMM_SYS                             "sys"
#define JKEY_COMM_TAMPER                          "tamper"
#define JKEY_COMM_TIME                            "time"
#define JKEY_COMM_TIME_UTC                        "time_utc"
#define JKEY_COMM_TOTALRAM                        "totalram"
#define JKEY_COMM_TRIGGER                         "trigger"
#define JKEY_COMM_TUTK_UUID                       "TUTK_UUID"
#define JKEY_COMM_TYPE                            "type"
#define JKEY_COMM_TYPE_E                          "type_e"
#define JKEY_COMM_TZ                              "tz"
#define JKEY_COMM_UDN                             "udn"
#define JKEY_COMM_UID                             "uid"
#define JKEY_COMM_UIDS                            "uids"
#define JKEY_COMM_UPTIME                          "uptime"
#define JKEY_COMM_URL                             "url"
#define JKEY_COMM_USE                             "use"
#define JKEY_COMM_USER                            "user"
#define JKEY_COMM_USERCODE                        "usercode"
#define JKEY_COMM_USER_ID                         "userID"
#define JKEY_COMM_USER_ID_NUM                     "usernum"
#define JKEY_COMM_USER_PASS                       "password"
#define JKEY_COMM_USER_PID                        "pid"
#define JKEY_COMM_USER_STATUS                     "status"
#define JKEY_COMM_SUCCESS                         "success"
#define JKEY_COMM_USE_BUILDIN_SIREN               "use_buildin_siren"
#define JKEY_COMM_UUID                            "uuid"
#define JKEY_COMM_VAL                             "val"
#define JKEY_COMM_VAR1                            "var1"
#define JKEY_COMM_VAR2                            "var2"
#define JKEY_COMM_VAR3                            "var3"
#define JKEY_COMM_VAR4                            "var4"
#define JKEY_COMM_VERSBDD                         "versBdd"
#define JKEY_COMM_VERSION                         "version"
#define JKEY_COMM_WIFIMODE                        "WifiMode"
#define JKEY_COMM_YEAR                            "year"
#define JKEY_COMM_ZIGBEE_PAYLOAD                  "zigbee_payload"

#define JKEY_METER_CURRENT                        "current"
#define JKEY_METER_KWH                            "kwh"
#define JKEY_METER_PF                             "pf"
#define JKEY_METER_VOLTAGE                        "voltage"
#define JKEY_METER_WATT                           "watt"

#define JKEY_WAKEUP_MIN                           "min"
#define JKEY_WAKEUP_MAX                           "max"
#define JKEY_WAKEUP_DEF                           "def"
#define JKEY_WAKEUP_INTERVAL                      "interval"
#define JKEY_WAKEUP_NOTIFY                        "notify"

#define JKEY_SETPOINT_TEMP                        "temp"
#define JKEY_SETPOINT_UNIT                        "unit"
//#define JKEY_THERMOSTAT_MODE                      "mode"

#define JKEY_TX_ACKCHANNELNO                      "ackchannelno"
#define JKEY_TX_BLASTFAILEDLINK_FROM              "bLastFailedLink_from"
#define JKEY_TX_BLASTFAILEDLINK_TO                "bLastFailedLink_to"
#define JKEY_TX_LASTTXCHANNELNO                   "lasttxchannelno"
#define JKEY_TX_REPEATER_0                        "repeater_0"
#define JKEY_TX_REPEATER_1                        "repeater_1"
#define JKEY_TX_REPEATER_2                        "repeater_2"
#define JKEY_TX_REPEATER_3                        "repeater_3"
#define JKEY_TX_REPEATER_RSSI_0                   "repeater_rssi_0"
#define JKEY_TX_REPEATER_RSSI_1                   "repeater_rssi_1"
#define JKEY_TX_REPEATER_RSSI_2                   "repeater_rssi_2"
#define JKEY_TX_REPEATER_RSSI_3                   "repeater_rssi_3"
#define JKEY_TX_REPEATER_RSSI_4                   "repeater_rssi_4"
#define JKEY_TX_REPEATERS                         "repeaters"
#define JKEY_TX_ROUTESCHEMESTATE                  "routeschemestate"
#define JKEY_TX_ROUTESPEED                        "routespeed"
#define JKEY_TX_ROUTETRIES                        "routetries"


//******************************************************************************
//** VALUE **
//******************************************************************************
#define JVAL_BASIC_ON                             255
#define JVAL_BASIC_OFF                            0

#define JVAL_BATTERY_AC_255                       255
#define JVAL_BATTERY_AC_MINUS_1                   -1
#define JVAL_BATTERY_FULL_100                     100
#define JVAL_BATTERY_LOW_238                      0xEE
#define JVAL_BATTERY_UNKNOW_253                   0xFD

#define JVAL_CHID_0                               0

#define JVAL_DEVNAME_NETWORK                      "network"
#define JVAL_DEVNAME_ZWAVE                        "zwave"
#define JVAL_DEVNAME_ZIGBEE                       "zigbee"

#define JVAL_SECURITY_NONE                        0

#define JVAL_BRANCH_V1                            "v1"
#define JVAL_BRANCH_V2                            "v2"
#define JVAL_BRANCH_V3                            "v3"
#define JVAL_BRANCH_S2                            "s2"

#define JVAL_MODEL_PSC02                          "PSC02"
#define JVAL_MODEL_PSC03                          "PSC03"
#define JVAL_MODEL_PSC05                          "PSC05"
#define JVAL_MODEL_LSCXX                          "LSCxx"

#define JVAL_CMD_RESULT_BYE_BYE                   "Bye-Bye !!!"
#define JVAL_CMD_RESULT_NO_SUPPORT                "No support !!!"

#define JVAL_UNKNOWN                              "???"
//#define JVAL_UNKNOWN_NUM                          4294967295
#define JVAL_UNKNOWN_NUM                          2147483647
#define JVAL_DEFAULT_0                            0
#define JVAL_DEFAULT_255                          0xFF

//******************************************************************************
//** VALUE (ERROR) **
//******************************************************************************
// ***** (Yokis) *****
#define JVAL_YERR_UNKNOWN                         0x00 //?UNKNOWN
#define JVAL_YERR_CMD                             0x01 // ErrCmd
#define JVAL_YERR_NOPARAM                         0x02 // ErrNoParam
#define JVAL_YERR_LACKPARAM                       0x03 // ErrLackParam
#define JVAL_YERR_PARAM                           0x04 // ErrParam
#define JVAL_YERR_TIMEOUT                         0x05 // ErrTimeOut
#define JVAL_YERR_DATA                            0x06 // ErrData
#define JVAL_YERR_BUSY                            0x07 // ErrBusy

#define JVAL_YERR_TIMESAMP                        0x08 // ErrTimestamp

#define JVAL_YERR_BDDFIND                         0x44 //68 ErrBDDFind

#define JVAL_YERR_ZIPWITHFILE                     0x59 //89 ErrZipWithFile

#define JVAL_YERR_SEND                            0x60 //96 ErrSend
#define JVAL_YERR_RECEPTION                       0x61 //97 ErrReception
#define JVAL_YERR_READ                            0x62 //98 ErrRead
#define JVAL_YERR_RETURN                          0x63 //99 ErrReturn
#define JVAL_YERR_LOOP                            0x64 //100 ErrLoop
#define JVAL_YERR_COMP                            0x65 //101 ErrComp
#define JVAL_YERR_ROLLING_CODE                    0x66 //102 ErrRollingCode
#define JVAL_YERR_RECEIVER_UNREACHABLE            0x67 //103 ErrReceiverUnreachable
#define JVAL_YERR_WITHID                          0x68 //104 ErrWithID
#define JVAL_YERR_BASICS                          0x69 //105 ERR_BASICS
#define JVAL_YERR_LIVE                            0x6A //106 ErrLive

#define JVAL_YERR_ROOT_ACCESS                     0x80 //128 ErrRootAccess
#define JVAL_YERR_ROOT_UNDEFINE                   0x81 //129 ErrRootUndefine
#define JVAL_YERR_ROOT_DEFINITION                 0x82 //130 ErrRootDefinition


//******************************************************************************
//** VALUE (function) **
//******************************************************************************
#define JVAL_NAME_BATTERY                         "Battery"
#define JVAL_NAME_CONTROLLER                      "Controller"
#define JVAL_NAME_DIMMER                          "Dimmer"
#define JVAL_NAME_DOOR                            "Door/Window sensor"
#define JVAL_NAME_FLOOD                           "Flood Sensor"
#define JVAL_NAME_ILLUMINATION_SENSOR             "Illumination Sensor"
#define JVAL_NAME_PIR_DETECTOR                    "PIR Detector"
#define JVAL_NAME_POWER_METER                     "Power meter"
#define JVAL_NAME_SMART_SWITCH                    "Smart switch"
#define JVAL_NAME_SWITCH                          "Switch"
#define JVAL_NAME_TAMPER_SENSOR                   "Tamper Sensor"
#define JVAL_NAME_TEMPERATURE_SENSOR              "Temperature Sensor"
#define JVAL_NAME_WAKE_UP_SENSOR                  "Wakeup Sensor"

// ***** (JVAL_FUNC_TYPE_XXX) *****
#define JVAL_FUNC_TYPE_UNKNOW                     0
/*故意保留 10個 給實體的 Channel 使用*/

#define JVAL_FUNC_TYPE_SENSOR_TEMPERATURE         11
#define JVAL_FUNC_TYPE_SENSOR_ILLUMINATION        12
#define JVAL_FUNC_TYPE_SENSOR_DOOR                13
#define JVAL_FUNC_TYPE_SENSOR_PIR                 14
#define JVAL_FUNC_TYPE_SENSOR_HUMIDITY            15
#define JVAL_FUNC_TYPE_SENSOR_GPIO                16
#define JVAL_FUNC_TYPE_SENSOR_BINARY              16 // 1.0
#define JVAL_FUNC_TYPE_SENSOR_SMOKE               17
#define JVAL_FUNC_TYPE_SENSOR_CO                  18
#define JVAL_FUNC_TYPE_SENSOR_CO2                 19
#define JVAL_FUNC_TYPE_SENSOR_FLOOD               20
#define JVAL_FUNC_TYPE_SENSOR_GLASS_BREAK         21

#define JVAL_FUNC_TYPE_METER_SWITCH               22
#define JVAL_FUNC_TYPE_SWITCH                     23
#define JVAL_FUNC_TYPE_DIMMER                     24
#define JVAL_FUNC_TYPE_SIREN                      25
#define JVAL_FUNC_TYPE_CURTAIN                    26
#define JVAL_FUNC_TYPE_REMOTE                     27
#define JVAL_FUNC_TYPE_BUTTON                     28
#define JVAL_FUNC_TYPE_SENSOR_METER               29
#define JVAL_FUNC_TYPE_METER_DIMMER               30
#define JVAL_FUNC_TYPE_DOOR_LOCK                  31
#define JVAL_FUNC_TYPE_THERMOSTAT_FAN             32
#define JVAL_FUNC_TYPE_THERMOSTAT_MODE            33
#define JVAL_FUNC_TYPE_THERMOSTAT_TEMP            34
#define JVAL_FUNC_TYPE_SIMPLE_AV                  35
#define JVAL_FUNC_TYPE_VALVE                      36

#define JVAL_FUNC_TYPE_SENSOR_VOC                 37
#define JVAL_FUNC_TYPE_SENSOR_SHOCK               39
#define JVAL_FUNC_TYPE_SENSOR_UV                  40

#define JVAL_FUNC_TYPE_SWITCH_COLOR               41
#define JVAL_FUNC_TYPE_SUN_RISE                   42
#define JVAL_FUNC_TYPE_SUN_SET                    43

#define JVAL_FUNC_TYPE_SCENE_STATUS               44
#define JVAL_FUNC_TYPE_SENSOR_DOOR_LOCK           45
#define JVAL_FUNC_TYPE_TIMER                      46
#define JVAL_FUNC_TYPE_IPCAM                      47

#define JVAL_FUNC_TYPE_SENSOR_GAS                 48
#define JVAL_FUNC_TYPE_SENSOR_TAMPER              49
#define JVAL_FUNC_TYPE_SENSOR_WAKE_UP             50

#define JVAL_FUNC_TYPE_BATTERY                    51

#define JVAL_FUNC_TYPE_REPEATER                   100
#define JVAL_FUNC_TYPE_CONTROLLER                 200

// ***** (JVAL_CTRL_TYPE_XXX) *****
#define JVAL_CTRL_TYPE_UNKNOW                     0
/*故意保留 10個 給實體的 Channel 使用*/

#define JVAL_CTRL_TYPE_SENSOR_TEMPERATURE         11
#define JVAL_CTRL_TYPE_SENSOR_ILLUMINATION        12
#define JVAL_CTRL_TYPE_SENSOR_DOOR                13
#define JVAL_CTRL_TYPE_SENSOR_PIR                 14
#define JVAL_CTRL_TYPE_SENSOR_HUMIDITY            15
#define JVAL_CTRL_TYPE_SENSOR_GPIO                16
#define JVAL_CTRL_TYPE_SENSOR_BINARY              16 // 1.0
#define JVAL_CTRL_TYPE_SENSOR_SMOKE               17
#define JVAL_CTRL_TYPE_SENSOR_CO                  18
#define JVAL_CTRL_TYPE_SENSOR_CO2                 19
#define JVAL_CTRL_TYPE_SENSOR_FLOOD               20
#define JVAL_CTRL_TYPE_SENSOR_GLASS_BREAK         21

#define JVAL_CTRL_TYPE_METER_SWITCH               22
#define JVAL_CTRL_TYPE_SWITCH                     23
#define JVAL_CTRL_TYPE_DIMMER                     24
#define JVAL_CTRL_TYPE_SIREN                      25
#define JVAL_CTRL_TYPE_CURTAIN                    26
#define JVAL_CTRL_TYPE_REMOTE                     27
#define JVAL_CTRL_TYPE_BUTTON                     28
#define JVAL_CTRL_TYPE_SENSOR_METER               29
#define JVAL_CTRL_TYPE_METER_DIMMER               30
#define JVAL_CTRL_TYPE_DOOR_LOCK                  31
#define JVAL_CTRL_TYPE_THERMOSTAT_FAN             32
#define JVAL_CTRL_TYPE_THERMOSTAT_MODE            33
#define JVAL_CTRL_TYPE_THERMOSTAT_TEMP            34
#define JVAL_CTRL_TYPE_SIMPLE_AV                  35
#define JVAL_CTRL_TYPE_VALVE                      36

#define JVAL_CTRL_TYPE_SENSOR_VOC                 37
#define JVAL_CTRL_TYPE_SENSOR_SHOCK               39
#define JVAL_CTRL_TYPE_SENSOR_UV                  40

#define JVAL_CTRL_TYPE_SWITCH_COLOR               41
#define JVAL_CTRL_TYPE_SUN_RISE                   42
#define JVAL_CTRL_TYPE_SUN_SET                    43

#define JVAL_CTRL_TYPE_SCENE_STATUS               44
#define JVAL_CTRL_TYPE_SENSOR_DOOR_LOCK           45
#define JVAL_CTRL_TYPE_TIMER                      46
#define JVAL_CTRL_TYPE_IPCAM                      47

#define JVAL_CTRL_TYPE_SENSOR_GAS                 48
#define JVAL_CTRL_TYPE_SENSOR_TAMPER              49
#define JVAL_CTRL_TYPE_SENSOR_WAKE_UP             50

#define JVAL_CTRL_TYPE_BATTERY                    51

#define JVAL_CTRL_TYPE_REPEATER                   100
#define JVAL_CTRL_TYPE_CONTROLLER                 200

// ***** (JVAL_DATA_UNIT_XXX) *****
#define JVAL_DATA_UNIT_CELSIUS                    1
#define JVAL_DATA_UNIT_FAHRENHEIT                 2
#define JVAL_DATA_UNIT_PERCENTAGE                 3
#define JVAL_DATA_UNIT_LUX                        4
#define JVAL_DATA_UNIT_POWER_WATT                 5
#define JVAL_DATA_UNIT_POWER_VOLTAGE              6
#define JVAL_DATA_UNIT_POWER_CURRENT              7
#define JVAL_DATA_UNIT_POWER_FACTOR               8
#define JVAL_DATA_UNIT_POWER_KWH                  9
#define JVAL_DATA_UNIT_PPM                        10
#define JVAL_DATA_UNIT_PPBV                       11
#define JVAL_DATA_UNIT_UV                         12


//******************************************************************************
//** CONTROL **
//******************************************************************************
#define JKEY_CONTROL_RESP_CODE                    "respcode"
#define JKEY_CONTROL_RESP_MSG                     "respmsg"


//******************************************************************************
//** VALUE (CONTROL_CMD) **
//******************************************************************************
#define JVAL_CONTROL_CMD_ABORT                    "abort"
#define JVAL_CONTROL_CMD_DELDEVICE                "deldevice"
#define JVAL_CONTROL_CMD_DELETE_RETURN_ROUTE      "delete_return_route"
#define JVAL_CONTROL_CMD_DIMMING                  "dimming"
#define JVAL_CONTROL_CMD_EXCLUDE                  "exclude"
#define JVAL_CONTROL_CMD_GET_ALL_DEVICE           "get_all_device"
#define JVAL_CONTROL_CMD_GET_DEVICE               "getdevice"
#define JVAL_CONTROL_CMD_GET_CONTROL              "getcontrol"
#define JVAL_CONTROL_CMD_GET_EVENT                "getevent"
#define JVAL_CONTROL_CMD_GET_INTERFACE            "getinterface"
#define JVAL_CONTROL_CMD_INCLUDE                  "include"
#define JVAL_CONTROL_CMD_RENAME                   "rename"
#define JVAL_CONTROL_CMD_RESET_HW                 "resethw"
#define JVAL_CONTROL_CMD_RESET_SW                 "resetsw"
#define JVAL_CONTROL_CMD_SWITCH                   "switch"
#define JVAL_CONTROL_CMD_IMA_ENABLE               "IMA_enable"
#define JVAL_CONTROL_CMD_IMA_DISABLE              "IMA_disable"

// ***** (v1) *****
#define JVAL_CONTROL_CMD_ADD_LINK                 "addlink"
#define JVAL_CONTROL_CMD_GET_FW                   "getfw"
#define JVAL_CONTROL_CMD_GET_GROUP_NUMBER         "getgroupnumber"
#define JVAL_CONTROL_CMD_GET_LINK                 "getlink"
#define JVAL_CONTROL_CMD_GET_ZWID                 "getZWID"
#define JVAL_CONTROL_CMD_REBOOT_PLATFORM          "rebootplatform"
#define JVAL_CONTROL_CMD_REMOVE_LINK              "rmlink"
#define JVAL_CONTROL_CMD_SAVE_DATA                "savedata"
#define JVAL_CONTROL_CMD_SAVE_UPDATEFILE          "sdf"
#define JVAL_CONTROL_CMD_SETAPP_SUBVER            "Setsubversion"
#define JVAL_CONTROL_CMD_SETCONTROLTYPE           "Setcontroltype"
#define JVAL_CONTROL_CMD_SETFUNCTIONTYPE          "Setfunctiontype"
#define JVAL_CONTROL_CMD_SETLASTBEATTIME          "Setlastbeattime"
#define JVAL_CONTROL_CMD_SETLASTBEATTIME_UTC      "Setlastbeattime_utc"
#define JVAL_CONTROL_CMD_SETMAP                   "setmap"
#define JVAL_CONTROL_CMD_SETZWMEMORY              "writezwmemory"
#define JVAL_CONTROL_CMD_SET_LOWBATTNOTIFY        "setlowbattnotify"
#define JVAL_CONTROL_CMD_SET_MAINSCENE            "setmainscene"
#define JVAL_CONTROL_CMD_SET_SCENE_DEVICES_NUMBER "set_s_dev_num"
#define JVAL_CONTROL_CMD_SET_SCENE_STATUS_NUMBER  "set_s_sta_num"
#define JVAL_CONTROL_CMD_SET_STATUS_FLAG          "setstatusflag"
#define JVAL_CONTROL_CMD_SET_TAMPERNOTIFY         "settampernotify"
#define JVAL_CONTROL_CMD_SET_CURTAIN_LOGIC        "setcurtain_logic"//James
#define JVAL_CONTROL_CMD_SUNRISE_SET_TRIG_JUDGE   "sunrise_set_trig_time_judge"// James
#define JVAL_CONTROL_CMD_SUNRISE_TIME_GET         "sunrise_time_get"// James
#define JVAL_CONTROL_CMD_SUNRISE_TIME_SET         "sunrise_time_set"// James
#define JVAL_CONTROL_CMD_SUNRISE_TRIG_TIME_GET    "sunrise_trig_time_get"// James
#define JVAL_CONTROL_CMD_SUNRISE_TRIG_TIME_SET    "sunrise_trig_time_set"// James
#define JVAL_CONTROL_CMD_SUNSET_TIME_GET          "sunset_time_get"// James
#define JVAL_CONTROL_CMD_SUNSET_TIME_SET          "sunset_time_set"// James
#define JVAL_CONTROL_CMD_SUNSET_TRIG_TIME_GET     "sunset_trig_time_get"// James
#define JVAL_CONTROL_CMD_SUNSET_TRIG_TIME_SET     "sunset_trig_time_set"// James
#define JVAL_CONTROL_CMD_SYS_BAT_STATE            "sysbatstate"
#define JVAL_CONTROL_CMD_SYS_BAT_VAL              "sysbatval"
#define JVAL_CONTROL_CMD_SYS_BTN_1                "sysbtn1"
#define JVAL_CONTROL_CMD_SYS_BTN_2                "sysbtn2"
#define JVAL_CONTROL_CMD_SYS_BTN_3                "sysbtn3"
#define JVAL_CONTROL_CMD_SYS_BTN_CHECK            "sysbtnchk"
#define JVAL_CONTROL_CMD_SYS_BTN_STATE            "sysbtnstate"
#define JVAL_CONTROL_CMD_SYS_DATETIME             "sysdatetime"
#define JVAL_CONTROL_CMD_SYS_FUNCSWITCH           "sysfuncswitch"
#define JVAL_CONTROL_CMD_SYS_LED_AROUND           "sysledaround"
#define JVAL_CONTROL_CMD_SYS_LED_LOGO             "sysledlogo"
#define JVAL_CONTROL_CMD_SYS_LED_MISC             "sysledmisc"
#define JVAL_CONTROL_CMD_SYS_M0_VER               "sysm0ver"
#define JVAL_CONTROL_CMD_SYS_PACKET_WAIT          "packetwait"
#define JVAL_CONTROL_CMD_SYS_SOUND                "syssound"
#define JVAL_CONTROL_CMD_SYS_WATCHDOG             "syswatchdog"
#define JVAL_CONTROL_CMD_USERDATACHANGE           "userdatachange"
#define JVAL_CONTROL_CMD_ZW_NO_SECURE             "zwnosecure"

// ***** zwave *****
#define JVAL_CONTROL_CMD_GET_SWITCH               "getswitch"
#define JVAL_CONTROL_CMD_SWITCHCOLOR              "switch_color_set"
#define JVAL_CONTROL_CMD_SWITCHCOLOR_CLOUD        "switchcolorset"
#define JVAL_CONTROL_CMD_SWITCH_ALL_GET           "all_switch_get"// James
#define JVAL_CONTROL_CMD_SWITCH_ALL_OFF           "all_switch_off"// James
#define JVAL_CONTROL_CMD_SWITCH_ALL_ON            "all_switch_on"// James
#define JVAL_CONTROL_CMD_SWITCH_ALL_SET           "all_switch_set"// James

// ***** zwave(v1) *****
#define JVAL_CONTROL_CMD_CENTRALSCENE_CONFIGURATION_GET_V3 "CentralSceneSlowget"
#define JVAL_CONTROL_CMD_CENTRALSCENE_CONFIGURATION_SET_V3 "CentralSceneSlow"
#define JVAL_CONTROL_CMD_DOOR_LOCK_OP             "doorlockop"
#define JVAL_CONTROL_CMD_GETEXTZWMEMORY           "NVM_ext_read_long_byte"
#define JVAL_CONTROL_CMD_GETEXTZWMEMORYID         "NVM_get_id"
#define JVAL_CONTROL_CMD_GETEXTZWMEMORYTOBUFFER   "NVM_ext_read_long_buffer"
#define JVAL_CONTROL_CMD_GETEXTZWMEMORYTOFILE     "NVM_ext_write_to_file"
#define JVAL_CONTROL_CMD_GETZWMEMORY              "readzwmemory"
#define JVAL_CONTROL_CMD_GET_ASSOCIATE            "getassociate"
#define JVAL_CONTROL_CMD_GET_ASSOCIATION          "getassociation"
#define JVAL_CONTROL_CMD_GET_CONFIG               "getconfig"
#define JVAL_CONTROL_CMD_GET_METER                "getmeter"
#define JVAL_CONTROL_CMD_GET_ZWVERSION            "getzwversion"
#define JVAL_CONTROL_CMD_ISFAILDEVICE             "isfailnode"
#define JVAL_CONTROL_CMD_MUTICHANNEL_GET_ASSOCIATE "mutichgetassociate"
#define JVAL_CONTROL_CMD_MUTICHANNEL_REMOVE_ASSOCIATE "mutichremoveassociate"
#define JVAL_CONTROL_CMD_MUTICHANNEL_SET_ASSOCIATE "mutichsetassociate"
#define JVAL_CONTROL_CMD_NVMBACKUP                "nvmbackup"
#define JVAL_CONTROL_CMD_NVMFROMFILE              "nvmfromfile"
#define JVAL_CONTROL_CMD_NVMRESTORE               "nvmrestore"
#define JVAL_CONTROL_CMD_NVMTOFILE                "nvmtofile"
#define JVAL_CONTROL_CMD_REMOVE_ASSOCIATE         "removeassociate"
#define JVAL_CONTROL_CMD_REPLACE                  "replace"
#define JVAL_CONTROL_CMD_RMFAILED                 "rmfailed"
#define JVAL_CONTROL_CMD_REMOVE_FAILNODE          "removefailnode"
#define JVAL_CONTROL_CMD_SETEXTZWMEMORYFROMBUFFER "NVM_ext_write_long_buffer"
#define JVAL_CONTROL_CMD_SET_ASSOCIATE            "setassociate"
#define JVAL_CONTROL_CMD_SET_CONFIG               "setconfig"
#define JVAL_CONTROL_CMD_SET_SIMPLEAV_CONTROL     "simpleAVcontrol"
#define JVAL_CONTROL_CMD_SWITCH2                  "switch2"
#define JVAL_CONTROL_CMD_SYS_RTC_TIME             "sysrtctime"
#define JVAL_CONTROL_CMD_THERMOSTAT_FAN           "thermostatfan"
#define JVAL_CONTROL_CMD_THERMOSTAT_MODE          "thermostatmode"
#define JVAL_CONTROL_CMD_THERMOSTAT_TEMP          "thermostattemp"
#define JVAL_CONTROL_CMD_USERCODE_GET             "usercodeget"
#define JVAL_CONTROL_CMD_USERCODE_GRAB            "usercodegrab"
#define JVAL_CONTROL_CMD_USERCODE_LIST            "usercodelist"
#define JVAL_CONTROL_CMD_USERCODE_NUMBER_GET      "usercodenumget"
#define JVAL_CONTROL_CMD_USERCODE_PUT             "usercodeput"
#define JVAL_CONTROL_CMD_USERCODE_REMOVE          "usercoderemove"
#define JVAL_CONTROL_CMD_USERCODE_SET             "usercodeset"
#define JVAL_CONTROL_CMD_ZLEARN                   "zlearn"
#define JVAL_CONTROL_CMD_ZNETUPDATE               "znetupdate"
#define JVAL_CONTROL_CMD_ZREQNIF                  "zreqnif"
#define JVAL_CONTROL_CMD_ZSENDNIF                 "zsendnif"
#define JVAL_CONTROL_CMD_ZSETSUC                  "zsetsuc"
#define JVAL_CONTROL_CMD_ZW_FIRMWARE_UPDATE       "zwfwupdate"

// ***** zwave (S2) *****
#define JVAL_CONTROL_CMD_BASIC                    "basic"
#define JVAL_CONTROL_CMD_BATTERY                  "battery"
#define JVAL_CONTROL_CMD_GRANT_CSA                "grant_csa"
#define JVAL_CONTROL_CMD_INPUT_PIN                "input_pin"
#define JVAL_CONTROL_CMD_NOP                      "nop"
#define JVAL_CONTROL_CMD_SWITCH_BINARY            "switch_binary"
#define JVAL_CONTROL_CMD_SWITCH_MULTILEVEL        "switch_multilevel"

// ***** onvif *****
#define JVAL_CONTROL_CMD_ADDDEVICE                "adddevice"
#define JVAL_CONTROL_CMD_DEBUG                    "debug"
#define JVAL_CONTROL_CMD_SNAPSHOT                 "snapshot"
#define JVAL_CONTROL_CMD_VIDEOCLIP                "videoclip"
#define JVAL_CONTROL_CMD_WSDISCOVERY              "wsdiscovery"
#define JVAL_CONTROL_CMD_WSLIST                   "wslist"

//******************************************************************************
//** EVENT (CONTROL_CMD) **
//******************************************************************************
#define JVAL_EC_0100_OPERATE_OK                   100
#define JVAL_EC_0101_OPERATE_CMD_UNKNOWN          101
#define JVAL_EC_0102_OPERATE_UID_INVALID          102
#define JVAL_EC_0103_OPERATE_TIMEOUT              103
#define JVAL_EC_0104_OPERATE_RF_BUSY              104
#define JVAL_EC_0105_OPERATE_INTERNAL_ERR         105

#define JVAL_EC_1000_DEVICE_INCLUDEorEXCLUDE      1000
#define JVAL_EC_1001_FOUND_DEVICE                 1001
#define JVAL_EC_1002_DEVICE_ADDED                 1002
#define JVAL_EC_1040_DEVICE_ADDED                 1040
#define JVAL_EC_1003_DEVICE_REMOVED               1003
#define JVAL_EC_1009_SYSTEM_DISARM                1009
#define JVAL_EC_1010_SYSTEM_ARM                   1010
#define JVAL_EC_1011_SYSTEM_PART_ARM1             1011
#define JVAL_EC_1012_SYSTEM_PART_ARM2             1012
#define JVAL_EC_1013_SYSTEM_PART_ARM3             1013
#define JVAL_EC_1014_SYSTEM_PART_ARM4             1014
#define JVAL_EC_1015_SYSTEM_PART_ARM5             1015
#define JVAL_EC_1020_SYSTEM_RESET                 1020
#define JVAL_EC_1021_SYSTEM_RESET_SW              1021
#define JVAL_EC_1030_OTA_START                    1030
#define JVAL_EC_1031_OTA_STOP                     1031
#define JVAL_EC_1032_OTA_SUCCESS                  1032
#define JVAL_EC_1033_OTA_FAIL                     1033
#define JVAL_EC_1034_READ_EXTNVM_SUCCESS          1034
#define JVAL_EC_1035_READ_EXTNVM_FAIL             1035
#define JVAL_EC_1036_WRITE_EXTNVM_SUCCESS         1036
#define JVAL_EC_1037_WRITE_EXTNVM_FAIL            1037

#define JVAL_EC_1380_ADDING_START                 1380
#define JVAL_EC_1381_ADDING_CSA                   1381
#define JVAL_EC_1382_ADDING_SSA                   1382
#define JVAL_EC_1383_ADDING_SEC                   1383
#define JVAL_EC_1384_ADDING_SEC_LOWER             1384
#define JVAL_EC_1385_ADDING_SSA_SET               1385
#define JVAL_EC_1387_ADDING_DONE                  1387
#define JVAL_EC_1389_ADDING_FAIL                  1389

#define JVAL_EC_1390_REMOVING_START               1390
#define JVAL_EC_1397_REMOVING_DONE                1397
#define JVAL_EC_1399_REMOVING_FAIL                1399

#define JVAL_EC_1400_RESETING_START               1400
#define JVAL_EC_1407_RESETING_DONE                1407
//#define JVAL_EC_1408_RESETING_REMOVED             1408 // JVAL_EC_1020_SYSTEM_RESET
#define JVAL_EC_1409_RESETING_FAIL                1409

#define JVAL_EC_1410_RMFAILED_START               1410
#define JVAL_EC_1417_RMFAILED_DONE                1417
#define JVAL_EC_1418_RMFAILED_REMOVED             1418
#define JVAL_EC_1419_RMFAILED_FAIL                1419

#define JVAL_EC_1420_REPLACING_START              1420
#define JVAL_EC_1422_REPLACING_SSA                1422
#define JVAL_EC_1427_REPLACING_DONE               1427
#define JVAL_EC_1428_REPLACING_REPLACED           1428
#define JVAL_EC_1429_REPLACING_FAIL               1429

#define JVAL_EC_1430_ABORTING_START               1430
#define JVAL_EC_1437_ABORTING_DONE                1437
#define JVAL_EC_1438_ABORTING_ABORTED             1438
#define JVAL_EC_1439_ABORTING_FAIL                1439

#define JVAL_EC_1440_LEARNING_START               1440
#define JVAL_EC_1442_LEARNING_SSA                 1442
#define JVAL_EC_1447_LEARNING_DONE                1447
#define JVAL_EC_1448_LEARNING_LEARNED             1448
#define JVAL_EC_1449_LEARNING_FAIL                1449

#define JVAL_EC_1990_NOP_OK                       1990
#define JVAL_EC_1991_NOP_FAIL                     1991

#define JVAL_EC_4001_TAMPER_TRIGGER               4001
#define JVAL_EC_4002_BATTERY_LOW                  4002
#define JVAL_EC_4003_BATTERY_NORMAL               4003
#define JVAL_EC_4005_DOORLOCK_KEYPAD_LOCKED       4005
#define JVAL_EC_4006_DOORLOCK_KEYPAD_UNLOCKED     4006
#define JVAL_EC_4007_WAKE_UP_INTERVAL             4007
#define JVAL_EC_4008_WAKE_UP_NOTIFICATION         4008

#define JVAL_EC_4101_PIR_TRIGGER                  4101
#define JVAL_EC_4102_DOOR_WINDOW_OPEN             4102
#define JVAL_EC_4103_DOOR_WINDOW_CLOSE            4103
#define JVAL_EC_4104_SMOKE_TRIGGER                4104
#define JVAL_EC_4105_CO_TRIGGER                   4105
#define JVAL_EC_4106_CO2_TRIGGER                  4106
#define JVAL_EC_4107_FLOOD_TRIGGER                4107
#define JVAL_EC_4108_GLASS_BREAK                  4108
#define JVAL_EC_4109_GPIO_ON                      4109
#define JVAL_EC_4110_GPIO_OFF                     4110
#define JVAL_EC_4111_TEMP_OVER                    4111 //data:Temperature
#define JVAL_EC_4112_TEMP_BELOW                   4112 //data:Temperature
#define JVAL_EC_4113_LUX_OVER                     4113 //data:Illumination
#define JVAL_EC_4114_LUX_BELOW                    4114 //data:Illumination
#define JVAL_EC_4115_HUMIDITY_OVER                4115 //data:Humidity
#define JVAL_EC_4116_HUMIDITY_BELOW               4116 //data:Humidity
#define JVAL_EC_4119_TRIGGER_OFF                  4119
#define JVAL_EC_4120_POWER_OVERLOAD               4120
#define JVAL_EC_4121_METER_CHANGED                4121 //data:Meter
#define JVAL_EC_4122_PANIC_TRIGGER                4122
#define JVAL_EC_4123_SONIC_TRIGGER                4123
#define JVAL_EC_4127_GAS_TRIGGER                  4127

#define JVAL_EC_4201_SNAPSHOT                     4201
#define JVAL_EC_4202_VIDEOCLIP                    4202

#define JVAL_EC_4401_BUTTON_1_DOWN                4401
#define JVAL_EC_4402_BUTTON_2_DOWN                4402
#define JVAL_EC_4403_BUTTON_3_DOWN                4403
#define JVAL_EC_4404_BUTTON_4_DOWN                4404
#define JVAL_EC_4405_BUTTON_5_DOWN                4405
#define JVAL_EC_4406_BUTTON_6_DOWN                4406
#define JVAL_EC_4407_BUTTON_7_DOWN                4407
#define JVAL_EC_4408_BUTTON_8_DOWN                4408

#define JVAL_EC_4700_DOORLOCK_CHANGED             4700
#define JVAL_EC_4701_USERCODE_UPDATE              4701
#define JVAL_EC_4702_USERCODE_OPEN                4702
#define JVAL_EC_4703_USERCODE_CLOSE               4703

#define JVAL_EC_4801_TEMP_REPORT                  4801 //data:Temperature
#define JVAL_EC_4802_LUX_REPORT                   4802 //data:Illumination
#define JVAL_EC_4803_HUMIDITY_REPORT              4803 //data:Humidity
#define JVAL_EC_4804_METER_REPORT                 4804 //data:Meter
#define JVAL_EC_4805_CO2_REPORT                   4805 //data:Meter
#define JVAL_EC_4806_VOC_REPORT                   4806 //data:Meter
#define JVAL_EC_4807_UV_REPORT                    4807 //data:Meter

#define JVAL_EC_4901_THERMO_FAN_REPORT            4901
#define JVAL_EC_4902_THERMO_MODE_REPORT           4902
#define JVAL_EC_4903_THERMO_TEMP_REPORT           4903

#define JVAL_EC_5001_GOT_CONTROL                  5001
#define JVAL_EC_5002_STATUS_UPDATE                5002
#define JVAL_EC_5102_STATUS_UPDATE                5102
#define JVAL_EC_5003_CONFIG_CHANGE                5003
#define JVAL_EC_5004_USERDATA_CHANGE              5004
#define JVAL_EC_5005_BUILD_IN_SIREN_ON            5005
#define JVAL_EC_5006_BUILD_IN_SIREN_OFF           5006
#define JVAL_EC_5007_ZWAVE_INFO_UPDATE            5007
#define JVAL_EC_5008_timer_v1_INFO_UPDATE         5008
#define JVAL_EC_5009_timer_v2_INFO_UPDATE         5009
#define JVAL_EC_5031_SET_MAP                      5031
#define JVAL_EC_5032_PUSH_MSG                     5032

#define JVAL_EC_5096_NODE_ALIVE                   5096
#define JVAL_EC_5097_NODE_SLEEPING                5097

#define JVAL_EC_9999_ZWAVE_RUN_SWITCH             9999


//******************************************************************************
//** VALUE (NETWORK_CMD) **
//******************************************************************************
#define JVAL_NETWORK_CMD_AUTHCODE                 "authcode"
#define JVAL_NETWORK_CMD_BACKUP                   "backup"
#define JVAL_NETWORK_CMD_DISCONNECT_ICLOUD        "disconnect_icloud"
#define JVAL_NETWORK_CMD_FETCH                    "fetch"
#define JVAL_NETWORK_CMD_GETTTYBAUDRATE           "getttybaudrate"
#define JVAL_NETWORK_CMD_GETENABLEASTCLOCK        "getenableastclock"
#define JVAL_NETWORK_CMD_GETCLOUD_STORAGE         "getcloud_storage"
#define JVAL_NETWORK_CMD_GETSOCKETSEC             "getsocketsec"
#define JVAL_NETWORK_CMD_GETSSIDLIST              "getssidlist"
#define JVAL_NETWORK_CMD_GETTTYNAME               "getttyname"
#define JVAL_NETWORK_CMD_PROCTABLE                "proctable"
#define JVAL_NETWORK_CMD_RESETCONFIG              "resetconfig"
#define JVAL_NETWORK_CMD_RESTORE                  "restore"
#define JVAL_NETWORK_CMD_SETTTYBAUDRATE           "setttybaudrate"
#define JVAL_NETWORK_CMD_SETCLOUD_STORAGE         "setcloud_storage"
#define JVAL_NETWORK_CMD_SETSOCKETSEC             "setsocketsec"
#define JVAL_NETWORK_CMD_SETTTYNAME               "setttyname"
#define JVAL_NETWORK_CMD_SYSINFO                  "sysinfo"

#endif
