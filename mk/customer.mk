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

CUSTOMERDIRS_$(PJ_HAS_WWW_COMMON) += $(PJ_ROOT)/user/customer/common/www
BINS_CHECK_$(PJ_HAS_WWW_COMMON) += $(SDK_WWW_DIR)/common/mqtt-web/index.html

#** customer (common) - Cloud **
CUSTOMERDIRS_$(PJ_HAS_ICLOUD) += $(PJ_ROOT)/user/customer/common/icloud
BINS_CHECK_$(PJ_HAS_ICLOUD) += $(SDK_BIN_DIR)/icloud

CUSTOMERDIRS_$(PJ_HAS_AWS_BOWSER) += $(PJ_ROOT)/user/customer/Urmet/awsBowser
LIBS_CHECK_$(PJ_HAS_AWS_BOWSER) +=
BINS_CHECK_$(PJ_HAS_AWS_BOWSER) += $(SDK_BIN_DIR)/s3sample $(SDK_BIN_DIR)/awsBowser

CUSTOMERDIRS_$(PJ_HAS_AWS_KVSMARIO) += $(PJ_ROOT)/user/customer/Urmet/kvsMario
BINS_CHECK_$(PJ_HAS_AWS_KVSMARIO) += $(SDK_BIN_DIR)/kvsWebrtcUrmet $(SDK_BIN_DIR)/kvsWebrtcRTSP $(SDK_BIN_DIR)/kvsWebrtcUDP
