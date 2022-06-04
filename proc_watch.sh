#!/bin/sh

HINT="$0 {start|stop|restart|status|debug|trigger|logger|clean} iface"
ROOTFS_PATH="/work/rootfs"
ROOTFS_PATH_ARG=""
PWD=`pwd`
SBIN_PATH="$ROOTFS_PATH/sbin"
[ -d "$SBIN_PATH" ] || SBIN_PATH="/sbin"
[ -x "/usr/bin/sudo" ] && SUDO_B="sudo -E -b" && SUDO="sudo -E"
[ -x "/usr/bin/whoami" ] && WHO=`whoami`
[ ! -z "$WHO" ] || WHO="admin"
export DBUS_SYSTEM_BUS_ADDRESS=""
[ ! -z "$DBUS_SYSTEM_BUS_ADDRESS" ] || unset DBUS_SYSTEM_BUS_ADDRESS

ACTION=$1

RUN_SH=`basename $0`
DAEMON="proc_watch"
[ -z "$DAEMON" ] || BIN_FILE="./$DAEMON"
[ -z "$BIN_FILE" ] || [ -x "$BIN_FILE" ] || [ "$PWD" = "/" ] || BIN_FILE="$PWD/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [ -x "$BIN_FILE" ] || BIN_FILE="/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [ -x "$BIN_FILE" ] || BIN_FILE="/usr/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [ -x "$BIN_FILE" ] || BIN_FILE="$ROOTFS_PATH/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [ -x "$BIN_FILE" ] || BIN_FILE="$ROOTFS_PATH/usr/bin/$DAEMON"
KILL_EX="$SUDO kill"
KILLALL_EX="$SUDO killall"
[ -z "$DAEMON" ] || PID=$(pidof $DAEMON)

IOT_PATH="/work/rootfs/IoT"
SAVE_PATH="/work/IoT"
SAVE_PATH_ARG=""
WORK_PATH="/tmp/IoT"
WORK_PATH_ARG=""
GROUP_NAME="xxx"
CFG_PATH=""
CFG_PATH_ARG=""
CFG_FILE=""
CFG_FILE_ARG=""
DEBUG="2"
DEBUG_ARG=""
LOG=""
LOG_ARG="2>&1"
[ "$LOG" != "" ] && LOG_ARG=">>$LOG 2>&1"
TEE_ARG="2>&1"
[ "$LOG" != "" ] && TEE_ARG="| tee -a $LOG"
LOGGER_TAG="$DAEMON"
LOGGER="logger"
LOGGER_ARG=""
ECHO="0"

INTERACTIVE=""

IFACE=$2
[ ! -z "$IFACE" ] || IFACE="enp0s8"
IFACE_ARG=""

die_fn()
{
	echo $@
	exit 1
}

bin_check_fn()
{
	[ -z "$DAEMON" ] || [ -z "$BIN_FILE" ] || [ -x "$BIN_FILE" ] || { die_fn "$BIN_FILE isn't found !!!";}

	return 0
}

runpid_fn()
{
	[ -z "$DAEMON" ] || PID=$(pidof $DAEMON)

	return 0
}

init_fn()
{
	return 0
}

clean_fn()
{
	echo "$RUN_SH ($PID) clean_fn ... "

	return 0
}

cfg_fn()
{
	return 0
}

arguments_fn()
{
	[ -z $ROOTFS_PATH ] || [ -d "$ROOTFS_PATH" ] || { die_fn "Please create ROOTFS_PATH($ROOTFS_PATH) first !!!";}
	#[ "$ROOTFS_PATH" != "" ] && ROOTFS_PATH_ARG="-r $ROOTFS_PATH"

	[ -z $SAVE_PATH ] || [ -d "$SAVE_PATH" ] || { die_fn "Please create SAVE_PATH($SAVE_PATH) first !!!";}
	#[ "$SAVE_PATH" != "" ] && SAVE_PATH_ARG="-s $SAVE_PATH"

	[ -z $CFG_PATH ] || [ -d "$CFG_PATH" ] || { die_fn "Please create CFG_PATH($CFG_PATH) first !!!";}
	#[ "$CFG_PATH" != "" ] && CFG_PATH_ARG="-f $CFG_PATH"

	[ -z $WORK_PATH ] || [ -d "$WORK_PATH" ] || { die_fn "Please create WORK_PATH($WORK_PATH) first !!!";}
	#[ "$WORK_PATH" != "" ] && WORK_PATH_ARG=""

	[ -z $IOT_PATH ] || [ -d "$IOT_PATH" ] || { die_fn "Please create IOT_PATH($IOT_PATH) first !!!";}

	[ "$DEBUG" != "" ] && DEBUG_ARG="-d $DEBUG"

	[ "$LOGGER" != "" ] && LOGGER_ARG="| $LOGGER -t $LOGGER_TAG"

	[ "$IFACE" != "" ] && IFACE_ARG="-i $IFACE"

	[ "$CFG_FILE" != "" ] && CFG_FILE_ARG="-s $CFG_FILE"

	return 0
}

