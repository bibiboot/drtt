#include "create_drtt_response.h"
void
create_drtt_response(struct custom_packet_header* hdr, addr_t my_addr)
{
    hdr->next_hop_addr = hdr->src_addr;
    hdr->dst_addr = hdr->src_addr;
    hdr->src_addr = my_addr;
    hdr->dst_port = DRTT_RES_PORT;
}
