#include "recv_ts.h"
#include "utils.h"
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
    int port;
    struct timeval now;

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
        ret = recv_rawpacket_ts(s, &msg, 0, &port);
        if (ret < 0){
            printf("Error receiving\n");
            exit(1);
        }
        gettimeofday(&now, 0);
        printf("User space ts:%ld.%06ld: sent %d bytes\n",                                    
               (long)now.tv_sec, (long)now.tv_usec, ret);
        if (port == 0){
            //Regular packet
             print_drtt_packet((void *)payload);
        }
        print_kernel_ts(&msg);
        //print_rawpacket(&msg, ret, payload, s, 0);
        
    }
    
}

