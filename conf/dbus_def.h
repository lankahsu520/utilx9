#ifndef PHILIO_DBUS_DEF_H
#define PHILIO_DBUS_DEF_H

//#include <dbus/dbus.h>
#define FILE_NVM_PIPE "/tmp/.nvm_pipe"
#define FILE_ZNVM_BIN "/mnt/PhilioData/ZNVM.bin"
#define FILE_ZNVM_BAK_BIN "/mnt/PhilioData/ZNVM_bck.bin"
#define FILE_ZNVM_FIN "/tmp/ZNVM.fin"

#define TIMEOUT_OF_DBUS_REPLY                     5000

//destination
#define PHILIO_SDK_DBUS_DEST                      "com.philio-tech.www.sdk"
#define PLATFORM_DBUS_DEST                        "com.philio-tech.www.platform"
#define CHECKUPDATE_DBUS_DEST                     "com.philio-tech.www.checkupdate"
#define UPDATE_DBUS_DEST                          "com.philio-tech.www.update"
#define APP_DBUS_DEST                             "com.philio-tech.www.app"
#define MQTT_DBUS_DEST                            "com.philio-tech.www.mqtt"
#define TELLDUS_DBUS_DEST                         "com.philio-tech.www.Telldus"
#define WATCHDOG_DBUS_DEST                        "com.philio-tech.www.debuger"
#define SOCKET_DBUS_DEST                          "com.philio-tech.www.socket"
#define SOCKET_LISTEN_DBUS_DEST                   "com.philio-tech.www.listen"
#define PHILIO_GPIO_DBUS_DEST                     "com.philio-tech.www.gpio"
#define DB_DBUS_DEST                              "com.philio-tech.www.database"
#define STORAGE_DBUS_DEST                         "com.philio-tech.www.storage"

//#define PLATFORM_SIG_IFAC                         "com.PhilioTech.signal.platform"
#define PHILIO_SDK_DBUS_CTRL_LED_IFAC             "com.PhilioTech.control.LED"
//#define APACHE_DBUS_IFAC                          "com.PhilioTech.message.Apache"
//#define UPDATE_DBUS_STATUS_IFAC                   "com.PhilioTech.update.status"
//#define ZWAVE_RECENT_EVENT_IFAC                   "com.PhilioTech.zwave.recentEvent"

#define DBUS_DEST_DEMO                            "com.luffanet.www.demo"
#define DBUS_DEST_MASTER                          "com.luffanet.www.master"
#define DBUS_DEST_YK_P2P_DAEMON                   "com.luffanet.www.yk_p2p_daemon"
#define DBUS_DEST_OTA_DAEMON                      "com.luffanet.www.ota_daemon"

//path - PhilioTech
#define ZWAVE_DBUS_DEV_PATH                       "/com/PhilioTech/zwave/device"
#define ZIGBEE_DBUS_DEV_PATH                      "/com/PhilioTech/zigbee/device"
#define PAN27_DBUS_DEV_PATH                       "/com/PhilioTech/pan27/device"
#define WATCHDOG_DBUS_PROCESS_PATH                "/com/PhilioTech/watchdog/process"

//path - Luffanet
#define DBUS_PATH_YK_P2P_DAEMON                   "/com/Luffanet/yk_p2p_daemon"
#define DBUS_PATH_YK_P2P_ECHO                     "/com/Luffanet/yk_p2p_echo"
#define DBUS_PATH_YK_P2P_CALL                     "/com/Luffanet/yk_p2p_call"
#define DBUS_PATH_YK_WS_DAEMON                    "/com/Luffanet/yk_ws_daemon"
#define DBUS_PATH_YK_MQTT_DAEMON                  "/com/Luffanet/yk_mqtt_daemon"

#define DBUS_PATH_OTA_DAEMON                      "/com/Luffanet/ota_daemon"

//path - xbox
#define DBUS_PATH_DBUS_123                        "/com/xbox/dbus_123"
#define DBUS_PATH_DBUS_456                        "/com/xbox/dbus_456"


//******************************************************************************
// libsdk
//******************************************************************************
// 2.0 libsdk => zwave, gpio
#define DBUS_S_IFAC_LEARNING_STATUS               "com.PhilioTech.signal.learning_status"
#define DBUS_S_MATCH_LEARNING_STATUS              "type='signal',interface='com.PhilioTech.signal.learning_status'"

#define DBUS_METHOD_INCLUDING                     "including"
#define DBUS_METHOD_EXCLUDING                     "excluding"
#define DBUS_METHOD_ABORTING                      "aborting"

// 2.0 libsdk => zwave, gpio
#define DBUS_S_IFAC_INTERNET_STATUS               "com.PhilioTech.signal.internet_status"
#define DBUS_S_MATCH_INTERNET_STATUS              "type='signal',interface='com.PhilioTech.signal.internet_status'"

#define DBUS_METHOD_INTERNET_STATUS               "internet_status"

// 2.0 libsdk => app, mqtt, gpio, sdk 
#define DBUS_S_IFAC_SDK                           "com.PhilioTech.signal.sdk"
#define DBUS_S_MATCH_SDK                          "type='signal',interface='com.PhilioTech.signal.sdk'"

#define DBUS_METHOD_CONTROLLER_EVENT              "controller_event"
#define DBUS_METHOD_SDK_EVENT                     "sdk_event"
#define DBUS_METHOD_UPDATE_DONGLE_LIST            "update_dongle_list"
#define DBUS_METHOD_UPDATE_CHANNEL                "update_channel"
#define DBUS_METHOD_UPDATE_DEVICE                 "update_device"
#define DBUS_METHOD_UPDATE_METER                  "update_meter"
#define DBUS_METHOD_UPDATE_TX_STATUS              "update_tx_status"
#define DBUS_METHOD_UPDATE_ZIGBEE_INFO            "update_zigbee_info"
#define DBUS_METHOD_UPDATE_ZWAVE_INFO             "update_zwave_info"
#define DBUS_METHOD_UPDATE_ZWAVE_SWITCH_COLOR     "update_zwave_switch_color"
#define DBUS_METHOD_UPDATE_ZWAVE_USERCODE_USER    "update_zwave_usercode_user"

