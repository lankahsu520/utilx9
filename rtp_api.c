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

//#define DBG_RTP_INFO

int rtp_port_get(void)
{
	static int rtp_port_g = 78798;
	rtp_port_g +=2;

	if (rtp_port_g >=78800)
	{
		rtp_port_g = 78700;
	}

	return rtp_port_g;
}

// unsigned char Get_Padding(rtp_hdr *rtp_hdr_msg, char *msg, int sz)
static unsigned char rtp_padding(rtp_hdr *rtp_hdr_msg, char *msg, int sz)
{
	char padding = 0;
	unsigned char len_padding = 0;

	/*
	 * Gestion du padding.
	 */
	padding = (rtp_hdr_msg->flags & 0x20) >> 5;
	if (padding)
	{
		memcpy(&len_padding, msg + (sz - 1), 1);
	}
	else
	{
		len_padding = 0;
	}
	return (len_padding);
}

#ifdef DBG_RTP_INFO
static void rtp_header_print(rtp_pkt *pkt)
{
	if (pkt->RTP_header)
	{
		DBG_TR_LN("Version       [%d]", (pkt->RTP_header->flags & 0xd0) >> 6);
		DBG_TR_LN("Padding       [%d]", (pkt->RTP_header->flags & 0x20) >> 5);
		DBG_TR_LN("Extension     [%d]", (pkt->RTP_header->flags & 0x10) >> 4);
		DBG_TR_LN("CSRC Count    [%d]", (pkt->RTP_header->flags & 0x0f));
		DBG_TR_LN("marker        [%d]", (pkt->RTP_header->mk_pt & 0x10) >> 7);
		DBG_TR_LN("PayLoad type  [%d]", (pkt->RTP_header->mk_pt & 0x7f));
		DBG_TR_LN("Sequence      [%d]", pkt->RTP_header->sq_nb);
		DBG_TR_LN("Timestamp     [%u]", pkt->RTP_header->ts);
		DBG_TR_LN("Sync Source   [0x%08x]", pkt->RTP_header->ssrc);
		if (pkt->RTP_header->csrc)
		{
			DBG_TR_LN("csrc          [%d]", (pkt->RTP_header->csrc[0]));
		}
	}
	if (pkt->RTP_extension)
	{
		DBG_TR_LN("ext->type     [%d]", (pkt->RTP_extension->ext_type));
		DBG_TR_LN("ext->len      [%d]", (pkt->RTP_extension->ext_len));
		DBG_TR_LN("ext[0]        [%d]", (pkt->RTP_extension->hd_ext[0]));
		DBG_TR_LN("ext[1]        [%d]", (pkt->RTP_extension->hd_ext[1]));
	}
	DBG_TR_LN("len PayLoad   [%d]", pkt->payload_len);
	//DBG_TR_LN("PayLoad       [%s]\n", pkt->payload);
}
#endif

