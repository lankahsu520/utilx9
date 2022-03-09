#ifndef __JSON_DEF_H__
#define __JSON_DEF_H__

//******************************************************************************
//** FILE **
//******************************************************************************
#define JSON_CONFIG_DIR                           "/mnt/PhilioData" // for PJ_HAS_PHILIO_SDK_V2/USE_ONVIF_MODULE_V2


//******************************************************************************
//** JKEY_ROOT_ **
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
#define JKEY_ROOT_TO                              "to"


//******************************************************************************
//** JKEY_INTERFACE_ **
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

// ***** onvif (v2) *****
#define JKEY_DEVICE_MEDIA                         "media"
#define JKEY_DEVICE_ONVIF_INFO                    "onvif_info"


//******************************************************************************
//** JKEY_CHANNEL_ **
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
//** JKEY_COMM_ **
//******************************************************************************
#define JKEY_COMM_ACTION                          "action"
#define JKEY_COMM_AP_SSID                         "AP_SSID"
#define JKEY_COMM_ASSOCIATE_GROUP                 "associategroup"
#define JKEY_COMM_ASSOCIATE_UID                   "assciateuid"
#define JKEY_COMM_BASIC_VALUE                     "basicvalue"
#define JKEY_COMM_BOOTUP                          "bootup"
#define JKEY_COMM_BRANCH                          "branch"
#define JKEY_COMM_BRAND                           "brand"
#define JKEY_COMM_BUILDER                         "builder"
#define JKEY_COMM_BUILDNO                         "buildno"
#define JKEY_COMM_BUILDTIME                       "buildtime"
#define JKEY_COMM_BUTTON                          "button"
#define JKEY_COMM_CDT                             "cdt"
#define JKEY_COMM_CFGS                            "cfgs"
#define JKEY_COMM_CHANNEL                         "channel"
#define JKEY_COMM_CHECKSUM                        "checksum"
#define JKEY_COMM_CHID                            "chid"
#define JKEY_COMM_CLASS                           "class"
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
#define JKEY_COMM_COMPARISON                      "comparison"
#define JKEY_COMM_CPU_USAGE                       "cpu_usage"
#define JKEY_COMM_CRONTAB                         "crontab"
#define JKEY_COMM_CURR_VAL                        "curr_val"
#define JKEY_COMM_DAYM                            "daym"
#define JKEY_COMM_DAYW                            "dayw"
#define JKEY_COMM_DATA                            "data"
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
#define JKEY_COMM_DELAY                           "delay"
#define JKEY_COMM_DELTA_TIME                      "delta_time"
#define JKEY_COMM_DEV_EUI64                       "dev_eui64"
#define JKEY_COMM_DIM_ON_VALUE                    "Dim_ON_Value"
#define JKEY_COMM_DUR                             "dur"
#define JKEY_COMM_DURATION                        "duration"
#define JKEY_COMM_ENABLE                          "enable"
#define JKEY_COMM_ERRORCODE                       "ErrorCode"
#define JKEY_COMM_ERROR_CODE                      "error_code"
#define JKEY_COMM_EVENT                           "event"
#define JKEY_COMM_EVENTCODE                       "eventCode"
#define JKEY_COMM_EVT                             "evt"
#define JKEY_COMM_EXT1                            "ext1"
#define JKEY_COMM_EXT2                            "ext2"
#define JKEY_COMM_FAIL                            "fail"
#define JKEY_COMM_FCM_TOKEN                       "fcm_token"
#define JKEY_COMM_FDCOUNT                         "fdcount"
#define JKEY_COMM_FDSIZE                          "fdsize"
#define JKEY_COMM_FIRMWARE                        "firmware"
#define JKEY_COMM_FIRMWARE_DATE                   "firmware_date"
#define JKEY_COMM_FILENAME                        "filename"
#define JKEY_COMM_FLAGS                           "flags"
#define JKEY_COMM_FREERAM                         "freeram"
#define JKEY_COMM_FULL                            "full"
#define JKEY_COMM_FUNCTION                        "function"
#define JKEY_COMM_GROUP                           "group"
#define JKEY_COMM_HOMEID                          "homeid"
#define JKEY_COMM_HOSTNAME                        "hostname"
#define JKEY_COMM_HR                              "hr"
#define JKEY_COMM_ID                              "id"
#define JKEY_COMM_IDENTIFIER                      "identifier"
#define JKEY_COMM_IF                              "if"
#define JKEY_COMM_IMPORT                          "import"
#define JKEY_COMM_INDEX                           "index"
#define JKEY_COMM_IP                              "ip"
#define JKEY_COMM_ISCEN                           "iscen"
#define JKEY_COMM_JSONGETUSERDATA_NUMBER          "jsongetuserdata_number"
#define JKEY_COMM_JSONSETALL_NUMBER               "jsonsetall_number"
#define JKEY_COMM_KERNEL                          "kernel"
#define JKEY_COMM_KEY                             "key"
#define JKEY_COMM_KEY_ATTR                        "key_attr"
#define JKEY_COMM_KEY_ATTR_NAME                   "key_attr_name"
#define JKEY_COMM_LANGUAGE                        "language"
#define JKEY_COMM_LAST_BEAT_TIME                  "lastbeattime"
#define JKEY_COMM_LAST_BEAT_TIME_UTC              "lastbeattime_utc"
#define JKEY_COMM_LAST_VALUE                      "last_value"
#define JKEY_COMM_LED                             "led"
#define JKEY_COMM_LEDS                            "leds"
#define JKEY_COMM_LEVEL                           "level"
#define JKEY_COMM_LINKS                           "links"
#define JKEY_COMM_LOAD0                           "load0"
#define JKEY_COMM_LOAD1                           "load1"
#define JKEY_COMM_LOAD2                           "load2"
#define JKEY_COMM_LOGICAL                         "logical"
#define JKEY_COMM_MAC                             "mac"
#define JKEY_COMM_MAP                             "map"
#define JKEY_COMM_MAXNUMBER                       "maxnumber"
#define JKEY_COMM_MAX_ADDR                        "maxaddr"
#define JKEY_COMM_MD5SUM                          "md5sum"
#define JKEY_COMM_MEM                             "mem"
#define JKEY_COMM_MIN                             "min"
#define JKEY_COMM_MIXTURE_NAME                    "mixture_name"
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
#define JKEY_COMM_REPRESENT                       "represent"
#define JKEY_COMM_ROOT                            "root"
#define JKEY_COMM_OFFSET                          "offset"
#define JKEY_COMM_ORDER                           "order"
#define JKEY_COMM_ORBWEB_UUID                     "Orbweb_UUID"
#define JKEY_COMM_PANID                           "panid"
#define JKEY_COMM_PASS                            "pass"
#define JKEY_COMM_PORT                            "port"
#define JKEY_COMM_PROTOCOL_ID                     "protocol_id"
#define JKEY_COMM_PROTOCOL_NAME                   "protocol_name"
#define JKEY_COMM_PRODUCT_TYPE                    "product_type"
#define JKEY_COMM_PRODUCT_UID                     "productUid"
#define JKEY_COMM_PROFILETOKEN                    "profiletoken"
#define JKEY_COMM_PROJECT                         "project"
#define JKEY_COMM_RATE_TYPE                       "rate_type"
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
#define JKEY_COMM_SCENE_NUMBER                    "scene_number"
#define JKEY_COMM_SECOND                          "sec"
#define JKEY_COMM_SECONDE                         "seconde"
#define JKEY_COMM_SECURITY                        "security"
#define JKEY_COMM_SEQ                             "seq"
#define JKEY_COMM_SETASTCLOCK_LAT                 "setastclock_lat"
#define JKEY_COMM_SETASTCLOCK_LON                 "setastclock_lon"
#define JKEY_COMM_SIGN                            "sign"
#define JKEY_COMM_SLOW_REFRESH                    "slow_refresh"
#define JKEY_COMM_SET_CHECKBOX                    "jsonsetcheckbox"
#define JKEY_COMM_SET_ENABLELOCK                  "enablelock"
#define JKEY_COMM_SET_SUpwd                       "SU_PASSWORD"
#define JKEY_COMM_SIZE                            "size"
#define JKEY_COMM_STATE                           "state"
#define JKEY_COMM_STATUS                          "status"
#define JKEY_COMM_STATUSFLAG                      "status_flag"
#define JKEY_COMM_STA_SSID                        "STA_SSID"
#define JKEY_COMM_STEAL                           "steal"
#define JKEY_COMM_SUNRISE                         "sunrise"
#define JKEY_COMM_SUNSET                          "sunset"
#define JKEY_COMM_SWVERSION                       "swversion"
#define JKEY_COMM_SYS                             "sys"
#define JKEY_COMM_TAMPER                          "tamper"
#define JKEY_COMM_TGT_VAL                         "tgt_val"
#define JKEY_COMM_TEHN                            "then"
#define JKEY_COMM_TIME                            "time"
#define JKEY_COMM_TIME_UTC                        "time_utc"
#define JKEY_COMM_TOGGLE                          "toggle"
#define JKEY_COMM_TONE_ID                         "tone_id"
#define JKEY_COMM_TONE_VOL                        "tone_vol"
#define JKEY_COMM_TOPIC                           "topic"
#define JKEY_COMM_TOTALRAM                        "totalram"
#define JKEY_COMM_TRIGGER                         "trigger"
#define JKEY_COMM_TUTK_UUID                       "TUTK_UUID"
#define JKEY_COMM_TYPE                            "type"
#define JKEY_COMM_TYPE_E                          "type_e"
#define JKEY_COMM_TYPE_NAME                       "type_name"
#define JKEY_COMM_TZ                              "tz"
#define JKEY_COMM_UDN                             "udn"
#define JKEY_COMM_UID                             "uid"
#define JKEY_COMM_UIDS                            "uids"
#define JKEY_COMM_UNIT                            "unit"
#define JKEY_COMM_UNIT_NAME                       "unit_name"
#define JKEY_COMM_UPTIME                          "uptime"
#define JKEY_COMM_URL                             "url"
#define JKEY_COMM_USE                             "use"
#define JKEY_COMM_USE_DEFAULT                     "use_default"
#define JKEY_COMM_USER                            "user"
#define JKEY_COMM_USERCODE                        "usercode"
#define JKEY_COMM_USER_ID                         "userID"
#define JKEY_COMM_USER_ID_NUM                     "usernum"
#define JKEY_COMM_USER_PASS                       "password"
#define JKEY_COMM_PRV_VALUE                       "prv_value"
#define JKEY_COMM_USER_PID                        "pid"
#define JKEY_COMM_USER_STATUS                     "status"
#define JKEY_COMM_USE_BUILDIN_SIREN               "use_buildin_siren"
#define JKEY_COMM_UUID                            "uuid"
#define JKEY_COMM_VALUE                           "value"
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


