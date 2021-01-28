#ifndef __PCONFIG_DEF_H__
#define __PCONFIG_DEF_H__

//******************************************************************************
// FILE
//******************************************************************************
#define PHILIO_CONFIG_FILE_PATH                   "/mnt/PhilioData/.config"
#define UBOOT_NVRAM_FILE_PATH                     "/mnt/PhilioData/.uboot_nvram_backup"
#define RT2860_NVRAM_FILE_PATH                    "/mnt/PhilioData/.rt2860_nvram_backup"

//******************************************************************************
// NAME /1 VALUE
//******************************************************************************
#define NVRAM_NAME_AP_SECURE                      "AP_secure"
#define NVRAM_VALUE_AP_SECURE_1                   "1"
#define NVRAM_VALUE_AP_SECURE_0                   "0"
#define NVRAM_NAME_REFLECT                       "setreflect"
#define NVRAM_NAME_COUNTRYREGION                  "CountryRegion"
#define NVRAM_NAME_CUSTOMERNAME                   "customerName"
#define NVRAM_NAME_DEVICENAME                     "DeviceName"
#define NVRAM_NAME_SET_CHECKBOX                   "jsonsetcheckbox"
#define NVRAM_NAME_JSONSETALL_NUMBER              "jsonsetall_number"
#define NVRAM_NAME_JSONGETUSERDATA_NUMBER         "jsongetuserdata_number"
#define NVRAM_NAME_SET_SUpwd                      "SET_SUpw"

#define NVRAM_NAME_MACTYPE                        "macType"
#define NVRAM_VALUE_MACTYPE_PHILIO                "Philio"

#define NVRAM_NAME_NTPSERVERIP                    "NTPServerIP"
#define NVRAM_VALUE_NTPSERVERIP                   "tock.stdtime.gov.tw"

#define NVRAM_NAME_NTPDISABLE                     "NTPDisable"
#define NVRAM_VALUE_NTPDISABLE_0                  0
#define NVRAM_NAME_NTPSYNC                        "NTPSync"
#define NVRAM_VALUE_NTPSYNC_30                    30

#define NVRAM_NAME_PPPOE_ENABLE                   "PPPoE_Enable"
#define NVRAM_NAME_PPPOE_USERNAME                 "PPPoE_UserName"
#define NVRAM_NAME_PPPOE_PASSWORD                 "PPPoE_PassWord"
#define NVRAM_NAME_SET_ENABLELOCK                 "enablelock"

#define NVRAM_NAME_SOCKETADDR                     "socketAddr"
#define NVRAM_NAME_SOCKETPORT                     "socketPort"
#define NVRAM_NAME_SOCKETSEC                      "socketSec"
#define NVRAM_NAME_SSID1                          "SSID1"
#define NVRAM_NAME_STA_SSID1                      "STA_SSID1"
#define NVRAM_NAME_STA_WPAPSK                     "STA_WPAPSK"

#define NVRAM_NAME_TELLDUSSECRET                  "TelldusSecret"
#define NVRAM_NAME_TTYNAME                        "ttyname"
#define NVRAM_NAME_TTYBAUDRATE                    "ttybaudrate"
#define NVRAM_NAME_TUTK_UUID                      "TUTK_UUID"
#define NVRAM_NAME_TUTK_USERNAME                  "TUTK_USERNAME"
#define NVRAM_NAME_TUTK_PASSWORD                  "TUTK_PASSWORD"
#define NVRAM_NAME_TZ                             "TZ"
#define NVRAM_VALUE_TZ_CST_008                    "CST_008"
#define NVRAM_NAME_TZ_NAME                        "TZ_name"
#define NVRAM_VALUE_TZ_NAME_GMT_8                 "GMT-8"

#define NVRAM_NAME_USE_BUILDIN_SIREN              "use_buildin_siren"
#define NVRAM_VALUE_USE_BUILDIN_SIREN_1           "1"
#define NVRAM_VALUE_USE_BUILDIN_SIREN_0           "0"

#define NVRAM_NAME_VIVOTEKUUID                    "VivotekUuid"

#define NVRAM_NAME_WPAPSK                         "WPAPSK"
#define NVRAM_VALUE_WPAPSK_12345678               "12345678"

#define NVRAM_NAME_WAN_GATEWAY                    "wan_gateway"

