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

QBUF_t qbuf_S;
ChainX_t chainX_S = {
	.mode = CHAINX_MODE_ID_TCP_CLIENT,
	.sockfd = -1,
	.status = 0,
	.isfree = 0,

	.security = 0,
	.noblock = 1,

	.retry_hold = TIMEOUT_OF_RETRY_HOLD,
	.select_wait = TIMEOUT_OF_SELECT_1,
	.c_data = &qbuf_S,
};

#if (1) // Philio
const unsigned char RSA_CLIENT_CERT[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIELTCCAxWgAwIBAgIUIk+ujm+obvfSXZkCg5jq+v1G7U8wDQYJKoZIhvcNAQEL\r\n"
"BQAwgaUxCzAJBgNVBAYTAlRXMQ8wDQYDVQQIDAZUYWl3YW4xDzANBgNVBAcMBlRh\r\n"
"aXBlaTEmMCQGA1UECgwdUGhpbGlvIFRlY2hub2xvZ3kgQ29ycG9yYXRpb24xJjAk\r\n"
"BgNVBAMMHVBoaWxpbyBUZWNobm9sb2d5IENvcnBvcmF0aW9uMSQwIgYJKoZIhvcN\r\n"
"AQkBFhVzYWxlc0BwaGlsaW8tdGVjaC5jb20wHhcNMTkwOTA0MDkxOTIyWhcNMjAw\r\n"
"OTAzMDkxOTIyWjCBpTELMAkGA1UEBhMCVFcxDzANBgNVBAgMBlRhaXdhbjEPMA0G\r\n"
"A1UEBwwGVGFpcGVpMSYwJAYDVQQKDB1QaGlsaW8gVGVjaG5vbG9neSBDb3Jwb3Jh\r\n"
"dGlvbjEmMCQGA1UEAwwdUGhpbGlvIFRlY2hub2xvZ3kgQ29ycG9yYXRpb24xJDAi\r\n"
"BgkqhkiG9w0BCQEWFXNhbGVzQHBoaWxpby10ZWNoLmNvbTCCASIwDQYJKoZIhvcN\r\n"
"AQEBBQADggEPADCCAQoCggEBAO/T2cx4y0WOnkUOapMt2qlQNCE+sqMMRbLDGY1W\r\n"
"/EQuexrxYMqAKwt247jBJAVKOpHqMZxnxdnd8VyIWgqkI+QWRUaGZ7cwHyG7Mnpk\r\n"
"A5AvRVpLwJdoZ4qkruPZXm8qPG/66C5h+Rg15XU67ldBhdL4sTzJuDqZKALTr7lb\r\n"
"Nh2wiqoEUGDKWAoiMSpnhxl30LiG5+rPwyivL+FLvwZRxV/1RnVW6fafdyDxkTT4\r\n"
"wV8FK5al5b0ctZwdgIpoAeCf6Qf5OP3yziO8xRV4yTqCohSEzDh5z2GT5SIR/hVA\r\n"
"8dl92pWdysdKEq230NitidlYgPX135sZwYhaXDaRS85+uaECAwEAAaNTMFEwHQYD\r\n"
"VR0OBBYEFK+hw5HyWevtgzePQKDp77at63coMB8GA1UdIwQYMBaAFK+hw5HyWevt\r\n"
"gzePQKDp77at63coMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEB\r\n"
"AF2CiwD11bCM1LZD6QEMQdbDEMAXDkg/JFnLZ9/9JACdK1jmbvmwyDMQYT13//XV\r\n"
"hSB1vqpPQz/UHTUOSzsOUlRp6R/EaeygXXFDycb8O1pcQRs9xVrJTfy1fXXrPIJH\r\n"
"rgT1EpyWaFmH1rzZ8dyMO6Zzh4rwZXUHP/ksvZ0iGXdExkTG+KTPUfENaiQND+uW\r\n"
"tvt8dEjmngZB0ktTdTkU6+BLGGegQqD+hIzEnHnynXq6EzlpVO9qx+6MQmOIxP1e\r\n"
"n6oFFxo4Qnw8/T8RYbQi4C6IUM2/uUwHfRfx3Y0fFI/S9/bkehK3EM2jvjmr6uZN\r\n"
"aFsSXDC4kbCaZbI9W2LYS1o=\r\n"
"-----END CERTIFICATE-----\r\n";

const unsigned char RSA_CLIENT_KEY[] =
"-----BEGIN PRIVATE KEY-----\r\n"
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDv09nMeMtFjp5F\r\n"
"DmqTLdqpUDQhPrKjDEWywxmNVvxELnsa8WDKgCsLduO4wSQFSjqR6jGcZ8XZ3fFc\r\n"
"iFoKpCPkFkVGhme3MB8huzJ6ZAOQL0VaS8CXaGeKpK7j2V5vKjxv+uguYfkYNeV1\r\n"
"Ou5XQYXS+LE8ybg6mSgC06+5WzYdsIqqBFBgylgKIjEqZ4cZd9C4hufqz8Mory/h\r\n"
"S78GUcVf9UZ1Vun2n3cg8ZE0+MFfBSuWpeW9HLWcHYCKaAHgn+kH+Tj98s4jvMUV\r\n"
"eMk6gqIUhMw4ec9hk+UiEf4VQPHZfdqVncrHShKtt9DYrYnZWID19d+bGcGIWlw2\r\n"
"kUvOfrmhAgMBAAECggEANwIomrW6KiIkO0KrP0btOJik3Fs9LhjKg84sNjcVda4T\r\n"
"noJu6QOs29xRLzddw7ja5k0JRA6pWueFTOwZewdbFB3nld2OPH5VJa+CTIBUMOYm\r\n"
"yidF7XSNC0fqtWhOOME/S5AJYVongF4cW19A+9KTl2hjfsXl88rdWoijbah2KSi7\r\n"
"eXe8BEuZzB3oknWSoHZ//y661ElcajgA2a7/K91dartYFIv6j1f745KT5XNfj1pL\r\n"
"DtHe6ndx5IMIE2Ylx86hFtkI2p1jVFIL3yhPHesco+zezJBW1tGecgPdWep0rVDB\r\n"
"zs8JICNuxP35BN0QKVZeZoznIIPm8s1Ebc0IgI7egQKBgQD58pdgVXOO2W2+FUeD\r\n"
"1xCK4t0sfPdqCY9iSbHcNGlNndBdrSPJB+TWvAM9l0uKds24mM84vthjma1S5WG3\r\n"
"yAoZbb4nQ5VkUv5n+oA0LLKEhFLRNyKVBu7A3yLhYA2opoumTjWMH2jhRpvf0GaH\r\n"
"/CZtEm8aOKtR4td0O9Cw3r4wTQKBgQD1ooaYGWDmfLu6DwaVwPQj0DwopPO4kRWI\r\n"
"WiiEfcTi+s7kbJNUyM9qp3GJkUp9TFLK/EGHUP59Z09m5K4ezkIBpYCxwEDWXyly\r\n"
"eZanNFTolM1AMS01DhGjLYEs0n7ssbIMgOMjAziLCxCH8OBUuhHtyxUvJx0+nwlB\r\n"
"Kox0Axv4pQKBgQD3EHnbanwgjwHwa75WLucWMivoBtrVgP+vayMZhOE2LLHDdxqx\r\n"
"Y1ErhYs6fWvZQZgWSU5ETDk/Mq/mCgEuldiNzDGzRBXOpk79XtsNN8V6QgZO8c4I\r\n"
"O2MTWT10Q+sccwwFZrd9e6rDS3VWpfxDnNYq6JbT94I5Hh5Usa+WtYaP3QKBgQCq\r\n"
"VFIqxGZqTZJLmcHCNHPXJb2hnYiXspuQ2pwAC8psbujqgtPDViBmX8geUc6qhjNf\r\n"
"KH80Gxjt0qa/vdFz8SjaRW6xU5RiUsjF5cRvG53JTe3qFm+3u5LFaXeKokh7T1kc\r\n"
"zH80tzYNTNXgvkqA1io6j7mX4fKoitV7B8svYzyRNQKBgERF2ONo33QnDufqdQA7\r\n"
"iAwRcGxDPKNdvobElz8PuHCrsgHFnXC+zTRvc2G9QukY2zoWy96obDHjPqEtgI9n\r\n"
"9SD1rf0MR6/hkao0jhTggcjxo7i77WvvJl/UftXHtJ3xh6MAxhGCHgDew26awGA3\r\n"
"d9aJrcfvYoadyWnFbzfyWdCN\r\n"
"-----END PRIVATE KEY-----\r\n";

const unsigned char RSA_CLIENT_CA_CERT[]="";
#else // Iblink
const unsigned char RSA_CLIENT_CERT[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDzDCCArQCCQDiGDNlEMjDOTANBgkqhkiG9w0BAQsFADCBpzELMAkGA1UEBhMC\r\n"
"SU4xDjAMBgNVBAgMBURlbGhpMRIwEAYDVQQHDAlOZXcgRGVsaGkxIzAhBgNVBAoM\r\n"
"Gm15bmduIGF1dG9tYXRpb24gcHZ0LiBsdGQuMRgwFgYDVQQLDA9JVCAmIElubm92\r\n"
"YXRpb24xFTATBgNVBAMMDGlvLm15bmduLmNvbTEeMBwGCSqGSIb3DQEJARYPYWRt\r\n"
"aW5AbXluZ24uY29tMB4XDTE5MDgyOTA4MzI0NVoXDTI5MDgyNjA4MzI0NVowgacx\r\n"
"CzAJBgNVBAYTAklOMQ4wDAYDVQQIDAVEZWxoaTESMBAGA1UEBwwJTmV3IERlbGhp\r\n"
"MSMwIQYDVQQKDBpteW5nbiBhdXRvbWF0aW9uIHB2dC4gbHRkLjEYMBYGA1UECwwP\r\n"
"SVQgJiBJbm5vdmF0aW9uMRUwEwYDVQQDDAxpby5teW5nbi5jb20xHjAcBgkqhkiG\r\n"
"9w0BCQEWD2FkbWluQG15bmduLmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\r\n"
"AQoCggEBAKkRFhI8aogPDIGkxzHpw4OLApLjr4gCE6cyevq7f+nhaTM9GkBXjq5z\r\n"
"U8MNvXOt4yqfWsC3lnhNCmGfMRaq4dpqk/YHHG1ZZRfL86DRCGip6swZGEAEmftd\r\n"
"u9Q1J4ie4aLqoYi1EUNjpkPktyXA8bzF4IV7QREi0IUC1stHMcm/NVTgzpwnwUN0\r\n"
"NPkzqlDNhVArY4EUVVXu2tRHN86rpSz/CflZCOrP35eYqS6W1YQ4tXBonMsB3mP0\r\n"
"JQzxPeGmHHucs5iBszdrIhpt9lrVwsPCZ1W/+AD3U/4Bc0iTxY0EV0xRhUBVVZZN\r\n"
"oKxcdCcDhHuD+thL1+2wEkAbJ5BsplkCAwEAATANBgkqhkiG9w0BAQsFAAOCAQEA\r\n"
"AD0RMK1Vs7ELOSMXsFpTw2ayzkq+qYO17RJs6czE3ZMhWe5cMw4CeKZJ3XfR5BPY\r\n"
"/KRAdw5tmNo/CNAk4kz5Xoql1f6Aj/RoGids4zKIN1luAutK5TlqEsg26Rzw+3sh\r\n"
"zwKI96Ucxyq3tg/oX8pxkTv1OdumX408PcSxGy5dB+ox5jhd6ebWypReyOUz8iBR\r\n"
"wETOMMYbSqkhHynrSTOIjPikPkpfHiFAlCYJu8n7lkSrnvgWbvvVRTK6ImIFQd8i\r\n"
"FGBgFgrMLXjBHzunuvlxwe6RNovtek4GpomyQq978FvyH3oe+ve7w51Iwq+PMyaf\r\n"
"mG/5wSHqkUqF4pq6HQ0myw==\r\n"
"-----END CERTIFICATE-----\r\n";

const unsigned char RSA_CLIENT_KEY[] =
"-----BEGIN PRIVATE KEY-----\r\n"
"MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCpERYSPGqIDwyB\r\n"
"pMcx6cODiwKS46+IAhOnMnr6u3/p4WkzPRpAV46uc1PDDb1zreMqn1rAt5Z4TQph\r\n"
"nzEWquHaapP2BxxtWWUXy/Og0QhoqerMGRhABJn7XbvUNSeInuGi6qGItRFDY6ZD\r\n"
"5LclwPG8xeCFe0ERItCFAtbLRzHJvzVU4M6cJ8FDdDT5M6pQzYVQK2OBFFVV7trU\r\n"
"RzfOq6Us/wn5WQjqz9+XmKkultWEOLVwaJzLAd5j9CUM8T3hphx7nLOYgbM3ayIa\r\n"
"bfZa1cLDwmdVv/gA91P+AXNIk8WNBFdMUYVAVVWWTaCsXHQnA4R7g/rYS9ftsBJA\r\n"
"GyeQbKZZAgMBAAECggEBAInrVV0FCkb6N9Ke8JzoPUXXJf9cXHqQbyXrSWW3ha7u\r\n"
"4toY04x/oPbxP/iUAeQXi4TewLMMUWTMPFbM/cenGV4Lqa5/uJH/5jdWeuXLAJgZ\r\n"
"XWCobB71YgQsQCjqP9j0+87ip2oVhAK8jQs/zqSu1MWRiwp5NOhcxUxst3rXFmek\r\n"
"D9Mx7GGKkKu79KuFrHZQ/qToX9UPKrHDc7ROPRCejMIs+7qIPRF/PNota6s0WJNQ\r\n"
"a5ebmcDk8sBgOICfveg8OyeBhKa3rOxeOxgVrzX9cDGt5L5EpgKRbrNUNmvMeTau\r\n"
"90F9YjxASOOQu9JoBkMfmVtkn/MIguaI0eMdgjIUP60CgYEA0kcXnS2dKjATwjZ4\r\n"
"Re0rGJ/CTK4D5Z2NXb5XE26HPOXB6SoxXg840LU/R92bVcvamttNgE9sg0lv/Ij8\r\n"
"7+cysBsk0e/eTZxK8QvwmizwbxeCNRZg//ZWSc0xL512WfCPTofDYdFWlSc/4/XD\r\n"
"Ojp9EfHxoZcoQjHol8phi01VAbcCgYEAzdQGcC+QrNUiebTPg02J7qtoFbiYGywq\r\n"
"2yKPeRKdoeSjXWdFjHZpHLc7w89T9ciYaYEIPRWVT0eR7h9F62yoR7kkAzvMHTEA\r\n"
"KPte7vVY03HhWLFHg6KvoO8jBwr/XSAo/F+TRJ+ZaQNyWmNx1EkYKhgnmtyDpPv1\r\n"
"e55z8qfWWG8CgYEAjmeE73Y3rJ14lBtNYpXWjMuMy19B1lvXo/fGgqtkvPIgW2au\r\n"
"njOS140XePT0QKtYtWz1VIL1SwgN5iljmpipdCg9zEs08rx46DucytzKS4HRNWCd\r\n"
"elr6Xuqud7+cqhZHBvjccb9ScpptI1WJzEJV9zQx3qw+oG2qRjnRy4QooIsCgYAx\r\n"
"DovKSUvuJY5l+5ZJ8T0iyW+xXaHDOC+usvoHHUy8vUXCiU6mP8KluXZhIRUdy4Wn\r\n"
"/7z68h34G1LIsmNzzR3+mj3fF216t6cWHXNu+MMHAml3PimRUkER1m0+zHw4seWS\r\n"
"4SS0gmWKBexHZtRGiHVd8wvdeRlXRUYpBIcWGrKXuQKBgQCIeV6jJXLViv2RCxg8\r\n"
"lgjGyQmFOOnNYzf/vApfrY2JoTH4Eu1fqHq4xDrY++spB4sL8Ld4iK73tzHDelqt\r\n"
"FMRt/8W7A7VIh6/klFG5aZo68UCYu+WAE20Oqt3ZtvhEhqDe21yX0Q8bHiSv8mW9\r\n"
"+r/0pPy8ylTnwsHXURmI09oO5g==\r\n"
"-----END PRIVATE KEY-----\r\n";

const unsigned char RSA_CLIENT_CA_CERT[]="";

#endif


static void chainXssl_cert_luffanet(ChainX_t *chainX_req)
{
	if (chainX_req)
	{
		//chainX_req->seed = LUFFANET_SEED;
#ifdef UTIL_EX_SOCKET_CERT_TXT
		chainX_req->certificate_txt = RSA_CLIENT_CERT;
		chainX_req->certificate_txt_size = sizeof(RSA_CLIENT_CERT);

		chainX_req->privatekey_txt = RSA_CLIENT_KEY;
		chainX_req->privatekey_txt_size = sizeof(RSA_CLIENT_KEY);

		chainX_req->ca_txt = RSA_CLIENT_CA_CERT;
		chainX_req->ca_txt_size = sizeof(RSA_CLIENT_CA_CERT);

		DBG_IF_LN("(chainX_req->ca_txt_size: %zu)", chainX_req->ca_txt_size);
#else
		chainXssl_certificate_file(chainX_req, RSA_CLIENT_CERT);
		chainXssl_privatekey_file(chainX_req, RSA_CLIENT_KEY);
		chainXssl_ca_file(chainX_req, RSA_CLIENT_CA_CERT);
#endif
	}
}

void qrequest_push(ChainX_t *chainX_req, char *buff, int buff_len)
{
	DBG_IF_LN("Got !!! (buff: %s)", buff);
}

static void socket_linked(ChainX_t *chainX_req)
{
	if (chainX_linked_check(chainX_req)==0)
	{
		DBG_IF_LN("%s (%s:%u)", DBG_TXT_LINKED, chainX_req->netinfo.addr.ipv4 , chainX_req->netinfo.port);
	}
	else
	{
		DBG_IF_LN("%s (%s:%u)", DBG_TXT_BYE_BYE, chainX_req->netinfo.addr.ipv4 , chainX_req->netinfo.port);
	}
}

static int socket_init(void)
{
	chainX_pipe_register(&chainX_S, qrequest_push);
	chainX_linked_register(&chainX_S, socket_linked);
	chainXssl_cert_luffanet(&chainX_S);

	qbuf_init(&qbuf_S, MAX_OF_QBUF_1MB);
	return chainX_thread_init(&chainX_S); 
}

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	dbg_lvl_set(DBG_LVL_TRACE);
	chainX_ip_set( &chainX_S, "192.168.50.108");
	chainX_port_set( &chainX_S, 9000 );
	chainX_security_set( &chainX_S, 0 );
	socket_init();

	int count = 0;
	while (1)
	{
		sleep(1);
		if (chainX_linked_check(&chainX_S)==0)
		{
			char buff[16] = "";
			sprintf(buff, "%06d", count++);
			DBG_IF_LN("Send !!! (buff: %s)", buff);
			SOCKETX_WRITE(&chainX_S, buff, strlen(buff));
		}
	}

	chainX_thread_close(&chainX_S);
	qbuf_free(&qbuf_S);

	exit(0);
}
