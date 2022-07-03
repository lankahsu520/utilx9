ifeq ("$(PJ_HAS_ZWARE)", "yes")
#CFLAGS += -DOS_LINUX -DZIP_V2 -DUSE_OPENSSL -DCONFIG_DEBUG
CFLAGS += -DOS_LINUX
CFLAGS += -I$(SDK_INC_DIR)/zware
endif

ifeq ("$(PJ_HAS_BEEX)", "yes")
ifneq (,$(wildcard $(SDK_LIB_DIR)/libbeex.so))
LIBS_yes += -lbeex
endif
endif

ifeq ("$(PJ_HAS_HORNETX)", "yes")
ifneq (,$(wildcard $(SDK_LIB_DIR)/libhornetx.so))
LIBS_yes += -lhornetx
endif
endif

ifeq ("$(PJ_HAS_HONEYX)", "yes")
ifneq (,$(wildcard $(SDK_LIB_DIR)/libhoneyx.so))
LIBS_yes += -lhoneyx
endif
endif

