#include "send_drtt_req.h"

void 
send_drtt_req()
{
    int s;
    void *pkt;
    struct sockaddr_ll sk;
    
    pkt = malloc(DRTT_SZ);
    memset(pkt, 0, DRTT_SZ);
    
    s = create_sending_socket();
    set_socket_inf(s, "lo", &sk); //[AB]move "lo" to config
    
    populate_header(STRATUM0, STRATUM0, STRATUM1, DRTT_REQ_PORT, &pkt);
    create_timestamp(pkt + CUSTOM_HEADER_SZ);
    
    print_drtt_packet(pkt);
    print_drtt_packet_net(pkt);
    
    send_packet(s, &sk, (void *)pkt, DRTT_SZ);

}