// rtp_pkt	*Get_RTP_Hdr(char *msg, int  sz)
static rtp_pkt	*rtp_header_parse(char *msg, int  sz)
{
	char cc;
	char ext;
	unsigned short hdr_sz = 0;
	unsigned char len_padding = 0;

	int raw_offset = 0;

	rtp_hdr *rtp_hdr_msg = NULL;
	rtp_ext *rtp_ext_msg = NULL;
	rtp_pkt *rtp_pkt_msg = NULL;

	/*
	 * Recuperation du rtp_header.
	 */
	//MEM_SALLOC(rtp_hdr_msg, sizeof(rtp_hdr));
	rtp_hdr_msg = (rtp_hdr*)SAFE_CALLOC(1, sizeof(rtp_hdr));
	rtp_hdr_msg->flags = msg[raw_offset++];
	rtp_hdr_msg->mk_pt = msg[raw_offset++];
	rtp_hdr_msg->sq_nb = (unsigned short)byte2big_endian(2, (unsigned char*)msg+raw_offset);
	raw_offset += 2;
	rtp_hdr_msg->ts = byte2big_endian(4, (unsigned char*)msg+raw_offset);
	raw_offset += 4;
	rtp_hdr_msg->ssrc = byte2big_endian(4, (unsigned char*)msg+raw_offset);
	raw_offset += 4;

	hdr_sz = 12;

	/*
	 * Recuperation du csrc.
	 */
	cc = (rtp_hdr_msg->flags) & 0x0f;
	if (cc)
	{
		//MEM_SALLOC(rtp_hdr_msg->csrc, (cc * 4));
		rtp_hdr_msg->csrc = (unsigned long*)SAFE_CALLOC(1, (cc * 4));
		int i = 0;
		for (i = 0 ; i < cc; i++)
		{
			rtp_hdr_msg->csrc[i] = byte2big_endian(4, (unsigned char*)msg+raw_offset);
			raw_offset += 4;
		}
		hdr_sz += (cc * 4);
	}

	/*
	 * Recuperation de Ext_type et Ext_len, puis des Ext.
	 */
	ext = (rtp_hdr_msg->flags & 0x10) >> 4;
	if (ext)
	{
		//MEM_ALLOC(rtp_ext_msg);
		rtp_ext_msg = (rtp_ext*)SAFE_CALLOC(1, sizeof(rtp_ext));
		rtp_ext_msg->ext_type = byte2big_endian(2, (unsigned char*)msg+raw_offset);
		raw_offset += 2;
		rtp_ext_msg->ext_len = byte2big_endian(2, (unsigned char*)msg+raw_offset);
		raw_offset += 2;

		//MEM_SALLOC(rtp_ext_msg->hd_ext, 4 * rtp_ext_msg->ext_len);
		rtp_ext_msg->hd_ext = (unsigned long *)SAFE_CALLOC(1, 4 * rtp_ext_msg->ext_len);
		int i = 0;
		for (i = 0; i < rtp_ext_msg->ext_len; i++)
		{
			rtp_ext_msg->hd_ext[i] = byte2big_endian(4, (unsigned char*)msg+raw_offset);
			raw_offset += 4;
		}

		hdr_sz += (rtp_ext_msg->ext_len * 4) + 4;
	}

	/*
	 * Gestion du padding.
	 */
	len_padding = rtp_padding(rtp_hdr_msg, msg, sz);

	/*
	 * Revoie du packet.
	 */
	//MEM_ALLOC(rtp_pkt_msg);
	rtp_pkt_msg = (rtp_pkt*)SAFE_CALLOC(1, sizeof(rtp_pkt));
	rtp_pkt_msg->RTP_header = rtp_hdr_msg;
	rtp_pkt_msg->RTP_extension = rtp_ext_msg;
	rtp_pkt_msg->payload_len = sz - (hdr_sz + len_padding);
	//MEM_SALLOC(rtp_pkt_msg->payload, rtp_pkt_msg->payload_len);

	rtp_pkt_msg->payload = (char*)SAFE_CALLOC(1, rtp_pkt_msg->payload_len);
	memcpy(rtp_pkt_msg->payload, msg + hdr_sz, rtp_pkt_msg->payload_len);

	return (rtp_pkt_msg);
}

