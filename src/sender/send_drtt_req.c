#include "send_drtt_req.h"

/*
 * Create sending socket and populate the header
 * with broadcast next hop and send the packet.
 * No timestamping is done.
 * The packet length is equal to the header length
 */
void
send_drtt_req()
{
    void *pkt = malloc(CH_LEN);
    memset(pkt, 0, CH_LEN);

    struct sockaddr_ll sk;
    int send_sock_fd = create_sending_socket(globals.sender_inf, &sk);

    populate_header(BROADCAST_ADDR, BROADCAST_ADDR,
                    globals.src_node, DRTT_REQ_PORT, &pkt);

    send_packet(send_sock_fd, &sk, (void *)pkt, CH_LEN);

    //print_drtt_packet(pkt);
    //print_drtt_packet_net(pkt);
    //print_timestamp((struct timestamp*)(pkt + CUSTOM_HEADER_SZ));
}