#define NVRAM_NAME_WAN_IPADDR                     "wan_ipaddr"

#define NVRAM_NAME_WAN_NETMASK                    "wan_netmask"

#define NVRAM_NAME_WAN_MAC_ADDR                   "WAN_MAC_ADDR"

#define NVRAM_NAME_WAN_PRIMARY_DNS                "wan_primary_dns"

#define NVRAM_NAME_WANCONNECTIONMODE              "wanConnectionMode"
#define NVRAM_VALUE_WANCONNECTIONMODE_DHCP        "DHCP"
#define NVRAM_VALUE_WANCONNECTIONMODE_STATIC      "STATIC"

#define NVRAM_NAME_WIFIMODE                       "WifiMode"
#define NVRAM_VALUE_WIFIMODE_STA                  "STA"
#define NVRAM_VALUE_WIFIMODE_AP                   "AP"
#define NVRAM_VALUE_WIFIMODE_OFF                  "OFF"


//******************************************************************************
// PATH / NAME / VALUE
//******************************************************************************
// apache
#define PCONFIG_PATH_APACHE                       "apache"
#define PCONFIG_NAME_ENABLE_VIEWER_ACCOUNT        "enable_viewer_account"
#define PCONFIG_NAME_VIEWER_PASSWORD              "viewer_password"

// customer
#define PCONFIG_PATH_CUSTOMER                     "customer"
#define PCONFIG_NAME_JSONSETALL_NUMBER            NVRAM_NAME_JSONSETALL_NUMBER
#define PCONFIG_VALUE_JSONSETALL_NUMBER_0         "0"

#define PCONFIG_NAME_JSONGETUSERDATA_NUMBER       NVRAM_NAME_JSONGETUSERDATA_NUMBER
#define PCONFIG_NAME_CUSTOMERNAME                 NVRAM_NAME_CUSTOMERNAME
#define PCONFIG_NAME_SET_CHECKBOX                 NVRAM_NAME_SET_CHECKBOX
#define PCONFIG_NAME_SET_SUpwd                    NVRAM_NAME_SET_SUpwd
#define PCONFIG_NAME_ENABLELOCK                   NVRAM_NAME_SET_ENABLELOCK	

// Language
#define PCONFIG_PATH_LANGUAGE                     "Language"
#define PCONFIG_NAME_LANG                         "lang"

// MQTT
#define PCONFIG_PATH_MQTT                         "MQTT"
#define PCONFIG_NAME_ENABLE                       "enable"
#define PCONFIG_NAME_SERVER_IP                    "server_ip"

// ntp_client
#define PCONFIG_PATH_NTPCLIENT                    "ntp_client"
#define PCONFIG_NAME_NTPDISABLE                   NVRAM_NAME_NTPDISABLE
#define PCONFIG_VALUE_NTPDISABLE_0                NVRAM_VALUE_NTPDISABLE_0
#define PCONFIG_NAME_NTPSERVERIP                  NVRAM_NAME_NTPSERVERIP
#define PCONFIG_VALUE_NTPSERVERIP                 NVRAM_VALUE_NTPSERVERIP
#define PCONFIG_NAME_NTPSYNC                      NVRAM_NAME_NTPSYNC
#define PCONFIG_VALUE_NTPSYNC_30                  NVRAM_VALUE_NTPSYNC_30
#define PCONFIG_NAME_TZ                           NVRAM_NAME_TZ
#define PCONFIG_VALUE_TZ                          NVRAM_VALUE_TZ_CST_008
#define PCONFIG_NAME_TZ_NAME                      NVRAM_NAME_TZ_NAME
#define PCONFIG_VALUE_TZ_NAME                     NVRAM_VALUE_TZ_NAME_GMT_8

// Orbweb
#define PCONFIG_PATH_ORBWEB                       "Orbweb"
#define PCONFIG_NAME_UUID                         "UUID"

// lat
#define PCONFIG_PATH_LAT                          "lat"
#define PCONFIG_NAME_SETASTCLOCK_LAT              "setastclock_lat"

// lon
#define PCONFIG_PATH_LON                          "lon"
#define PCONFIG_NAME_SETASTCLOCK_LON              "setastclock_lon"
// reflect
#define PCONFIG_PATH_REFLECT                       "reflect"
#define PCONFIG_NAME_REFLECT                       "setreflect"


