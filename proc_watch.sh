#!/bin/sh

RUN_SH=`basename $0`
HINT="$RUN_SH {start|stop|restart|status|debug|trigger|logger|clean} iface"
ROOTFS_PATH="/work/rootfs"
ROOTFS_PATH_ARG=""
NOW_t=`date +"%Y%m%d%H%M%S"`
PWD=`pwd`
SBIN_PATH=`dirname $0`
[ -d "$SBIN_PATH" ] || SBIN_PATH="${ROOTFS_PATH}/sbin"
SUDO_EX=$(which sudo 2>&1) && SUDO_B="sudo -E -b" && SUDO="sudo -E"
WHOAMI_EX=$(which whoami 2>&1) && WHO=`whoami`
[ ! -z "$WHO" ] || WHO="root"
export DBUS_SYSTEM_BUS_ADDRESS=""
[ ! -z "$DBUS_SYSTEM_BUS_ADDRESS" ] || unset DBUS_SYSTEM_BUS_ADDRESS

ACTION=$1

DAEMON="proc_watch"
[ -z "$DAEMON" ] || BIN_FILE="./$DAEMON"
[ -z "$BIN_FILE" ] || [[ -f "$BIN_FILE" && -x "$BIN_FILE" ]] || BIN_FILE="$ROOTFS_PATH/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [[ -f "$BIN_FILE" && -x "$BIN_FILE" ]] || BIN_FILE="$ROOTFS_PATH/usr/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [[ -f "$BIN_FILE" && -x "$BIN_FILE" ]] || BIN_FILE="/bin/$DAEMON"
[ -z "$BIN_FILE" ] || [[ -f "$BIN_FILE" && -x "$BIN_FILE" ]] || BIN_FILE="/usr/bin/$DAEMON"
[ -z "$BIN_FILE" ] || BIN_FILE=`realpath $BIN_FILE` && BIN_PATH=`dirname $BIN_FILE`
KILL_EX="$SUDO kill"
KILLALL_EX="$SUDO killall"

IS_INTERACTIVE=""
IS_ECHO="0"
IS_QUIT=0

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

DAEMON_ARG="&"
DO_COMMAND_ARG=""

#IFACE=$2
#[ ! -z "$IFACE" ] || IFACE="enp0s8"
IFACE_ARG=""

now_fn()
{
	NOW_t=`date +"%Y%m%d%H%M%S"`
	return $NOW_t
}

datetime_fn()
{
	PROMPT=$1

	if [ "${PROMPT}" = "" ]; then
		echo
	else
		now_fn
		DO_COMMAND_NOW="echo \"$NOW_t ${RUN_SH}|${PROMPT}\" $TEE_ARG"; sh -c "$DO_COMMAND_NOW"
	fi

	return 0
}

eval_fn()
{
	DO_COMMAND="$2"
	datetime_fn "$1- [$DO_COMMAND]"
	eval ${DO_COMMAND}
}

die_fn()
{
	datetime_fn "$@"; datetime_fn ""
	exit 1
}

tools_chk_fn()
{
	return 0
}

runpid_fn()
{
	[ -z "$DAEMON" ] || PID=$(pidof $DAEMON)

	return 0
}

bin_check_fn()
{
	[ -z "$DAEMON" ] || [ -z "$BIN_FILE" ] || [[ -f "$BIN_FILE" && -x "$BIN_FILE" ]] || { die_fn "${FUNCNAME[0]}:${LINENO}- $BIN_FILE isn't found !!!";}

	runpid_fn

	return 0
}

init_fn()
{
	return 0
}

clean_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	return 0
}

cfg_fn()
{
	return 0
}

