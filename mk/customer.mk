#********************************************************************************
#** CUSTOMERDIRS **
#********************************************************************************
CUSTOMERDIRS_yes=

#** customer (common) **
CUSTOMERDIRS_$(PJ_HAS_DBUS_HANDLER) += $(PJ_ROOT)/user/customer/common/dbus_handler
LIBS_CHECK_$(PJ_HAS_DBUS_HANDLER) += $(SDK_LIB_DIR)/libdbus_handler.so

CUSTOMERDIRS_$(PJ_HAS_DBUS_DEMO) += $(PJ_ROOT)/user/customer/common/dbus_demo
BINS_CHECK_$(PJ_HAS_DBUS_DEMO) +=$(SDK_BIN_DIR)/dbus_demo

CUSTOMERDIRS_$(PJ_HAS_FCM_DEMO) += $(PJ_ROOT)/user/customer/common/fcm_demo
BINS_CHECK_$(PJ_HAS_FCM_DEMO) +=$(SDK_BIN_DIR)/fcm_demo

#** customer (common) - MQTT & MCTT **
CUSTOMERDIRS_$(PJ_HAS_MASTER) += $(PJ_ROOT)/user/customer/common/master
BINS_CHECK_$(PJ_HAS_MASTER) += $(SDK_BIN_DIR)/master

CUSTOMERDIRS_$(PJ_HAS_QUEEN_BEE) += $(PJ_ROOT)/user/customer/common/queen_bee
BINS_CHECK_$(PJ_HAS_QUEEN_BEE) += $(SDK_BIN_DIR)/queen_bee

CUSTOMERDIRS_$(PJ_HAS_HONEY_MARKET) += $(PJ_ROOT)/user/customer/common/honey_market
BINS_CHECK_$(PJ_HAS_HONEY_MARKET) += $(SDK_BIN_DIR)/honey_market

#** customer (common) - UART **
CUSTOMERDIRS_$(PJ_HAS_URCOMMANDER) += $(PJ_ROOT)/user/customer/common/uRCommander
BINS_CHECK_$(PJ_HAS_URCOMMANDER) += $(SDK_BIN_DIR)/uRCommander

#** customer (common) - OTA **
CUSTOMERDIRS_$(PJ_HAS_OTA) += $(PJ_ROOT)/user/customer/common/ota_daemon
BINS_CHECK_$(PJ_HAS_OTA) += $(SDK_BIN_DIR)/ota_daemon

#** customer (common) - USB **
CUSTOMERDIRS_$(PJ_HAS_USBHUNTER) += $(PJ_ROOT)/user/customer/common/usbHunter
BINS_CHECK_$(PJ_HAS_USBHUNTER) += $(SDK_BIN_DIR)/usbHunter

#** customer (common) - WEB **
CUSTOMERDIRS_$(PJ_HAS_FASTCGI) += $(PJ_ROOT)/user/customer/common/fastcgi
BINS_CHECK_$(PJ_HAS_FASTCGI) += $(SDK_BIN_DIR)/echo_cgi

CUSTOMERDIRS_$(PJ_HAS_MOD_IOT) += $(PJ_ROOT)/user/customer/common/mod_iot_api
LIBS_CHECK_$(PJ_HAS_MOD_IOT) += $(SDK_MODULES_DIR)/mod_iot_api.so

CUSTOMERDIRS_$(PJ_HAS_MOD_LUFFA) += $(PJ_ROOT)/user/customer/common/mod_luffa_api
LIBS_CHECK_$(PJ_HAS_MOD_LUFFA) += $(SDK_MODULES_DIR)/mod_luffa_api.so

CUSTOMERDIRS_$(PJ_HAS_WWW_COMMON) += $(PJ_ROOT)/user/customer/common/www
BINS_CHECK_$(PJ_HAS_WWW_COMMON) += $(SDK_WWW_DIR)/common/mqtt-web/index.html

#** customer (common) - Cloud **
CUSTOMERDIRS_$(PJ_HAS_ICLOUD) += $(PJ_ROOT)/user/customer/common/icloud
BINS_CHECK_$(PJ_HAS_ICLOUD) += $(SDK_BIN_DIR)/icloud

