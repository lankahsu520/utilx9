#** ROOT **
PJ_ROOT = get_option('PJ_ROOT')
PJ_REVISION = get_option('PJ_REVISION')
PKG_CONFIG_SYSROOT_DIR = get_option('PKG_CONFIG_SYSROOT_DIR')

#** INSTALL **
#SDK_BIN_DIR = get_option('SDK_BIN_DIR')
#SDK_ETC_DIR = get_option('SDK_ETC_DIR')
SDK_INC_DIR = get_option('SDK_INC_DIR')
#SDK_IOT_DIR = get_option('SDK_IOT_DIR')
SDK_LIB_DIR = get_option('SDK_LIB_DIR')
#SDK_ROOT_DIR = get_option('SDK_ROOT_DIR')
#SDK_SBIN_DIR = get_option('SDK_SBIN_DIR')
SDK_USR_PREFIX_DIR = get_option('SDK_USR_PREFIX_DIR')

INSTALL_IOT_DIR = get_option('PJ_INSTALL_IOT')
INSTALL_IOT_RELATIVE_DIR = get_option('PJ_INSTALL_IOT_RELATIVE')

INSTALL_BIN_DIR = SDK_USR_PREFIX_DIR + 'bin'
INSTALL_ETC_DIR = 'etc'
INSTALL_INC_DIR = SDK_USR_PREFIX_DIR + 'include'
INSTALL_IOD_DIR = INSTALL_IOT_RELATIVE_DIR
INSTALL_LIB_DIR = SDK_USR_PREFIX_DIR + 'lib'
INSTALL_SBIN_DIR = SDK_USR_PREFIX_DIR + 'sbin'
INSTALL_MODULES_DIR = INSTALL_IOT_RELATIVE_DIR + '/modules'

#** CFLAGS & LDFLAGS **
INC_DIR_ARY = [ './' ]
INC_DIR_ARY += [ SDK_INC_DIR ]
#dependency('dbus-1')
if run_command('[', '-d', SDK_INC_DIR + '/dbus-1.0', ']').returncode() == 0
INC_DIR_ARY += [ SDK_INC_DIR + '/dbus-1.0' ]
INC_DIR_ARY += [ SDK_INC_DIR + '/dbus-1.0/dbus' ]
INC_DIR_ARY += [ SDK_LIB_DIR + '/dbus-1.0/include' ]
INC_DIR_ARY += [ SDK_INC_DIR + '/apr-1' ]
elif run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/dbus-1.0', ']').returncode() == 0
INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/dbus-1.0' ]
INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/lib' + '/dbus-1.0/include' ]
INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apache2' ]
endif

CFLAGS_CUSTOMER = []
if run_command('[', '-f', SDK_INC_DIR + '/customer_def.h', ']').returncode() == 0
CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/customer_def.h' ]
CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/dbus_def.h' ]
CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/json_def.h' ]
CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/query_def.h' ]
elif run_command('[', '-f', PJ_ROOT + '/include/customer_def.h', ']').returncode() == 0
CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/customer_def.h' ]
CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/dbus_def.h' ]
CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/json_def.h' ]
CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/query_def.h' ]
endif
#CFLAGS_CUSTOMER += ['-D_GNU_SOURCE' ]


#** dependency **
cc = meson.get_compiler('c')
LIB_ARY = []
LIB_ARY += cc.find_library('utilx9', required : true)
LIB_ARY += cc.find_library('dbus_handler', dirs: [ SDK_LIB_DIR ], required : false)
#dependency('uci')
LIB_ARY += cc.find_library('uci', required : false)
#dependency('usb-1.0')
LIB_ARY += cc.find_library('usb-1.0', required : true)
#dependency('bluetooth')
LIB_ARY += cc.find_library('bluetooth', required : false)
#dependency('jansson')
LIB_ARY += cc.find_library('jansson', required : true)
#dependency('apr-1')
LIB_ARY += cc.find_library('rt', required : true)
LIB_ARY += cc.find_library('apr-1', required : true)
LIB_ARY += cc.find_library('aprutil-1', required : true)
#dependency('mosquitto')
LIB_ARY += cc.find_library('mosquitto', required : true)
#dependency('xml2')
LIB_ARY += cc.find_library('xml2', required : false)
#dependency('mxml')
LIB_ARY += cc.find_library('mxml', required : false)
#dependency('websockets')
LIB_ARY += cc.find_library('websockets', required : true)
LIB_ARY += cc.find_library('websockets-evlib_uv', required : true)
#dependency('curl')
LIB_ARY += cc.find_library('curl', required : true)
#dependency('ical')
LIB_ARY += cc.find_library('ical', required : false)
#dependency('uv')
LIB_ARY += cc.find_library('uv', required : true)
#dependency('yuarel')
LIB_ARY += cc.find_library('yuarel', required : true)
#dependency('expat')
LIB_ARY += cc.find_library('expat', required : true)
#dependency('dbus-1')
LIB_ARY += cc.find_library('dbus-1', required : true)
#dependency('ubus')
LIB_ARY += cc.find_library('ubus', required : false)
#dependency('blobmsg_json')
LIB_ARY += cc.find_library('blobmsg_json', required : false)
#dependency('gobject-2.0')
LIB_ARY += cc.find_library('gobject-2.0', required : false)
#dependency('gio-2.0')
LIB_ARY += cc.find_library('gio-2.0', required : false)
#dependency('glib-2.0')
LIB_ARY += cc.find_library('glib-2.0', required : false)
#dependency('readline')
LIB_ARY += cc.find_library('readline', required : false)
#dependency('ncurses')
LIB_ARY += cc.find_library('ncurses', required : false)
#dependency('ssl')
LIB_ARY += cc.find_library('ssl', required : true)
LIB_ARY += cc.find_library('crypto', required : true)
#dependency('z')
LIB_ARY += cc.find_library('z', required : true)
#dependency('dl')
LIB_ARY += cc.find_library('dl', required : true)
#dependency('pthread')
LIB_ARY += cc.find_library('pthread', required : true)
#dependency('m')
LIB_ARY += cc.find_library('m', required : true)

LIB_GLOBLE = []
