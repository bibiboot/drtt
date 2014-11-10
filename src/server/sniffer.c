#include "sniffer.h"
#include "utils.h"

void*
start_sniffer(void *argument)
{
    struct sniffer_arg* arg;
    arg = (struct sniffer_arg*)argument;
    pcap_t* handle;
   
    handle = get_pcap_handle(arg->dev); 
    arg->inf_index = inf_to_index(arg->dev);
    pcap_loop(handle, -1, packet_received, argument );

}

void packet_received(u_char *argument, const struct pcap_pkthdr *header, 
                        const u_char *packet )
{
    printf("Received packet\n");
    print_drtt_packet((void *)packet);
}
