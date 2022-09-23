ifeq ($(PJ_HAS_PHILIO_SDK_V2),y)
LIBS_yes += -lsdk -lapp
endif

ifeq ("$(PJ_HAS_LOGCAT)", "yes")
LIBS_yes += -llogcat
ifneq (,$(wildcard $(SDK_INC_DIR)/logcat_api.h))
CFLAGS += -include $(SDK_INC_DIR)/logcat_api.h
endif
endif

ifeq ("$(PJ_HAS_TIMEZONE)", "yes")
LIBS_yes += -ltimezone
ifneq ("$(wildcard $(SDK_INC_DIR)/timezone_api.h)","")
CFLAGS += -include $(SDK_INC_DIR)/timezone_api.h
endif
endif

include $(PJ_MK_USER_LIB_MCTT)
include $(PJ_MK_USER_LIB_PUB)

include $(PJ_MK_REVISION)
include $(PJ_MK_MESON)