// 2.0 libsdk => mqtt
#define DBUS_S_IFAC_MQTT                          "com.PhilioTech.signal.mqtt"
#define DBUS_S_MATCH_MQTT                         "type='signal',interface='com.PhilioTech.signal.mqtt'"

#define DBUS_METHOD_PUBLISH                       "publish"
#define DBUS_METHOD_SUBSCRIBE                     "subscribe"
#define DBUS_METHOD_UNSUBSCRIBE                   "unsubscribe"

// 2.0 libsdk => storage
#define DBUS_S_IFAC_SYSTEM                        "com.PhilioTech.signal.system"
#define DBUS_S_MATCH_SYSTEM                       "type='signal',interface='com.PhilioTech.signal.system'"

#define DBUS_METHOD_PROCESS_START                 "process_start"

// 2.0 libsdk - DBUS_METHOD_XXX
#define DBUS_METHOD_ABORT                         "abort"
#define DBUS_METHOD_ADD_HOME_ID                   "add_home_id"
#define DBUS_METHOD_ALL_SWITCH_BROADCAST          "all_switch_broadcast"
#define DBUS_METHOD_ASSIGN_PRIORITY_RETURN_ROUTE  "assign_priority_return_route"

#define DBUS_METHOD_BACKUP_NVM                    "backup_nvm"

#define DBUS_METHOD_COMMON_CONTROL                "common_control"
#define DBUS_METHOD_CONFIG_CURTAIN_TIME           "config_curtain_time"
#define DBUS_METHOD_CONFIG_KEY_TYPE               "config_key_type"
#define DBUS_METHOD_CONFIG_CURTAIN_LOGIC          "setcurtain_logic"

#define DBUS_METHOD_DELETE_RETURN_ROUTE           "delete_return_route"
#define DBUS_METHOD_DEVICE_FIRMWARE_UPDATE        "device_firmware_update"
#define DBUS_METHOD_DEVICE_RESET_AND_EXCLUDE      "device_reset_and_exclude"

#define DBUS_METHOD_EVENT_LIST                    "event_list"
#define DBUS_METHOD_EXECUTE_CMD                   "execute_cmd"
#define DBUS_METHOD_EXCLUDE                       "exclude"

#define DBUS_METHOD_GET_ALL_DEVICE                "get_all_device"
#define DBUS_METHOD_GET_CH_FUNCTYPE               "get_ch_functype"
#define DBUS_METHOD_GET_CHANNEL                   "get_channel"
#define DBUS_METHOD_GET_DEVICE                    "get_device"
#define DBUS_METHOD_GET_INTERFACE                 "get_interface"
#define DBUS_METHOD_GET_LOG                       "get_log"
#define DBUS_METHOD_GET_OPS                       "get_ops"
#define DBUS_METHOD_GET_S2_KEY                    "get_s2_key"
#define DBUS_METHOD_GETSWITCH                     "getswitch"

#define DBUS_METHOD_IMA_ENABLE                    "IMA_enable"
#define DBUS_METHOD_IMA_DISABLE                   "IMA_disable"
#define DBUS_METHOD_IMPORT                        "import"
#define DBUS_METHOD_INCLUDE                       "include"

#define DBUS_METHOD_NVM_EXT_READ_LONG_BUFFER      "NVM_ext_read_long_buffer"

#define DBUS_METHOD_PID_FILE_CHECK_ENABLE         "pid_file_check_enable"
#define DBUS_METHOD_PROCESS_CRASH                 "process_crash"

#define DBUS_METHOD_REBOOT                        "reboot"
#define DBUS_METHOD_REMOVE_ALL_DEVICE             "remove_all_device"
#define DBUS_METHOD_REMOVE_DEVICE                 "remove_device"
#define DBUS_METHOD_REMOVE_SDK_DEVICE             "remove_sdk_device"
#define DBUS_METHOD_REMOVE_HOME_ID                "remove_home_id"
#define DBUS_METHOD_REPORT_BINDING                "report_binding"
#define DBUS_METHOD_REPORT_FREQ                   "report_freq"

#define DBUS_METHOD_REMOVE_CHANNEL                "remove_channel"
#define DBUS_METHOD_RESET                         "reset"
#define DBUS_METHOD_RESTART                       "restart"
#define DBUS_METHOD_RESTORE_NVM                   "restore_nvm"
#define DBUS_METHOD_RUN_CMD_CLASS                 "run_cmd_class"
#define DBUS_METHOD_RUN_CMD                       "run_cmd"

#define DBUS_METHOD_NVRAM_BACKUP                  "nvram_backup"
#define DBUS_METHOD_NVRAM_UBOOT_WRITE             "nvram_uboot_write"
#define DBUS_METHOD_NVRAM_UBOOT_READ              "nvram_uboot_read"
#define DBUS_METHOD_NVRAM_RT2860_WRITE            "nvram_rt2860_write"
#define DBUS_METHOD_NVRAM_RT2860_READ             "nvram_rt2860_read"
#define DBUS_METHOD_NVRAM_UBOOT_COMMIT            "nvram_uboot_commit"
#define DBUS_METHOD_NVRAM_RT2860_COMMIT           "nvram_rt2860_commit"

#define DBUS_METHOD_PCONFIG_WRITE_STRING          "pconfig_write_string"
#define DBUS_METHOD_PCONFIG_READ_STRING           "pconfig_read_string"
#define DBUS_METHOD_PCONFIG_WRITE_INT             "pconfig_write_int"
#define DBUS_METHOD_PCONFIG_READ_INT              "pconfig_read_int"
#define DBUS_METHOD_PCONFIG_COMMIT                "pconfig_commit"

#define DBUS_METHOD_SEND_LOG                      "send_log"
#define DBUS_METHOD_SET_DEVICE_CHANNEL            "set_device_channel"
#define DBUS_METHOD_SET_DEVICE                    "set_device"
#define DBUS_METHOD_SET_MODBUS_ADDR               "set_modbus_addr"
#define DBUS_METHOD_SET_MODBUS_PAN26_ADDR         "set_modbus_pan26_addr"
#define DBUS_METHOD_SET_MODBUS_PAN26_CURTAIN_LEN  "set_modbus_pan26_curtain_len"
#define DBUS_METHOD_SET_ZWAVE_DSK                 "set_zwave_dsk"
#define DBUS_METHOD_SWITCH_SIGNAL                 "switch_signal"
#define DBUS_METHOD_SWITCH                        "switch"

