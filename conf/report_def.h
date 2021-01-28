#ifndef __REPORT_DEF_H__
#define __REPORT_DEF_H__

#include "stdint.h"

//******************************************************************************
//** define **
//******************************************************************************
#define MAC_NULL "000000000000"
#define MAC_BROADCAST "FFFFFFFFFFFF"
#define UUID_NULL "00000000-0000-0000-0000"
#define UUID_BROADCAST "FFFFFFFF-FFFF-FFFF-FFFF"

#ifndef LEN_OF_MAC
#define LEN_OF_MAC 24
#endif
#ifndef LEN_OF_UUID
#define LEN_OF_UUID 40
#endif

typedef struct Identity_Struct
{
	char macid[LEN_OF_MAC]; // LEN_OF_MAC 24
	uint16_t groupid;
	uint16_t protocolid;
	char uuid[LEN_OF_UUID]; // LEN_OF_UUID 40
	uint16_t nodeid; // 0xFFFF
	uint8_t epid; // 0xFF
	// 24+2+2+40+2+1 = 71
} Identity_t;

typedef struct Commander_Struct
{
	Identity_t id_frm;
	Identity_t id_to;
} Commander_t;

typedef struct Reporter_Struct
{
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

//******************************************************************************
// REPORT
//******************************************************************************
// VALUE
#define JSTR_REPORT_0000                          "0"
#define JSTR_REPORT_0001                          "1"
#define JSTR_REPORT_0008                          "8"
#define JSTR_REPORT_0010                          "10"
#define JSTR_REPORT_0100                          "100"
#define JSTR_REPORT_0x00                          "0x00"
#define JSTR_REPORT_0xFF                          "0xFF"
#define JSTR_REPORT_CLOSED                        "closed"
#define JSTR_REPORT_CSA                           "csa"
#define JSTR_REPORT_DETECT                        "24"  // 30, but 3*8=24
#define JSTR_REPORT_DONE                          "done"
#define JSTR_REPORT_FAIL                          "fail"
#define JSTR_REPORT_FALSE                         "false"
#define JSTR_REPORT_NULL                          ""
#define JSTR_REPORT_OFF                           "off"
#define JSTR_REPORT_ON                            "on"
#define JSTR_REPORT_OPEN                          "open"
#define JSTR_REPORT_REPLACEMENT                   "replacement"
#define JSTR_REPORT_SEC                           "sec"
#define JSTR_REPORT_SENSITIVITY                   "50"
#define JSTR_REPORT_SSA                           "ssa"
#define JSTR_REPORT_SSA_SET                       "ssa_set"
#define JSTR_REPORT_TRUE                          "true"
#define JSTR_REPORT_UNSEC                         "unsec"
#define JSTR_REPORT_1ST_SUP                       "1st_sup"
#define JSTR_REPORT_ALARM                         "alarm"
#define JSTR_REPORT_APPL_BUSY                     "appl_busy"
#define JSTR_REPORT_APPL_REJECT                   "appl_reject"
#define JSTR_REPORT_AUX                           "aux"
#define JSTR_REPORT_BASIC                         "basic"
#define JSTR_REPORT_BASIC_SET                     "basic_set"
#define JSTR_REPORT_BATTERY                       "battery"
#define JSTR_REPORT_BSENSOR_SUP                   "bsensor_sup"
#define JSTR_REPORT_CATEGORY                      "category"
#define JSTR_REPORT_CFG                           "cfg"
#define JSTR_REPORT_CLOCK                         "clock"
#define JSTR_REPORT_CNT                           "cnt"
#define JSTR_REPORT_CO                            "co"
#define JSTR_REPORT_CO2                           "co2"
#define JSTR_REPORT_CO2_LVL                       "co2_lvl"
#define JSTR_REPORT_COLOR                         "color"
#define JSTR_REPORT_COLOR_MASK                    "color_mask"
#define JSTR_REPORT_COLOR_SUP                     "color_sup"
#define JSTR_REPORT_COMMAND                       "command"
#define JSTR_REPORT_CO_LVL                        "co_lvl"
#define JSTR_REPORT_CSC_CFG                       "csc_cfg"
#define JSTR_REPORT_CSC_NOTIFICATION              "csc_notification"
#define JSTR_REPORT_CSC_SUP                       "csc_sup"
#define JSTR_REPORT_CURR_LVL                      "curr_lvl"
#define JSTR_REPORT_CUSTOMER                      "customer"
#define JSTR_REPORT_DEBUG                         "debug"
#define JSTR_REPORT_DEFAULT                       "default"
#define JSTR_REPORT_DOOR                          "door"
#define JSTR_REPORT_ECHO                          "echo"
#define JSTR_REPORT_EMERGENCY                     "emergency"
#define JSTR_REPORT_EVT                           "zevent"
#define JSTR_REPORT_FIRST                         "first"
#define JSTR_REPORT_FREEZE                        "freeze"
#define JSTR_REPORT_GATEWAY                       "gateway"
#define JSTR_REPORT_GLASS                         "glass"
#define JSTR_REPORT_GP                            "gp"
#define JSTR_REPORT_GROUP                         "group"
#define JSTR_REPORT_GROUP_ACTIVE                  "group_active"
#define JSTR_REPORT_GROUP_SUP                     "group_sup"
#define JSTR_REPORT_HEAT                          "heat"
#define JSTR_REPORT_HIGHEST_LVL                   "highest_lvl"
#define JSTR_REPORT_HUMIDITY                      "humidity"
#define JSTR_REPORT_ISSUEID                       "issueid"
#define JSTR_REPORT_INTERVAL                      "interval"
#define JSTR_REPORT_INTRUSION                     "intrusion"
#define JSTR_REPORT_LEVEL                         "level"
#define JSTR_REPORT_LEVEL_POSTSET                 "level_postset"
#define JSTR_REPORT_LEVEL_SUP                     "level_sup"
#define JSTR_REPORT_LOCK                          "lock"
#define JSTR_REPORT_LOCK_POSTSET                  "lock_postset"
#define JSTR_REPORT_LUMINANCE                     "luminance"
#define JSTR_REPORT_MAX_CNT                       "max_cnt"
#define JSTR_REPORT_MAX                           "max"
#define JSTR_REPORT_METER                         "meter"
#define JSTR_REPORT_METER_SUP                     "meter_sup"
#define JSTR_REPORT_MIN                           "min"
#define JSTR_REPORT_MOTION                        "motion"
#define JSTR_REPORT_NAME                          "name"
#define JSTR_REPORT_NODE                          "node"
#define JSTR_REPORT_NODEID                        "nodeid"
#define JSTR_REPORT_NODES                         "nodes"
#define JSTR_REPORT_NODE_ALIVE                    "alive"
#define JSTR_REPORT_NODE_GENERIC                  "generic"
#define JSTR_REPORT_NODE_INFO                     "nodeinfo"
#define JSTR_REPORT_NODE_SLEEPING                 "sleeping"
#define JSTR_REPORT_NODE_VENDOR                   "vendor"
#define JSTR_REPORT_NODE_XXX                      "node_xxx"
#define JSTR_REPORT_NOP                           "nop"
#define JSTR_REPORT_NULL                          ""
#define JSTR_REPORT_NW_BOOTUP                     "bootup"
#define JSTR_REPORT_NW_BUSY                       "busy"
#define JSTR_REPORT_NW_HOMEID                     "homeid"
#define JSTR_REPORT_NW_NOROUTE                    "noroute"
#define JSTR_REPORT_NW_NO_ACK                     "no_ack"
#define JSTR_REPORT_NW_SERIAL                     "serial"
#define JSTR_REPORT_NW_SYS_ERR                    "sys_err"
#define JSTR_REPORT_NW_XXX                        "nw_xxx"
#define JSTR_REPORT_OP                            "op"
#define JSTR_REPORT_OP_ABORTED                    "aborted"
#define JSTR_REPORT_OP_ABORTING                   "aborting"
#define JSTR_REPORT_OP_ADDED                      "added"
#define JSTR_REPORT_OP_ADDING                     "adding"
#define JSTR_REPORT_OP_LEARNED                    "learned"
#define JSTR_REPORT_OP_LEARNING                   "learning"
#define JSTR_REPORT_OP_NORMAL                     "normal"
#define JSTR_REPORT_OP_REMOVED                    "removed"
#define JSTR_REPORT_OP_REMOVING                   "removing"
#define JSTR_REPORT_OP_REPLACED_FAILED            "replaced_failed"
#define JSTR_REPORT_OP_REPLACING_FAILED           "replacing_failed"
#define JSTR_REPORT_OP_RESET                      "reset"
#define JSTR_REPORT_OP_RESETING                   "reseting"
#define JSTR_REPORT_OP_REMOVED_FAILED             "removed_failed"
#define JSTR_REPORT_OP_REMOVING_FAILED            "removing_failed"
#define JSTR_REPORT_OSD_ORIENTATION               "cfg_osd_orientation"
#define JSTR_REPORT_PARAM_NUM                     "param_num"
#define JSTR_REPORT_PID                           "pid"
#define JSTR_REPORT_POWER                         "power"
#define JSTR_REPORT_POWER_LEVEL                   "power_level"
#define JSTR_REPORT_POWER_LEVEL_TEST              "power_level_test"
#define JSTR_REPORT_PROTECTION                    "protection"
#define JSTR_REPORT_PTYPE                         "ptype"
#define JSTR_REPORT_READY                         "ready"
#define JSTR_REPORT_SEC_LOWER                     "sec_lower"
#define JSTR_REPORT_SEC_NORMAL                    "sec_normal"
#define JSTR_REPORT_SENSOR_SUP                    "sensor_sup"
#define JSTR_REPORT_SENSOR_UNIT_SUP               "sensor_unit_sup"
#define JSTR_REPORT_SIMPLE_AV_CONTROL             "simple_av_control"
#define JSTR_REPORT_SIMPLE_AV_CONTROL_SET         "simple_av_control_set"
#define JSTR_REPORT_SIREN                         "siren"
#define JSTR_REPORT_SIZE                          "size"
#define JSTR_REPORT_SMOKE                         "smoke"
#define JSTR_REPORT_START                         "start"
#define JSTR_REPORT_STATE                         "zstate"
#define JSTR_REPORT_SWITCH                        "switch"
#define JSTR_REPORT_SWITCH_ALL                    "switch_all"
#define JSTR_REPORT_SYSTEM                        "system"
#define JSTR_REPORT_TAMPER                        "tamper"
#define JSTR_REPORT_TEMPERATURE                   "temperature"
#define JSTR_REPORT_THERMOSTAT_FAN_MODE           "thermostat_fan"
#define JSTR_REPORT_THERMOSTAT_FAN_MODE_SUP       "thermostat_fan_sup"
#define JSTR_REPORT_THERMOSTAT_FAN_STATE          "thermostat_fan_state"
#define JSTR_REPORT_THERMOSTAT_MODE               "thermostat_mode"
#define JSTR_REPORT_THERMOSTAT_MODE_SUP           "thermostat_mode_sup"
#define JSTR_REPORT_THERMOSTAT_OPERATING_STATE    "thermostat_op"
#define JSTR_REPORT_THERMOSTAT_SETPOINT           "thermostat_setp"
#define JSTR_REPORT_THERMOSTAT_SETPOINT_SUP       "thermostat_setp_sup"
#define JSTR_REPORT_THERMOSTAT_SETPOINT_SUP_RANGE "thermostat_setp_sup_range"
#define JSTR_REPORT_TIMESTAMP                     "timestamp"
#define JSTR_REPORT_TILT                          "tilt"
#define JSTR_REPORT_TYPES_LEN                     "types_len"
#define JSTR_REPORT_TYPES                         "types"
#define JSTR_REPORT_UNIT                          "unit"
#define JSTR_REPORT_USE_DEFAULT                   "use_default"
#define JSTR_REPORT_USER_CODE                     "user_code"
#define JSTR_REPORT_USER_CODE_SUP                 "user_code_sup"
#define JSTR_REPORT_UV                            "uv"
#define JSTR_REPORT_VALUE                         "value"
#define JSTR_REPORT_VERSION_CC                    "version_cc"
#define JSTR_REPORT_VERSION_ZW                    "version_zw"
#define JSTR_REPORT_VID                           "vid"
#define JSTR_REPORT_VOC                           "volatile_organic_compound"
#define JSTR_REPORT_WAKEUP                        "wakeup"
#define JSTR_REPORT_WAKEUP_INTERVAL               "wakeup_interval"
#define JSTR_REPORT_WATCH_OFF                     "watch_off"
#define JSTR_REPORT_WATER                         "water"
#define JSTR_REPORT_WATER_LEAK                    "water_leak"
#define JSTR_REPORT_WATER_LVL                     "water_lvl"
#define JSTR_REPORT_ZWINFO                        "zwinfo"
#define JSTR_REPORT_XXX                           "report_xxx"

//******************************************************************************
// Report Payload
//******************************************************************************
// ** report **
// macid/groupid/protocolid/homeid/nodeid/epid/issue/mode/submode/category/ts/val_len/val

#if (0)
#define REPORT_IDX_MACID                         0
#define REPORT_IDX_GROUPID                       (REPORT_IDX_MACID+20)
#define REPORT_IDX_PROTOCOLID                    (REPORT_IDX_GROUPID+2)
#define REPORT_IDX_HOMEID                        (REPORT_IDX_PROTOCOLID+2)
#define REPORT_IDX_NODEID                        (REPORT_IDX_HOMEID+40)
#define REPORT_IDX_EPID                          (REPORT_IDX_NODEID+1)
#define REPORT_IDX_PADDING                       (REPORT_IDX_EPID+1)
#define REPORT_IDX_ISSUEID                       (REPORT_IDX_PADDING+2)
#define REPORT_IDX_MODE                          (REPORT_IDX_ISSUEID+4)
#define REPORT_IDX_SUBMODE                       (REPORT_IDX_MODE+2)
#define REPORT_IDX_REPORTER                      (REPORT_IDX_SUBMODE+2)
#define REPORT_IDX_TIME                          (REPORT_IDX_REPORTER+2)
#define REPORT_IDX_LEN                           (REPORT_IDX_TIME+4)
#define REPORT_IDX_VALUE                         (REPORT_IDX_LEN+4)
#define REPORT_IDX_MAX                           (REPORT_IDX_VALUE+80)

#define LEN_OF_REPORT_PAYLOAD                    REPORT_IDX_MAX
#endif

#define JVAL_GROUPID_NORMAL                      0
#define JVAL_GROUPID_BROADCAST                   0xFFFF

#define JVAL_PROTOCOLID_BASE                     0
#define JVAL_PROTOCOLID_ZWAVE                    1
#define JVAL_PROTOCOLID_ZWAVES2                  2
#define JVAL_PROTOCOLID_ZIGBEE                   3
#define JVAL_PROTOCOLID_PAN27                    4
#define JVAL_PROTOCOLID_BLUETOOTH                5
#define JVAL_PROTOCOLID_ONVIF                    11
#define JVAL_PROTOCOLID_WIFI_PHILIO              21
#define JVAL_PROTOCOLID_ZIGBEE_PHILIO            41
#define JVAL_PROTOCOLID_ECHO                     0xFFFD
#define JVAL_PROTOCOLID_MASTER                   0xFFFE
#define JVAL_PROTOCOLID_BROADCAST                0xFFFF

#define JVAL_NODEID_CONTROLLER                   1
#define JVAL_NODEID_BROADCAST                    0xFFFF
#define JVAL_EPID_BASE                           0

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

#define JKEY_ISSUEID_COMMAND                     0x00100000

#define JKEY_ISSUEID_GATEWAY_MASK                0x000FFFFF
#define JKEY_ISSUEID_COMMAND_MASK                0xFFF00000

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
#define JKEY_ISSUEID_TEMP                        0x00030001 // Temperature sensor
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

#define JKEY_ISSUEID_CC_LEVEL                    0x00092601 // level
#define JKEY_ISSUEID_CC_LEVEL_SUP                0x00092602 // level_sup
#define JKEY_ISSUEID_CC_LEVEL_POSTSET            0x000926FF // level_postset

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

#define JKEY_ISSUEID_CC_BATTERY                  0x00098001 // battery

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

#endif