//******************************************************************************
// JKEY_REPORT_
//******************************************************************************
#define JKEY_REPORT_1ST_SUP                       "1st_sup"
#define JKEY_REPORT_AUX                           "aux"

#define JKEY_REPORT_BASIC                         "basic"
#define JKEY_REPORT_BASIC_SET                     "basic_set"

#define JKEY_REPORT_BATTERY                       "battery"
#define JKEY_REPORT_BSENSOR_SUP                   "bsensor_sup"
#define JKEY_REPORT_CFG                           "cfg"
#define JKEY_REPORT_CLOCK                         "clock"
#define JKEY_REPORT_CO                            "co"
#define JKEY_REPORT_CO2                           "co2"
#define JKEY_REPORT_COMMAND                       "command"
#define JKEY_REPORT_CSC_CFG                       "csc_cfg"
#define JKEY_REPORT_CSC_NOTIFICATION              "csc_notification"
#define JKEY_REPORT_CSC_SUP                       "csc_sup"
#define JKEY_REPORT_DEBUG                         "debug"
#define JKEY_REPORT_DIMMER                        "dimmer"
#define JKEY_REPORT_DOOR                          "door"
#define JKEY_REPORT_ECHO                          "echo"
#define JKEY_REPORT_EMERGENCY                     "emergency"
#define JKEY_REPORT_EVT                           "zevent"
#define JKEY_REPORT_FIRST                         "first"
#define JKEY_REPORT_FREEZE                        "freeze"
#define JKEY_REPORT_GATEWAY                       "gateway"
#define JKEY_REPORT_GLASS                         "glass"
#define JKEY_REPORT_GP                            "gp"

#define JKEY_REPORT_GROUP                         "group"
#define JKEY_REPORT_GROUP_ACTIVE                  "group_active"
#define JKEY_REPORT_GROUP_SUP                     "group_sup"

#define JKEY_REPORT_HEAT                          "heat"
#define JKEY_REPORT_HUMIDITY                      "humidity"
#define JKEY_REPORT_INFRARED                      "infrared"
#define JKEY_REPORT_LUMINANCE                     "luminance"

#define JKEY_REPORT_METER                         "meter"
#define JKEY_REPORT_METER_SUP                     "meter_sup"

#define JKEY_REPORT_MOTION                        "motion"