#define DBUS_METHOD_USB_RESET                     "usb_reset"
#define DBUS_METHOD_ZWAVE_SWITCH_COLOR_SET        "zwave_switch_color_set"
#define DBUS_METHOD_ZIGBEE_SWITCH_COLOR_SET       "zigbee_switch_color_set"
#define DBUS_METHOD_SWITCH_COLOR_SET              "zigbee_switch_color_set"
#define DBUS_METHOD_ZWAVE_NETWORK_RESET           "zwave_network_reset"
#define DBUS_METHOD_ZWAVE_SET_DEFAULT             "zwave_set_default"


//******************************************************************************
// libapp
//******************************************************************************
// 2.0 libapp - DBUS_METHOD_XXX
#define DBUS_METHOD_DEL_MACRO                     "del_macro"
#define DBUS_METHOD_DEL_ROOM                      "del_room"
#define DBUS_METHOD_DEL_SCENE                     "del_scene"
#define DBUS_METHOD_DEL_SCHEDULE                  "del_schedule"
#define DBUS_METHOD_DOSCENE                       "doscene"
#define DBUS_METHOD_ENABLE_ALL_MACRO              "enable_all_macro"
#define DBUS_METHOD_GET_CAMERA_LIST               "get_camera_list"
#define DBUS_METHOD_GET_EVENT_FILTER_LIST         "get_event_filter_list"
#define DBUS_METHOD_DEL_EVENT_FILTER              "del_event_filter"
#define DBUS_METHOD_GET_EVENT_LOG_LIST_BY_SEQ     "get_event_log_list_by_seq"
#define DBUS_METHOD_GET_ROOM_LIST                 "get_room_list"
#define DBUS_METHOD_GET_MACRO_EVENT_LOG_LIST_BY_SEQ "get_macro_event_log_list_by_seq"
#define DBUS_METHOD_GET_MACRO_LIST                "get_macro_list"
#define DBUS_METHOD_GET_REG_DEV_LIST              "get_reg_dev_list"
#define DBUS_METHOD_GET_SCENE_LIST                "get_scene_list"
#define DBUS_METHOD_GET_SCHEDULE_LIST             "get_schedule_list"
#define DBUS_METHOD_GET_TARGET_NAME_LIST          "get_target_name_list"
#define DBUS_METHOD_GET_TITLE_LIST                "get_title_list"
#define DBUS_METHOD_MESSAGE                       "message"
#define DBUS_METHOD_SAVE_CONFIG                   "save_config"
#define DBUS_METHOD_SEARCH_CAMERA                 "search_camera"
#define DBUS_METHOD_SEARCH_EVENT_FILTER           "search_event_filter"
#define DBUS_METHOD_SEARCH_REG_DEV                "search_reg_dev"
#define DBUS_METHOD_SEARCH_ROOM                   "search_room"
#define DBUS_METHOD_SEARCH_MACRO                  "search_macro"
#define DBUS_METHOD_SEARCH_SCENE                  "search_scene"
#define DBUS_METHOD_SEARCH_SCHEDULE               "search_schedule"
#define DBUS_METHOD_SEARCH_TARGET_NAME            "search_target_name"
#define DBUS_METHOD_SET_CAMERA                    "set_camera"
#define DBUS_METHOD_SET_EVENT_FILTER              "set_event_filter"
#define DBUS_METHOD_SET_MACRO                     "set_macro"
#define DBUS_METHOD_SET_REG_DEV                   "set_reg_dev"
#define DBUS_METHOD_SET_ROOM                      "set_room"
#define DBUS_METHOD_SET_SCENE                     "set_scene"
#define DBUS_METHOD_SET_SCHEDULE                  "set_schedule"
#define DBUS_METHOD_SET_TARGET_NAME               "set_target_name"


//******************************************************************************
// app
//******************************************************************************
// 1.0, 2.0 -> app
#define DBUS_M_IFAC_APP                           "com.PhilioTech.app"

