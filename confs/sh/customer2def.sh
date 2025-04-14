#!/bin/sh

[ ! -z $CONFIG_CUSTOMER_DEF_H ] || exit 1
[ ! -z $CONFIG_CUSTOMER ] || exit 1
[ -f ${CONFIG_CUSTOMER_DEF_H} ] && rm -f ${CONFIG_CUSTOMER_DEF_H}
[ -f ${CONFIG_CUSTOMER} ] && rm -f ${CONFIG_CUSTOMER}
[ -f ${CONFIG_CUSTOMER}.export ] && rm -f ${CONFIG_CUSTOMER}.export
[ -f ${CONFIG_MESON} ] && rm -f ${CONFIG_MESON}

echo "#ifndef __CUSTOMER_DEF_H__" >> ${CONFIG_CUSTOMER_DEF_H}
echo "#define __CUSTOMER_DEF_H__" >> ${CONFIG_CUSTOMER_DEF_H}
echo "" >> ${CONFIG_CUSTOMER_DEF_H}

#** PJ_XXX **
env | grep ^PJ_ | sort > env.tmp
#IFS=''
while read line; do
	KEY=`echo $line | cut -d'=' -f 1`
	VAL=`echo $line | cut -d'=' -f 2-`

	if [ "$VAL" = "yes" ]; then
		echo "#define ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=yes" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: true)" >> ${CONFIG_MESON}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=no" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: false)" >> ${CONFIG_MESON}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=${VAL}" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'string', value: '${VAL}')" >> ${CONFIG_MESON}
	fi
done < env.tmp
rm -f env.tmp

#** special **
echo "#define PJ_NAME_${PJ_NAME}" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export PJ_NAME_${PJ_NAME}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
	echo "PJ_NAME_${PJ_NAME}=yes" >> ${CONFIG_CUSTOMER}
	echo "option('PJ_NAME_${PJ_NAME}', type: 'boolean', value: true)" >> ${CONFIG_MESON}
echo "#define PJ_MODE_${PJ_MODE}" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export PJ_MODE_${PJ_MODE}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
	echo "PJ_MODE_${PJ_MODE}=yes" >> ${CONFIG_CUSTOMER}
	echo "option('PJ_MODE_${PJ_MODE}', type: 'boolean', value: true)" >> ${CONFIG_MESON}

#** CONFIG_XXX **
env | grep ^CONFIG_ | sort > env.tmp
#IFS=''
while read line; do
	KEY=`echo $line | cut -d'=' -f 1`
	VAL=`echo $line | cut -d'=' -f 2-`

	if [ "$VAL" = "yes" ]; then
		echo "#define ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=yes" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: true)" >> ${CONFIG_MESON}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=no" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: false)" >> ${CONFIG_MESON}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=${VAL}" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'string', value: '${VAL}')" >> ${CONFIG_MESON}
	fi
done < env.tmp
rm -f env.tmp

#** CFLAGS_XXX **
echo "export CFLAGS_COMMON=\"${CFLAGS_COMMON}\"" >> ${CONFIG_CUSTOMER}.export
	echo "CFLAGS_COMMON=${CFLAGS_COMMON}" >> ${CONFIG_CUSTOMER}
	echo "option('CFLAGS_COMMON', type: 'string', value: '${CFLAGS_COMMON}')" >> ${CONFIG_MESON}
echo "export CFLAGS_CUSTOMER=\"${CFLAGS_CUSTOMER}\"" >> ${CONFIG_CUSTOMER}.export
	echo "CFLAGS_CUSTOMER=${CFLAGS_CUSTOMER}" >> ${CONFIG_CUSTOMER}
	echo "option('CFLAGS_CUSTOMER', type: 'string', value: '${CFLAGS_CUSTOMER}')" >> ${CONFIG_MESON}
echo "export CFLAGS=\"${CFLAGS}\"" >> ${CONFIG_CUSTOMER}.export
	echo "CFLAGS=${CFLAGS}" >> ${CONFIG_CUSTOMER}
	echo "option('CFLAGS', type: 'string', value: '${CFLAGS}')" >> ${CONFIG_MESON}

#** LDFLAGS_XXX **
echo "export LIBS=\"${LIBS}\"" >> ${CONFIG_CUSTOMER}.export
	echo "LIBS=${LIBS}" >> ${CONFIG_CUSTOMER}
	echo "option('LIBS', type: 'string', value: '${LIBS}')" >> ${CONFIG_MESON}
echo "export LDFLAGS=\"${LDFLAGS}\"" >> ${CONFIG_CUSTOMER}.export
	echo "LDFLAGS=${LDFLAGS}" >> ${CONFIG_CUSTOMER}
	echo "option('LDFLAGS', type: 'string', value: '${LDFLAGS}')" >> ${CONFIG_MESON}

#** SDK_XXX **
SDK_ALL=`env | grep ^SDK_ | sort`
for line in $SDK_ALL
do
	KEY=`echo $line | cut -d'=' -f 1`
	VAL=`echo $line | cut -d'=' -f 2-`

	if [ "$VAL" = "yes" ]; then
		echo "#define ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=yes" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: true)" >> ${CONFIG_MESON}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=no" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: false)" >> ${CONFIG_MESON}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=${VAL}" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'string', value: '${VAL}')" >> ${CONFIG_MESON}
	fi
done

#** HOMEX_XXX **
HOMEX_ALL=`env | grep ^HOMEX_ | sort`
for line in $HOMEX_ALL
do
	KEY=`echo $line | cut -d'=' -f 1`
	VAL=`echo $line | cut -d'=' -f 2-`

	if [ "$VAL" = "yes" ]; then
		echo "#define ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=yes" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: true)" >> ${CONFIG_MESON}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=no" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: false)" >> ${CONFIG_MESON}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=${VAL}" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'string', value: '${VAL}')" >> ${CONFIG_MESON}
	fi
done

#** PKG_XXX **
PKG_ALL=`env | grep ^PKG_ | sort`
for line in $PKG_ALL
do
	KEY=`echo $line | cut -d'=' -f 1`
	VAL=`echo $line | cut -d'=' -f 2-`

	if [ "$VAL" = "yes" ]; then
		echo "#define ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=yes" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: true)" >> ${CONFIG_MESON}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=no" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'boolean', value: false)" >> ${CONFIG_MESON}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}.export
		echo "${KEY}=${VAL}" >> ${CONFIG_CUSTOMER}
		echo "option('${KEY}', type: 'string', value: '${VAL}')" >> ${CONFIG_MESON}
	fi
done

echo "" >> ${CONFIG_CUSTOMER_DEF_H}

echo "#endif" >> ${CONFIG_CUSTOMER_DEF_H}

chmod 775 ${CONFIG_CUSTOMER_DEF_H}