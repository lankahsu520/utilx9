ifeq ($(PJ_HAS_PHILIO_SDK_V2),y)
LIBS_yes += -lsdk -lapp
endif

ifeq ("$(PJ_HAS_LOGCAT)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/liblogcat.a)","")
LIBS_$(PJ_HAS_STATIC_LIB) += $(SDK_LIB_DIR)/liblogcat.a
endif
ifneq ("$(wildcard $(SDK_LIB_DIR)/liblogcat.so)","")
LIBS_$(PJ_HAS_SHARE_LIB) += -llogcat
endif
ifneq (,$(wildcard $(SDK_INC_DIR)/logcat_api.h))
CFLAGS += -include $(SDK_INC_DIR)/logcat_api.h
endif
endif

ifeq ("$(PJ_HAS_TIMEZONE)", "yes")
ifneq ("$(wildcard $(SDK_LIB_DIR)/libtimezone.a)","")
LIBS_$(PJ_HAS_STATIC_LIB) += $(SDK_LIB_DIR)/libtimezone.a
endif
ifneq ("$(wildcard $(SDK_LIB_DIR)/libtimezone.so)","")
LIBS_$(PJ_HAS_SHARE_LIB) += -ltimezone
endif
ifneq ("$(wildcard $(SDK_INC_DIR)/timezone_api.h)","")
CFLAGS += -include $(SDK_INC_DIR)/timezone_api.h
endif
endif

include $(PJ_MK_USER_LIB_MCTT)
include $(PJ_MK_USER_LIB_PUB)

include $(PJ_MK_REVISION)
include $(PJ_MK_MESON)