#define JKEY_REPORT_NODE_APP_VER                  "app_ver"
#define JKEY_REPORT_NODE_CATEGORY                 "category"
#define JKEY_REPORT_NODE_DSK                      "dsk"
#define JKEY_REPORT_NODE_GENERIC                  "generic"
#define JKEY_REPORT_NODE_INFO                     "nodeinfo"
#define JKEY_REPORT_NODE_INSTR_ICON               "instr_icon"
#define JKEY_REPORT_NODE_LIB_TYPE                 "lib_type"
#define JKEY_REPORT_NODE_LISTEN                   "listen"
#define JKEY_REPORT_NODE_PIN                      "pin"
#define JKEY_REPORT_NODE_PROPTY                   "propty"
#define JKEY_REPORT_NODE_PROPTY_NAME              "propty_name"
#define JKEY_REPORT_NODE_PROTO_VER                "proto_ver"
#define JKEY_REPORT_NODE_ROLE_TYPE                "role_type"
#define JKEY_REPORT_NODE_S2_GRNT_KEYS             "s2_grnt_keys"
#define JKEY_REPORT_NODE_S2_GRNT_KEYS_NAME        "s2_grnt_keys_name"
#define JKEY_REPORT_NODE_S2_KEYS_VALID            "s2_keys_valid"
#define JKEY_REPORT_NODE_SENSOR                   "sensor"
#define JKEY_REPORT_NODE_SLEEP_CAP                "sleep_cap"
#define JKEY_REPORT_NODE_SPECIFIC                 "specific"
#define JKEY_REPORT_NODE_TYPE                     "node_type"
#define JKEY_REPORT_NODE_USR_ICON                 "usr_icon"
#define JKEY_REPORT_NODE_VENDOR                   "vendor"
#define JKEY_REPORT_NODE_VENDOR_PID               "pid"
#define JKEY_REPORT_NODE_VENDOR_PTYPE             "ptype"
#define JKEY_REPORT_NODE_VENDOR_VID               "vid"
#define JKEY_REPORT_NODE_XXX                      "node_xxx"
#define JKEY_REPORT_NODE_ZWPLUS_VER               "zwplus_ver"

#define JKEY_REPORT_NOP                           "nop"

#define JKEY_REPORT_NW_BOOTUP                     "bootup"
#define JKEY_REPORT_NW_BUSY                       "busy"
#define JKEY_REPORT_NW_HOMEID                     "homeid"
#define JKEY_REPORT_NW_NOROUTE                    "noroute"
#define JKEY_REPORT_NW_NO_ACK                     "no_ack"
#define JKEY_REPORT_NW_SERIAL                     "serial"
#define JKEY_REPORT_NW_SYS_ERR                    "sys_err"
#define JKEY_REPORT_NW_XXX                        "nw_xxx"

#define JKEY_REPORT_OP                            "op"
#define JKEY_REPORT_OP_ABORTED                    "aborted"
#define JKEY_REPORT_OP_ABORTING                   "aborting"
#define JKEY_REPORT_OP_ADDED                      "added"
#define JKEY_REPORT_OP_ADDING                     "adding"
#define JKEY_REPORT_OP_LEARNED                    "learned"
#define JKEY_REPORT_OP_LEARNING                   "learning"
#define JKEY_REPORT_OP_NORMAL                     "normal"
#define JKEY_REPORT_OP_REMOVED                    "removed"
#define JKEY_REPORT_OP_REMOVED_FAILED             "removed_failed"
#define JKEY_REPORT_OP_REMOVING                   "removing"
#define JKEY_REPORT_OP_REMOVING_FAILED            "removing_failed"
#define JKEY_REPORT_OP_REPLACED_FAILED            "replaced_failed"
#define JKEY_REPORT_OP_REPLACING_FAILED           "replacing_failed"
#define JKEY_REPORT_OP_RESET                      "reset"
#define JKEY_REPORT_OP_RESETING                   "reseting"

#define JKEY_REPORT_POWER                         "power"
#define JKEY_REPORT_POWER_OVER_LOAD               "power_over_load"

#define JKEY_REPORT_PROTECTION                    "protection"
#define JKEY_REPORT_READY                         "ready"

#define JKEY_REPORT_SETPOINT_TEMP                 "temp"
#define JKEY_REPORT_SETPOINT_UNIT                 "unit"

#define JKEY_REPORT_SEC                           "sec"
#define JKEY_REPORT_SENSOR_SUP                    "sensor_sup"
#define JKEY_REPORT_SENSOR_UNIT_SUP               "sensor_unit_sup"
#define JKEY_REPORT_SIREN                         "siren"
#define JKEY_REPORT_SMOKE                         "smoke"
#define JKEY_REPORT_SWITCH                        "switch"
#define JKEY_REPORT_SWITCH_ALL                    "switch_all"
#define JKEY_REPORT_SYSTEM                        "system"
#define JKEY_REPORT_TAMPER                        "tamper"
#define JKEY_REPORT_TEMPERATURE                   "temperature"
#define JKEY_REPORT_TILT                          "tilt"

#define JKEY_REPORT_WAKEUP                        "wakeup"
#define JKEY_REPORT_WAKEUP_CUR                    "cur"
#define JKEY_REPORT_WAKEUP_DEF                    "def"
#define JKEY_REPORT_WAKEUP_INTERVAL               "interval"
#define JKEY_REPORT_WAKEUP_MAX                    "max"
#define JKEY_REPORT_WAKEUP_MIN                    "min"
#define JKEY_REPORT_WAKEUP_NOTIFY                 "notify"

#define JKEY_REPORT_WATCH_OFF                     "watch_off"

#define JKEY_REPORT_WATER                         "water"

#define JKEY_REPORT_XXX                           "report_xxx"
#define JKEY_REPORT_ZWINFO                        "zwinfo"

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
//** JVAL_ **
//******************************************************************************
#define JVAL_ACTION_GET                           "GET"
#define JVAL_ACTION_PUT                           "PUT"
#define JVAL_ACTION_DELETE                        "DELETE"
#define JVAL_ACTION_POST                          "POST"
#define JVAL_ACTION_PATCH                         "PATCH"

#define JVAL_BRANCH_S2                            "s2"
#define JVAL_BRANCH_V1                            "v1"
#define JVAL_BRANCH_V2                            "v2"
#define JVAL_BRANCH_V3                            "v3"

#define JVAL_COMM_CLOSED                          "closed"
#define JVAL_COMM_SUCCESS                         "success"
#define JVAL_COMM_FAIL                            "fail"
#define JVAL_COMM_IDLE                            "idle"
#define JVAL_COMM_OFF                             "off"
#define JVAL_COMM_ON                              "on"
#define JVAL_COMM_OPEN                            "open"
#define JVAL_COMM_LOCK                            "lock"
#define JVAL_COMM_UNLOCK                          "unlock"
#define JVAL_COMM_UNKNOWN                         "unknown"

