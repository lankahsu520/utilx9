#ifndef PHILIO_DBUS_DEF_H
#define PHILIO_DBUS_DEF_H

//******************************************************************************
// DEST
//******************************************************************************
#define DBUS_DEST_DEMO                            "com.luffanet.www.demo"

//******************************************************************************
// PATH
//******************************************************************************
//path - xbox
#define DBUS_PATH_DBUS_123                        "/com/xbox/dbus_123"
#define DBUS_PATH_DBUS_456                        "/com/xbox/dbus_456"

//******************************************************************************
// METHOD
//******************************************************************************
#define DBUS_METHOD_COMMAND                       "command"

//******************************************************************************
// dbus_demo
//******************************************************************************
// -> dbus_demo
#define DBUS_M_IFAC_DEMO_CMD                      "com.lankahsu520.demo.command" // sync

// dbus_demo => all
#define DBUS_S_IFAC_DEMO                          "com.lankahsu520.signal.demo"
#define DBUS_S_MATCH_DEMO                         "type='signal',interface='com.lankahsu520.signal.demo'"

#define DBUS_METHOD_ECHO                          "echo"

#endif
