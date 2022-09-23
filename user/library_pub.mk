ifeq ("$(PJ_HAS_UTILX9)", "yes")
LIBS_yes += -lutilx9
endif

ifeq ("$(PJ_HAS_DBUS_HANDLER)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libdbus_handler.so)","")
LIBS_yes += -ldbus_handler
endif
endif

ifeq ("$(PJ_HAS_AWS_KVSWEBRTC)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libkvsWebrtcClient.so)","")
LIBS_yes += -lkvsWebrtcClient -lkvsWebrtcSignalingClient
endif
endif

ifeq ("$(PJ_HAS_AWS_KVSPRODUCER)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libcproducer.so)","")
LIBS_yes += -lcproducer
endif
endif

ifeq ("$(PJ_HAS_AWS_KVSPIC)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libkvspic.so)","")
LIBS_yes += -lkvspic -lkvspicClient -lkvspicUtils -lkvspicState
endif
endif

ifeq ("$(PJ_HAS_LIBSRTP)", "yes")
LIBS_yes += -lsrtp2
endif

ifeq ("$(PJ_HAS_LIBUSRSCTP)", "yes")
LIBS_yes += -lusrsctp
endif

ifeq ("$(PJ_HAS_LOG4CPLUS)", "yes")
LIBS_yes += -llog4cplus -llog4cplusU
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
LIBS_yes += -lswconfig
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
LIBS_yes += -luci
endif

ifeq ("$(PJ_HAS_LIBUBOX)", "yes")
LIBS_yes += -lubox
endif

ifeq ("$(PJ_HAS_LIBNL_TINY)", "yes")
LIBS_yes += -lnl-tiny
CFLAGS += -I$(SDK_INC_DIR)/libnl-tiny
endif

ifeq ("$(PJ_HAS_LIBUSB)", "yes")
LIBS_yes += -lusb-1.0
endif

ifeq ("$(PJ_HAS_EUDEV)", "yes")
LIBS_yes += -ludev
endif

ifeq ("$(PJ_HAS_BLUEZ)", "yes")
LIBS_yes += -lbluetooth
endif

ifeq ("$(PJ_HAS_JANSSON)", "yes")
LIBS_yes += -ljansson
endif

ifeq ("$(PJ_HAS_JSONC)", "yes")
LIBS_yes += -ljson-c
endif

ifeq ("$(PJ_HAS_FASTCGI)", "yes")
LIBS_yes += -lfcgi -lfcgi++
endif

ifeq ("$(PJ_HAS_APR)", "yes")
LIBS_yes += -lrt -lapr-1
CFLAGS += -I$(SDK_INC_DIR)/apr-1
endif

ifeq ("$(PJ_HAS_LIBXML2)", "yes")
LIBS_yes += -lxml2
endif

ifeq ("$(PJ_HAS_MXML)", "yes")
LIBS_yes += -lmxml
endif

ifeq ("$(PJ_HAS_MOSQUITTO)", "yes")
LIBS_yes += -lmosquitto
endif

ifeq ("$(PJ_HAS_LIBWEBSOCKETS)", "yes")
LIBS_yes += -lwebsockets #-lwebsockets-evlib_uv
endif

ifeq ("$(PJ_HAS_CURL)", "yes")
LIBS_yes += -lcurl
endif

ifeq ("$(PJ_HAS_LIBSSH)", "yes")
LIBS_yes += -lssh
endif

ifeq ("$(PJ_HAS_LIBICAL)", "yes")
LIBS_yes += -lical
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
LIBS_yes += -luv
endif

ifeq ("$(PJ_HAS_URIPARSER)", "yes")
LIBS_yes += -luriparser
endif

ifeq ("$(PJ_HAS_LIBYUAREL)", "yes")
LIBS_yes += -lyuarel
endif

ifeq ("$(PJ_HAS_DBUS)", "yes")
LIBS_yes += -lexpat -ldbus-1
CFLAGS += -I$(SDK_INC_DIR)/dbus-1.0/dbus -I$(SDK_INC_DIR)/dbus-1.0 -I$(SDK_LIB_DIR)/dbus-1.0/include
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
LIBS_yes += -lubus -lblobmsg_json
endif

ifeq ("$(PJ_HAS_GLIB_SYSROOT)", "yes")
LIBS_yes += -lgobject-2.0 -lgio-2.0 -lglib-2.0
ifeq ("$(PJ_CROSS)", "")
CFLAGS += $(shell pkg-config --cflags gio-2.0 gio-unix-2.0 glib-2.0)
endif
endif

ifeq ("$(PJ_HAS_OPENSSL)", "yes")
LIBS_yes += -lssl -lcrypto
endif

LIBS_yes += $(LIBS_CUSTOMER) -lz