void rtp_context_print(sess_context_t *sess_req)
{
	if (sess_req == NULL)
	{
		DBG_ER_LN("return, sess_req is NULL !!!");
		return;
	}

	int i;
	DBG_DB_LN("***************************************************");
	DBG_DB_LN("SSRC number                      [0x%08x]", sess_req->my_ssrc);
	DBG_DB_LN("Number of packets sent           [%d]", sess_req->sending_pkt_count);
	DBG_DB_LN("Number of bytes sent             [%d]", sess_req->sending_octet_count);
	DBG_DB_LN("Version                          [%d]", sess_req->version);
	DBG_DB_LN("Marker flag                      [%d]", sess_req->marker);
	DBG_DB_LN("Padding length                   [%d]", sess_req->padding);
	DBG_DB_LN("CSRC length                      [%d]", sess_req->CSRClen);
	DBG_DB_LN("Payload type                     [%d]", sess_req->pt);
	for (i = 0; i < sess_req->CSRClen; i++)
	{
		DBG_DB_LN("CSRC list[%i]                     [%d]", i, sess_req->CSRCList[i]);
	}
	DBG_DB_LN("First value of timestamp         [%u]", sess_req->init_RTP_timestamp);
	DBG_DB_LN("Current value of timestamp       [%u]", sess_req->RTP_timestamp);
	DBG_DB_LN("Time elapsed since the beginning [%u]", sess_req->time_elapsed);
	DBG_DB_LN("First sequence number            [%d]", sess_req->init_seq_no);
	DBG_DB_LN("Current sequence number          [%d]", sess_req->seq_no);
	DBG_DB_LN("Lost sequence count              [%d]", (sess_req->seq_no - sess_req->init_seq_no + 1) - sess_req->sending_pkt_count);

	if (sess_req->hdr_extension)
	{
		DBG_DB_LN("Extension header Type            [%d]", sess_req->hdr_extension->ext_type);
		DBG_DB_LN("Extension header Len             [%d]", sess_req->hdr_extension->ext_len);
		for (i = 0; i < sess_req->hdr_extension->ext_len; i++)
		{
			DBG_DB_LN("Extension header[%d]              [%ld]", i, sess_req->hdr_extension->hd_ext[i]);
		}
	}
}

// void	Put_Pkt_in_Context(rtp_pkt *pkt, char *msg, int cid, int sz)
static void rtp_context_parse(rtp_pkt *pkt, char *msg, int sz)
{
	int i;

	if (pkt == NULL)
	{
		DBG_ER_LN("return, pkt is NULL !!!");
		return;
	}

	sess_context_t *sess_req = pkt->sess_req;

	/* SSRC number - send/receive */
	sess_req->my_ssrc = pkt->RTP_header->ssrc;

	/* Number of packets sent - send/receive */
	sess_req->sending_pkt_count++;

	/* Number of bytes sent - send/receive */
	sess_req->sending_octet_count += sz;

	/* Version - receive */
	sess_req->version = (pkt->RTP_header->flags & 0xd0) >> 6;

	/* Marker flag - receive */
	sess_req->marker = (pkt->RTP_header->mk_pt & 0x10) >> 7;

	/* Padding length - receive */
	sess_req->padding = rtp_padding(pkt->RTP_header, msg, sz);

	/* CSRC length - send/receive */
	sess_req->CSRClen = (pkt->RTP_header->flags & 0x0f);

	/* Payload type - send/receive */
	sess_req->pt = (pkt->RTP_header->mk_pt & 0x7f);

	/* CSRC list - send/receive */
	//MEM_SALLOC(sess_req->CSRCList, (sess_req->CSRClen * 4));
	sess_req->CSRCList = (unsigned int *)SAFE_CALLOC(1, sess_req->CSRClen * 4);
	memcpy(sess_req->CSRCList, pkt->RTP_header->csrc, (sess_req->CSRClen * 4));

	/* current value of timestamp - receive */
	sess_req->RTP_timestamp = pkt->RTP_header->ts;

	/* First value of timestamp - send/receive */
	if (sess_req->sending_pkt_count == 1)
	{
		sess_req->init_RTP_timestamp = sess_req->RTP_timestamp;
	}

	/* Time elapsed since the beginning - send/receive */
	if (sess_req->sending_pkt_count == 1)
	{
		sess_req->time_elapsed = 0;
	}
	else
	{
		sess_req->time_elapsed = sess_req->RTP_timestamp  - sess_req->init_RTP_timestamp;
	}

	/* Current sequence number - send/receive */
	sess_req->seq_no = pkt->RTP_header->sq_nb; //ntohs(pkt->RTP_header->sq_nb);

	/* First sequence number - send/receive */
	if (sess_req->sending_pkt_count == 1)
	{
		sess_req->init_seq_no = sess_req->seq_no;
	}

	//DBG_TR_LN("(sess_req->pt: %d, sess_req->seq_no: %d, pkt->RTP_extension: %p)", sess_req->pt, sess_req->seq_no, pkt->RTP_extension);

	if (pkt->RTP_extension)
	{
		/* Extension header - send/receive */
		//MEM_ALLOC(sess_req[cid]->hdr_extension);
		sess_req->hdr_extension = (rtp_ext*)SAFE_CALLOC(1, sizeof(rtp_ext));
		sess_req->hdr_extension->ext_len = pkt->RTP_extension->ext_len;
		sess_req->hdr_extension->ext_type = pkt->RTP_extension->ext_type;

		DBG_TR_LN("(sess_req->hdr_extension->ext_len: %d)", sess_req->hdr_extension->ext_len);
		DBG_TR_LN("(sess_req->hdr_extension->ext_type: %d)", sess_req->hdr_extension->ext_type);
		if (sess_req->hdr_extension->ext_len)
		{
			//MEM_SALLOC(sess_req->hdr_extension->hd_ext,  (4 * sess_req->hdr_extension->ext_len));
			sess_req->hdr_extension->hd_ext = (unsigned long*)SAFE_CALLOC(1, (4 * sess_req->hdr_extension->ext_len));
			memcpy(sess_req->hdr_extension->hd_ext, pkt->RTP_extension->hd_ext, (4 * sess_req->hdr_extension->ext_len));
			for (i = 0; i < sess_req->hdr_extension->ext_len; i++)
			{
				sess_req->hdr_extension->hd_ext[i] = sess_req->hdr_extension->hd_ext[i];
			}
		}
	}
}

