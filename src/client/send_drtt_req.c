#include "send_drtt_req.h"

void 
send_drtt_req()
{
    int s;
    void *pkt;
    struct sockaddr_ll sk;
    
    pkt = malloc(DRTT_SZ);
    memset(pkt, 0, DRTT_SZ);
    
    s = create_sending_socket(SENDER_INF, &sk);
    //set_socket_inf(s, SENDER_INF, &sk); //[AB]move "lo" to config
    
    populate_header(BROADCAST_ADDR, BROADCAST_ADDR, STRATUM0, DRTT_REQ_PORT, &pkt);
    create_timestamp((struct timestamp*)(pkt + CUSTOM_HEADER_SZ));
    
    send_packet(s, &sk, (void *)pkt, DRTT_SZ);
   
    print_drtt_packet(pkt);
    print_drtt_packet_net(pkt);
    print_timestamp((struct timestamp*)(pkt + CUSTOM_HEADER_SZ));

}
