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

INSTALL_BIN_DIR = SDK_USR_PREFIX_DIR + 'bin'
INSTALL_ETC_DIR = 'etc'
INSTALL_INC_DIR = SDK_USR_PREFIX_DIR + 'include'
INSTALL_IOD_DIR = INSTALL_IOT_RELATIVE_DIR
INSTALL_LIB_DIR = SDK_USR_PREFIX_DIR + 'lib'
INSTALL_SBIN_DIR = SDK_USR_PREFIX_DIR + 'sbin'
INSTALL_MODULES_DIR = INSTALL_IOT_RELATIVE_DIR + '/modules'

#********************************************************************************
#** INC_DIR_ARY **
#********************************************************************************
INC_DIR_ARY = [ './' ]

if ( SDK_INC_DIR != '' ) and ( run_command('[', '-d', SDK_INC_DIR , ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ SDK_INC_DIR ]
endif

#dependency('dbus-1')
if ( SDK_INC_DIR != '' ) and ( run_command('[', '-d', SDK_INC_DIR + '/dbus-1.0', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ SDK_INC_DIR + '/dbus-1.0' ]
	INC_DIR_ARY += [ SDK_INC_DIR + '/dbus-1.0/dbus' ]
	INC_DIR_ARY += [ SDK_LIB_DIR + '/dbus-1.0/include' ]
	INC_DIR_ARY += [ SDK_INC_DIR + '/apr-1' ]
elif ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/dbus-1.0', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/dbus-1.0' ]
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/lib' + '/dbus-1.0/include' ]
endif

#dependency('glib-2.0')
if ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/glib-2.0', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/glib-2.0' ]
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/lib' + '/glib-2.0/include' ]
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/readline' ]
endif

if ( PKG_CONFIG_SYSROOT_DIR != '' ) and ( run_command('[', '-d', PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apache2', ']', check : false).returncode() == 0 )
	INC_DIR_ARY += [ PKG_CONFIG_SYSROOT_DIR + '/usr/include' + '/apache2' ]
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
endif
#CFLAGS_CUSTOMER += ['-D_GNU_SOURCE' ]

#********************************************************************************
#** LIB_DIR_ARY **
#********************************************************************************
LIB_DIR_ARY = [ ]
if ( SDK_INC_DIR != '' ) and ( run_command('[', '-d', SDK_LIB_DIR , ']', check : false).returncode() == 0 )
	LIB_DIR_ARY += [ SDK_LIB_DIR ]
endif

#********************************************************************************
#** dependency **
#********************************************************************************
if is_variable('LIB_REQUIRE_FULL')
else
	LIB_REQUIRE_FULL=true
endif

# I prefer to use find_library.
# Some libs don't follow pkgconfig.
cc = meson.get_compiler('c')
LIB_ARY = []
LIB_ARY += cc.find_library('utilx9', required : LIB_REQUIRE_FULL)
LIB_ARY += cc.find_library('dbus_handler', dirs: LIB_DIR_ARY, required : false)
#dependency('uci')
LIB_ARY += cc.find_library('uci', required : false)
#dependency('usb-1.0')
LIB_ARY += cc.find_library('usb-1.0', required : LIB_REQUIRE_FULL)
#dependency('bluetooth')
LIB_ARY += cc.find_library('bluetooth', required : false)
#dependency('jansson')
LIB_ARY += cc.find_library('jansson', required : LIB_REQUIRE_FULL)
#dependency('apr-1')
LIB_ARY += cc.find_library('rt', required : LIB_REQUIRE_FULL)
LIB_ARY += cc.find_library('apr-1', required : LIB_REQUIRE_FULL)
LIB_ARY += cc.find_library('aprutil-1', required : LIB_REQUIRE_FULL)
#dependency('mosquitto')
LIB_ARY += cc.find_library('mosquitto', required : LIB_REQUIRE_FULL)
#dependency('xml2')
LIB_ARY += cc.find_library('xml2', required : false)
#dependency('mxml')
LIB_ARY += cc.find_library('mxml', required : false)
#dependency('websockets')
LIB_ARY += cc.find_library('websockets', required : LIB_REQUIRE_FULL)
LIB_ARY += cc.find_library('websockets-evlib_uv', required : LIB_REQUIRE_FULL)
#dependency('curl')
LIB_ARY += cc.find_library('curl', required : LIB_REQUIRE_FULL)
#dependency('ical')
LIB_ARY += cc.find_library('ical', required : false)
#dependency('uv')
LIB_ARY += cc.find_library('uv', required : LIB_REQUIRE_FULL)
#dependency('yuarel')
LIB_ARY += cc.find_library('yuarel', required : LIB_REQUIRE_FULL)
#dependency('expat')
LIB_ARY += cc.find_library('expat', required : LIB_REQUIRE_FULL)
#dependency('dbus-1')
LIB_ARY += cc.find_library('dbus-1', required : LIB_REQUIRE_FULL)
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
#dependency('openssl')
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

#********************************************************************************
#** LIB_GLOBLE (Please put local libs) **
#********************************************************************************
LIB_GLOBLE = []

