#include "globals.h"
#include "my_pcap.h"
struct sniffer_arg
{
    char* dev;
    addr_t my_addr;
    int inf_index;
};

void packet_received(u_char*, const struct pcap_pkthdr *, const u_char *);
void* start_sniffer(void *);
