#********************************************************************************
#** Built-in options **
#********************************************************************************
message('>> (prefix: @0@)'.format( get_option('prefix') ))
message('>> (bindir: @0@)'.format( get_option('bindir') ))
message('>> (datadir: @0@)'.format( get_option('datadir') ))
message('>> (includedir: @0@)'.format( get_option('includedir') ))
message('>> (infodir: @0@)'.format( get_option('infodir') ))
message('>> (libdir: @0@)'.format( get_option('libdir') ))
message('>> (libexecdir: @0@)'.format( get_option('libexecdir') ))
message('>> (localedir: @0@)'.format( get_option('localedir') ))
message('>> (localstatedir: @0@)'.format( get_option('localstatedir') ))
message('>> (mandir: @0@)'.format( get_option('mandir') ))
message('>> (sbindir: @0@)'.format( get_option('sbindir') ))
message('>> (sharedstatedir: @0@)'.format( get_option('sharedstatedir') ))
message('>> (sysconfdir: @0@)'.format( get_option('sysconfdir') ))

#********************************************************************************
#** get_option (meson_options.txt) **
#********************************************************************************
# https://mesonbuild.com/Builtin-options.html
PJ_ROOT = meson.source_root()#get_option('PJ_ROOT')
PJ_REVISION = get_option('PJ_REVISION')
PKG_CONFIG_SYSROOT_DIR = get_option('PKG_CONFIG_SYSROOT_DIR')

#** INSTALL **
#SDK_BIN_DIR = get_option('SDK_BIN_DIR')
#SDK_ETC_DIR = get_option('SDK_ETC_DIR')
SDK_INC_DIR = get_option('SDK_INC_DIR')
#SDK_IOT_DIR = get_option('SDK_IOT_DIR')
SDK_LIB_DIR = get_option('SDK_LIB_DIR')
SDK_ROOT_DIR = get_option('SDK_ROOT_DIR')
#SDK_SBIN_DIR = get_option('SDK_SBIN_DIR')
SDK_USR_PREFIX_DIR = get_option('SDK_USR_PREFIX_DIR')

INSTALL_IOT_DIR = get_option('PJ_INSTALL_IOT')
INSTALL_IOT_RELATIVE_DIR = get_option('PJ_INSTALL_IOT_RELATIVE')

INSTALL_BIN_DIR = SDK_USR_PREFIX_DIR + '/bin'
INSTALL_ETC_DIR = 'etc'
INSTALL_INC_DIR = SDK_USR_PREFIX_DIR + '/include'
INSTALL_LIB_DIR = SDK_USR_PREFIX_DIR + '/lib'
INSTALL_SBIN_DIR = SDK_USR_PREFIX_DIR + '/sbin'
INSTALL_MODULES_DIR = INSTALL_IOT_RELATIVE_DIR + '/modules'

#********************************************************************************
#** INC_DIR_ARY **
#********************************************************************************
INC_DIR_ARY = [ './' ]

if ( SDK_INC_DIR != '' ) and ( run_command('[', '-d', SDK_INC_DIR , ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ SDK_INC_DIR ]
endif

if ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apache2', ']', check : false).returncode() == 0 )
	found_apache2 = 1
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apache2' ]
else
	found_apache2 = 0
endif

#********************************************************************************
#** CFLAGS_CUSTOMER **
#********************************************************************************
CFLAGS_CUSTOMER = []
if ( SDK_INC_DIR != '' ) and ( run_command('[', '-f', SDK_INC_DIR + '/customer_def.h', ']', check : false).returncode() == 0 )
	CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/customer_def.h' ]
	CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/dbus_def.h' ]
	CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/json_def.h' ]
	CFLAGS_CUSTOMER += ['-include', SDK_INC_DIR + '/query_def.h' ]
elif ( SDK_INC_DIR != '' ) and ( run_command('[', '-f', PJ_ROOT + '/include/customer_def.h', ']', check : false).returncode() == 0 )
	CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/customer_def.h' ]
	CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/dbus_def.h' ]
	CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/json_def.h' ]
	CFLAGS_CUSTOMER += ['-include', PJ_ROOT + '/include/query_def.h' ]
elif ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-f', PKG_CONFIG_SYSROOT_DIR + '/usr/include/customer_def.h', ']', check : false).returncode() == 0 )
	CFLAGS_CUSTOMER += ['-include', PKG_CONFIG_SYSROOT_DIR + '/usr/include/customer_def.h' ]
	CFLAGS_CUSTOMER += ['-include', PKG_CONFIG_SYSROOT_DIR + '/usr/include/dbus_def.h' ]
	CFLAGS_CUSTOMER += ['-include', PKG_CONFIG_SYSROOT_DIR + '/usr/include/json_def.h' ]
	CFLAGS_CUSTOMER += ['-include', PKG_CONFIG_SYSROOT_DIR + '/usr/include/query_def.h' ]
endif
#CFLAGS_CUSTOMER += ['-D_GNU_SOURCE' ]

#********************************************************************************
#** LIB_DIR_ARY **
#********************************************************************************
LIB_DIR_ARY = [ ]
if ( SDK_LIB_DIR != '' ) and ( run_command('[', '-d', SDK_LIB_DIR , ']', check : false).returncode() == 0 )
	LIB_DIR_ARY += [ SDK_LIB_DIR ]
