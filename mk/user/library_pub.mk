ifeq ("$(PJ_HAS_UTILX9)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libutilx9.so)","")
LIBS_yes += -lutilx9
endif
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
ifneq ("$(wildcard $(SDK_LIB_DIR)/libkvsWebRtcThreadpool.so)","")
LIBS_yes += -lkvsWebRtcThreadpool
endif
endif

ifeq ("$(PJ_HAS_AWS_KVSPRODUCER)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libcproducer.so)","")
LIBS_yes += -lcproducer -lkvsCommonCurl -lkvsCommonLws
endif
endif

ifeq ("$(PJ_HAS_AWS_KVSPIC)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libkvspic.so)","")
LIBS_yes += -lkvspic -lkvspicClient -lkvspicUtils -lkvspicState
endif
endif

ifeq ("$(PJ_HAS_LIBSRTP)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libsrtp2.so)","")
LIBS_yes += -lsrtp2
endif
endif

ifeq ("$(PJ_HAS_LIBUSRSCTP)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libusrsctp.so)","")
LIBS_yes += -lusrsctp
endif
endif

ifeq ("$(PJ_HAS_LOG4CPLUS)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/liblog4cplus.so)","")
LIBS_yes += -llog4cplus -llog4cplusU
endif
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libswconfig.so)","")
LIBS_yes += -lswconfig
endif
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libuci.so)","")
LIBS_yes += -luci
endif
endif

ifeq ("$(PJ_HAS_LIBUBOX)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libubox.so)","")
LIBS_yes += -lubox
endif
endif

ifeq ("$(PJ_HAS_LIBNL_TINY)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libnl-tiny.so)","")
LIBS_yes += -lnl-tiny
CFLAGS += -I$(SDK_INC_DIR)/libnl-tiny
endif
endif

ifeq ("$(PJ_HAS_LIBUSB)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libusb-1.0.so)","")
LIBS_yes += -lusb-1.0
else
LIBS_yes += -lusb-1.0
CFLAGS += $(shell pkg-config --cflags libusb-1.0)
endif
endif

ifeq ("$(PJ_HAS_EUDEV)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libudev.so)","")
LIBS_yes += -ludev
endif
endif

ifeq ("$(PJ_HAS_BLUEZ)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libbluetooth.so)","")
LIBS_yes += -lbluetooth
endif
endif

ifeq ("$(PJ_HAS_JANSSON)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libjansson.so)","")
LIBS_yes += -ljansson
else
LIBS_yes += -ljansson
CFLAGS += $(shell pkg-config --cflags jansson)
endif
endif

ifeq ("$(PJ_HAS_JSONC)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libjson-c.so)","")
LIBS_yes += -ljson-c
else
LIBS_yes += -ljson-c
CFLAGS += $(shell pkg-config --cflags json-c)
endif
endif

ifeq ("$(PJ_HAS_FASTCGI)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libfcgi.so)","")
LIBS_yes += -lfcgi -lfcgi++
endif
endif

ifeq ("$(PJ_HAS_APR)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libapr-1.so)","")
LIBS_yes += -lrt -lapr-1
CFLAGS += -I$(SDK_INC_DIR)/apr-1
endif
endif

ifeq ("$(PJ_HAS_LIBXML2)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libxml2.so)","")
LIBS_yes += -lxml2
endif
endif

ifeq ("$(PJ_HAS_MXML)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libmxml.so)","")
LIBS_yes += -lmxml
endif
endif

ifeq ("$(PJ_HAS_MOSQUITTO)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libmosquitto.so)","")
LIBS_yes += -lmosquitto #-lwebsockets-evlib_uv
else
LIBS_yes += -lmosquitto #-lwebsockets-evlib_uv
CFLAGS += $(shell pkg-config --cflags libmosquitto)
endif
endif

ifeq ("$(PJ_HAS_LIBWEBSOCKETS)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libwebsockets.so)","")
LIBS_yes += -lwebsockets -lwebsockets-evlib_uv
else
LIBS_yes += -lwebsockets
CFLAGS += $(shell pkg-config --cflags libwebsockets)
endif
endif

ifeq ("$(PJ_HAS_LIBBACKTRACE)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libbacktrace.so)","")
LIBS_yes += -lbacktrace
endif
endif

ifeq ("$(PJ_HAS_AWSX9)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libawsx9.so)","")
LIBS_yes += \
					-lawsx9
endif
endif

ifeq ("$(PJ_HAS_AWS_SDK_CPP)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libaws-cpp-sdk-core.so)","")
LIBS_yes += \
					-laws-cpp-sdk-dynamodb \
					-laws-cpp-sdk-s3 \
					-laws-cpp-sdk-core \
					-laws-crt-cpp \
					-laws-c-mqtt \
					-laws-c-event-stream \
					-laws-c-s3 \
					-laws-c-auth \
					-laws-c-http \
					-laws-c-io \
					-ls2n \
					-laws-c-compression \
					-laws-c-cal \
					-laws-c-sdkutils \
					-laws-checksums \
					-laws-c-common
endif
endif

ifeq ("$(PJ_HAS_SQLITE)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libsqlite3.so)","")
LIBS_yes += -lsqlite3
endif
endif

ifeq ("$(PJ_HAS_CURL)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libcurl.so)","")
LIBS_yes += -lcurl
else
LIBS_yes += -lcurl
CFLAGS += $(shell pkg-config --cflags libcurl)
endif
endif

ifeq ("$(PJ_HAS_LIBSSH)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libssh.so)","")
LIBS_yes += -lssh
endif
endif

ifeq ("$(PJ_HAS_LIBICAL)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libical.so)","")
LIBS_yes += -lical
endif
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libuv.so)","")
LIBS_yes += -luv
else
LIBS_yes += -luv
CFLAGS += $(shell pkg-config --cflags libuv)
endif
endif

ifeq ("$(PJ_HAS_URIPARSER)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/liburiparser.so)","")
LIBS_yes += -luriparser
endif
endif

ifeq ("$(PJ_HAS_LIBYUAREL)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libyuarel.so)","")
LIBS_yes += -lyuarel
endif
endif

ifeq ("$(PJ_HAS_DBUS)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libdbus-1.so)","")
LIBS_yes += -lexpat -ldbus-1
CFLAGS += -I$(SDK_INC_DIR)/dbus-1.0/dbus -I$(SDK_INC_DIR)/dbus-1.0 -I$(SDK_LIB_DIR)/dbus-1.0/include
else
LIBS_yes += -lexpat -ldbus-1
CFLAGS += $(shell pkg-config --cflags dbus-1)
endif
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
LIBS_yes += -lubus -lblobmsg_json
endif

ifeq ("$(PJ_HAS_GSTREAMER)", "yes")
LIBS_yes += -lgstapp-1.0 -lgstbase-1.0 -lgstreamer-1.0
else ifeq ("$(PJ_HAS_GSTREAMER_SYSROOT)", "yes")
LIBS_yes += -lgstapp-1.0 -lgstbase-1.0 -lgstreamer-1.0
endif

ifeq ("$(PJ_HAS_GLIB_SYSROOT)", "yes")
LIBS_yes += -lgobject-2.0 -lgio-2.0 -lglib-2.0
ifeq ("$(PJ_CROSS)", "")
CFLAGS += $(shell pkg-config --cflags gio-2.0 gio-unix-2.0 glib-2.0)
endif
endif

ifeq ("$(PJ_HAS_OPENSSL)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libssl.so)","")
LIBS_yes += -lssl -lcrypto
endif
endif

LIBS_yes += $(LIBS_CUSTOMER) -lz

