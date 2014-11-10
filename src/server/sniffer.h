#include "globals.h"
#include "my_pcap.h"
#include <linux/if_packet.h>
struct sniffer_arg
{
    char* dev;      //device name
    addr_t my_addr; 
    int inf_index;  
    int send_sfd;   //sender socket file descriptor
    struct sockaddr_ll sk;
};

void packet_received(u_char*, const struct pcap_pkthdr *, const u_char *);
void* start_sniffer(void *);
