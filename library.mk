
ifeq ("$(PJ_HAS_LIBUSB)", "yes")
LIBXXX_OBJS += \
							usbX_api.o
LIBS_yes += -lusb-1.0
endif

ifeq ("$(PJ_HAS_JANSSON)", "yes")
LIBXXX_OBJS += \
							json_api.o
LIBS_yes += -ljansson
endif

ifeq ("$(PJ_HAS_JSONC)", "yes")
LIBS_yes += -ljson-c
endif

ifeq ("$(PJ_HAS_MXML)", "yes")
LIBXXX_OBJS += \
							onvif_api.o \
							soap_api.o \
							wsdiscovery_api.o
LIBS_yes += -lmxml
endif

ifeq ("$(PJ_HAS_LIBWEBSOCKETS)", "yes")
LIBS_yes += -lwebsockets
endif

ifeq ("$(PJ_HAS_CURL)", "yes")
LIBXXX_OBJS += \
							curl_api.o \
							rtp_api.o
LIBS_yes += -lcurl
endif

ifeq ("$(PJ_HAS_LIBSSH)", "yes")
LIBXXX_OBJS += \
							ssh_api.o \
#LIBS_yes += -lssh
LIBS_yes += $(SDK_LIB_DIR)/libssh.a
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
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
LIBXXX_OBJS += \
							dbus_api.o
LIBS_yes += -lexpat -ldbus-1
CFLAGS += -I$(SDK_INC_DIR)/dbus-1.0/dbus -I$(SDK_INC_DIR)/dbus-1.0 -I$(SDK_LIB_DIR)/dbus-1.0/include
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
LIBXXX_OBJS += \
							ubus_api.o
LIBS_yes += -lubus -lblobmsg_json
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
LIBS_yes += -lswconfig
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
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

ifeq ("$(PJ_HAS_OPENSSL)", "yes")
LIBS_yes += -lssl -lcrypto
endif

LIBS := $(LIBS_yes) $(LIBS)