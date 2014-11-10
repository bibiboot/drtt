#include "sniffer.h"
#include "utils.h"
#include "packet_filter.h"
#include "create_drtt_response.h"
#include "my_socket.h"
void*
start_sniffer(void *argument)
{
    struct sniffer_arg* arg;
    arg = (struct sniffer_arg*)argument;
    pcap_t* handle;
   
    handle = get_pcap_handle(arg->dev); 
    arg->inf_index = inf_to_index(arg->dev);
    arg->send_sfd = create_sending_socket(arg->dev, &(arg->sk));
    pcap_loop(handle, -1, packet_received, argument );

}

void packet_received(u_char *argument, const struct pcap_pkthdr *header, 
                        const u_char *packet )
{
    struct custom_packet_header* hdr;
    struct sniffer_arg* arg;
    struct timestamp ts;
    struct timestamp time_diff;
    struct timestamp *from_packet;

    hdr = (struct custom_packet_header*)packet;
    arg = (struct sniffer_arg*)argument;

    if (!IS_SRC_ADDR_MATCH(hdr, arg->my_addr)){
        printf("Received packet\n");
        print_drtt_packet((void*)packet);
        
        if (IS_DRTT_REQUEST(hdr)) {
            printf("Received drtt request\n");
            create_drtt_response(hdr, arg->my_addr);
            printf("Processed response\n");
            print_drtt_packet((void*)packet);
            send_packet(arg->send_sfd, &(arg->sk), (void*)packet, DRTT_SZ );
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

}