endif

if ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/lib', ']', check : false).returncode() == 0 )
	LIB_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/lib' ]
endif

#********************************************************************************
#** dependency **
#********************************************************************************
if is_variable('LIB_REQUIRE_FULL')
else
	LIB_REQUIRE_FULL=false
endif

# I prefer to use find_library.
# Some libs don't follow pkgconfig.
cc = meson.get_compiler('c')
LIB_ARY = []

#dependency('yuarel')
dep_yuarel = cc.find_library('yuarel', required : false)
LIB_ARY += dep_yuarel

dep_utilx9 = cc.find_library('utilx9', required : false)
LIB_ARY += dep_utilx9

dep_dbus_handler = cc.find_library('dbus_handler', dirs: LIB_DIR_ARY, required : false)
LIB_ARY += dep_dbus_handler

#dependency('uci')
dep_uci = cc.find_library('uci', required : false)
LIB_ARY += dep_uci

#dependency('usb-1.0')
dep_usb = cc.find_library('usb-1.0', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_usb

#dependency('bluetooth')
dep_bluetooth = cc.find_library('bluetooth', required : false)
LIB_ARY += dep_bluetooth

#dependency('jansson')
dep_jansson = cc.find_library('jansson', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_jansson

#dependency('apr-1')
dep_rt = cc.find_library('rt', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_rt

dep_apr = cc.find_library('apr-1', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_apr

if ( SDK_INC_DIR != '' ) and ( run_command('[', '-d', SDK_INC_DIR + '/apr-1', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ SDK_INC_DIR + '/apr-1' ]
elif ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apr-1', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apr-1' ]
endif

dep_aprutil = cc.find_library('aprutil-1', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_aprutil

#dependency('mosquitto')
dep_mosquitto = cc.find_library('mosquitto', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_mosquitto

#dependency('xml2')
dep_xml2 = cc.find_library('xml2', required : false)
LIB_ARY += dep_xml2

#dependency('mxml')
dep_mxml = cc.find_library('mxml', required : false)
LIB_ARY += dep_mxml

#dependency('websockets')
dep_websockets = cc.find_library('websockets', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_websockets
dep_websockets_uv = cc.find_library('websockets-evlib_uv', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_websockets_uv

#dependency('sqlite')
dep_sqlite = cc.find_library('sqlite3', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_sqlite

#dependency('curl')
dep_curl = cc.find_library('curl', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_curl

#dependency('ical')
dep_ical = cc.find_library('ical', required : false)
LIB_ARY += dep_ical

#dependency('uv')
dep_uv = cc.find_library('uv', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_uv

#dependency('expat')
dep_expat = cc.find_library('expat', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_expat

#dependency('dbus-1')
dep_dbus = cc.find_library('dbus-1', required : LIB_REQUIRE_FULL)
LIB_ARY += dep_dbus

if ( SDK_INC_DIR != '' ) and ( run_command('[', '-d', SDK_INC_DIR + '/dbus-1.0', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ SDK_INC_DIR + '/dbus-1.0' ]
	INC_DIR_ARY += [ SDK_INC_DIR + '/dbus-1.0/dbus' ]
	INC_DIR_ARY += [ SDK_LIB_DIR + '/dbus-1.0/include' ]
elif ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/dbus-1.0', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/dbus-1.0' ]
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/lib' + '/dbus-1.0/include' ]
endif

#dependency('ubus')
dep_ubus = cc.find_library('ubus', required : false)
LIB_ARY += dep_ubus

#dependency('blobmsg_json')
dep_blobmsg_json = cc.find_library('blobmsg_json', required : false)
LIB_ARY += dep_blobmsg_json

#dependency('gobject-2.0')
dep_gobject = cc.find_library('gobject-2.0', required : false)
LIB_ARY += dep_gobject

#dependency('gio-2.0')
dep_gio = cc.find_library('gio-2.0', required : false)
LIB_ARY += dep_gio

#dependency('glib-2.0')
dep_glib = cc.find_library('glib-2.0', required : false)
LIB_ARY += dep_glib

if ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/glib-2.0', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/glib-2.0' ]
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/lib' + '/glib-2.0/include' ]
endif

#dependency('readline')
dep_readline = cc.find_library('readline', required : false)
LIB_ARY += dep_readline

if ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/readline', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/readline' ]
endif

#dependency('ncurses')
dep_ncurses = cc.find_library('ncurses', required : false)
LIB_ARY += dep_ncurses

#dependency('openssl')
dep_openssl = cc.find_library('ssl', required : true)
LIB_ARY += dep_openssl

dep_crypto = cc.find_library('crypto', required : true)
LIB_ARY += dep_crypto

#dependency('z')
dep_z = cc.find_library('z', required : true)
LIB_ARY += dep_z

#dependency('dl')
dep_dl = cc.find_library('dl', required : true)
LIB_ARY += dep_dl

#dependency('pthread')
dep_pthread = cc.find_library('pthread', required : true)
LIB_ARY += dep_pthread

#dependency('m')
dep_m = cc.find_library('m', required : true)
LIB_ARY += dep_m

#********************************************************************************
#** LIB_GLOBLE (Please put local libs) **
#********************************************************************************
LIB_GLOBLE = []