# wait_fn RUNNING TIMEOUT
wait_fn()
{
	RUNNING=$1
	[ ! -z "$RUNNING" ] || RUNNING=0

	TIMEOUT=$2
	[ ! -z "$TIMEOUT" ] || TIMEOUT=20

	count=1
	while [ $count -le $TIMEOUT ]
	do
		runpid_fn
		if [ "$RUNNING" = "1" ]; then
			[ ! -z "$PID" ] && break;
		else
			[ -z "$PID" ] && break;
		fi
		count=$(($count+1))
		sleep 1
	done

	return 0
}

start_fn()
{
	runpid_fn

	echo "$RUN_SH ($PID) start_fn ... "
	[ -z "$DAEMON" ] || [ -z "$PID" ] || { die_fn "$RUN_SH ($PID) is already running.";}

	init_fn
	arguments_fn
	cfg_fn

	if [ "$SUDO" = "" ]; then
		DO_COMMAND="$BIN_FILE $DEBUG_ARG $LOG_ARG $LOGGER_ARG &"
	else
		DO_COMMAND="$SUDO $BIN_FILE $DEBUG_ARG $LOG_ARG $LOGGER_ARG &"
	fi
	echo "[$DO_COMMAND]"
	sh -c "$DO_COMMAND"

	wait_fn 1 1

	echo "$RUN_SH ($PID) start_fn ok."

	return 0
}

stop_fn()
{
	runpid_fn

	echo "$RUN_SH ($PID) stop_fn ... "

	[ ! -z "$DAEMON" ] && [ ! -z "$PID" ] && $KILL_EX $PID

	clean_fn

	echo "$RUN_SH ($PID) stop_fn ok."

	return 0
}

status_fn()
{
	runpid_fn

	echo "$RUN_SH ($PID) status_fn ... "

	[ -z "$DAEMON" ] || [ -z "$PID" ] || { die_fn "$RUN_SH ($PID) is already running.";}
	[ ! -z "$DAEMON" ] && [ -z "$PID" ] && { die_fn "$RUN_SH () isn't running.";}

	return 0
}

debug_fn()
{
	echo "$RUN_SH ($PID) debug_fn ... "

	$KILLALL_EX -USR2 $DAEMON

	return 0
}

trigger_fn()
{
	echo "$RUN_SH ($PID) trigger_fn ... "

	$KILLALL_EX -USR1 $DAEMON

	return 0
}

logger_fn()
{
	echo "$RUN_SH ($PID) logger_fn [$LOGGER_TAG] ... "

	DO_COMMAND="(logread -f -e $LOGGER_TAG 2>/dev/null;) || (logread -f $LOGGER_COLOR | grep $LOGGER_TAG 2>/dev/null; ) || (tail -f /var/log/syslog  $LOGGER_COLOR | grep $LOGGER_TAG;)"
	echo "[$DO_COMMAND]"
	sh -c "$DO_COMMAND"

	return 0
}

showusage_fn()
{
	die_fn "$HINT"

	return 0
}

trap_ctrlc()
{
	echo "$RUN_SH ($PID) trap_ctrlc ..."

	[ -z $INTERACTIVE ] || stop_fn
}

[ "$ACTION" != "" ] || showusage_fn

main_fn()
{
	bin_check_fn

	case $ACTION in
		start)
			start_fn
		;;
		stop)
			# stop may call return, instead of exit
			stop_fn || exit 1
		;;
		restart)
			stop_fn
			wait_fn 0 20
			start_fn
		;;
		status)
			status_fn
		;;
		debug)
			debug_fn
		;;
		trigger)
			trigger_fn
		;;
		logger)
			logger_fn
		;;
		clean)
			clean_fn
		;;
		*)
			showusage_fn
		;;
	esac
}

[ -z $INTERACTIVE ] || trap "trap_ctrlc" 2
main_fn

exit 0