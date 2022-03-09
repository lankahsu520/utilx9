#!/bin/sh

[ ! -z $CONFIG_CUSTOMER_DEF_H ] || exit 1
[ ! -z $CONFIG_CUSTOMER ] || exit 1
[ -f ${CONFIG_CUSTOMER_DEF_H} ] && rm -f ${CONFIG_CUSTOMER_DEF_H}
[ -f ${CONFIG_CUSTOMER} ] && rm -f ${CONFIG_CUSTOMER}

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
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}
	fi
done < env.tmp
rm -f env.tmp

#** special **
echo "#define PJ_NAME_${PJ_NAME}" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export PJ_NAME_${PJ_NAME}=\"yes\"" >> ${CONFIG_CUSTOMER}
echo "#define PJ_MODE_${PJ_MODE}" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export PJ_MODE_${PJ_MODE}=\"yes\"" >> ${CONFIG_CUSTOMER}

#** CONFIG_XXX **
echo "#define CONFIG_AUTOCONF_H \"${CONFIG_AUTOCONF_H}\"" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export CONFIG_AUTOCONF_H=\"${CONFIG_AUTOCONF_H}\"" >> ${CONFIG_CUSTOMER}
echo "#define CONFIG_CONFIG \"${CONFIG_CONFIG}\"" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export CONFIG_CONFIG=\"${CONFIG_CONFIG}\"" >> ${CONFIG_CUSTOMER}
echo "#define CONFIG_CUSTOMER_DEF_H \"${CONFIG_CUSTOMER_DEF_H}\"" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export CONFIG_CUSTOMER_DEF_H=\"${CONFIG_CUSTOMER_DEF_H}\"" >> ${CONFIG_CUSTOMER}
echo "#define CONFIG_CUSTOMER \"${CONFIG_CUSTOMER}\"" >> ${CONFIG_CUSTOMER_DEF_H}
	echo "export CONFIG_CUSTOMER=\"${CONFIG_CUSTOMER}\"" >> ${CONFIG_CUSTOMER}

#** CFLAGS_XXX **
echo "export CFLAGS_COMMON=\"${CFLAGS_COMMON}\"" >> ${CONFIG_CUSTOMER}
echo "export CFLAGS_OPENSSL_INCLUDES=\"${CFLAGS_OPENSSL_INCLUDES}\"" >> ${CONFIG_CUSTOMER}
echo "export CFLAGS_CUSTOMER=\"${CFLAGS_CUSTOMER}\"" >> ${CONFIG_CUSTOMER}
echo "export CFLAGS=\"${CFLAGS_COMMON}\"" >> ${CONFIG_CUSTOMER}

#** LDFLAGS_XXX **
echo "export LDFLAGS_OPENSSL_LIBS=\"${LDFLAGS_OPENSSL_LIBS}\"" >> ${CONFIG_CUSTOMER}
echo "export LIBS=\"${LIBS}\"" >> ${CONFIG_CUSTOMER}
echo "export LDFLAGS=\"${LDFLAGS}\"" >> ${CONFIG_CUSTOMER}

#** SDK_XXX **
SDK_ALL=`env | grep ^SDK_ | sort`
for line in $SDK_ALL
do
	KEY=`echo $line | cut -d'=' -f 1`
	VAL=`echo $line | cut -d'=' -f 2-`

	if [ "$VAL" = "yes" ]; then
		echo "#define ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}
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
		echo "export ${KEY}=\"yes\"" >> ${CONFIG_CUSTOMER}
	elif [ "$VAL" = "no" ]; then
		echo "#undef ${KEY}" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"no\"" >> ${CONFIG_CUSTOMER}
	else
		echo "#define ${KEY} \"${VAL}\"" >> ${CONFIG_CUSTOMER_DEF_H}
		echo "export ${KEY}=\"${VAL}\"" >> ${CONFIG_CUSTOMER}
	fi
done

echo "" >> ${CONFIG_CUSTOMER_DEF_H}

echo "#endif" >> ${CONFIG_CUSTOMER_DEF_H}

chmod 775 ${CONFIG_CUSTOMER_DEF_H}