static int h264_write_nal(RTPX_t *rtp_req)
{
	if (rtp_req)
	{
		FILE *fp = NULL;
		if ((rtp_req) && (rtp_req->http_req) && (fp = rtp_req->http_req->rtsp_req.fp))
		{
			if ((rtp_req->max_size==0) || ((rtp_req->total + 4) <= rtp_req->max_size))
			{
				unsigned char nal_header[4] = {0x00, 0x00, 0x00, 0x01};
				//unsigned char nal_header[3] = {0x00, 0x00, 0x01};

				rtp_req->total += sizeof(nal_header);
				return SAFE_FWRITE(nal_header, 1, sizeof(nal_header), fp);
			}
		}
	}
	return -1;
}

static int h264_write(RTPX_t *rtp_req, char *buf, size_t count)
{
	if (rtp_req)
	{
		FILE *fp = NULL;
		if ((rtp_req) && (rtp_req->http_req) && (fp = rtp_req->http_req->rtsp_req.fp))
		{
			if ((rtp_req->max_size==0) || ((rtp_req->total + 4) <= rtp_req->max_size))
			{
				rtp_req->total += count;

				DBG_TMP_Y("	(count: %zd, total: %zd/%zd)", count, rtp_req->total, rtp_req->max_size);

				return SAFE_FWRITE(buf, 1, count, fp);
			}
		}
	}
	return -1;
}

