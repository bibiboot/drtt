#include "globals.h"
#include "sniffer.h"
int main(int argc, char *argv[])
{
    /*
    struct sniffer_arg arg; 

    arg.dev = SENDER_INF;
    arg.my_addr = STRATUM1;
    start_sniffer((void*)&arg);
    */
    start_receiver(NULL);
    return 0;
}
