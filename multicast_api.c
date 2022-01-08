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

mctt_recv_fn mctt_recv_cb = NULL;

void mctt_publish(ChainXCtx_t *chainX_req, char *payload, int payload_len)
{
	MCTT_t packet;

	packet.bom = MCTT_BOM;
	packet.payload_len = payload_len;
	SAFE_MEMCPY(packet.payload, payload, payload_len, payload_len);
	packet.checksum = buff_crc16(packet.payload, packet.payload_len, 0xFFFF);

	int packet_len = sizeof(unsigned short) * 2 + sizeof(int) + payload_len;

	chainX_multi_sender(chainX_req, (char*)&packet, packet_len);
}

static void mctt_response(ChainXCtx_t *chainX_req, char *buff, int buff_len)
{
	if ((chainX_req) && (buff) && (buff_len > (4+sizeof(int))) )
	{
		MCTT_t *packet_rcv = (MCTT_t *)buff;
		if (packet_rcv->bom == MCTT_BOM)
		{
			unsigned checksum = buff_crc16(packet_rcv->payload, packet_rcv->payload_len, 0xFFFF);
			if (checksum == packet_rcv->checksum)
			{
				if (mctt_recv_cb)
				{
					mctt_recv_cb(chainX_req->c_data, packet_rcv->payload, packet_rcv->payload_len);
				}
			}
		}
	}
}

void mctt_thread_close(ChainXCtx_t *chainX_req)
{
	if ( (chainX_req) && ( chainX_req->isfree == 0 ) )
	{
		chainX_thread_stop(chainX_req);
		chainX_thread_close(chainX_req);
		SAFE_FREE(chainX_req);
	}
}

ChainXCtx_t *mctt_thread_init(void *userdata, char *ip, int port, mctt_recv_fn cb)
{
	ChainXCtx_t *chainX_req = (ChainXCtx_t*)SAFE_CALLOC(1, sizeof(ChainXCtx_t));

	if (chainX_req)
	{
		chainX_req->mode = CHAINX_MODE_ID_MULTI_RECEIVER;
		chainX_req->sockfd = -1;
		chainX_req->c_data = (void*)userdata;
		chainX_req->select_wait = TIMEOUT_OF_SELECT_1;
		chainX_req->retry_hold = TIMEOUT_OF_RETRY_HOLD,
		chainX_req->noblock =  1;
		chainX_req->isfree = 0;

		chainX_ip_set(chainX_req, ip);
		chainX_port_set(chainX_req, port);
		chainX_post_register(chainX_req, mctt_response);

		mctt_recv_cb = cb;
		chainX_thread_init(chainX_req);
	}

	return chainX_req;
}
