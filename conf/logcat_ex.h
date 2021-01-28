#ifndef __LOGCAT_EX_H__
#define __LOGCAT_EX_H__

#if defined(UTIL_EX_DBG) && defined(__LOGCAT_API_H__)
#define LOGE_EX(LOG_TAG, fmt, args...) \
	LOGE(LOG_TAG, fmt"\n", ## args); \
	DBG_ER_LN(fmt, ## args);
#define LOGW_EX(LOG_TAG, fmt, args...) \
	LOGW(LOG_TAG, fmt"\n", ## args); \
	DBG_WN_LN(fmt, ## args);
#define LOGI_EX(LOG_TAG, fmt, args...) \
	LOGI(LOG_TAG, fmt"\n", ## args); \
	DBG_IF_LN(fmt, ## args);
#define LOGD_EX(LOG_TAG, fmt, args...) \
	LOGD(LOG_TAG, fmt"\n", ## args); \
	DBG_DB_LN(fmt, ## args);
#define LOGV_EX(LOG_TAG, fmt, args...) \
	LOGV(LOG_TAG, fmt"\n", ## args); \
	DBG_TR_LN(fmt, ## args);

#elif defined(UTIL_EX_DBG)
#define LOGE_EX(LOG_TAG,fmt,args...) DBG_ER_LN(fmt, ## args)
#define LOGW_EX(LOG_TAG,fmt,args...) DBG_WN_LN(fmt, ## args)
#define LOGI_EX(LOG_TAG,fmt,args...) DBG_IF_LN(fmt, ## args)
#define LOGD_EX(LOG_TAG,fmt,args...) DBG_DB_LN(fmt, ## args)
#define LOGV_EX(LOG_TAG,fmt,args...) DBG_TR_LN(fmt, ## args)

#elif defined(__LOGCAT_API_H__)
#define LOGE_EX(LOG_TAG,fmt,args...) LOGE(LOG_TAG, fmt"\n", ## args)
#define LOGW_EX(LOG_TAG,fmt,args...) LOGW(LOG_TAG, fmt"\n", ## args)
#define LOGI_EX(LOG_TAG,fmt,args...) LOGI(LOG_TAG, fmt"\n", ## args)
#define LOGD_EX(LOG_TAG,fmt,args...) LOGD(LOG_TAG, fmt"\n", ## args)
#define LOGV_EX(LOG_TAG,fmt,args...) LOGV(LOG_TAG, fmt"\n", ## args)

#else
#define LOGE_EX(LOG_TAG,fmt,args...)
#define LOGW_EX(LOG_TAG,fmt,args...)
#define LOGI_EX(LOG_TAG,fmt,args...)
#define LOGD_EX(LOG_TAG,fmt,args...)
#define LOGV_EX(LOG_TAG,fmt,args...)
#endif

#define FUNC_ENTRY LOGV_EX(TAG, "enter %s", __func__)
#define FUNC_LEAVE LOGV_EX(TAG, "leave %s", __func__)

#define MYLOG(x)

#define DBG_DBUS_ERR(x) LOGE_EX(TAG,"%s (dest: %s, ifac: %s, cmd: %s)", x, dest, ifac, cmd);
#define DBG_DBUS_ERR_ARG(x) LOGE_EX(TAG,"%s (dest: %s, ifac: %s, cmd: %s, arg_str: %s)", x, dest, ifac, cmd, arg_str);

#endif
