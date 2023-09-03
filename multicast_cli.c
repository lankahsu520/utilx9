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

#define  MULTICAST_PORT 3618
#define  MULTICAST_IP  "239.255.255.250" // 224.0.0.0 ~ 239.255.255.255

int main(int argc, char* argv[])
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	int reuse = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*) &reuse, sizeof(reuse));

	printf("link ... (%s:%d, argc: %d)\n", MULTICAST_IP, MULTICAST_PORT, argc);
	struct sockaddr_in srv;
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(MULTICAST_IP);
	srv.sin_port = htons(MULTICAST_PORT);

	char buff[1024] = "";
	if(argc>=2)
	{
		sprintf(buff, "%s", argv[1]);
		sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&srv, sizeof(srv));
		printf("sendto (buff: %s)\n", buff);
	}
	else
	{
		int i = 0;
		while(1)
		{
			sprintf(buff, "%d", i++);
			sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&srv, sizeof(srv));
			printf("sendto (buff: %s)\n", buff);


			sleep(1);
		}
	}
	close(sockfd);
	return 0;
}