#** customer (Philio) **
CUSTOMERDIRS_$(PJ_HAS_LIBNVRAM) += $(PJ_ROOT)/user/customer/Philio/libnvram
LIBS_CHECK_$(PJ_HAS_LIBNVRAM) += $(SDK_LIB_DIR)/libnvram.so

CUSTOMERDIRS_$(PJ_HAS_LOGCAT) += $(PJ_ROOT)/user/customer/Philio/logcat
LIBS_CHECK_$(PJ_HAS_LOGCAT) += $(SDK_LIB_DIR)/liblogcat.so

CUSTOMERDIRS_$(PJ_HAS_TIMEZONE) += $(PJ_ROOT)/user/customer/Philio/timezone
LIBS_CHECK_$(PJ_HAS_TIMEZONE) += $(SDK_LIB_DIR)/libtimezone.so

CUSTOMERDIRS_$(PJ_HAS_DBUS123) += $(PJ_ROOT)/user/customer/Philio/dbus123
BINS_CHECK_$(PJ_HAS_DBUS123) +=$(SDK_BIN_DIR)/dbus123

CUSTOMERDIRS_$(PJ_HAS_APP) += $(PJ_ROOT)/user/customer/Philio/app
BINS_CHECK_$(PJ_HAS_APP) += $(SDK_BIN_DIR)/app

CUSTOMERDIRS_$(PJ_HAS_PHILIO_SDK_V1) += $(PJ_ROOT)/user/customer/Philio/philio_sdk_v1
BINS_CHECK_$(PJ_HAS_PHILIO_SDK_V1) += $(SDK_BIN_DIR)/philio_sdk

CUSTOMERDIRS_$(PJ_HAS_PHILIO_SDK_V2) += $(PJ_ROOT)/user/customer/Philio/philio_sdk_v2
BINS_CHECK_$(PJ_HAS_PHILIO_SDK_V2) += $(SDK_BIN_DIR)/philio_sdk

CUSTOMERDIRS_$(PJ_HAS_PHILIO_SDK_S2) += $(PJ_ROOT)/user/customer/Philio/philio_sdk_s2
BINS_CHECK_$(PJ_HAS_PHILIO_SDK_s2) += $(SDK_BIN_DIR)/philio_sdk

CUSTOMERDIRS_$(PJ_HAS_PHILIO_SDK_V3) += $(PJ_ROOT)/user/customer/Philio/philio_sdk_v3
BINS_CHECK_$(PJ_HAS_PHILIO_SDK_V3) += $(SDK_BIN_DIR)/philio_sdk

#** customer (Yokis) **
CUSTOMERDIRS_$(PJ_HAS_YK_P2P) += $(PJ_ROOT)/user/customer/Yokis/yk_p2p_daemon
BINS_CHECK_$(PJ_HAS_YK_P2P) += $(SDK_BIN_DIR)/yk_p2p_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_COMMAND) += $(PJ_ROOT)/user/customer/Yokis/yk_command_daemon
BINS_CHECK_$(PJ_HAS_YK_COMMAND) += $(SDK_BIN_DIR)/yk_command_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_DATAB) += $(PJ_ROOT)/user/customer/Yokis/yk_datab_daemon
BINS_CHECK_$(PJ_HAS_YK_DATAB) += $(SDK_BIN_DIR)/yk_datab_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_INFO) += $(PJ_ROOT)/user/customer/Yokis/yk_info_daemon
BINS_CHECK_$(PJ_HAS_YK_INFO) += $(SDK_BIN_DIR)/yk_info_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_REQUEST) += $(PJ_ROOT)/user/customer/Yokis/yk_request_daemon
BINS_CHECK_$(PJ_HAS_YK_REQUEST) += $(SDK_BIN_DIR)/yk_request_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_SERVER) += $(PJ_ROOT)/user/customer/Yokis/yk_server_daemon
BINS_CHECK_$(PJ_HAS_YK_SERVER) += $(SDK_BIN_DIR)/yk_server_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_UPDATE) += $(PJ_ROOT)/user/customer/Yokis/yk_update_daemon
BINS_CHECK_$(PJ_HAS_YK_UPDATE) += $(SDK_BIN_DIR)/yk_update_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_SUBNET) += $(PJ_ROOT)/user/customer/Yokis/yk_subnet_daemon
BINS_CHECK_$(PJ_HAS_YK_SUBNET) += $(SDK_BIN_DIR)/yk_subnet_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_KMS) += $(PJ_ROOT)/user/customer/Yokis/yk_kms_daemon
BINS_CHECK_$(PJ_HAS_YK_KMS) += $(SDK_BIN_DIR)/yk_kms_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_STANDALONE) += $(PJ_ROOT)/user/customer/Yokis/yk_standalone_daemon
BINS_CHECK_$(PJ_HAS_YK_STANDALONE) += $(SDK_BIN_DIR)/yk_standalone_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_THERMO) += $(PJ_ROOT)/user/customer/Yokis/yk_thermo_daemon
BINS_CHECK_$(PJ_HAS_YK_THERMO) += $(SDK_BIN_DIR)/yk_thermo_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_WS) += $(PJ_ROOT)/user/customer/Yokis/yk_ws_daemon
BINS_CHECK_$(PJ_HAS_YK_WS) += $(SDK_BIN_DIR)/yk_ws_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_MQTT) += $(PJ_ROOT)/user/customer/Yokis/yk_mqtt_daemon
BINS_CHECK_$(PJ_HAS_YK_MQTT) += $(SDK_BIN_DIR)/yk_mqtt_daemon

