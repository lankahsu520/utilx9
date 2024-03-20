CLEAN_BINS = 
DUMMY_BINS = 

#** chainX_api **
CLEAN_BINS += \
							chainX_123 \
							client_123 \
							tty_123 \
							ping_123

#** clist_api **
CLEAN_BINS += \
							clist_123

#** thread_api, led_api **
CLEAN_BINS += \
							led_123

#** statex_api **
CLEAN_BINS += \
							statex_123

#** thread_api **
CLEAN_BINS += \
							thread_123

ifeq ("$(PJ_HAS_LIBUSB)", "yes")
CLEAN_BINS += \
							usb_123
LIBXXX_OBJS += \
							usbX_api.o
LIBS_yes += -lusb-1.0
endif

ifeq ("$(PJ_HAS_JANSSON)", "yes")
DUMMY_BINS += \
							jqx
CLEAN_BINS += \
							json_123
LIBXXX_OBJS += \
							json_api.o
LIBS_yes += -ljansson
endif

ifeq ("$(PJ_HAS_JSONC)", "yes")
LIBS_yes += -ljson-c
endif

ifeq ("$(PJ_HAS_MXML)", "yes")
CLEAN_BINS += \
							onvif_pass_123 \
							onvif_client_123 \
							wsdiscovery_123
LIBXXX_OBJS += \
							onvif_api.o \
							soap_api.o \
							wsdiscovery_api.o
LIBS_yes += -lmxml
endif

ifeq ("$(PJ_HAS_MOSQUITTO)", "yes")
CLEAN_BINS += \
							mqtt_123
LIBXXX_OBJS += \
							mqtt_api.o
LIBS_yes += -lmosquitto
endif

ifeq ("$(PJ_HAS_LIBWEBSOCKETS)", "yes")
CLEAN_BINS += \
							lws_123
LIBXXX_OBJS += \
							lws_api.o
LIBS_yes += -lwebsockets #-lwebsockets-evlib_uv
endif

ifeq ("$(PJ_HAS_CURL)", "yes")
CLEAN_BINS += \
							http_client_123
LIBXXX_OBJS += \
							curl_api.o \
							rtp_api.o
LIBS_yes += -lcurl
endif

ifeq ("$(PJ_HAS_LIBSSH)", "yes")
CLEAN_BINS += \
							sshX_123 \
							tunnel_123
LIBXXX_OBJS += \
							ssh_api.o \
#LIBS_yes += -lssh
LIBS_yes += $(SDK_LIB_DIR)/libssh.a
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
CLEAN_BINS += \
							uv_000 \
							uv_spawn_123 \
							cronx_123 \
							uv_123
LIBXXX_OBJS += \
							uv_api.o
LIBS_yes += -luv
endif

ifeq ("$(PJ_HAS_URIPARSER)", "yes")
LIBS_yes += -luriparser
endif

ifeq ("$(PJ_HAS_LIBYUAREL)", "yes")
LIBXXX_OBJS += \
							yuarel_api.o
LIBS_yes += -lyuarel
endif

ifeq ("$(PJ_HAS_DBUS)", "yes")
CLEAN_BINS += \
							dbusx_456
LIBXXX_OBJS += \
							dbusx_api.o
LIBS_yes += -lexpat -ldbus-1
CFLAGS += -I$(SDK_INC_DIR)/dbus-1.0/dbus -I$(SDK_INC_DIR)/dbus-1.0 -I$(SDK_LIB_DIR)/dbus-1.0/include
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
CLEAN_BINS += \
							ubus_123
LIBXXX_OBJS += \
							ubus_api.o
LIBS_yes += -lubus -lblobmsg_json
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
CLEAN_BINS += 	\
							swlink_123
LIBS_yes += -lswconfig
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
CLEAN_BINS += \
							uci_123
LIBXXX_OBJS += \
							uci_api.o
LIBS_yes += -luci
endif

ifeq ("$(PJ_HAS_LIBUBOX)", "yes")
LIBS_yes += -lubox
endif

ifeq ("$(PJ_HAS_LIBNL_TINY)", "yes")
LIBS_yes += -lnl-tiny
CFLAGS += -I$(SDK_INC_DIR)/libnl-tiny
endif

ifeq ("$(PJ_HAS_LIBBACKTRACE)", "yes")
CLEAN_BINS += 	\
							backtrace_456
LIBXXX_OBJS += \
							backtrace_api.o
LIBS_yes += -lbacktrace
endif

ifeq ("$(PJ_HAS_OPENSSL)", "yes")
LIBS_yes += -lssl -lcrypto
endif

LIBS_yes += -lz

include $(PJ_MK_REVISION)
include $(PJ_MK_MESON)