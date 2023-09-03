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

#include <stdlib.h>

#define USE_NSLOOKUP
#define USE_DNS_IP
#define USE_NETLIST
#define USE_IFACE_INFO
//#define USE_NWLOOP

#ifdef USE_NWLOOP
#include <net/if.h>
//#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

static void network_loop(void * data)
{
	struct sockaddr_nl addr;
	int nls, len, rtl;
	char buffer[4096];

	struct nlmsghdr * nlh;
	struct ifaddrmsg * ifa;
	struct rtattr * rth;

	if((nls = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE)) == -1)
	{
		printf("MY_PROG: socket failure\n");
	}

	memset(&addr, 0, sizeof(addr));
	addr.nl_family = AF_NETLINK;
	addr.nl_groups = 0xffffffff;//RTMGRP_IPV4_IFADDR;

	if(bind(nls, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		printf("MY_PROG:network_work_handler bind failure\n");
	}

	nlh = (struct nlmsghdr *)buffer;

	while((len = recv(nls, nlh, 4096, 0)) > 0)
	{
		for(; (NLMSG_OK(nlh, len)) && (nlh->nlmsg_type != NLMSG_DONE); nlh = NLMSG_NEXT(nlh, len))
		{
			if(nlh->nlmsg_type == RTM_NEWADDR)
			{
				printf("MY_PROG:network_work_handler RTM_NEWADDR\n");
			}
			else if(nlh->nlmsg_type == RTM_DELADDR)
			{
				printf("MY_PROG:network_work_handler RTM_DELADDR\n");
			}
			else
			{
				printf("MY_PROG:network_work_handler nlmsg_type=%d\n", nlh->nlmsg_type);
			}

			if((nlh->nlmsg_type != RTM_NEWADDR) && (nlh->nlmsg_type != RTM_DELADDR))
			{
				continue; /* some other kind of announcement */
			}

			ifa = (struct ifaddrmsg *)NLMSG_DATA(nlh);

			rth = IFA_RTA(ifa);
			rtl = IFA_PAYLOAD(nlh);

			for(; rtl && RTA_OK(rth, rtl); rth = RTA_NEXT(rth, rtl))
			{
				char name[IFNAMSIZ];
				uint32_t ipaddr;

				if(rth->rta_type != IFA_LOCAL)
				{
					continue;
				}

				ipaddr = * ((uint32_t *) RTA_DATA(rth));
				ipaddr = htonl(ipaddr);

				printf("MY_PROG:network_work_handler %s is now %X\n", if_indextoname(ifa->ifa_index, name), ipaddr);
			}
		}
	}
}
#endif

int main(int argc, char* argv[])
{
	DBG_TR_LN("enter");

	//dbg_lvl_set(DBG_LVL_DEBUG);

#ifdef UTIL_EX_CHAINX
#ifdef USE_NSLOOKUP
	if(argc>=2)
	{
		char hostname[LEN_OF_HOSTNAME]="";
		char ipv4[LEN_OF_IP] = "";
		char ipv6[LEN_OF_IP] = "";

		SAFE_SPRINTF_EX(hostname, "%s", argv[1]);

		chainX_nslookup(hostname, ipv4, sizeof(ipv4));
		DBG_IF_LN("(%s -> ipv4: %s)", hostname, ipv4);
		chainX_nslookup6(hostname, ipv6, sizeof(ipv6));
		DBG_IF_LN("(%s -> ipv6: %s)", hostname, ipv6);
	}
#endif

#ifdef USE_DNS_IP
	{
		char dns[LEN_OF_BUF1024] = "";
		chainX_dns_get(dns);
		DBG_LN_Y("dns: %s", dns);
	}
#endif

#ifdef USE_NETLIST
	{
		chainX_if_list(NULL);
		DBG_LN_LN();
	}
#endif

#ifdef USE_IFACE_INFO
	{
		char iface[] = "eth2.2";
		DBG_LN_Y("**************************************************");
		DBG_LN_Y("** %s **", iface);

		char ip[LEN_OF_IP] = "";
		chainX_if_ipaddr(iface, ip, sizeof(ip));
		DBG_LN_Y("ip: %s", ip);

		char netmask[LEN_OF_IP] = "";
		chainX_if_netmask(iface, netmask, sizeof(netmask));
		DBG_LN_Y("netmask: %s", netmask);

		char broadcast[LEN_OF_IP] = "";
		chainX_if_broadcast(iface, broadcast, sizeof(broadcast));
		DBG_LN_Y("broadcast: %s", broadcast);

		char gateway[LEN_OF_IP] = "";
		chainX_if_gateway(iface, gateway, sizeof(gateway));
		DBG_LN_Y("gateway: %s", gateway);

		char ethmac[LEN_OF_MAC]= "";
		chainX_if_hwaddr(iface, ethmac, sizeof(ethmac), ":");
		DBG_LN_Y("ethmac: %s", ethmac);

		chainX_if_hwaddr(iface, ethmac, sizeof(ethmac), "");
		DBG_LN_Y("ethmac: %s", ethmac);
	}

	{
		char iface[] = "ra0";
		DBG_LN_Y("**************************************************");
		DBG_LN_Y("** %s **", iface);

		char ip[LEN_OF_IP] = "";
		chainX_if_ipaddr(iface, ip, sizeof(ip));
		DBG_LN_Y("ip: %s", ip);

		char netmask[LEN_OF_IP] = "";
		chainX_if_netmask(iface, netmask, sizeof(netmask));
		DBG_LN_Y("netmask: %s", netmask);

		char broadcast[LEN_OF_IP] = "";
		chainX_if_broadcast(iface, broadcast, sizeof(broadcast));
		DBG_LN_Y("broadcast: %s", broadcast);

		char gateway[LEN_OF_IP] = "";
		chainX_if_gateway(iface, gateway, sizeof(gateway));
		DBG_LN_Y("gateway: %s", gateway);

		char ethmac[LEN_OF_MAC]= "";
		chainX_if_hwaddr(iface, ethmac, sizeof(ethmac), ":");
		DBG_LN_Y("ethmac: %s", ethmac);

		chainX_if_hwaddr(iface, ethmac, sizeof(ethmac), "");
		DBG_LN_Y("ethmac: %s", ethmac);

		char ssid[LEN_OF_SSID]= "";
		chainX_if_ssid("ra0", ssid, sizeof(ssid));
		DBG_LN_Y("ssid: %s", ssid);
	}
#endif

	//chainX_if_staticip(iface, "192.168.50.106", "255.255.255.0", "192.168.50.1");
#endif

	exit(0);
}
