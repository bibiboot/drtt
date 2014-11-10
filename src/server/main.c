#include "globals.h"
#include "sniffer.h"
int main(int argc, char *argv[])
{
    struct sniffer_arg arg; 

    arg.dev = SENDER_INF;
    //arg.my_addr = DRTT_RECEIVER_ADDR;
    arg.my_addr = STRATUM1;
    //arg.my_addr = STRATUM0;
    start_sniffer((void*)&arg);
    return 0;
}