#define JVAL_WATER_LEAK                           "water_leak"
#define JVAL_WATER_LEVEL_DROPPED                  "water_level_dropped"

#define JVAL_DEVNAME_NETWORK                      "network"
#define JVAL_DEVNAME_ZIGBEE                       "zigbee"
#define JVAL_DEVNAME_ZWAVE                        "zwave"

#define JVAL_METER_CURRENT                        "current"
#define JVAL_METER_KWH                            "kwh"
#define JVAL_METER_PF                             "pf"
#define JVAL_METER_VOLTAGE                        "voltage"
#define JVAL_METER_WATT                           "watt"

#define JVAL_CLASS_MAC_ADDRESS                    "MAC Address"
#define JVAL_CLASS_GROUPID                        "Group ID"
#define JVAL_CLASS_UUID                           "UUID"
#define JVAL_CLASS_NODEID                         "Node ID"
#define JVAL_CLASS_EPID                           "Endpoint ID"

#define JVAL_CLASS_BASIC                          "Basic"
#define JVAL_CLASS_BASIC_SET                      "Basic Set"
#define JVAL_CLASS_BATTERY                        "Battery"
#define JVAL_CLASS_CONFIGURATION                  "Configuration"
#define JVAL_CLASS_CONTROLLER                     "Controller"
#define JVAL_CLASS_CENTRAL_SCENE                  "Central Scene"
#define JVAL_CLASS_CRON                           "Cron"
#define JVAL_CLASS_DIMMER                         "Dimmer"
#define JVAL_CLASS_DOOR                           "Door/Window Sensor"
#define JVAL_CLASS_DOOR_LOCK                      "Door Lock"
#define JVAL_CLASS_FLOOD                          "Flood Sensor"
#define JVAL_CLASS_HUMIDITY_SENSOR                "Humidity Sensor"
#define JVAL_CLASS_INFRARED                       "Infrared"
#define JVAL_CLASS_INFRARED_CONFIGURATION         "Infrared Configuration"
#define JVAL_CLASS_LUMINANCE_SENSOR               "Luminance Sensor"
#define JVAL_CLASS_MIXTURE                        "Mixture"
#define JVAL_CLASS_MOTION_SENSOR                  "Motion Sensor"
#define JVAL_CLASS_PHONE                          "Phone"
#define JVAL_CLASS_POWER_METER                    "Power Meter"
#define JVAL_CLASS_SMART_SWITCH                   "Smart switch"
#define JVAL_CLASS_SMOKE_SENSOR                   "Smoke Sensor"
#define JVAL_CLASS_SOUND_SWITCH                   "Sound Switch"
#define JVAL_CLASS_SWITCH                         "Switch"
#define JVAL_CLASS_TAMPER_SENSOR                  "Tamper Sensor"
#define JVAL_CLASS_TEMPERATURE_SENSOR             "Temperature Sensor"
#define JVAL_CLASS_WAKE_UP_INTERVAL               "Wakeup Interval"
#define JVAL_CLASS_WAKE_UP_SENSOR                 "Wakeup Sensor"

#define JVAL_NODE_ALIVE                           "alive"
#define JVAL_NODE_SLEEPING                        "sleeping"

#define JVAL_REPORT_START                         "start"
#define JVAL_REPORT_DONE                          "done"

#define JVAL_SECURITY_CSA                         "csa"
#define JVAL_SECURITY_LOWER                       "sec_lower"
#define JVAL_SECURITY_NORMAL                      "sec_normal"
#define JVAL_SECURITY_SSA                         "ssa"
#define JVAL_SECURITY_SET                         "ssa_set"

#define JVAL_UNKNOWN                              "???"

//******************************************************************************
// Report Payload (MQTT & MCTT)
//******************************************************************************
// ** report **
// methodid/protocolid/c_macid/c_uuid/c_nodeid/epid/issue/mode/submode/category/ts/val_len/val
#define JVAL_C_USERNAME_BROADCAST                "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"

#define JVAL_C_MAC_NULL                          "000000000000"
#define JVAL_C_MAC_BROADCAST                     "FFFFFFFFFFFF"
#define JVAL_C_UUID_NULL                         "00000000-0000-0000-0000-000000000000"
#define JVAL_C_UUID_BROADCAST                    "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"

#define JVAL_C_NODEID_NULL                       "00000000-0000-0000-0000-000000000000"
#define JVAL_C_NODEID_0                          "0"
#define JVAL_C_NODEID_1                          "1"
#define JVAL_C_NODEID_BROADCAST                  "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
#define JVAL_NODEID_CONTROLLER                   1
#define JVAL_EPID_BASE                           0

#define JVAL_METHODID_EVENT                      0
#define JVAL_METHODID_PUT                        1
#define JVAL_METHODID_GET                        2
#define JVAL_METHODID_RESPONSE                   3
#define JVAL_METHODID_MIXTURE                    JVAL_METHODID_GET//4
#define JVAL_METHODID_MIXTURE_RESPONSE           JVAL_METHODID_RESPONSE//5

#define JVAL_C_METHODID_EVENT                    "0"
#define JVAL_C_METHODID_PUT                      "1"
#define JVAL_C_METHODID_GET                      "2"
#define JVAL_C_METHODID_RESPONSE                 "3"
#define JVAL_C_METHODID_MIXTURE                  JVAL_C_METHODID_GET//4
#define JVAL_C_METHODID_MIXTURE_RESPONSE         JVAL_C_METHODID_RESPONSE//5

#define JVAL_PROTOCOLID_BASE                     0
#define JVAL_PROTOCOLID_ZWAVE                    1
#define JVAL_PROTOCOLID_ZWAVES2                  2
#define JVAL_PROTOCOLID_ZIGBEE                   3
#define JVAL_PROTOCOLID_PAN27                    4
#define JVAL_PROTOCOLID_BLUETOOTH                5
#define JVAL_PROTOCOLID_ONVIF                    11
#define JVAL_PROTOCOLID_WIFI_PHILIO              21
#define JVAL_PROTOCOLID_ZIGBEE_PHILIO            41
#define JVAL_PROTOCOLID_TIQIAA                   51 // IR
#define JVAL_PROTOCOLID_HONEY_MAEKET             0xFFFB
#define JVAL_PROTOCOLID_HONEYCOMB                0xFFFC
#define JVAL_PROTOCOLID_ECHO                     0xFFFD
#define JVAL_PROTOCOLID_MASTER                   0xFFFE
#define JVAL_PROTOCOLID_BROADCAST                0xFFFF



#define JVAL_MODE_NORMAL                         0
#define JVAL_SUBMODE_NORMAL                      0