CUSTOMERDIRS_$(PJ_HAS_YK_UP_FORMATTER) += $(PJ_ROOT)/user/customer/Yokis/yk_up_formatter
BINS_CHECK_$(PJ_HAS_YK_UP_FORMATTER) += $(SDK_BIN_DIR)/yk_up_formatter

CUSTOMERDIRS_$(PJ_HAS_YK_BT) += $(PJ_ROOT)/user/customer/Yokis/yk_bt_daemon
BINS_CHECK_$(PJ_HAS_YK_BT) += $(SDK_BIN_DIR)/yk_bt_daemon

CUSTOMERDIRS_$(PJ_HAS_WWW_YOKIS) += $(PJ_ROOT)/user/customer/Yokis/www
BINS_CHECK_$(PJ_HAS_WWW_YOKIS) += $(SDK_WWW_DIR)/yokis/index.html

CUSTOMERDIRS_$(PJ_HAS_MOD_YOKIS) += $(PJ_ROOT)/user/customer/Yokis/mod_yokis_api
LIBS_CHECK_$(PJ_HAS_MOD_YOKIS) += $(SDK_MODULES_DIR)/mod_yokis_api.so

CUSTOMERDIRS_$(PJ_HAS_WWW_YOKIS_PREBUILT) += $(PJ_ROOT)/user/customer/Yokis/www_prebuilt

CUSTOMERDIRS_$(PJ_HAS_WWW_YOKIS_BACKUP) += $(PJ_ROOT)/user/customer/Yokis/www_backup
BINS_CHECK_$(PJ_HAS_WWW_YOKIS_BACKUP) += $(SDK_WWW_DIR)/yokis/index.html

CUSTOMERDIRS_$(PJ_HAS_MOD_YOKIS_BACKUP) += $(PJ_ROOT)/user/customer/Yokis/mod_yokis_backup_api
LIBS_CHECK_$(PJ_HAS_MOD_YOKIS_BACKUP) += $(SDK_MODULES_DIR)/mod_yokis_backup_api.so

#** customer (Urmet) **
CUSTOMERDIRS_$(PJ_HAS_URMET_MQTT) += $(PJ_ROOT)/user/customer/Urmet/urmet_mqtt_daemon
BINS_CHECK_$(PJ_HAS_URMET_MQTT) += $(SDK_BIN_DIR)/urmet_mqtt_daemon

CUSTOMERDIRS_$(PJ_HAS_WWW_URMET) += $(PJ_ROOT)/user/customer/Urmet/www
BINS_CHECK_$(PJ_HAS_WWW_URMET) += $(SDK_WWW_DIR)/urmet/mqtt-web/index.html

CUSTOMERDIRS_$(PJ_HAS_WWW_URMET_PREBUILT) += $(PJ_ROOT)/user/customer/Urmet/www_prebuilt
