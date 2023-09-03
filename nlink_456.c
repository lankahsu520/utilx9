#include <linux/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/* Utility function for parse rtattr. */
static void
netlink_parse_rtattr(struct rtattr **tb, int max, struct rtattr *rta, int len)
{
	while (RTA_OK(rta, len))
	{
		if (rta->rta_type <= max)
		{
			tb[rta->rta_type] = rta;
		}
		rta = RTA_NEXT(rta, len);
	}
}

/* Recieving netlink message. */
void netlink_recv(int nsock)
{
	char buf[4096];
	struct iovec iov = { buf, sizeof(buf) };
	struct sockaddr_nl snl;
	struct msghdr msg = { (void*)&snl, sizeof(snl), &iov, 1, NULL, 0, 0};
	struct nlmsghdr *h;
	struct rtattr *tb[IFLA_MAX > IFA_MAX ? IFLA_MAX : IFA_MAX + 1];
	struct ifinfomsg *ifi;

	int status = recvmsg(nsock, &msg, 0);

	if (status < 0)
	{
		perror("recvmsg(nsock)");
		return;
	}
	else if (status == 0)
	{
		perror("recvmsg(nsock): received zero sizenetlink message");
		return;
	}

	if (msg.msg_namelen != sizeof(snl))
	{
		perror("recvmsg(nsock): received invalid netlink message");
		return;
	}

	if (msg.msg_flags & MSG_TRUNC)
	{
		perror("recvmsg(nsock): received truncated netlink message");
		return;
	}

	for (h = (struct nlmsghdr *) buf; NLMSG_OK(h, status); h = NLMSG_NEXT(h, status))
	{

		switch (h->nlmsg_type)
		{
			case NLMSG_DONE:
				return;
			case NLMSG_ERROR:
				NLMSG_DATA(h);
				if (h->nlmsg_len < NLMSG_LENGTH(sizeof(struct nlmsgerr)))
				{
					perror("received error message with invalid length");
					return;
				}
				return;
			case RTM_NEWLINK:
			case RTM_DELLINK:
				ifi = NLMSG_DATA(h);;

				int len = h->nlmsg_len - NLMSG_LENGTH(sizeof(struct ifinfomsg));
				char ifname[IF_NAMESIZE+1];
				if (len < 0)
				{
					continue;
				}

				memset(tb, 0, sizeof(tb));
				netlink_parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifi), len);

				if (tb[IFLA_IFNAME] == NULL)
				{
					continue;
				}

				strncpy(ifname, (char *) RTA_DATA(tb[IFLA_IFNAME]), IF_NAMESIZE);

				switch (h->nlmsg_type)
				{
					case RTM_NEWLINK:
						if (ifi->ifi_flags & IFF_RUNNING)
						{
							printf("interface %s(%d): UP\n", ifname, ifi->ifi_index);
						}
						else
						{
							printf("interface %s(%d): DOWN\n", ifname, ifi->ifi_index);
						}
						break;
					case RTM_DELLINK:
						printf("interface %s(%d): REMOVED\n", ifname, ifi->ifi_index);
						break;
				}
				break;
			default:
				continue;
		}
	}
}

/* Make the kernel send us an RTM_NEWLINK for all interfaces */
void netlink_getlink(int nsock)
{
	struct nlmsghdr* n;
	struct ifinfomsg *ifi;
	u_int8_t req[sizeof(struct nlmsghdr) + sizeof(struct ifinfomsg) + sizeof(struct ifaddrmsg) + 4096];

	memset(&req, 0, sizeof(req));
	n = (struct nlmsghdr*) req;
	n->nlmsg_len = NLMSG_LENGTH(sizeof(*ifi));
	n->nlmsg_type = RTM_GETLINK;
	n->nlmsg_seq = 1;
	n->nlmsg_flags = NLM_F_ROOT | NLM_F_MATCH | NLM_F_REQUEST;
	n->nlmsg_pid = 0;

	ifi = NLMSG_DATA(n);
	ifi->ifi_family = AF_UNSPEC;
	ifi->ifi_change = -1;

	if (send(nsock, n, n->nlmsg_len, 0) < 0)
	{
		perror("send");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	struct sockaddr_nl nl_addr;
	int nsock,ret;
	fd_set r;

	/* initialize netlink socket */
	if ((nsock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE)) < 0)
	{
		perror("socket");
		return 2;
	}
	memset(&nl_addr, 0, sizeof(nl_addr));
	nl_addr.nl_family = AF_NETLINK;
	nl_addr.nl_groups = RTMGRP_LINK;
	nl_addr.nl_pid = getpid();

	if ((bind(nsock, (struct sockaddr *) &nl_addr, sizeof(nl_addr))) < 0)
	{
		perror("bind");
		return 2;
	}

	netlink_getlink(nsock);
	netlink_recv(nsock);

	while (1)
	{
		FD_ZERO(&r);
		FD_SET(nsock, &r);

		ret = select(nsock + 1, &r, NULL, NULL, NULL);
		switch (ret)
		{
			case -1:
				if (errno != EINTR)
				{
					perror("select");
					return 2;
				}
				continue;
			case 0:	 /* timeout */
				break;
			default:
				break;
		}

		if (FD_ISSET(nsock, &r))
		{
			netlink_recv(nsock);
		}
	}

	return 0;
}