#define DBUS_METHOD_BACKUPCONFIG                  "backupConfig"
#define DBUS_METHOD_DEL_CAMERA                    "del_camera"
//#define DBUS_METHOD_DEL_EVENT_FILTER              "del_event_filter"
//#define DBUS_METHOD_DEL_MACRO                     "del_macro"
#define DBUS_METHOD_DEL_REG_DEV                   "del_reg_dev"
//#define DBUS_METHOD_DEL_ROOM                      "del_room"
//#define DBUS_METHOD_DEL_SCENE                     "del_scene"
//#define DBUS_METHOD_DEL_SCHEDULE                  "del_schedule"
#define DBUS_METHOD_DEL_TARGET_NAME               "del_target_name"
//#define DBUS_METHOD_ENABLE_ALL_MACRO              "enable_all_macro"
//#define DBUS_METHOD_GET_CAMERA_LIST               "get_camera_list"
//#define DBUS_METHOD_GET_EVENT_FILTER_LIST         "get_event_filter_list"
//#define DBUS_METHOD_GET_EVENT_LOG_LIST_BY_SEQ     "get_event_log_list_by_seq"
#define DBUS_METHOD_COMMAND                       "command"
//#define DBUS_METHOD_DOSCENE                       "doscene"
#define DBUS_METHOD_DOSCENEMODE                   "doscenemode"
#define DBUS_METHOD_DUMP_HTTP_LOG_LIST            "dump_http_log_list"
#define DBUS_METHOD_ENABLEASTCLOCK                "enableastclock"
#define DBUS_METHOD_ENABLELOCK                    "enablelock"
//#define DBUS_METHOD_GET_MACRO_EVENT_LOG_LIST_BY_SEQ "get_macro_event_log_list_by_seq"
//#define DBUS_METHOD_GET_MACRO_LIST                "get_macro_list"
//#define DBUS_METHOD_GET_REG_DEV_LIST              "get_reg_dev_list"
//#define DBUS_METHOD_GET_ROOM_LIST                 "get_room_list"
//#define DBUS_METHOD_GET_SCENE_LIST                "get_scene_list"
//#define DBUS_METHOD_GET_SCHEDULE_LIST             "get_schedule_list"
#define DBUS_METHOD_GET_SUNRISE_TIME              "get_sunrise_time"
#define DBUS_METHOD_GET_SUNSET_TIME               "get_sunset_time"
//#define DBUS_METHOD_GET_TARGET_NAME_LIST          "get_target_name_list"
//#define DBUS_METHOD_GET_TITLE_LIST                "get_title_list"
#define DBUS_METHOD_GETDAT                        "getDat"
#define DBUS_METHOD_JSONDEL                       "jsondel"
#define DBUS_METHOD_JSONGETALL                    "jsongetall"
#define DBUS_METHOD_JSONGETEVENTBYSEQ             "jsongeteventbyseq"
#define DBUS_METHOD_JSONGETGROUP                  "jsongetgroup"
#define DBUS_METHOD_JSONGETMACROEVENTBYSEQ        "jsongetmacroeventbyseq"
#define DBUS_METHOD_JSONGETTITLES                 "jsongettitles"
#define DBUS_METHOD_JSONRENAME                    "jsonrename"
#define DBUS_METHOD_JSONSETALL                    "jsonsetall"
#define DBUS_METHOD_JSONSETUSERDATA               "jsonsetuserdata"
//#define DBUS_METHOD_MESSAGE                       "message"
#define DBUS_METHOD_P2PRECONNECT                  "p2preconnect"
#define DBUS_METHOD_RESETCONFIG                   "resetConfig"
#define DBUS_METHOD_RESTORECONFIG                 "restoreConfig"
#define DBUS_METHOD_RESTORECONFIG2                 "restoreConfig2"
//#define DBUS_METHOD_SAVE_CONFIG                   "save_config"
//#define DBUS_METHOD_SEARCH_CAMERA                 "search_camera"
//#define DBUS_METHOD_SEARCH_EVENT_FILTER           "search_event_filter"
//#define DBUS_METHOD_SEARCH_MACRO                  "search_macro"
//#define DBUS_METHOD_SEARCH_REG_DEV                "search_reg_dev"
//#define DBUS_METHOD_SEARCH_ROOM                   "search_room"
//#define DBUS_METHOD_SEARCH_SCENE                  "search_scene"
//#define DBUS_METHOD_SEARCH_SCHEDULE               "search_schedule"
//#define DBUS_METHOD_SEARCH_TARGET_NAME            "search_target_name"
#define DBUS_METHOD_SENDDAT                       "sendDat"
//#define DBUS_METHOD_SET_CAMERA                    "set_camera"
//#define DBUS_METHOD_SET_EVENT_FILTER              "set_event_filter"
//#define DBUS_METHOD_SET_MACRO                     "set_macro"
//#define DBUS_METHOD_SET_REG_DEV                   "set_reg_dev"
//#define DBUS_METHOD_SET_ROOM                      "set_room"
//#define DBUS_METHOD_SET_SCENE                     "set_scene"
//#define DBUS_METHOD_SET_SCHEDULE                  "set_schedule"
//#define DBUS_METHOD_SET_TARGET_NAME               "set_target_name"
#define DBUS_METHOD_SETASTCLOCK_LAT               "setastclock_lat"
#define DBUS_METHOD_SETASTCLOCK_LON               "setastclock_lon"
#define DBUS_METHOD_SETDST                        "setDST"
#define DBUS_METHOD_SETRECENTEVENTLOGNUM          "setRecentEventLogNum"
#define DBUS_METHOD_SETHOMESECURITY               "setHomeSecurity"
//#define DBUS_METHOD_UPDATE_DEVICE                 "update_device"

// 1.0 -> app
#define DBUS_M_IFAC_SWITCH_APP                    "com.PhilioTech.switch.app"

//#define DBUS_METHOD_BACKUPCONFIG                  "backupConfig"
#define DBUS_METHOD_BACKUPPHILIODATA              "backupPhilioData"
//#define DBUS_METHOD_RESETCONFIG                   "resetConfig"
#define DBUS_METHOD_RESETCONFIG2                  "resetConfig2"
//#define DBUS_METHOD_RESTORECONFIG                 "restoreConfig"
#define DBUS_METHOD_SETHOMESCENE                  "setHomeScene"

// 1.0 -> app
#define DBUS_M_IFAC_ZWAVE_EVENT                   "com.PhilioTech.zwave.event"

#define DBUS_METHOD_EVENT                         "event"

// 1.0 -> app
#define DBUS_M_IFAC_DEBUG                         "com.PhilioTech.debug"

#define DBUS_METHOD_MEMORY_DEBUG                  "memory_debug"

// 1.0 app => icloud
#define DBUS_S_IFAC_APP_EVENTLOG                  "com.PhilioTech.signal.eventLog"
#define DBUS_S_MATCH_APP_EVENTLOG                 "type='signal',interface='com.PhilioTech.signal.eventLog'"

//#define DBUS_METHOD_JSONGETALL                    "jsongetall"
#define DBUS_METHOD_MACROEVENT                    "MacroEvent"
#define DBUS_METHOD_RECENT                        "recent"

// 1.0  app => philio-sdk, watchdog
#define DBUS_S_IFAC_JSON_COMMAND                  "com.PhilioTech.signal.json.command"
#define DBUS_S_MATCH_JSON_COMMAND                 "type='signal',interface='com.PhilioTech.signal.json.command'"

//#define DBUS_METHOD_COMMAND                       "command"
#define DBUS_METHOD_KICK_THEDOG                   "kick_thedog"

// 2.0 apache_module, app => app, database, icloud, listen, gpio, uartEvent
#define DBUS_S_IFAC_APP                           "com.PhilioTech.signal.app"
#define DBUS_S_MATCH_APP                          "type='signal',interface='com.PhilioTech.signal.app'"

#define DBUS_METHOD_RADD_HTTP_LOG                 "add_http_log"
//#define DBUS_METHOD_MACROEVENT                    "MacroEvent"
#define DBUS_METHOD_RECENT_EVENT                  "recent_event"


//******************************************************************************
// apache_module
//******************************************************************************
// 1.0, 2.0 apache_module, update => icloud, platform, watchdog
#define DBUS_S_IFAC_UPDATE_EVENT                  "com.PhilioTech.signal.update"
#define DBUS_S_MATCH_UPDATE_EVENT                 "type='signal',interface='com.PhilioTech.signal.update'"