#define JVAL_CATEGORY_NORMAL                     0
#define JVAL_CATEGORY_PLUG                       1
#define JVAL_CATEGORY_SIREN                      2
#define JVAL_CATEGORY_BINARY                     3
#define JVAL_CATEGORY_SETTING                    0x255
#define JVAL_CATEGORY_MASK_ID                    0x00FF
#define JVAL_CATEGORY_MASK_COUNT                 0xFF00

// Controller Issue
#define JKEY_ISSUEID_NULL                        0x00000000
#define JKEY_ISSUEID_GW                          0x00000000

#define JKEY_ISSUEID_READY                       0x00000001
#define JKEY_ISSUEID_ADDING                      0x00000002
#define JKEY_ISSUEID_REMOVING                    0x00000003
#define JKEY_ISSUEID_ABORTING                    0x00000004
#define JKEY_ISSUEID_LEARNING                    0x00000005
#define JKEY_ISSUEID_NW                          0x00000007
#define JKEY_ISSUEID_RESETING                    0x00000008
#define JKEY_ISSUEID_OP                          0x00000009

#define JKEY_ISSUEID_REPLACING                   0x0000000A
#define JKEY_ISSUEID_RMFAILED                    0x0000000B
#define JKEY_ISSUEID_NODE                        0x00000010
#define JKEY_ISSUEID_NOP                         0x00000011

#define JKEY_ISSUEID_GATEWAY_MASK                0x000FFFFF

// Node Issue
// ZW_BSENSOR_TYPE_XXX
#define JKEY_ISSUEID_GP                          0x00010001 // gp
#define JKEY_ISSUEID_SMOKE                       0x00010002 // smoke
#define JKEY_ISSUEID_CO                          0x00010003 // co
#define JKEY_ISSUEID_CO2                         0x00010004 // co2
#define JKEY_ISSUEID_HEAT                        0x00010005 // heat
#define JKEY_ISSUEID_WATER                       0x00010006 // water
#define JKEY_ISSUEID_FREEZE                      0x00010007 // 
#define JKEY_ISSUEID_TAMPER                      0x00010008 // tamper
#define JKEY_ISSUEID_AUX                         0x00010009
#define JKEY_ISSUEID_DR_WIN                      0x0001000A // door
#define JKEY_ISSUEID_TILT                        0x0001000B
#define JKEY_ISSUEID_MOTION                      0x0001000C // motion
#define JKEY_ISSUEID_GLASS_BRK                   0x0001000D // glass

// ZW_ALRM_XXX, it sometimes is the same as ZW_BSENSOR_TYPE_XXX
#define JKEY_ISSUEID_SYSTEM                      0x00020001 // system
#define JKEY_ISSUEID_EMERGENCY                   0x00020002 // emergency
#define JKEY_ISSUEID_ALARM                       0x00020003 // alarm
#define JKEY_ISSUEID_FIRST                       0x00020004 // first

#define JKEY_ISSUEID_INTRUSION                   0x00020005 // intrusion

#define JKEY_ISSUEID_CUSTOMER                    0x00020011 // customer

// ZW_SENSOR_TYPE_XXX
#define JKEY_ISSUEID_TEMPERATURE                 0x00030001 // Temperature sensor
#define JKEY_ISSUEID_GP_LEVEL                    0x00030002
#define JKEY_ISSUEID_LUM                         0x00030003 // Luminance sensor
#define JKEY_ISSUEID_POW                         0x00030004 // Power sensor
#define JKEY_ISSUEID_HUMD                        0x00030005 // Relative humidity sensor
#define JKEY_ISSUEID_VELO                        0x00030006
#define JKEY_ISSUEID_DIR                         0x00030007
#define JKEY_ISSUEID_ATM                         0x00030008
#define JKEY_ISSUEID_BARO                        0x00030009
#define JKEY_ISSUEID_SLR                         0x0003000A
#define JKEY_ISSUEID_DEW                         0x0003000B
#define JKEY_ISSUEID_RAIN                        0x0003000C
#define JKEY_ISSUEID_TIDE                        0x0003000D
#define JKEY_ISSUEID_WGT                         0x0003000E
#define JKEY_ISSUEID_VOLT                        0x0003000F
#define JKEY_ISSUEID_CUR                         0x00030010
#define JKEY_ISSUEID_CO2_LVL                     0x00030011 // CO2-level sensor
#define JKEY_ISSUEID_AIR                         0x00030012
#define JKEY_ISSUEID_TANK                        0x00030013
#define JKEY_ISSUEID_DIST                        0x00030014
#define JKEY_ISSUEID_AGL                         0x00030015
#define JKEY_ISSUEID_ROT                         0x00030016
#define JKEY_ISSUEID_WTR_TEMP                    0x00030017
#define JKEY_ISSUEID_SOIL_TEMP                   0x00030018
#define JKEY_ISSUEID_SEIS_INT                    0x00030019
#define JKEY_ISSUEID_SEIS_MAG                    0x0003001A
#define JKEY_ISSUEID_UV                          0x0003001B // Ultraviolet sensor
#define JKEY_ISSUEID_ELEC_RES                    0x0003001C
#define JKEY_ISSUEID_ELEC_COND                   0x0003001D
#define JKEY_ISSUEID_LOUDNESS                    0x0003001E
#define JKEY_ISSUEID_MOIST                       0x0003001F
#define JKEY_ISSUEID_FREQ                        0x00030020
#define JKEY_ISSUEID_TIME                        0x00030021
#define JKEY_ISSUEID_TGT_TEMP                    0x00030022
#define JKEY_ISSUEID_PM_2_5                      0x00030023
#define JKEY_ISSUEID_F_CH2O                      0x00030024
#define JKEY_ISSUEID_RAD_CONT                    0x00030025
#define JKEY_ISSUEID_METH_DENS                   0x00030026
#define JKEY_ISSUEID_VOC                         0x00030027 // Volatile Organic Compound sensor
#define JKEY_ISSUEID_CO_LVL                      0x00030028 // Carbon Monoxide CO-level sensor
#define JKEY_ISSUEID_SOIL_HUMD                   0x00030029
#define JKEY_ISSUEID_SOIL_REAC                   0x0003002A
#define JKEY_ISSUEID_SOIL_SAL                    0x0003002B
#define JKEY_ISSUEID_HEART_RT                    0x0003002C
#define JKEY_ISSUEID_BLOOD_PRS                   0x0003002D
#define JKEY_ISSUEID_MUSCLE_MS                   0x0003002E
#define JKEY_ISSUEID_FAT_MS                      0x0003002F
#define JKEY_ISSUEID_BONE_MS                     0x00030030
#define JKEY_ISSUEID_TBW                         0x00030031
#define JKEY_ISSUEID_BMR                         0x00030032
#define JKEY_ISSUEID_BMI                         0x00030033
#define JKEY_ISSUEID_ACCEL_X                     0x00030034
#define JKEY_ISSUEID_ACCEL_Y                     0x00030035
#define JKEY_ISSUEID_ACCEL_Z                     0x00030036
#define JKEY_ISSUEID_SMOKE_DEN                   0x00030037
#define JKEY_ISSUEID_WATER_FLW                   0x00030038
#define JKEY_ISSUEID_WATER_PRS                   0x00030039
#define JKEY_ISSUEID_RF_SGN                      0x0003003A