// RTP Payload Format for H.264 Video
// https://datatracker.ietf.org/doc/html/rfc6184
static int rtp_h264(RTPX_t *rtp_req, char *payload, long payload_len)
{
	int ret = -1;
	if (rtp_req)
	{
		{
			DBG_TMP_DUMP(payload, 16, " ", "(len: %d)", 16);

			int nal_type = (payload[0] & 0x1F);
#if (0)
			int nal_forbidden_zero = CHECK_BIT(payload[0], 7);
			int nal_nri = (payload[0] & 0x60) >> 5;
			unsigned char *ptr = (unsigned char *)payload;
			DBG_TMP_Y(">>>>> %ld, 0x%02x.0x%02x.0x%02x.0x%02x (Forbidden zero: %d, NRI: %d, Type: %d)", payload_len, ptr[0], ptr[1], ptr[2], ptr[3], nal_forbidden_zero, nal_nri, nal_type);
			//SAFE_FWRITE(payload, 1, payload_len, fp);
#endif

			if ((nal_type>= NAL_TYPE_SINGLE_NAL_MIN) && (nal_type <= NAL_TYPE_SINGLE_NAL_MAX))
			{
				// 1 ~ 23
				/* Write NAL header */
				ret = h264_write_nal(rtp_req);

				/* Write NAL unit */
				ret = h264_write(rtp_req, payload, payload_len);
			}
			else if ((nal_type >= NAL_TYPE_STAP_A) && (nal_type <= NAL_TYPE_MTAP24))
			{
				// 24 ~ 27
				unsigned char *q;
				unsigned short nalu_size;

				q = (unsigned char *)payload + 1;
				int nidx = 0;

				nidx = 0;
				while (nidx < payload_len - 1)
				{
					/* write NAL header */
					ret = h264_write_nal(rtp_req);

					/* get NALU size */
					nalu_size = (q[nidx] << 8) | (q[nidx + 1]);
					DBG_TMP_Y("(nidx: %d, NAL size: %d)", nidx, nalu_size);
					nidx += 2;

					/* write NALU size */
					ret = h264_write(rtp_req, (char *)&nalu_size, 2);

					if (nalu_size == 0)
					{
						nidx++;
						continue;
					}

					/* write NALU data */
					ret = h264_write(rtp_req, (char *)q + nidx, nalu_size);
					nidx += nalu_size;
				}
			}
			else if ((nal_type == NAL_TYPE_FU_A) || (nal_type == NAL_TYPE_FU_B))
			{
				// 28 ~ 29
				// 5.8. Fragmentation Units (FUs) (p29)
				/*
				 0							 1							 2							 3
				 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
				+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
				|  FU indicator | 	FU header 	| 						 DON							|
				+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-|
				| 																															|
				| 												 FU payload 													|
				| 																															|
				| 															+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
				| 															: 	...OPTIONAL RTP padding 		|
				+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
				*/
				int fu_b = (nal_type == NAL_TYPE_FU_B) ? 4:2;
				unsigned char *q = (unsigned char *)payload;

				unsigned char h264_key       = (q[0] & 0xE0);
				unsigned char h264_type      = (q[1] & 0x1F);
				h264_key |= h264_type;

				unsigned char h264_start_bit = (q[1] & 0x80) >> 7;
				unsigned char h264_end_bit   = (q[1] & 0x40) >> 6;


				DBG_TMP_Y("	(S: %d, E: %d, type: 0x%02x, key: 0x%02x)", h264_start_bit, h264_end_bit, h264_type, h264_key);
				if (h264_start_bit)
				{
					/* write NAL header */
					ret = h264_write_nal(rtp_req);

					/* write NAL unit code */
					ret = h264_write(rtp_req, (char *)&h264_key, sizeof(h264_key));
				}
				ret = h264_write(rtp_req, (char *)q + fu_b, payload_len - fu_b);

				if (h264_end_bit)
				{
					/* nothing to do... */
				}
			}
			else
			{
			}
		}
	}
	return ret;
}

int dummy_write(RTPX_t *rtp_req, void *buf, size_t count)
{
	if (rtp_req)
	{
		FILE *fp = NULL;
		if ((rtp_req) && (rtp_req->http_req) && (fp = rtp_req->http_req->rtsp_req.fp))
		{
			if ((rtp_req->max_size==0) || ((rtp_req->total + 4) <= rtp_req->max_size))
			{
				rtp_req->total += count;

				DBG_TMP_Y("	(total: %zd/%zd)", rtp_req->total, rtp_req->max_size);

				return SAFE_FWRITE(buf, 1, count, fp);
			}
		}
	}
	return -1;
}