#define DBUS_METHOD_ALIVE                         "alive"
#define DBUS_METHOD_REWRITE_ENTIRE                "rewriteEntire"


//******************************************************************************
// gpio
//******************************************************************************
//#define GPIO_MSG_IFAC 			              	      "com.PhilioTech.message.gpio"
//#define GPIO_SIG_IFAC 			          	          "com.PhilioTech.signal.gpio"
// 1.0 -> gpio
#define DBUS_M_IFAC_GPIO_LED                        "com.PhilioTech.gpio.ledctrl"

//#define DBUS_METHOD_COMMAND                       "command"

//******************************************************************************
// icloud
//******************************************************************************
// 1.0, 2.0 -> icloud
#define DBUS_M_IFAC_SOCKET_CMD                    "com.PhilioTech.socket.cmd" // "com.PhilioTech.method.socket.cmd"

//#define DBUS_METHOD_COMMAND                       "command"


//******************************************************************************
// mqtt
//******************************************************************************
// -> mqtt
//#define DBUS_M_IFAC_MQTT                          "com.PhilioTech.mqtt"

//******************************************************************************
// onvif (sdk)
//******************************************************************************
// 2.0 -> onvif (sdk)
#define DBUS_M_IFAC_ONVIF                         "com.PhilioTech.onvif"

//#define DBUS_METHOD_REMOVE_DEVICE                 "remove_device"

//******************************************************************************
// PAN27
//******************************************************************************
// 2.0 -> pan27
#define DBUS_M_IFAC_PAN27                         "com.PhilioTech.pan27"

//#define DBUS_METHOD_CONFIG_CURTAIN_TIME           "config_curtain_time"
//#define DBUS_METHOD_CONFIG_KEY_TYPE               "config_key_type"
//#define DBUS_METHOD_SET_MODBUS_ADDR               "set_modbus_addr"
//#define DBUS_METHOD_SWITCH                        "switch"
//#define DBUS_METHOD_USB_RESET                     "usb_reset"

// => pan27, wrong used !!!
#define DBUS_S_IFAC_PAN27                         "com.PhilioTech.signal.pan27"
#define DBUS_S_MATCH_PAN27                        "type='signal',interface='com.PhilioTech.signal.pan27'"

//#define DBUS_METHOD_SWITCH_SIGNAL                 "switch_signal"

//******************************************************************************
// dbus_demo
//******************************************************************************
// -> dbus_demo
#define DBUS_M_IFAC_DEMO_CMD                      "com.luffanet.demo.command" // sync

// dbus_demo => all
#define DBUS_S_IFAC_DEMO                          "com.luffanet.signal.demo"
#define DBUS_S_MATCH_DEMO                         "type='signal',interface='com.luffanet.signal.demo'"

#define DBUS_METHOD_ECHO                          "echo"

//******************************************************************************
// ota_daemon
//******************************************************************************
// -> ota_daemon
#define DBUS_M_IFAC_OTA_COMMAND                   "com.luffanet.ota.command" // sync

// ota_daemon => all
#define DBUS_S_IFAC_OTA                           "com.luffanet.signal.ota"
#define DBUS_S_MATCH_OTA                          "type='signal',interface='com.luffanet.signal.ota'"

#define DBUS_METHOD_GETFW                         "getfw"

//******************************************************************************
// yk_p2p_daemon
//******************************************************************************
// -> yk_p2p_daemon
#define DBUS_M_IFAC_P2P_COMMAND                   "com.luffanet.p2p.command" // sync
#define DBUS_M_IFAC_P2P_POST                      "com.luffanet.p2p.post" // sync
#define DBUS_M_IFAC_P2P_SCENE                     "com.luffanet.p2p.scene" // sync
#define DBUS_M_IFAC_P2P_SUBNET                    "com.luffanet.p2p.subnet" // sync

// yk_p2p_daemon => all
#define DBUS_S_IFAC_P2P                           "com.luffanet.signal.p2p"
#define DBUS_S_MATCH_P2P                          "type='signal',interface='com.luffanet.signal.p2p'"

#define DBUS_METHOD_BOOTUP                        "bootup"
#define DBUS_METHOD_GETZIP                        "getzip"
#define DBUS_METHOD_NOTIFICATION                  "notification"
#define DBUS_METHOD_UID_AP                        "uid_ap"
#define DBUS_METHOD_UNZIP                         "unzip"
#define DBUS_METHOD_SCAN                          "scan"

//******************************************************************************
// philio-sdk
//******************************************************************************
// 1.0 -> philio-sdk
#define DBUS_M_IFAC_JSON_COMMAND                  "com.PhilioTech.json.command"

//#define DBUS_METHOD_COMMAND                       "command"

// 1.0 -> philio-sdk
#define DBUS_M_IFAC_EASY_COMMAND                  "com.PhilioTech.easy.command"

#define DBUS_METHOD_NAME                          "name"

// 1.0 -> philio-sdk
#define DBUS_M_IFAC_FIRMWARE                      "com.PhilioTech.firmware"

#define DBUS_METHOD_VERSION                       "version"
#define DBUS_METHOD_DATE                          "date"

// 1.0 -> philio-sdk
#define DBUS_M_IFAC_BUTTON                        "com.PhilioTech.button"

#define DBUS_METHOD_GETBTN                        "getBtn"

// 1.0 -> philio-sdk
#define DBUS_M_IFAC_NETSTATUS                     "com.PhilioTech.netstatus"

//#define DBUS_METHOD_COMMAND                       "command"

// 1.0 -> philio-sdk
#define DBUS_M_IFAC_MEMORY                        "com.PhilioTech.memory"

#define DBUS_METHOD_GETALLOCATED                  "getAllocated"
//#define DBUS_METHOD_MEMORY_DEBUG                  "memory_debug"

// 1.0 philio-sdk => app, icloud, platform, watchdog
#define DBUS_S_IFAC_EVENT                         "com.PhilioTech.signal.event"
#define DBUS_S_MATCH_EVENT                        "type='signal',interface='com.PhilioTech.signal.event'"

