//#include "sender.h"
#include "globals.h"                                                            
#include "my_socket.h"                                                   
#include "populate_header.h"                                                    
#include "send_packet.h"
void 
sender()
{
    int s;
    struct sockaddr_ll sk;
    void *pkt;
    pkt = malloc(DRTT_SZ);
    memset(pkt, 0, DRTT_SZ);
    s = create_socket();
    set_sock_inf(s, "lo", &sk);
}
