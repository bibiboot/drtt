#include "create_drtt_response.h"

/*
 * Header
 * ++++++++++++++++++++++++++++++++++++++++++++++++
 * | Next hop | Src ip | Dest ip | DRTT Resp port |
 * ++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Payload
 * ++++++++++++++++++++++++
 * | local transmit time  |
 * ++++++++++++++++++++++++
 * | remote receieve time |
 * ++++++++++++++++++++++++
 */
void
create_drtt_response(struct custom_packet_header* hdr,
                     addr_t my_addr,
                     int size,
                     struct timestamp *recv_kern )
{
    hdr->dst_addr = hdr->src_addr;
    hdr->next_hop_addr = BROADCAST_ADDR;
    //hdr->next_hop_addr = hdr->src_addr;
    //hdr->src_addr = my_addr;
    hdr->src_addr = globals.src_node;
    hdr->dst_port = DRTT_RES_PORT;

    memcpy((void *)hdr + size, recv_kern,
            sizeof(struct timestamp));
}
