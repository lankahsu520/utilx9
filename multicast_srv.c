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
#include <arpa/inet.h>

#define MULTICAST_PORT 3618
#define MULTICAST_IP   "239.255.255.250" // 224.0.0.0 ~ 239.255.255.255

int main(int argc, char* argv[])
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	int reuse = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*) &reuse, sizeof(reuse));

	struct sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(MULTICAST_PORT);

	printf("listen ... (%s:%d)\n", MULTICAST_IP, MULTICAST_PORT);
	if (bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0)
	{
		perror("bind");
		return -1;
	}

	printf("setsockopt IP_ADD_MEMBERSHIP\n");
	struct ip_mreq seMember;
	memset((unsigned char *)&seMember, 0x00, sizeof(seMember));
	seMember.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
	seMember.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &seMember,sizeof(seMember)) < 0)
	{
		perror("setsockopt");
		return -1;
	}

#if (1)
	while (1)
	{
		char buff[1024] = "";
		struct sockaddr_in cli;
		int n = sizeof(cli);
		int nread = 0;

		fd_set fdrset;
		fd_set fdwset;
		fd_set fdeset;

		FD_ZERO(&fdrset);
		FD_SET(sockfd, &fdrset);
		FD_ZERO(&fdwset);
		FD_SET(sockfd, &fdwset);
		FD_ZERO(&fdeset);
		FD_SET(sockfd, &fdeset);

		//printf("call select ~~~\n");
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		int result = select(sockfd+1, &fdrset, (fd_set *)NULL, &fdeset, &tv);
		//printf("(result: %d)\n", result);
		if (result == -1)
		{
		}
		else if (result==0)
		{
		}
		else if (FD_ISSET(sockfd, &fdrset))
		{
#if (1)
			nread = recvfrom(sockfd, buff, 1023, 0, (struct sockaddr *)&cli, (socklen_t*)&n);

			if (nread>0)
			{
				printf("%s - %s\n", inet_ntoa(cli.sin_addr), buff);
			}
#endif
		}

		sleep(1);
	}
#endif
	if (sockfd>=0)
	{
		close(sockfd);
	}

	return 0;
}