#define DBUS_METHOD_BUTTOM_PRESSED                "buttom_pressed"
//#define DBUS_METHOD_COMMAND                       "command"
#define DBUS_METHOD_FWVERSION                     "fwVersion"
#define DBUS_METHOD_TRIGGER_APP                   "triggerAPP"
#define DBUS_METHOD_TRIGGER                       "trigger"

//******************************************************************************
// platform
//******************************************************************************
// 2.0 -> platform
#define DBUS_M_IFAC_PLATFORM                      "com.PhilioTech.platform"

#define DBUS_METHOD_WIFI_AP_COMMAND               "wifi_ap_command"
#define DBUS_METHOD_WIFI_STA_COMMAND              "wifi_sta_command"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_CONFIG                        "com.PhilioTech.platform.config"

//#define DBUS_METHOD_RESET                         "reset"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_NET                           "com.PhilioTech.platform.net"

#define DBUS_METHOD_GETDNS                        "getdns"
#define DBUS_METHOD_GETGATEWAY                    "getgateway"
#define DBUS_METHOD_GETIP                         "getip"
#define DBUS_METHOD_GETMAC                        "getMac"
#define DBUS_METHOD_GETNETMASK                    "getnetmask"
#define DBUS_METHOD_GETWIFISTAIP                  "getwifistaip"
#define DBUS_METHOD_INITINTERNET                  "initInternet"

// 1.0 -> platform
#define DBUS_M_IFAC_NVRAM                         "com.PhilioTech.platform.nvram"

#define DBUS_METHOD_COMMIT                        "commit"
#define DBUS_METHOD_GETLIST                       "getList"
#define DBUS_METHOD_GET                           "get"
#define DBUS_METHOD_SET                           "set"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_ADMIN                         "com.PhilioTech.platform.admin"

#define DBUS_METHOD_GETMODEL                      "getModel"
#define DBUS_METHOD_GETPLATFORM                   "getPlatform"
#define DBUS_METHOD_DOSYSTEM                      "doSystem"
#define DBUS_METHOD_UPDATE_APACHE_PASSWORD        "update_apache_password"
//#define DBUS_METHOD_REBOOT                        "reboot"
#define DBUS_METHOD_RESTARTP2P                    "restartP2P"
//#define DBUS_METHOD_RESTART                       "restart"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_WEBEHOME                      "com.PhilioTech.platform.webehome"

#define DBUS_METHOD_REFRESH                       "refresh"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_WIFI_MODE                     "com.PhilioTech.platform.wifi.mode"

//#define DBUS_METHOD_COMMIT                        "commit"
#define DBUS_METHOD_GETMD5                        "getmd5"
//#define DBUS_METHOD_SWITCH                        "switch"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_WIFI_SSID                     "com.PhilioTech.platform.wifi.ssid"

//#define DBUS_METHOD_REFRESH                       "refresh"

// 1.0 -> platform
#define DBUS_M_IFAC_WIFI_AP                       "com.PhilioTech.platform.wifi.AP"

//#define DBUS_METHOD_COMMAND                       "command"

// 1.0 -> platform
#define DBUS_M_IFAC_WIFI_STA                      "com.PhilioTech.platform.wifi.STA"

//#define DBUS_METHOD_COMMAND                       "command"

// 1.0, 2.0 -> platform
#define DBUS_M_IFAC_WSC                           "com.PhilioTech.platform.wsc"

#define DBUS_METHOD_STATUS                        "status"

// 1.0, 2.0 => platform
#define DBUS_S_IFAC_CHECKUPDATE                   "com.PhilioTech.signal.checkupdate"
#define DBUS_S_MATCH_CHECKUPDATE                  "type='signal',interface='com.PhilioTech.signal.checkupdate'"

//#define DBUS_METHOD_STATUS                        "status"
#define DBUS_METHOD_NET_FIRMWARE                  "new_firmware"


//******************************************************************************
// sdk
//******************************************************************************
// 2.0 -> sdk
#define DBUS_M_IFAC_SDK                           "com.PhilioTech.sdk"

//#define DBUS_METHOD_ADD_HOME_ID                   "add_home_id"
//#define DBUS_METHOD_EVENT_LIST                    "event_list"
//#define DBUS_METHOD_GET_ALL_DEVICE                "get_all_device"
//#define DBUS_METHOD_GET_CH_FUNCTYPE               "get_ch_functype"
//#define DBUS_METHOD_GET_CHANNEL                   "get_channel"
//#define DBUS_METHOD_GET_DEVICE                    "get_device"
//#define DBUS_METHOD_GET_INTERFACE                 "get_interface"
//#define DBUS_METHOD_REMOVE_CHANNEL                "remove_channel"
//#define DBUS_METHOD_REMOVE_HOME_ID                "remove_home_id"
//#define DBUS_METHOD_SET_DEVICE_CHANNEL            "set_device_channel"
//#define DBUS_METHOD_SET_DEVICE                    "set_device"
//#define DBUS_METHOD_NVM_EXT_READ_LONG_BUFFER      "NVM_ext_read_long_buffer"

// 2.0 => zwave
#define DBUS_S_IFAC_SDK_START                     "com.PhilioTech.signal.sdk.start"
#define DBUS_S_MATCH_SDK_START                    "type='signal',interface='com.PhilioTech.signal.sdk.start'"

#define DBUS_METHOD_SDK_START                     "sdk_start"

//******************************************************************************
// storage
//******************************************************************************
// 2.0 -> storage
#define DBUS_M_IFAC_STORAGE                       "com.PhilioTech.storage"

//#define DBUS_METHOD_RESET                         "reset"
//#define DBUS_METHOD_NVRAM_BACKUP                  "nvram_backup"
#define DBUS_METHOD_NVRAM_UBOOT_LIST              "nvram_uboot_list"
#define DBUS_METHOD_NVRAM_RT2860_LIST             "nvram_rt2860_list"
//#define DBUS_METHOD_NVRAM_UBOOT_WRITE             "nvram_uboot_write"
//#define DBUS_METHOD_NVRAM_UBOOT_READ              "nvram_uboot_read"
//#define DBUS_METHOD_NVRAM_RT2860_WRITE            "nvram_rt2860_write"
//#define DBUS_METHOD_NVRAM_RT2860_READ             "nvram_rt2860_read"
//#define DBUS_METHOD_NVRAM_UBOOT_COMMIT            "nvram_uboot_commit"
//#define DBUS_METHOD_NVRAM_RT2860_COMMIT           "nvram_rt2860_commit"

