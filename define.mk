
define generate_expiration
	@echo "#ifndef __UTIL_EXPIRATION_H__" > util_expiration.h
	@echo "#define __UTIL_EXPIRATION_H__" >> util_expiration.h
	@if [ "$(strip $(1))" = "" ]; then \
		echo "#define UTIL_EX_EXPIRATION_DATE 0" >> util_expiration.h; \
	else \
		echo "#define UTIL_EX_EXPIRATION_DATE $(1)" >> util_expiration.h; \
	fi
	@echo "#endif" >> util_expiration.h

	mkdir -p conf
	[ -f $(CONFIG_AUTOCONF_H) ] && cp -avf $(CONFIG_AUTOCONF_H) conf/autoconf_def.h
	#[ -f $(CONFIG_CONFIG) ] && cp -avf $(CONFIG_CONFIG) conf/
	[ -f $(CONFIG_CUSTOMER_H) ] && cp -avf $(CONFIG_CUSTOMER_H) conf/
	[ -f $(CONFIG_CUSTOMER) ] && cp -avf $(CONFIG_CUSTOMER) conf/
	cp -avf $(PJ_ROOT)/include/* conf/
endef

.configured:
	$(call generate_expiration, $(PJ_EXPIRATION_DATE))

ifeq ("$(PJ_HAS_OPENSSL)", "yes")
	sed -i "s|#undef UTIL_EX_SSL.*|#define UTIL_EX_SSL|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_SSL.*|#undef UTIL_EX_SSL|g" utilx9.h
endif

ifeq ("$(PJ_HAS_JANSSON)", "yes")
	sed -i "s|#undef UTIL_EX_JSON.*|#define UTIL_EX_JSON|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_JSON.*|#undef UTIL_EX_JSON|g" utilx9.h
endif

ifeq ("$(PJ_HAS_CURL)", "yes")
	sed -i "s|#undef UTIL_EX_CURL.*|#define UTIL_EX_CURL|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_CURL.*|#undef UTIL_EX_CURL|g" utilx9.h
endif

ifeq ("$(PJ_HAS_MXML)", "yes")
	sed -i "s|#undef UTIL_EX_MXML.*|#define UTIL_EX_MXML|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_MXML.*|#undef UTIL_EX_MXML|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBSSH)", "yes")
	sed -i "s|#undef UTIL_EX_SSH.*|#define UTIL_EX_SSH|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_SSH.*|#undef UTIL_EX_SSH|g" utilx9.h
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
	sed -i "s|#undef UTIL_EX_SWCONFIG.*|#define UTIL_EX_SWCONFIG|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_SWCONFIG.*|#undef UTIL_EX_SWCONFIG|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
	sed -i "s|#undef UTIL_EX_UV.*|#define UTIL_EX_UV|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_UV.*|#undef UTIL_EX_UV|g" utilx9.h
endif

ifeq ("$(PJ_HAS_DBUS)", "yes")
	sed -i "s|#undef UTIL_EX_DBUS.*|#define UTIL_EX_DBUS|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_DBUS.*|#undef UTIL_EX_DBUS|g" utilx9.h
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
	sed -i "s|#undef UTIL_EX_UBUS.*|#define UTIL_EX_UBUS|g" ubus_ex.h
else
	sed -i "s|#define UTIL_EX_UBUS.*|#undef UTIL_EX_UBUS|g" ubus_ex.h
endif

ifeq ("$(PJ_HAS_LIBUSB)", "yes")
	sed -i "s|#undef UTIL_EX_USB.*|#define UTIL_EX_USB|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_USB.*|#undef UTIL_EX_USB|g" utilx9.h
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
	sed -i "s|#undef UTIL_EX_UCI.*|#define UTIL_EX_UCI|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_UCI.*|#undef UTIL_EX_UCI|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBUBOX)", "yes")
	sed -i "s|#undef UTIL_EX_UBOX.*|#define UTIL_EX_UBOX|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_UBOX.*|#undef UTIL_EX_UBOX|g" utilx9.h
endif

ifeq ("$(PJ_HAS_FASTCGI)", "yes")
	sed -i "s|#undef UTIL_EX_FASTCGI.*|#define UTIL_EX_FASTCGI|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_FASTCGI.*|#undef UTIL_EX_FASTCGI|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBYUAREL)", "yes")
	sed -i "s|#undef UTIL_EX_YUAREL.*|#define UTIL_EX_YUAREL|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_YUAREL.*|#undef UTIL_EX_YUAREL|g" utilx9.h
endif

ifeq ("$(PJ_HAS_LIBWEBSOCKETS)", "yes")
	sed -i "s|#undef UTIL_EX_WEBSOCKETS.*|#define UTIL_EX_WEBSOCKETS|g" utilx9.h
else
	sed -i "s|#define UTIL_EX_WEBSOCKETS.*|#undef UTIL_EX_WEBSOCKETS|g" utilx9.h
endif

	touch $@