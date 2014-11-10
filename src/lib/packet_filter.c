#include "packet_filter.h"
bool
is_drtt_request(void* packet)
{
    addr_t* ptr;
    ptr = (addr_t*)packet;
    //printf("Port:%d\n",*(ptr+3));
    return (DRTT_REQ_PORT == *(ptr+3));
}
/*
bool
is_src_addr_match(void* packet, addr_t my_addr)
{
    addr_t* ptr;
    ptr = (addr_t*)packet;
    return (my_addr == 
}*/