// COMMAND_CLASS_XXX
#define JKEY_ISSUEID_CC_XXX_POSTSET              0x000900FF // xxx_postset

#define JKEY_ISSUEID_CC_APPLICATION_BUSY         0x00092201 // appl_busy
#define JKEY_ISSUEID_CC_APPLICATION_REJECT       0x00092202 // appl_reject

#define JKEY_ISSUEID_CC_DIMMER                   0x00092601 // level
#define JKEY_ISSUEID_CC_DIMMER_SUP               0x00092602 // level_sup
#define JKEY_ISSUEID_CC_DIMMER_POSTSET           0x000926FF // level_postset

#define JKEY_ISSUEID_CC_BASIC                    0x00092001 // basic
#define JKEY_ISSUEID_CC_BASIC_SET                0x00092002 // basic_set

#define JKEY_ISSUEID_CC_SWITCH                   0x00092501 // switch
#define JKEY_ISSUEID_CC_SWITCH_SIREN             0x00092502 // siren
#define JKEY_ISSUEID_CC_SWITCH_PLUG              0x00092503 // plug

#define JKEY_ISSUEID_CC_SWITCH_ALL               0x00092701 // switch_all

#define JKEY_ISSUEID_CC_BSENSOR                  0x00093001 // bsensor
#define JKEY_ISSUEID_CC_BSENSOR_SUP              0x00093002 // bsensor_sup

#define JKEY_ISSUEID_CC_SENSOR                   0x00093101 // sensor
#define JKEY_ISSUEID_CC_SENSOR_SUP               0x00093102 // sensor_sup
#define JKEY_ISSUEID_CC_SENSOR_UNIT_SUP          0x00093103 // sensor_unit_sup

#define JKEY_ISSUEID_CC_METER                    0x00093201 // meter
#define JKEY_ISSUEID_CC_METER_SUP                0x00093202 // meter_sup

#define JKEY_ISSUEID_CC_COLOR                    0x00093301 // color
#define JKEY_ISSUEID_CC_COLOR_MASK               0x00093302 // color_mask
#define JKEY_ISSUEID_CC_COLOR_SUP                0x00093303 // color_sup

#define JKEY_ISSUEID_CC_THERMOSTAT_MODE          0x00094001 // thermostat_mode
#define JKEY_ISSUEID_CC_THERMOSTAT_MODE_SUP      0x00094002 // thermostat_mode_sup
#define JKEY_ISSUEID_CC_THERMOSTAT_OPERATING     0x00094201 // thermostat_op
#define JKEY_ISSUEID_CC_THERMOSTAT_SETPOINT      0x00094301 // thermostat_setp
#define JKEY_ISSUEID_CC_THERMOSTAT_SETPOINT_SUP  0x00094302 // thermostat_setp_sup
#define JKEY_ISSUEID_CC_THERMOSTAT_SETPOINT_SUP_RANGE 0x00094303 // thermostat_setp_sup_range
#define JKEY_ISSUEID_CC_THERMOSTAT_FAN_MODE      0x00094401 // thermostat_fan
#define JKEY_ISSUEID_CC_THERMOSTAT_FAN_MODE_SUP  0x00094402 // thermostat_fan_sup
#define JKEY_ISSUEID_CC_THERMOSTAT_FAN_STATE     0x00094501 // thermostat_fan_state

#define JKEY_ISSUEID_CC_CENTRAL_SCENE_NOTIFICATION 0x00095b01 // csc_notification
#define JKEY_ISSUEID_CC_CENTRAL_SCENE_SUP        0x00095b02 // csc_sup
#define JKEY_ISSUEID_CC_CENTRAL_SCENE_CFG        0x00095b03 // csc_cfg

#define JKEY_ISSUEID_CC_DOOR_LOCK                0x00096201 // lock
#define JKEY_ISSUEID_CC_DOOR_LOCK_CFG            0x00096202 // lock_cfg
#define JKEY_ISSUEID_CC_DOOR_LOCK_POSTSET        0x000962FF // lock_postset

#define JKEY_ISSUEID_CC_USER_CODE                0x00096301 // user_code
#define JKEY_ISSUEID_CC_USER_CODE_SUP            0x00096302 // user_code_sup

#define JKEY_ISSUEID_CC_CONFIGURATION            0x00097001 // configuration

#define JKEY_ISSUEID_CC_POWER_LEVEL              0x00097301 // power_level
#define JKEY_ISSUEID_CC_POWER_LEVEL_TEST         0x00097302 // power_level_test

#define JKEY_ISSUEID_CC_PROTECTION               0x00097501 // protection

#define JKEY_ISSUEID_CC_SOUND_SWITCH             0x00097901 // COMMAND_CLASS_SOUND_SWITCH

#define JKEY_ISSUEID_CC_BATTERY                  0x00098001 // COMMAND_CLASS_BATTERY

#define JKEY_ISSUEID_CC_WAKE_UP_INTERVAL         0x00098401 // wakeup_interval
#define JKEY_ISSUEID_CC_WAKE_UP_NOTIFICATION     0x00098402 // wakeup_notification

#define JKEY_ISSUEID_CC_CLOCK                    0x00098101 // clock

#define JKEY_ISSUEID_CC_GROUP                    0x00098501 // group
#define JKEY_ISSUEID_CC_GROUP_SUP                0x00098502 // group_sup
#define JKEY_ISSUEID_CC_GROUP_ACTVIE             0x00098503 // group_active

#define JKEY_ISSUEID_CC_VERSION_CC               0x00098601 // version_cc
#define JKEY_ISSUEID_CC_VERSION_ZW               0x00098602 // version_zw

#define JKEY_ISSUEID_CC_SIMPLE_AV_CONTROL_SET    0x00099401 // simple_av_control_set
#define JKEY_ISSUEID_CC_SIMPLE_AV_CONTROL        0x00099402 // simple_av_control

// USER-DEFINDED
#define JKEY_ISSUEID_CC_INFRARED                 0x000A9501 //
#define JKEY_ISSUEID_CC_INFRARED_CODE            0x000A9502 //

