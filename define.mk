
CONFIGURED = .configured

define generate_expiration
	@echo "#ifndef __UTIL_EXPIRATION_H__" > util_expiration.h
	@echo "#define __UTIL_EXPIRATION_H__" >> util_expiration.h
	@if [ "$(strip $(1))" = "" ]; then \
		echo "#define UTIL_EX_EXPIRATION_DATE 0" >> util_expiration.h; \
	else \
		echo "#define UTIL_EX_EXPIRATION_DATE $(1)" >> util_expiration.h; \
	fi
	@echo "#endif" >> util_expiration.h
endef

.patched:
	$(PJ_SH_SED) "s|#define LIBUTILX9_VERSION.*|#define LIBUTILX9_VERSION $(LIBUTILX9_VERSION)|g" utilx9.h

ifeq ("$(PJ_HAS_OPENSSL)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_SSL.*|#define UTIL_EX_SSL|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_SSL.*|#undef UTIL_EX_SSL|g" utilx9.h
endif

ifeq ("$(PJ_HAS_JANSSON)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_JSON.*|#define UTIL_EX_JSON|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_JSON.*|#undef UTIL_EX_JSON|g" utilx9.h
endif

ifeq ("$(PJ_HAS_CURL)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_CURL.*|#define UTIL_EX_CURL|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_CURL.*|#undef UTIL_EX_CURL|g" utilx9.h
endif

ifeq ("$(PJ_HAS_MXML)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_MXML.*|#define UTIL_EX_MXML|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_MXML.*|#undef UTIL_EX_MXML|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBSSH)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_SSH.*|#define UTIL_EX_SSH|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_SSH.*|#undef UTIL_EX_SSH|g" utilx9.h
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_SWCONFIG.*|#define UTIL_EX_SWCONFIG|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_SWCONFIG.*|#undef UTIL_EX_SWCONFIG|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_UV.*|#define UTIL_EX_UV|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_UV.*|#undef UTIL_EX_UV|g" utilx9.h
endif

ifeq ("$(PJ_HAS_DBUS)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_DBUS.*|#define UTIL_EX_DBUS|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_DBUS.*|#undef UTIL_EX_DBUS|g" utilx9.h
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_UBUS.*|#define UTIL_EX_UBUS|g" ubus_ex.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_UBUS.*|#undef UTIL_EX_UBUS|g" ubus_ex.h
endif

ifeq ("$(PJ_HAS_LIBUSB)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_USB.*|#define UTIL_EX_USB|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_USB.*|#undef UTIL_EX_USB|g" utilx9.h
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_UCI.*|#define UTIL_EX_UCI|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_UCI.*|#undef UTIL_EX_UCI|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBUBOX)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_UBOX.*|#define UTIL_EX_UBOX|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_UBOX.*|#undef UTIL_EX_UBOX|g" utilx9.h
endif

ifeq ("$(PJ_HAS_FASTCGI)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_FASTCGI.*|#define UTIL_EX_FASTCGI|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_FASTCGI.*|#undef UTIL_EX_FASTCGI|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBYUAREL)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_YUAREL.*|#define UTIL_EX_YUAREL|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_YUAREL.*|#undef UTIL_EX_YUAREL|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBWEBSOCKETS)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_WEBSOCKETS.*|#define UTIL_EX_WEBSOCKETS|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_WEBSOCKETS.*|#undef UTIL_EX_WEBSOCKETS|g" utilx9.h
endif

ifeq ("$(PJ_HAS_MOSQUITTO)", "yes")
	$(PJ_SH_SED) "s|#undef UTIL_EX_MQTT.*|#define UTIL_EX_MQTT|g" utilx9.h
else
	$(PJ_SH_SED) "s|#define UTIL_EX_MQTT.*|#undef UTIL_EX_MQTT|g" utilx9.h
endif
	touch $@

.configured: .patched
	$(call generate_expiration, $(PJ_EXPIRATION_DATE))

	[ -f $(CONFIG_CUSTOMER) ] || ($(PJ_SH_CUSTOMER2DEF); touch .customer; )
	[ -f $(SDK_CONFIG_CUSTOMER_DEF_H) ] || ($(PJ_SH_MKDIR) $(SDK_INC_DIR); $(PJ_SH_CP) include/* $(SDK_INC_DIR); )

	touch $@

.PHONY: expired
expired:
	$(call generate_expiration, $(shell date -d "+4 years" "+%s"))

.PHONY: target_install
target_install:
ifneq "$(wildcard $(HOMEX_ROOT_DIR) )" ""
ifneq ("$(PJ_INSTALL_TARGET)", "")
	$(PJ_SH_MKDIR) $(PJ_INSTALL_TARGET)
	(cd $(PJ_INSTALL_TARGET); $(PJ_SH_RMDIR) *)
	$(PJ_SH_CP) $(HOMEX_ROOT_DIR)/* $(PJ_INSTALL_TARGET)
endif
endif