//#define DBUS_METHOD_PCONFIG_WRITE_STRING          "pconfig_write_string"
//#define DBUS_METHOD_PCONFIG_READ_STRING           "pconfig_read_string"
//#define DBUS_METHOD_PCONFIG_WRITE_INT             "pconfig_write_int"
//#define DBUS_METHOD_PCONFIG_READ_INT              "pconfig_read_int"
//#define DBUS_METHOD_PCONFIG_COMMIT                "pconfig_commit"


//******************************************************************************
// Telldus
//******************************************************************************
// 1.0, 2.0 -> Telldus
#define DBUS_M_IFAC_TELLDUS_SEND433               "com.PhilioTech.Telldus.send433"

#define DBUS_METHOD_TEST                          "test"


//******************************************************************************
// zigbee
//******************************************************************************
// 2.0 -> zigbee
#define DBUS_M_IFAC_ZIGBEE                        "com.PhilioTech.zigbee"

//#define DBUS_METHOD_ABORT                         "abort"
//#define DBUS_METHOD_DEVICE_RESET_AND_EXCLUDE      "device_reset_and_exclude"
//#define DBUS_METHOD_EXCLUDE                       "exclude"
//#define DBUS_METHOD_GET_LOG                       "get_log"
//#define DBUS_METHOD_GET_OPS                       "get_ops"
//#define DBUS_METHOD_INCLUDE                       "include"
//#define DBUS_METHOD_REMOVE_DEVICE                 "remove_device"
//#define DBUS_METHOD_REPORT_BINDING                "report_binding"
//#define DBUS_METHOD_REPORT_FREQ                   "report_freq"
//#define DBUS_METHOD_RUN_CMD                       "run_cmd"
//#define DBUS_METHOD_SWITCH                        "switch"
//#define DBUS_METHOD_ZIGBEE_SWITCH_COLOR_SET       "zigbee_switch_color_set"

// 2.0 -> zigbee
// 2.0 libsdk, zigbee => zigbee
#define DBUS_S_IFAC_ZIGBEE                        "com.PhilioTech.signal.zigbee"
#define DBUS_S_MATCH_ZIGBEE                       "type='signal',interface='com.PhilioTech.signal.zigbee'"

//#define DBUS_METHOD_SWITCH_SIGNAL                 "switch_signal"


//******************************************************************************
// zwave
//******************************************************************************
// 2.0 -> zwave
#define DBUS_M_IFAC_ZWAVE                         "com.PhilioTech.zwave"

//#define DBUS_METHOD_ABORT                         "abort"
//#define DBUS_METHOD_ALL_SWITCH_BROADCAST          "all_switch_broadcast"
//#define DBUS_METHOD_ASSIGN_PRIORITY_RETURN_ROUTE  "assign_priority_return_route"
//#define DBUS_METHOD_GET_S2_KEY                    "get_s2_key"
//#define DBUS_METHOD_BACKUP_NVM                    "backup_nvm"
//#define DBUS_METHOD_DELETE_RETURN_ROUTE           "delete_return_route"
//#define DBUS_METHOD_DEVICE_FIRMWARE_UPDATE        "device_firmware_update"
//#define DBUS_METHOD_EXCLUDE                       "exclude"
#define DBUS_METHOD_GET_S0_KEY                      "get_s0_key"
#define DBUS_METHOD_GET_CMD_CLASS                   "get_cmd_class"
//#define DBUS_METHOD_GET_OPS                       "get_ops"
//#define DBUS_METHOD_GETSWITCH                     "getswitch"
//#define DBUS_METHOD_IMA_ENABLE                    "IMA_enable"
//#define DBUS_METHOD_IMA_DISABLE                   "IMA_disable"
//#define DBUS_METHOD_INCLUDE                       "include"
#define DBUS_METHOD_MCU_FW_VERSION                  "mcu_fw_version"
#define DBUS_METHOD_MCU_GET_BTN                     "mcu_get_btn"
//#define DBUS_METHOD_MEMORY_DEBUG                  "memory_debug"
//#define DBUS_METHOD_REMOVE_ALL_DEVICE             "remove_all_device"
//#define DBUS_METHOD_REMOVE_DEVICE                 "remove_device"
//#define DBUS_METHOD_RESTART                       "restart"
//#define DBUS_METHOD_RESTORE_NVM                   "restore_nvm"
//#define DBUS_METHOD_RUN_CMD_CLASS                 "run_cmd_class"
#define DBUS_METHOD_SET_LEARN_MODE                "set_learn_mode"
//#define DBUS_METHOD_SET_ZWAVE_DSK                 "set_zwave_dsk"
#define DBUS_METHOD_SWITCH_ALL_SIREN              "switch_all_siren"
//#define DBUS_METHOD_SWITCH                        "switch"
//#define DBUS_METHOD_ZWAVE_NETWORK_RESET           "zwave_network_reset"
//#define DBUS_METHOD_ZWAVE_SET_DEFAULT             "zwave_set_default"

// 2.0 -> zwave
// 2.0 app, libsdk, apache_module, platform, update, watchdog, zwave => platform, zwave
#define DBUS_S_IFAC_ZWAVE                         "com.PhilioTech.signal.zwave"
#define DBUS_S_MATCH_ZWAVE                        "type='signal',interface='com.PhilioTech.signal.zwave'"

#define DBUS_METHOD_MCU_CMD                       "mcu_cmd"
//#define DBUS_METHOD_SWITCH_SIGNAL                 "switch_signal"
#define DBUS_METHOD_UPDATE_BTN                    "update_btn"


//******************************************************************************
// watchdog
//******************************************************************************
// 1.0 -> watchdog
#define DBUS_M_IFAC_PROCESS                       "com.PhilioTech.process"
#define DBUS_S_MATCH_PROCESS                      "type='signal',interface='com.PhilioTech.process'"

// 1.0,2.0 -> watchdog
#define DBUS_M_IFAC_WATCHDOG_OOM                  "com.PhilioTech.watchdog.oom"

//#define DBUS_METHOD_GETLIST                       "getList"