arguments_fn()
{
	[ -z $ROOTFS_PATH ] || [ -d "$ROOTFS_PATH" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- Please create ROOTFS_PATH($ROOTFS_PATH) first !!!";}
	#[ "$ROOTFS_PATH" != "" ] && ROOTFS_PATH_ARG="-r $ROOTFS_PATH"

	[ -z $SAVE_PATH ] || [ -d "$SAVE_PATH" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- Please create SAVE_PATH($SAVE_PATH) first !!!";}
	#[ "$SAVE_PATH" != "" ] && SAVE_PATH_ARG="-s $SAVE_PATH"

	[ -z $CFG_PATH ] || [ -d "$CFG_PATH" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- Please create CFG_PATH($CFG_PATH) first !!!";}
	#[ "$CFG_PATH" != "" ] && CFG_PATH_ARG="-f $CFG_PATH"

	[ -z $WORK_PATH ] || [ -d "$WORK_PATH" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- Please create WORK_PATH($WORK_PATH) first !!!";}
	#[ "$WORK_PATH" != "" ] && WORK_PATH_ARG=""

	[ -z $IOT_PATH ] || [ -d "$IOT_PATH" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- Please create IOT_PATH($IOT_PATH) first !!!";}

	[ "$DEBUG" != "" ] && DEBUG_ARG="-d $DEBUG"

	[ "$LOGGER" != "" ] && LOGGER_ARG="| $LOGGER -t $LOGGER_TAG"

	[ "$IFACE" != "" ] && IFACE_ARG="-i $IFACE"

	[ "$CFG_FILE" != "" ] && CFG_FILE_ARG="-s $CFG_FILE"

	DO_COMMAND_ARG="$IFACE_ARG $SAVE_PATH_ARG $CFG_PATH_ARG $WORK_PATH_ARG $DEBUG_ARG $LOG_ARG $LOGGER_ARG $DAEMON_ARG"

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
		sleep 0.1
	done

	return 0
}

start_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."
	[ -z "$DAEMON" ] || [ -z "$PID" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- ($PID) is already running.";}

	init_fn
	cfg_fn
	arguments_fn

	if [ "$SUDO" = "" ]; then
		DO_COMMAND="$BIN_FILE $DO_COMMAND_ARG"
	else
		DO_COMMAND="$SUDO $BIN_FILE $DO_COMMAND_ARG"
	fi
	eval_fn "${FUNCNAME[0]}:${LINENO}" "$DO_COMMAND"

	wait_fn 1 10

	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."

	return 0
}

stop_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	IS_QUIT=1

	[ ! -z "$DAEMON" ] && [ ! -z "$PID" ] && $KILL_EX $PID

	clean_fn

	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."

	return 0
}

status_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	[ -z "$DAEMON" ] || [ -z "$PID" ] || { die_fn "${FUNCNAME[0]}:${LINENO}- ($PID) is already running.";}
	[ ! -z "$DAEMON" ] && [ -z "$PID" ] && { die_fn "${FUNCNAME[0]}:${LINENO}- ($PID) isn't running.";}

	return 0
}

debug_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	$KILLALL_EX -USR2 $DAEMON

	return 0
}

trigger_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	$KILLALL_EX -USR1 $DAEMON

	return 0
}

logger_fn()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) [$LOGGER_TAG] ..."

	LOGREAD=`which logread`
	LOGREAD_ARG=" [ ! -z '$LOGREAD' ] "
	[ -z "$LOGREAD" ] || LOGREAD_ARG="(logread -f -e $LOGGER_TAG 2>/dev/null;) || (logread -f $LOGGER_COLOR | grep $LOGGER_TAG 2>/dev/null; )"
	eval_fn "${FUNCNAME[0]}:${LINENO}" "$LOGREAD_ARG || (tail -f /var/log/syslog $LOGGER_COLOR | grep '${LOGGER_TAG}:';)"

	return 0
}

showusage_fn()
{
	printf "$HINT"; datetime_fn ""; exit 1

	return 0
}

trap_ctrlc()
{
	datetime_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	[ -z $IS_INTERACTIVE ] || stop_fn
}

[ "$ACTION" != "" ] || showusage_fn
tools_chk_fn

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

[ -z $IS_INTERACTIVE ] || trap "trap_ctrlc" 2
main_fn

exit 0
