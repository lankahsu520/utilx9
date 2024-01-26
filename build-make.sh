#!/bin/bash

RUN_SH=`basename $0`
HINT="$0 {build|clean|distclean|rebuild} [x86|i486|aarch64]"

ACTION=$1
ARCH=$2
[ -z "$ARCH" ] && export ARCH="x86"
export PJ_TARGET_CONF="_$ARCH"

#** Toolchain **

#** Setup Environment **
export PJ_ROOT=`pwd`
[ ! -z "$PJ_INSTALL" ] || export PJ_INSTALL="${PJ_ROOT}/install"
[ ! -z "$PJ_CPACK" ] || export PJ_CPACK="${PJ_ROOT}/install_Cpack"
[ ! -z "$SDK_ROOT_DIR" ] || export SDK_ROOT_DIR="${PJ_INSTALL}"
export SDK_USR_PREFIX_DIR="usr"

export CONFIG_CUSTOMER_DEF_H="${PJ_ROOT}/include/customer_def.h"

#export CROSS_FILE=

export PJ_BUILD_DIR="build_xxx"
export PJ_BUILD_VERBOSE="-v"
#export PJ_MAKE_VERBOSE="VERBOSE=1"

#export PKG_CONFIG_SYSROOT_DIR="${PJ_INSTALL}"

now_fn()
{
	NOW_t=`date +"%Y%m%d%H%M%S"`
	return $NOW_t
}

datetimeX_fn()
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

do_commandX_fn()
{
	FUNCX=$1
	LINEX=$2
	DO_COMMAND=$3
	datetimeX_fn "${FUNCX}:${LINEX}- [$DO_COMMAND]"
	sh -c "$DO_COMMAND"
}

do_env_fn()
{
	. confs/simple${PJ_TARGET_CONF}.conf >/dev/null 2>&1
	return 0
}

die_fn()
{
	datetimeX_fn "$@"; datetimeX_fn ""
	exit 1
}

distclean_install_fn()
{
	while true; do
		echo
		echo "install: ${SDK_ROOT_DIR}"
		echo "Cpack: ${PJ_CPACK}"
		read -p "WARNING! They will be removed [y/N] ? " yn
		case $yn in
			[Yy]* )
				DO_COMMAND="rm -rf ${SDK_ROOT_DIR} ${PJ_CPACK}"
				do_commandX_fn "${FUNCNAME[0]}" "${LINENO}" "${DO_COMMAND}"
				break
				;;
			[Nn]* )
				break
				;;
			* )
				break
			;;
		esac
	done

	return 0
}

distclean_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	DO_COMMAND="(make distclean)"
	do_commandX_fn "${FUNCNAME[0]}" "${LINENO}" "${DO_COMMAND}"

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	return 0
}

cfg_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	#** customer_def.h **

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	datetimeX_fn
	return 0
}

showusage_fn()
{
	#datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."
	printf "$HINT"; datetimeX_fn ""; exit 1

	return 0
}

build_setup_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	#** build setup **

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	datetimeX_fn
}

build_run_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	DO_COMMAND="(make ${PJ_MAKE_VERBOSE})"
	do_commandX_fn "${FUNCNAME[0]}" "${LINENO}" "${DO_COMMAND}"

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	datetimeX_fn
}

build_install_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	DO_COMMAND="(make install)"
	do_commandX_fn "${FUNCNAME[0]}" "${LINENO}" "${DO_COMMAND}"

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	datetimeX_fn
}

build_clean_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	DO_COMMAND="(make clean)"
	do_commandX_fn "${FUNCNAME[0]}" "${LINENO}" "${DO_COMMAND}"

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	datetimeX_fn
}

build_cpack_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ok."
	datetimeX_fn
}

build_fn()
{
	datetimeX_fn "${FUNCNAME[0]}:${LINENO}- ($PID) ..."

	distclean_fn

	cfg_fn

	build_setup_fn

	build_run_fn

	build_install_fn

	build_cpack_fn
}

main_fn()
{
	do_env_fn

	case $ACTION in
		build)
			build_fn
		;;
		clean)
			build_clean_fn
		;;
		rebuild)
			build_clean_fn
			build_fn
		;;
		distclean)
			distclean_fn
		;;
		*)
			showusage_fn
		;;
	esac
}

main_fn

exit 0
