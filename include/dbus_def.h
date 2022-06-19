#ifndef __DBUS_DEF_H__
#define __DBUS_DEF_H__


#define TIMEOUT_OF_DBUS_REPLY                     5000


//******************************************************************************
// DEST
//******************************************************************************


//******************************************************************************
// PATH
//******************************************************************************


//******************************************************************************
// dbus_demo
//******************************************************************************
#define DBUS_DEST_DEMO                            "com.github.lankahsu520.demo"
#define DBUS_PATH_DEMO                            "/com/github/lankahsu520/demo"

// -> dbus_demo
#define DBUS_M_IFAC_DBUS_DEMO                     "com.github.lankahsu520.dbus_demo" // sync

#define DBUS_METHOD_COMMAND                       "command"

// dbus_demo => all
#define DBUS_S_IFAC_DBUS_DEMO                     "com.github.lankahsu520.dbus_demo"
#define DBUS_S_MATCH_DBUS_DEMO                    "type='signal',interface='com.github.lankahsu520.dbus_demo'"

#define DBUS_S_NAME_COMMAND                       "command"
#define DBUS_S_NAME_ECHO                          "echo"


#endif
