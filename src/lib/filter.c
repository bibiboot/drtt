#include "filter.h"

bool is_drtt_request(unsigned char *packet)
{
    struct custom_packet_header *hdr = (struct custom_packet_header *)packet;
    /*
    printf("Next hop : %d\n", hdr->next_hop_addr);
    printf("Port     : %d\n", hdr->dst_port);
    printf("Src node : %d\n", globals.src_node);
    printf("Cntp port: %d\n", DRTT_REQ_PORT);
    */

    if (hdr->next_hop_addr == BROADCAST_ADDR &&
        hdr->src_addr != globals.src_node &&
        hdr->dst_port == DRTT_REQ_PORT) {
        return true;
    }

    return false;
}

bool is_drtt_reply(unsigned char *packet)
{
    struct custom_packet_header *hdr = (struct custom_packet_header *)packet;
    /*
    printf("Next hop : %d\n", hdr->next_hop_addr);
    printf("Port     : %d\n", hdr->dst_port);
    printf("Src node : %d\n", globals.src_node);
    printf("Cntp port: %d\n", DRTT_RES_PORT);
    */

    if (hdr->next_hop_addr == globals.src_node &&
        hdr->src_addr != globals.src_node &&
        hdr->dst_port == DRTT_RES_PORT) {
        return true;
    }

    return false;
}
