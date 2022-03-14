#ifndef __DBUS_DEF_H__
#define __DBUS_DEF_H__


#define TIMEOUT_OF_DBUS_REPLY                     5000


//******************************************************************************
// DEST
//******************************************************************************
#define DBUS_DEST_DEMO                            "com.lankahsu520.www.demo"

//******************************************************************************
// PATH
//******************************************************************************
//path - xbox
#define DBUS_PATH_DBUS_123                        "/com/xbox/dbus_123"
#define DBUS_PATH_DBUS_456                        "/com/xbox/dbus_456"

//******************************************************************************
// dbus_demo
//******************************************************************************
// -> dbus_demo
#define DBUS_M_IFAC_DBUS_DEMO                     "com.lankahsu520.www.dbus_demo" // sync

#define DBUS_METHOD_COMMAND                       "command"

// dbus_demo => all
#define DBUS_S_IFAC_DBUS_DEMO                     "com.lankahsu520.www.dbus_demo"
#define DBUS_S_MATCH_DBUS_DEMO                    "type='signal',interface='com.lankahsu520.www.dbus_demo'"

#define DBUS_S_NAME_COMMAND                       "command"
#define DBUS_S_NAME_ECHO                          "echo"


#endif
