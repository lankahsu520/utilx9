#ifndef __DBUS_DEF_H__
#define __DBUS_DEF_H__


#define TIMEOUT_OF_DBUS_REPLY 5000


//******************************************************************************
// Baresip
//******************************************************************************
#define DBUS_DEST_BARESIP "com.github.Baresip"

// -> Baresip
#define DBUS_M_IFAC_BARESIP_CMD "com.github.Baresip" // sync

// Baresip => all
#define DBUS_S_IFAC_BARESIP "com.github.Baresip"
#define DBUS_S_MATCH_BARESIP "type='signal',interface='com.github.Baresip'"

#define DBUS_S_NAME_EVENT "event"
#define DBUS_S_NAME_MESSAGE "message"


//******************************************************************************
// demo
//******************************************************************************
#define DBUS_DEST_LANKAHSU520 "com.github.lankahsu520"
#define DBUS_PATH_LANKAHSU520 "/com/github/lankahsu520"

// -> demo
#define DBUS_M_IFAC_LANKAHSU520_DEMO "com.github.lankahsu520.demo" // sync

#define DBUS_METHOD_COMMAND "command"

// demo => all
#define DBUS_S_IFAC_LANKAHSU520_DEMO "com.github.lankahsu520.demo"
#define DBUS_S_MATCH_LANKAHSU520_DEMO "type='signal',interface='com.github.lankahsu520.demo'"

#define DBUS_S_NAME_COMMAND "command"
#define DBUS_S_NAME_ECHO "echo"


#endif
