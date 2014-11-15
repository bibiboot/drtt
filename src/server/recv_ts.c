#include "recv_ts.h"
void*
start_receiver(void *argument)
{
    struct msghdr msg;
    struct iovec entry;
    struct control control;
    char *payload;
    int payload_len = 1024; //[AB] put in config
    struct sockaddr_in from_addr;
    int ret;
    int s;

    payload = (char *)malloc(payload_len); 
    memset(payload, 0, payload_len);
   
    //s = create_recv_socket_ts("eth0", 5555);
    s = create_recv_rawsocket_ts("eth0", 5555);
    setup_msghdr(&msg, 
                 &entry, 
                 &control,  
                 payload, 
                 payload_len, 
                 &from_addr);

    while(1)
    {
        ret = recv_packet_ts(s, &msg, 0);
        if (ret < 0){
            printf("Error receiving\n");
            exit(1);
        }
        printpacket(&msg, ret, payload, s, 0);
        
    }
    
}