static void rtp_body_free(rtp_pkt *pkt)
{
	if (pkt == NULL)
	{
		DBG_ER_LN("return, pkt is NULL !!!");
		return;
	}

	sess_context_t *sess_req = pkt->sess_req;

	/*
	 * Free Memoire.
	 */
	if ((pkt) && (pkt->RTP_extension))
	{
		SAFE_FREE(pkt->RTP_extension->hd_ext);
		SAFE_FREE(pkt->RTP_extension);
	}
	if ((pkt) && (pkt->RTP_header))
	{
		SAFE_FREE(pkt->RTP_header->csrc);
		SAFE_FREE(pkt->RTP_header);
	}
	SAFE_FREE(pkt);

	if (sess_req->hdr_extension)
	{
		SAFE_FREE(sess_req->hdr_extension->hd_ext);
		SAFE_FREE(sess_req->hdr_extension);
	}
	SAFE_FREE(sess_req->CSRCList);
	return;
}

void rtp_body_parse(RTPX_t *rtp_req, char *buff, int buff_len)
{
	if (rtp_req)
	{
		DBG_TMP_DUMP(buff, 32, " ", "(len: %d)", 32);
		rtp_pkt *pkt = rtp_header_parse(buff, buff_len);

		if (pkt)
		{
			pkt->sess_req = &rtp_req->sess_data;

			rtp_context_parse(pkt, buff, buff_len);

#ifdef DBG_RTP_INFO
			if (pkt->sess_req->sending_pkt_count==1)
			{
				rtp_header_print(pkt);
			}
			rtp_context_print(&rtp_req->sess_data);
#endif

			if (pkt->RTP_header)
			{
				int result = 0;
				switch (pkt->RTP_header->mk_pt & 0x7f)
				{
					case 96:
						result = rtp_h264(rtp_req, pkt->payload, pkt->payload_len);
						break;
					default:
						DBG_ER_LN("%s (PlayLoad Type: %d)", DBG_TXT_NO_SUPPORT, pkt->RTP_header->mk_pt & 0x7f);
						//dummy_write(rtp_req, pkt->payload, pkt->payload_len);
						break;
				}

				if (result==-1)
				{
					HttpX_t *http_req = NULL;
					if ((http_req = rtp_req->http_req))
					{
						http_req->rtsp_req.stop = 1;
					}
				}
			}
		}

		rtp_body_free(pkt);
	}
}

static void rtp_response(ChainX_t *chainX_req, char *buff, int buff_len)
{
	if ((chainX_req) && (chainX_req->c_data))
	{
		RTPX_t *rtp_req = (RTPX_t *)chainX_req->c_data;
		rtp_body_parse(rtp_req, buff, buff_len);
	}
}

void rtp_free(RTPX_t *rtp_req)
{
	if (rtp_req)
	{
		{
			rtp_context_print(&rtp_req->sess_data);
		}

		SAFE_FREE(rtp_req);
	}
}

RTPX_t *rtp_init(int port, int interleaved)
{
	RTPX_t *rtp_req = (RTPX_t*)SAFE_CALLOC(1, sizeof(RTPX_t));

	if (rtp_req)
	{
		rtp_req->total = 0;

		if (interleaved==0)
		{
			ChainX_t *chainX_req = (ChainX_t*)SAFE_CALLOC(1, sizeof(ChainX_t));
			if (chainX_req)
			{
				rtp_req->total = 0;

				chainX_req->mode = CHAINX_MODE_ID_UDP_SERVER;
				chainX_req->sockfd = -1;
				chainX_req->c_data = (void*)rtp_req;
				chainX_req->select_wait = TIMEOUT_OF_SELECT_1;

				if (port==0)
				{
					port = rtp_port_get();
				}

				chainX_ip_set(chainX_req, "0.0.0.0");
				chainX_port_set(chainX_req, port);
				chainX_post_register(chainX_req, rtp_response);

				chainX_thread_init(chainX_req);

				sleep(1);
			}
			else
			{
				SAFE_FREE(rtp_req);
			}
		}
	}

	return rtp_req;
}
