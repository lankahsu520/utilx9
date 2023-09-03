/***************************************************************************
 * Copyright (C) 2017 - 2020, Lanka Hsu, <lankahsu@gmail.com>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include "utilx9.h"

#define DBG_TMP_Y(format,args...) //DBG_LN_Y(format, ## args)
#define DBG_TMP_DUMP(ibuf,len,delim,format,args...) //DBG_TR_DUMP(ibuf,len,delim,format,## args)

static char *onvif_xml(SOAP_ACTION_ID act_id)
{
	switch (act_id)
	{
		case SOAP_ACTION_ID_DEVICE_GETCAPABILITIES:
			return ONVIF_XML_GETCAPABILITIES;
			break;
		case SOAP_ACTION_ID_DEVICE_GETSERVICES:
			return ONVIF_XML_GETSERVICES;
			break;

		case SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI:
			return ONVIF_XML_GETSNAPSHOTURI;
			break;
		case SOAP_ACTION_ID_MEDIA_GETSTREAMURI:
			return ONVIF_XML_GETSTREAMURI;
			break;

		case SOAP_ACTION_ID_DEVICE_GETHOSTNAME:
		case SOAP_ACTION_ID_MEDIA_GETPROFILES:
		case SOAP_ACTION_ID_DEVICE_GETSCOPES:
		case SOAP_ACTION_ID_DEVICE_GETNETWORKINTERFACES:
		default:
			return ONVIF_XML_BODY;
			break;
	}
}

//#define USE_EVP_MD
#include <openssl/sha.h>
char *onvif_pass_sha1(char *nonce, int nonce_len, char *created, int create_len, char *password, int password_len)
{
	char *buffer = SAFE_CALLOC(1, LEN_OF_VAL32);

#ifdef USE_EVP_MD
	unsigned int buffer_len = LEN_OF_VAL32;
	EVP_MD_CTX *ctx = NULL;

	if ((ctx = EVP_MD_CTX_create()) == NULL)
	{
		DBG_ER_LN("EVP_MD_CTX_create error !!!");
		goto exit_sha1;
	}

	if (1 != EVP_DigestInit_ex(ctx, EVP_sha1(), NULL))
	{
		DBG_ER_LN("EVP_DigestInit_ex error !!!");
		goto exit_sha1;
	}

	if (1 != EVP_DigestUpdate(ctx, nonce, nonce_len))
	{
		DBG_ER_LN("EVP_DigestUpdate error - nonce !!!");
		goto exit_sha1;
	}
	if (1 != EVP_DigestUpdate(ctx, created, create_len))
	{
		DBG_ER_LN("EVP_DigestUpdate error - created !!!");
		goto exit_sha1;
	}
	if (1 != EVP_DigestUpdate(ctx, password, password_len))
	{
		DBG_ER_LN("EVP_DigestUpdate error - created !!!");
		goto exit_sha1;
	}

	if (1 != EVP_DigestFinal_ex(ctx, (unsigned char*)buffer, &buffer_len))
	{
		DBG_ER_LN("EVP_DigestFinal_ex error !!!");
		goto exit_sha1;
	}
#else
	SHA_CTX sha1;

	SHA1_Init(&sha1);
	SHA1_Update(&sha1, nonce, nonce_len);
	SHA1_Update(&sha1, created, create_len);
	SHA1_Update(&sha1, password, password_len);
	SHA1_Final((unsigned char *)buffer, &sha1);
#endif

#ifdef USE_EVP_MD
exit_sha1:
	if (ctx)
	{
		EVP_MD_CTX_destroy(ctx);
	}
#endif

	return buffer;
}

void onvif_auth(OnvifX_t *onvif_req, SoapX_t *soap)
{
	soap_node_t *request_node = soap->request_node;

	{
		soap_node_t	*Envelope_node = soap_element_fetch(request_node, NULL, "Envelope", NULL, NULL);
		{
			soap_node_t *header_node = soap_element_add(Envelope_node, "SOAP-ENV:Header");
			{
				soap_node_t *Security_node = soap_element_add(header_node, "Security");

				soap_element_attr_set(Security_node, "SOAP-ENV:mustUnderstand", "1");
				soap_element_attr_set(Security_node, "xmlns", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");
				{
					soap_node_t *UsernameToken_node = soap_element_add(Security_node, "UsernameToken");
					{
						time_t create_t;
						char create_s[LEN_OF_VAL32] = "";

						time(&create_t);
						//strftime(create_s, sizeof(create_s), "%Y-%m-%dT%T.000Z", time(NULL));
						strftime(create_s, sizeof(create_s), "%Y-%m-%dT%H:%M:%S.000Z", localtime(&create_t));

						soap_node_t *Created_node = soap_element_add(UsernameToken_node, "Created");
						{
							soap_element_attr_set(Created_node, "xmlns", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");

							//DBG_DB_LN("(create_s: %s)", create_s);
							soap_element_text_new(Created_node, 0, create_s);
						}

						char *nonce_rand = os_urandom(20);
						if (nonce_rand)
						{
							int enc_len = 0;
							char *nonce_b64 = sec_base64_enc(nonce_rand, 20, &enc_len);
							if (nonce_b64)
							{
								DBG_TMP_Y("nonce_b64 (enc_len: %d, [%s])", enc_len, nonce_b64);
								soap_node_t *Nonce_node = soap_element_add(UsernameToken_node, "Nonce");
								{
									soap_element_attr_set(Nonce_node, "EncodingType", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-soap-message-security-1.0#Base64Binary");

									soap_element_text_new(Nonce_node, 0, nonce_b64);
								}
								SAFE_FREE(nonce_b64);
							}

							soap_node_t *Username_node = soap_element_add(UsernameToken_node, "Username");
							{
								soap_element_text_new(Username_node, 0, (const char *)onvif_req->netinfo.user);
							}

							char *password = onvif_pass_sha1(nonce_rand, 20, create_s, strlen(create_s), onvif_req->netinfo.pass, strlen(onvif_req->netinfo.pass));
							if (password)
							{
								int enc_len = 0;
								char *password_b64 = sec_base64_enc(password, 20, &enc_len);
								if (password_b64)
								{
									DBG_TMP_Y("password_b64 (enc_len: %d, [%s] -> [%s])", enc_len, onvif_req->netinfo.pass, password_b64);

									soap_node_t *Password_node = soap_element_add(UsernameToken_node, "Password");
									{
										soap_element_attr_set(Password_node, "Type", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordDigest");

										soap_element_text_new(Password_node, 0, password_b64);
									}
									SAFE_FREE(password_b64);
								}
								SAFE_FREE(password);
							}

							SAFE_FREE(nonce_rand);
						}
					}
				}
			}
		}
	}

	//soap_element_save(request_node, "/tmp/sdk/test.xml");
}

soap_node_t *onvif_open(OnvifX_t *onvif_req, onvif_resuest_fn request_cb)
{
	soap_node_t *response_node = NULL;
	if ((onvif_req) && (strlen(onvif_req->netinfo.url)>0))
	{
		HttpX_t http_req =
		{
			.mode = HTTP_MODE_ID_SOAP,
			.url = "",
			.port = onvif_req->netinfo.port,
			.log = "",
		};
		SAFE_SPRINTF(http_req.url, "%s", onvif_req->netinfo.url);

		if (onvif_req->http_auth > 0)
		{
			http_req.user = onvif_req->netinfo.user;
			http_req.password = onvif_req->netinfo.pass;
		}

		SoapX_t *soap = soap_create(onvif_xml(onvif_req->act_id));
		if (soap)
		{
			{
				// to fill user and pass
				onvif_auth(onvif_req, soap);

				// to fill request
				if (request_cb)
				{
					request_cb(soap, onvif_req);
				}
			}

			soap_http_access(soap, &http_req);

			{
				// to keep response
				char act_name[LEN_OF_NAME_ONVIF_ACT]="";
				SAFE_SNPRINTF(act_name, (int)sizeof(act_name), "%sResponse", onvif_req->act_name);

				response_node = soap_element_fetch(soap->response_node, onvif_req->act_ns, act_name, NULL, NULL);
				soap_element_remove(response_node);
			}

			soap_free(soap);
		}
	}
	else
	{
		DBG_ER_LN("onvif_req is NULL !!!");
	}
	return response_node;
}

static void onvif_media_GetSnapshotUri_request_cb(SoapX_t *soap, OnvifX_t *onvif_req)
{
	char *ProfileToken = (char *)onvif_req->request;
	soap_node_t *ptoken_node = soap_element_fetch(soap->request_node, NULL, "ProfileToken", NULL, NULL);
	if (ptoken_node)
	{
		// to fill request
		soap_element_text_set(ptoken_node, 0, ProfileToken);
	}
}

static void onvif_media_GetStreamUri_request_cb(SoapX_t *soap, OnvifX_t *onvif_req)
{
	char *ProfileToken = (char *)onvif_req->request;
	soap_node_t *ptoken_node = soap_element_fetch(soap->request_node, NULL, "ProfileToken", NULL, NULL);
	if (ptoken_node)
	{
		// to fill request
		soap_element_text_set(ptoken_node, 0, ProfileToken);
	}
}

static void onvif_GeCommon_request_cb(SoapX_t *soap, OnvifX_t *onvif_req)
{
	soap_node_t *body_node = soap_element_fetch(soap->request_node, NULL, "Body", NULL, NULL);
	if ((onvif_req) && (body_node))
	{
		char act_name[LEN_OF_NAME_ONVIF_ACT];
		SAFE_SNPRINTF(act_name, (int)sizeof(act_name), "%s:%s", onvif_req->act_ns, onvif_req->act_name);
		soap_element_add(body_node, act_name);
	}
	else
	{
		DBG_ER_LN("body_node is NULL !!!");
	}
}

soap_node_t *onvif_GetCommon(OnvifX_t *onvif_req)
{
	onvif_resuest_fn request_cb = NULL;
	switch (onvif_req->act_id)
	{
		case SOAP_ACTION_ID_MEDIA_GETSNAPSHOTURI:
			request_cb = onvif_media_GetSnapshotUri_request_cb;
			break;
		case SOAP_ACTION_ID_MEDIA_GETSTREAMURI:
			request_cb = onvif_media_GetStreamUri_request_cb;
			break;

		// device
		case SOAP_ACTION_ID_DEVICE_GETCAPABILITIES:
		case SOAP_ACTION_ID_DEVICE_GETSERVICES:
			break;
		case SOAP_ACTION_ID_DEVICE_GETDEVICEINFORMATION:
		case SOAP_ACTION_ID_DEVICE_GETHOSTNAME:
		case SOAP_ACTION_ID_DEVICE_GETSCOPES:
		case SOAP_ACTION_ID_DEVICE_GETNETWORKINTERFACES:
		// media
		case SOAP_ACTION_ID_MEDIA_GETPROFILES:
		default:
			request_cb = onvif_GeCommon_request_cb;
			break;
	}

	return onvif_open(onvif_req, request_cb);
}

int onvif_GetSnapshot(OnvifX_t *onvif_req, char *snapshot_uri, char *prefixname)
{
	int ret = 0;
	if (snapshot_uri)
	{
		HttpX_t http_req =
		{
			.mode = HTTP_MODE_ID_DOWNLOAFILE_MJPEG,
			.url = "",
			.log = "",
			.mjpeg_req.max_size = 2*1024*1024, // 2MB
			.mjpeg_req.maxfiles = 1, //
			.mjpeg_req.prefixname = "",

			.mjpeg_req.fp = NULL,
			.mjpeg_req.num = 0,
		};
		SAFE_SPRINTF(http_req.url, "%s", snapshot_uri);
		SAFE_SPRINTF(http_req.mjpeg_req.prefixname, "%s", prefixname);
		SAFE_MEMSET(http_req.mjpeg_req.boundary, 0, sizeof(http_req.mjpeg_req.boundary));

		http_req.user = onvif_req->netinfo.user;
		http_req.password = onvif_req->netinfo.pass;

		ret = http_request(&http_req);
		DBG_DB_LN("(http_req.log: %s)", http_req.log);
	}
	return ret;
}

int onvif_GetVideoClip(OnvifX_t *onvif_req, char *videoclip_uri, char *filename, int duration)
{
	int ret = 0;
	if (videoclip_uri)
	{
		HttpX_t http_req =
		{
			.mode = HTTP_MODE_ID_DOWNLOAFILE_RTSP,
			.url = "",
			.log = "",

			.rtsp_req.max_size = 0,
			.rtsp_req.filename = "",
			.rtsp_req.fp = NULL,
			.rtsp_req.duration = duration,

			.rtsp_req.rtp_port = rtp_port_get(),
			.rtsp_req.interleaved = 0, // for firewall
			.rtsp_req.stop = 0,

			.rtsp_req.progress = 1,
		};

		SAFE_SPRINTF(http_req.url, "%s", videoclip_uri);
		SAFE_SPRINTF(http_req.rtsp_req.filename, "%s", filename);

		http_req.user = onvif_req->netinfo.user;
		http_req.password = onvif_req->netinfo.pass;

		ret = http_request(&http_req);
		DBG_DB_LN("(http_req.log: %s)", http_req.log);
	}
	return ret;
}