// PPPoE
#define PCONFIG_PATH_PPPOE                        "PPPoE"
#define PCONFIG_NAME_PPPOE_ENABLE                 NVRAM_NAME_PPPOE_ENABLE
#define PCONFIG_VALUE_PPPOE_ENABLE_0              0
#define PCONFIG_NAME_PPPOE_USERNAME               NVRAM_NAME_PPPOE_USERNAME
#define PCONFIG_VALUE_PPPOE_USERNAME              "user1"
#define PCONFIG_NAME_PPPOE_PASSWORD               NVRAM_NAME_PPPOE_PASSWORD
#define PCONFIG_VALUE_PPPOE_PASSWORD              "888888"

// previous_boot_status
#define PCONFIG_PATH_PRE_BOOT_STATUS              "previous_boot_status"
#define PCONFIG_NAME_WIFI_FAIL                    "wifi_fail"


// RT2860_NVRAM
#define PCONFIG_PATH_RT2860_NVRAM                 "RT2860_NVRAM"

// socket
#define PCONFIG_PATH_SOCKET                       "socket"
#define PCONFIG_NAME_SOCKETADDR                   NVRAM_NAME_SOCKETADDR
#define PCONFIG_NAME_SOCKETPORT                   NVRAM_NAME_SOCKETPORT
#define PCONFIG_NAME_SOCKETSEC                    NVRAM_NAME_SOCKETSEC

#define PCONFIG_NAME_TTYNAME                      NVRAM_NAME_TTYNAME
#define PCONFIG_NAME_TTYBAUDRATE                  NVRAM_NAME_TTYBAUDRATE

// Telldus
#define PCONFIG_PATH_TELLDUS                      "Telldus"
#define PCONFIG_NAME_TELLDUSSECRET                NVRAM_NAME_TELLDUSSECRET

// TUTK
#define PCONFIG_PATH_TUTK                         "TUTK"
#define PCONFIG_NAME_TUTK_UUID                    NVRAM_NAME_TUTK_UUID
#define PCONFIG_NAME_TUTK_USERNAME                NVRAM_NAME_TUTK_USERNAME
#define PCONFIG_NAME_TUTK_PASSWORD                NVRAM_NAME_TUTK_PASSWORD

#define PCONFIG_VALUE_TUTK_USERNAME               "admin"
#define PCONFIG_VALUE_TUTK_PASSWORD               "888888"
#define PCONFIG_VALUE_TUTK_PASSWORD_AIRLIVE       "airlive"

// UBOOT_NVRAM
#define PCONFIG_PATH_UBOOT_NVRAM                  "UBOOT_NVRAM"

// Vivotek
#define PCONFIG_PATH_VIVOTEK                      "Vivotek"
#define PCONFIG_NAME_VIVOTEKUUID                  NVRAM_NAME_VIVOTEKUUID

// WAN
#define PCONFIG_PATH_WAN                          "WAN"

// wifi
#define PCONFIG_PATH_WIFI                         "wifi"
#define PCONFIG_NAME_SSID1                        NVRAM_NAME_SSID1
#define PCONFIG_VALUE_SSID1_UNDEFINED             "undefined"
#define PCONFIG_NAME_STA_SSID1                    NVRAM_NAME_STA_SSID1
#define PCONFIG_NAME_STA_WPAPSK                   NVRAM_NAME_STA_WPAPSK

#define PCONFIG_NAME_WIFIMODE                     NVRAM_NAME_WIFIMODE
#define PCONFIG_VALUE_WIFIMODE_STA                NVRAM_VALUE_WIFIMODE_STA
#define PCONFIG_VALUE_WIFIMODE_AP                 NVRAM_VALUE_WIFIMODE_AP
#define PCONFIG_VALUE_WIFIMODE_OFF                NVRAM_VALUE_WIFIMODE_OFF

#define PCONFIG_NAME_WPAPSK                       NVRAM_NAME_WPAPSK
#define PCONFIG_VALUE_WPAPSK_12345678             NVRAM_VALUE_WPAPSK_12345678

// zigbee
#define PCONFIG_PATH_ZIGBEE                       "zigbee"

// zwave
#define PCONFIG_PATH_ZWAVE                        "zwave"
#define PCONFIG_NAME_NETWORK_KEY                  "network_key"

#endif
