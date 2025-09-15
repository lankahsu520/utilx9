#!/bin/sh

# "": disable or "1": enable
CURL_AUTH="1"
CURL_AUTH_ARG=""

#CURL_DIGEST="--digest"

CURL_VERBOSE="-v"

# "": save to file or "1": display
ONVIF_VERBOSE="1"
ONVIF_XML_FILE_RES_ARG=""

USER=admin
PASSWORD=admin

[ "$CURL_AUTH" == "1" ] && CURL_AUTH_ARG="${CURL_DIGEST} -u ${USER}:${PASSWORD}"

ONVIF_URL="http://192.168.50.21/onvif/media_service"
ONVIF_ACTION="GetProfiles"
ONVIF_AUTH="-auth"

ONVIF_XML_USERNAME=${USER}
ONVIF_XML_CREATED=
ONVIF_XML_NONCE=
ONVIF_XML_PASSWORD=

generate_onvif_nonce_and_pass_fn()
{
	#valgrind --tool=memcheck --leak-check=full --show-reachable=yes -s ../onvif_pass_123 admin
	#../onvif_pass_123 ${PASSWORD}
	#chmod 777 ./onvif_pass.sh
	#. ./onvif_pass.sh

	ONVIF_XML_CREATED=$(date -u +"%Y-%m-%dT%H:%M:%SZ")

	nonce_file=$(mktemp)
	trap 'rm -f "$nonce_file"' EXIT
	openssl rand 16 > "$nonce_file"
	ONVIF_XML_NONCE=$(base64 < "$nonce_file" | tr -d '\n')

	ONVIF_XML_PASSWORD=$( (cat "$nonce_file"; printf "%s%s" "$ONVIF_XML_CREATED" "$PASSWORD") \
  | openssl dgst -sha1 -binary | openssl base64 | tr -d '\n')
}

generate_onvif_request_fn()
{
	echo "(ONVIF_XML_USERNAME=$ONVIF_XML_USERNAME)"
	echo "(ONVIF_XML_CREATED=$ONVIF_XML_CREATED)"
	echo "(ONVIF_XML_NONCE=$ONVIF_XML_NONCE)"
	echo "(ONVIF_XML_PASSWORD=$ONVIF_XML_PASSWORD)"

	ONVIF_XML_FILE=${ONVIF_ACTION}${ONVIF_AUTH}.xml
	ONVIF_XML_FILE_REQ=${ONVIF_ACTION}${ONVIF_AUTH}-req.xml
	ONVIF_XML_FILE_RES=${ONVIF_ACTION}${ONVIF_AUTH}-res.xml

	[ "$ONVIF_VERBOSE" == "" ] && ONVIF_XML_FILE_RES_ARG="| xmllint --format - > ${ONVIF_XML_FILE_RES}"

	cp -avr ${ONVIF_XML_FILE} ${ONVIF_XML_FILE_REQ}

	sed -i "s|{ONVIF_XML_CREATED}|${ONVIF_XML_CREATED}|g" ${ONVIF_XML_FILE_REQ}
	sed -i "s|{ONVIF_XML_NONCE}|${ONVIF_XML_NONCE}|g" ${ONVIF_XML_FILE_REQ}
	sed -i "s|{ONVIF_XML_USERNAME}|${ONVIF_XML_USERNAME}|g" ${ONVIF_XML_FILE_REQ}
	sed -i "s|{ONVIF_XML_PASSWORD}|${ONVIF_XML_PASSWORD}|g" ${ONVIF_XML_FILE_REQ}
}

send_onvif_request_fn()
{
	DO_COMMAND="curl ${CURL_VERBOSE} ${CURL_AUTH_ARG} -H 'Content-Type: application/soap+xml; charset=utf-8' -H 'Accept-Encoding: gzip, deflate' -d @./${ONVIF_XML_FILE_REQ} ${ONVIF_URL} ${ONVIF_XML_FILE_RES_ARG}"
	echo "[$DO_COMMAND]"
	sh -c "$DO_COMMAND"
}

main_fn()
{
	generate_onvif_nonce_and_pass_fn
	generate_onvif_request_fn
	send_onvif_request_fn
}

main_fn

exit 0