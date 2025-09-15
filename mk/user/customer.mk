#********************************************************************************
#** CUSTOMERDIRS **
#********************************************************************************
CUSTOMERDIRS_yes=

#** customer (common) **
CUSTOMERDIRS_$(PJ_HAS_DBUS_HANDLER) += $(PJ_COMMON_DIR)/dbus_handler
LIBS_CHECK_$(PJ_HAS_DBUS_HANDLER) += $(SDK_LIB_DIR)/libdbus_handler.so

CUSTOMERDIRS_$(PJ_HAS_DBUS_DEMO) += $(PJ_COMMON_DIR)/dbus_demo
BINS_CHECK_$(PJ_HAS_DBUS_DEMO) +=$(SDK_BIN_DIR)/dbus_demo

CUSTOMERDIRS_$(PJ_HAS_FCM_DEMO) += $(PJ_COMMON_DIR)/fcm_demo
BINS_CHECK_$(PJ_HAS_FCM_DEMO) +=$(SDK_BIN_DIR)/fcm_demo

CUSTOMERDIRS_$(PJ_HAS_AWS_KVSMARIO) += $(PJ_COMMON_DIR)/kvsMario
BINS_CHECK_$(PJ_HAS_AWS_KVSMARIO) += $(SDK_BIN_DIR)/kvsMario
#BINS_CHECK_$(PJ_HAS_AWS_KVSMARIO) += $(SDK_BIN_DIR)/kvsWebrtcRTSP $(SDK_BIN_DIR)/kvsWebrtcUDP

#** customer (common) - MQTT & MCTT **
CUSTOMERDIRS_$(PJ_HAS_MASTER) += $(PJ_COMMON_DIR)/master
BINS_CHECK_$(PJ_HAS_MASTER) += $(SDK_BIN_DIR)/master

CUSTOMERDIRS_$(PJ_HAS_QUEEN_BEE) += $(PJ_COMMON_DIR)/queen_bee
BINS_CHECK_$(PJ_HAS_QUEEN_BEE) += $(SDK_BIN_DIR)/queen_bee

CUSTOMERDIRS_$(PJ_HAS_HONEY_MARKET) += $(PJ_COMMON_DIR)/honey_market
BINS_CHECK_$(PJ_HAS_HONEY_MARKET) += $(SDK_BIN_DIR)/honey_market

#** customer (common) - UART **
CUSTOMERDIRS_$(PJ_HAS_URCOMMANDER) += $(PJ_COMMON_DIR)/uRCommander
BINS_CHECK_$(PJ_HAS_URCOMMANDER) += $(SDK_BIN_DIR)/uRCommander

#** customer (common) - OTA **
CUSTOMERDIRS_$(PJ_HAS_OTA) += $(PJ_COMMON_DIR)/ota_daemon
BINS_CHECK_$(PJ_HAS_OTA) += $(SDK_BIN_DIR)/ota_daemon

#** customer (common) - USB **
CUSTOMERDIRS_$(PJ_HAS_USBHUNTER) += $(PJ_COMMON_DIR)/usbHunter
BINS_CHECK_$(PJ_HAS_USBHUNTER) += $(SDK_BIN_DIR)/usbHunter

#** customer (common) - WEB **
CUSTOMERDIRS_$(PJ_HAS_FASTCGI) += $(PJ_COMMON_DIR)/fastcgi
BINS_CHECK_$(PJ_HAS_FASTCGI) += $(SDK_BIN_DIR)/echo_cgi

CUSTOMERDIRS_$(PJ_HAS_MOD_IOT) += $(PJ_COMMON_DIR)/mod_iot_api
LIBS_CHECK_$(PJ_HAS_MOD_IOT) += $(SDK_MODULES_DIR)/mod_iot_api.so

CUSTOMERDIRS_$(PJ_HAS_WWW_COMMON) += $(PJ_COMMON_DIR)/www
BINS_CHECK_$(PJ_HAS_WWW_COMMON) += $(SDK_WWW_DIR)/common/mqtt-web/index.html

#** customer (common) - Cloud **
CUSTOMERDIRS_$(PJ_HAS_ICLOUD) += $(PJ_COMMON_DIR)/icloud
BINS_CHECK_$(PJ_HAS_ICLOUD) += $(SDK_BIN_DIR)/icloud