// 1.0, 2.0 -> watchdog
#define DBUS_M_IFAC_WATCHDOG                      "com.PhilioTech.watchdog"

#define DBUS_METHOD_GETFWVER                      "getfwver"
#define DBUS_METHOD_PROCESS_END                   "process_end"
#define DBUS_METHOD_PROCESS_SEARCH_BY_CMD         "process_search_by_cmd"
//#define DBUS_METHOD_PROCESS_START                 "process_start"
#define DBUS_METHOD_STOPTRACKING                  "stopTracking"

// 2.0 app, libphiliolog, libsdk => watchdog
#define DBUS_S_IFAC_WATCHDOG                      "com.PhilioTech.signal.watchdog"
#define DBUS_S_MATCH_WATCHDOG                     "type='signal',interface='com.PhilioTech.signal.watchdog'"

#define DBUS_METHOD_CRASH                         "crash"
//#define DBUS_METHOD_PID_FILE_CHECK_ENABLE         "pid_file_check_enable"
//#define DBUS_METHOD_PROCESS_CRASH                 "process_crash"
#define DBUS_METHOD_PROCESS_RESTART               "process_restart"
//#define DBUS_METHOD_SEND_LOG                      "send_log"
//#define DBUS_METHOD_EXECUTE_CMD                   "execute_cmd"
//#define DBUS_METHOD_REBOOT                        "reboot"


//******************************************************************************
// others
//******************************************************************************
// 1.0  => philio-sdk, watchdog
#define DBUS_S_IFAC_JSON                          "com.PhilioTech.signal.json"
#define DBUS_S_MATCH_JSON                         "type='signal',interface='com.PhilioTech.signal.json'"

//#define DBUS_METHOD_COMMAND                       "command"

//******************************************************************************
// value
//******************************************************************************
#ifndef __ASSEMBLER__
enum NetStatus
{
	NETSTATUS_OFF=0,
	NETSTATUS_LINKED,
	NETSTATUS_CLOUD_LINKED,
	NETSTATUS_CLOUD_FAIL,
	NETSTATUS_MAX
};

enum LedCtrl
{
	LED_CTRL_OFF = 1,
	LED_CTRL_ON = 0x02,
	LED_CTRL_BLINK = 0x04,
	LED_CTRL_BLINK_PER_SEC = 0x08,
	LED_CTRL_BREATH = 1 << 4,
};

typedef struct dbus_req
{
	const char *dest;
	const char *ifac;
	const char *command;
	char *objPath;
	int timeout_milliseconds;
}DBUS_REQ;
#endif

#define DONGLE_IDX_ZWAVE                          0 // 1.0, 2.0
#define DONGLE_IDX_ZIGBEE                         1 // 2.0
#define DONGLE_IDX_SUN                            1 // 1.0
#define DONGLE_IDX_ONVIF                          2 // 1.0, 2.0
#define DONGLE_IDX_PAN27                          3 // 2.0
#define DONGLE_IDX_WIFI                           4 // 1.0 non-use
#define DONGLE_IDX_MAX                            5

// 1.0, 2.0
#define DEVICE_UID_NUM_RANGE                      256

#define DEVICE_UID_0_NULL_M                       0x0000

#define DEVICE_UID_256_ROOT                       256

#define DEVICE_UID_256_ZWAVE_M                    ((DONGLE_IDX_ZWAVE+1)<<8)
#define DEVICE_UID_257_ZWAVE_START                (DEVICE_UID_256_ZWAVE_M+1)
#define DEVICE_UID_257_ZWAVE_5007                 (DEVICE_UID_257_ZWAVE_START)
#define DEVICE_UID_511_ZWAVE_END                  (DEVICE_UID_256_ZWAVE_M+DEVICE_UID_NUM_RANGE - 1)

#define DEVICE_UID_512_ZIGBEE_M                   ((DONGLE_IDX_ZIGBEE+1)<<8)
#define DEVICE_UID_513_ZIGBEE_START               (DEVICE_UID_512_ZIGBEE_M + 1)
#define DEVICE_UID_767_ZIGBEE_END                 (DEVICE_UID_512_ZIGBEE_M+DEVICE_UID_NUM_RANGE - 1)

#define DEVICE_UID_768_ONVIF_M                    ((DONGLE_IDX_ONVIF+1)<<8)
#define DEVICE_UID_769_ONVIF_START                (DEVICE_UID_768_ONVIF_M + 1)
#define DEVICE_UID_1023_ONVIF_END                 (DEVICE_UID_768_ONVIF_M + DEVICE_UID_NUM_RANGE - 1)

#define DEVICE_UID_1024_PAN27_M                   ((DONGLE_IDX_PAN27+1)<<8)
#define DEVICE_UID_1025_PAN27_START               (DEVICE_UID_1024_PAN27_M + 1)
#define DEVICE_UID_1079_PAN27_END                 (DEVICE_UID_1024_PAN27_M + DEVICE_UID_NUM_RANGE - 1)

#define DEVICE_UID_1280_WIFI_M                    ((DONGLE_IDX_WIFI+1)<<8)
#define DEVICE_UID_1281_WIFI_START                (DEVICE_UID_1280_WIFI_M + 1)
#define DEVICE_UID_1535_WIFI_END                  (DEVICE_UID_1280_WIFI_M + DEVICE_UID_NUM_RANGE - 1)

#define DEVICE_UID_1536_MAX_M                     ((DONGLE_IDX_MAX+1)<<8)

// 1.0
#define DEVICE_UID_505_UNKNOW                     505
#define DEVICE_UID_508_SUNSET                     508
#define DEVICE_UID_509_SUNRISE                    509
#define DEVICE_UID_510_SWITCH_ALL                 510
#define DEVICE_UID_511_SCENE_STATUS               511
#define DEVICE_UID_512_TIMER                      512

// 1.0, 2.0
/**
 * RF Dongle,
 */
#define RF_TYPE_UNKNOW                            0
#define RF_TYPE_ZWAVE                             1
#define RF_TYPE_ZWAVES2                           2
#define RF_TYPE_ZIGBEE                            3
#define RF_TYPE_PAN27                             4
#define RF_TYPE_ONVIF                             11
#define RF_TYPE_WIFI_PHILIO                       21
#define RF_TYPE_ZIGBEE_PHILIO                     41

#endif
