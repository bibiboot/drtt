#include "recv_ts.h"
#include "utils.h"
#include "packet_filter.h"                                                      
#include "create_drtt_response.h"                                               
#include "my_socket.h" 
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
    int err_packet;
    struct timeval now;

    struct custom_packet_header* hdr;                                           
    struct timestamp ts;                                                        
    struct timestamp time_diff;                                                 
    struct timestamp *from_packet;
    struct receiver_arg* arg;                                                    
    
    arg = (struct receiver_arg*)argument;


    payload = (char *)malloc(payload_len); 
    memset(payload, 0, payload_len);
   
    s = create_recv_rawsocket_ts(arg->dev);
    setup_msghdr(&msg, 
                 &entry, 
                 &control,  
                 payload, 
                 payload_len, 
                 &from_addr);
    
    while(1)
    {
        ret = recv_rawpacket_ts(s, &msg, 0, &err_packet);
        if (ret < 0){
            printf("Error receiving\n");
            exit(1);
        }
        gettimeofday(&now, 0);
        printf("User space ts:%ld.%06ld: received %d bytes\n",                                    
               (long)now.tv_sec, (long)now.tv_usec, ret);
        if (!err_packet) {
            hdr = (struct custom_packet_header*)payload;

            if (!IS_SRC_ADDR_MATCH(hdr, arg->my_addr)){                                 
                printf("Received packet\n");                                            
                print_drtt_packet((void*)payload);                                       
                                                                                
                if (IS_DRTT_REQUEST(hdr)) {                                             
                    printf("Received drtt request\n");                                  
                    create_drtt_response(hdr, arg->my_addr);                            
                    printf("Processed response\n");                                     
                    print_drtt_packet((void*)payload);                                   
                    send_packet(arg->send_sfd, &(arg->sk), (void*)payload, DRTT_SZ );    
                }                                                                       
                                                                                
                else if (IS_DRTT_RESPONSE(hdr)){                                        
                    create_timestamp(&ts);                                              
                    from_packet = (struct timestamp*)(hdr+1);                           
                    cal_time_diff(&time_diff, &ts, from_packet);                        
                                                                                 
                    printf("Time now\n");                                               
                    print_timestamp(&ts);                                               
                    printf("Time from packet\n");                                       
                    print_timestamp(from_packet);                                       
                    printf("Time diff\n");                                              
                    print_timestamp(&time_diff);                                        
                }                                                                       
            }                                           

            //Regular packet
            //print_drtt_packet((void *)payload);
        }
        print_kernel_ts(&msg);
        //print_rawpacket(&msg, ret, payload, s, 0);
        
    }
    
}