#define JKEY_ISSUEID_CC_CRON                     0x000A9601 //

#define JKEY_ISSUEID_CC_PHONE                    0x000A9701 //

// JKEY_ISSUEID_GW, 
#define ZWAVE_EVT_GW_CFG                        95
#define ZWAVE_EVT_GW_CMD                        96
#define ZWAVE_EVT_GW_DEBUG                      97
#define ZWAVE_EVT_GW_WATCH_OFF                  98
#define ZWAVE_EVT_GW_ECHO                       99

// JKEY_ISSUEID_ADDING, 
#define ZWAVE_EVT_ADDING_START                  0
#define ZWAVE_EVT_ADDING_SSA_SET                80
#define ZWAVE_EVT_ADDING_CSA                    81
#define ZWAVE_EVT_ADDING_SSA                    82
#define ZWAVE_EVT_ADDING_SEC                    83
#define ZWAVE_EVT_ADDING_DONE                   97
#define ZWAVE_EVT_ADDING_ADDED                  98
#define ZWAVE_EVT_ADDING_FAIL                   99

// JKEY_ISSUEID_REMOVING,
#define ZWAVE_EVT_REMOVING_START                0
#define ZWAVE_EVT_REMOVING_DONE                 97
#define ZWAVE_EVT_REMOVING_REMOVED              98
#define ZWAVE_EVT_REMOVING_FAIL                 99

// JKEY_ISSUEID_LEARNING,
#define ZWAVE_EVT_LEARNING_START                0
#define ZWAVE_EVT_LEARNING_INI_PROTOCOL_DONE    1
#define ZWAVE_EVT_LEARNING_SSA                  82
#define ZWAVE_EVT_LEARNING_DONE                 97
#define ZWAVE_EVT_LEARNING_LEARNED              98
#define ZWAVE_EVT_LEARNING_FAIL                 99

// JKEY_ISSUEID_ABORTING,
#define ZWAVE_EVT_ABORTING_START                0
#define ZWAVE_EVT_ABORTING_DONE                 97
#define ZWAVE_EVT_ABORTING_ABORTED              98
#define ZWAVE_EVT_ABORTING_FAIL                 99

// JKEY_ISSUEID_RMFAILED,
#define ZWAVE_EVT_RMFAILED_START                0
#define ZWAVE_EVT_RMFAILED_DONE                 97
#define ZWAVE_EVT_RMFAILED_REMOVED              98
#define ZWAVE_EVT_RMFAILED_FAIL                 99

// JKEY_ISSUEID_REPLACING,
#define ZWAVE_EVT_REPLACING_START               0
#define ZWAVE_EVT_REPLACING_PROTOCOL_DONE       1
#define ZWAVE_EVT_REPLACING_GET_NODE_INFO       2
#define ZWAVE_EVT_REPLACING_SSA                 82
#define ZWAVE_EVT_REPLACING_DONE                97
#define ZWAVE_EVT_REPLACING_REPLACED            98
#define ZWAVE_EVT_REPLACING_FAIL                99

// JKEY_ISSUEID_RESETING, 
#define ZWAVE_EVT_RESETING_START                0
#define ZWAVE_EVT_RESETING_DONE                 97
#define ZWAVE_EVT_RESETING_REMOVED              98
#define ZWAVE_EVT_RESETING_FAIL                 99

// JKEY_ISSUEID_NW
#define ZWAVE_EVT_NW_NOROUTE                    4 // ZWNET_TX_NOROUTE
#define ZWAVE_EVT_NW_BUSY                       5 // ZWNET_TX_DEST_BUSY
#define ZWAVE_EVT_NW_NO_ACK                     6 // ZWNET_TX_NO_ACK
#define ZWAVE_EVT_NW_SYS_ERR                    7 // ZWNET_TX_SYS_ERR
#define ZWAVE_EVT_NW_BOOTUP                     27
#define ZWAVE_EVT_NW_SERIAL                     28
#define ZWAVE_EVT_NW_HOMEID                     29
#define ZWAVE_EVT_NW_SAVE                       96
#define ZWAVE_EVT_NW_DEBUG                      97
#define ZWAVE_EVT_NW_WATCH_OFF                  98
#define ZWAVE_EVT_NW_ECHO                       99

// JKEY_ISSUEID_NODE
#define ZWAVE_EVT_NODE_ALIVE                    1
#define ZWAVE_EVT_NODE_SLEEPING                 2
#define ZWAVE_EVT_NODE_TYPE                     93
#define ZWAVE_EVT_NODE_SEE_YOU                  94 // gw to others
#define ZWAVE_EVT_NODE_GENERIC                  95
#define ZWAVE_EVT_NODE_HELLO                    96
#define ZWAVE_EVT_NODE_INFO                     97
#define ZWAVE_EVT_NODE_VENDOR                   98

// ZWAVE_EVT_XXX
#define ZWAVE_EVT_0XFF                          0xFF
#define ZWAVE_EVT_0X00                          0x00

// JKEY_ISSUEID_CC_DOOR_LOCK
#define ZWAVE_EVT_DOOR_UNSEC                    0x00 // ZW_DOOR_UNSEC
#define ZWAVE_EVT_DOOR_SEC                      0xFF // ZW_DOOR_SEC

// Alarm
#define ZWAVE_EVT_INACTIVE_CLEAR                0x00 // ZW_ALRM_EVT_INACTIVE_CLEAR

#define ZWAVE_EVT_WINDOW_DOOR_OPEN              0x16 // ZW_ALRM_EVT_WINDOW_DOOR_OPEN
#define ZWAVE_EVT_WINDOW_DOOR_CLOSED            0x17 // ZW_ALRM_EVT_WINDOW_DOOR_CLOSED

#define ZWAVE_EVT_SMOKE_L                       0x01 // ZW_ALRM_EVT_SMOKE_L
#define ZWAVE_EVT_SMOKE                         0x02 // ZW_ALRM_EVT_SMOKE
#define ZWAVE_EVT_SMOKE_TEST                    0x03 // ZW_ALRM_EVT_SMOKE_TEST
#define ZWAVE_EVT_SMOKE_REPLA                   0x04 // ZW_ALRM_EVT_SMOKE_REPLA

#define ZWAVE_EVT_CO_L                          0x01 // ZW_ALRM_EVT_CO_L
#define ZWAVE_EVT_CO                            0x02 // ZW_ALRM_EVT_CO
#define ZWAVE_EVT_CO_TEST                       0x03 // ZW_ALRM_EVT_CO_TEST
#define ZWAVE_EVT_CO_REPLA                      0x04 // ZW_ALRM_EVT_CO_REPLA

#define ZWAVE_EVT_CO2_L                         0x01 // ZW_ALRM_EVT_CO2_L
#define ZWAVE_EVT_CO2                           0x02 // ZW_ALRM_EVT_CO2
#define ZWAVE_EVT_CO2_TEST                      0x03 // ZW_ALRM_EVT_CO2_TEST
#define ZWAVE_EVT_CO2_REPLA                     0x04 // ZW_ALRM_EVT_CO2_REPLA

#define ZWAVE_EVT_EVT_POLICE                    0x01 // ZW_ALRM_EVT_POLICE
#define ZWAVE_EVT_EVT_FIRE                      0x02 // ZW_ALRM_EVT_FIRE
#define ZWAVE_EVT_EVT_MEDICAL                   0x03 // ZW_ALRM_EVT_MEDICAL

#define ZWAVE_EVT_INTRUSION_L                   0x01 // ZW_ALRM_EVT_INTRUSION_L
#define ZWAVE_EVT_INTRUSION                     0x02 // ZWAVE_EVT_INTRUSION

#define ZWAVE_EVT_TMPR_COVER                    0x03 // ZW_ALRM_EVT_TMPR_COVER

#define ZWAVE_EVT_GLASS_L                       0x05 // ZW_ALRM_EVT_GLASS_L
#define ZWAVE_EVT_GLASS                         0x06 // ZW_ALRM_EVT_GLASS

#define ZWAVE_EVT_MOTION_DET_L                  0x07 // ZW_ALRM_EVT_MOTION_DET_L
#define ZWAVE_EVT_MOTION_DET                    0x08 // ZW_ALRM_EVT_MOTION_DET

#define ZWAVE_EVT_LEAK_L                        0x01 // ZW_ALRM_EVT_LEAK_L
#define ZWAVE_EVT_LEAK                          0x02 // ZW_ALRM_EVT_LEAK
#define ZWAVE_EVT_LVL_L                         0x03 // ZW_ALRM_EVT_LVL_L
#define ZWAVE_EVT_LVL                           0x04 // ZW_ALRM_EVT_LVL
#define ZWAVE_EVT_REPLACE_WATER_FILTER          0x05 // ZW_ALRM_EVT_REPLACE_WATER_FILTER
#define ZWAVE_EVT_WATER_FLOW                    0x06 // ZW_ALRM_EVT_WATER_FLOW
#define ZWAVE_EVT_WATER_PRESSURE                0x07 // ZW_ALRM_EVT_WATER_PRESSURE

#define ZWAVE_IDX_ALRM_EX_EVENT                 0
#define ZWAVE_IDX_ALRM_EX_HAS_SEQUENCE          (ZWAVE_IDX_ALRM_EX_EVENT + 1)
#define ZWAVE_IDX_ALRM_EX_SEQUENCE_NO           (ZWAVE_IDX_ALRM_EX_HAS_SEQUENCE + 1)
#define ZWAVE_IDX_ALRM_EX_EVT_TYPE              (ZWAVE_IDX_ALRM_EX_SEQUENCE_NO + 1)
#define ZWAVE_IDX_ALRM_EX_EVT_LEN               (ZWAVE_IDX_ALRM_EX_EVT_TYPE + 1)
#define ZWAVE_IDX_ALRM_EX_EVT_PRM               (ZWAVE_IDX_ALRM_EX_EVT_LEN + 1)

// Values used for Color Supported Report command
#define COLOR_COMPONENT_WARM_WHITE              0 // 0x0001
#define COLOR_COMPONENT_COLD_WHITE              1 // 0x0002
#define COLOR_COMPONENT_RED                     2 // 0x0004
#define COLOR_COMPONENT_GREEN                   3 // 0x0008
#define COLOR_COMPONENT_BLUE                    4 // 0x0010
#define COLOR_COMPONENT_AMBER                   5 // 0x0020
#define COLOR_COMPONENT_CYAN                    6 // 0x0040
#define COLOR_COMPONENT_PURPLE                  7 // 0x0080
#define COLOR_COMPONENT_INDEXED_COLOR           8 // 0x0100
#define COLOR_COMPONENT_MAX                     9

//******************************************************************************
//** JSTR_ (Philio - NETWORK_CMD) **
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


//******************************************************************************
//** JVAL_ (Philio - CONTROL) **
//******************************************************************************
#define JVAL_RESULT_BYE_BYE                   "Bye-Bye !!!"
#define JVAL_RESULT_NO_SUPPORT                "No support !!!"


//******************************************************************************
//** JKEY_ (Philio - CONTROL) **
//******************************************************************************
#define JKEY_CONTROL_RESP_CODE                    "respcode"
#define JKEY_CONTROL_RESP_MSG                     "respmsg"


//******************************************************************************
//** JSTR_ (Philio - CONTROL_CMD) **
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
//** JVAL_ **
//******************************************************************************
#define JVAL_BASIC_OFF                            0
#define JVAL_BASIC_ON                             255

#define JVAL_DIMMER_OFF                           0x0
#define JVAL_DIMMER_99                            0x63
#define JVAL_DIMMER_ON                            0xFF
#define JVAL_DIMMER_UNKNOWN                       0xFE

#define JVAL_BATTERY_AC_255                       255
#define JVAL_BATTERY_AC_MINUS_1                   -1
#define JVAL_BATTERY_FULL_100                     100
#define JVAL_BATTERY_LOW_238                      0xEE
#define JVAL_BATTERY_UNKNOW_253                   0xFD

#define JVAL_CHID_0                               0
#define JVAL_DEFAULT_0                            0
#define JVAL_DEFAULT_255                          0xFF
#define JVAL_SECURITY_NONE                        0
#define JVAL_UNKNOWN_NUM                          2147483647
#define JVAL_FAIL                                 -2147483648

//#define JVAL_UNKNOWN_NUM                          4294967295


//******************************************************************************
//** JVAL_ (Yokis - ERROR) **
//******************************************************************************
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
//** JVAL_ (Philio - function) **
//******************************************************************************
// ***** (JVAL_FUNC_TYPE_XXX) *****
#define JVAL_FUNC_TYPE_UNKNOW                     0
/*故意保留 10個 給實體的 Channel 使用*/

#define JVAL_FUNC_TYPE_SENSOR_TEMPERATURE         11
#define JVAL_FUNC_TYPE_SENSOR_LUMINANCE           12
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
#define JVAL_CTRL_TYPE_SENSOR_LUMINANCE           12
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
#define JVAL_EC_4113_LUX_OVER                     4113 //data:Luminance
#define JVAL_EC_4114_LUX_BELOW                    4114 //data:Luminance
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
#define JVAL_EC_4802_LUX_REPORT                   4802 //data:Luminance
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


#endif
