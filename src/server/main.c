#include "globals.h"
#include "sniffer.h"
#include "ipc_master.h"
#include "recv_ts.h"

/*
 * Create two threads
 * 1. Sniffer thread which replies back as welll as
 *    recv reply and calcukates the drtt and stores it
 *    in global variable.
 * 2. IPC thread which stores the drtt at certain
 *    memory location.
 */
void start(void *recv_arg)
{
    pthread_create(&(globals.recv_th), 0, start_receiver, recv_arg);
    pthread_create(&(globals.ipc_th), 0, start_ipc_master, NULL);

    pthread_join(globals.recv_th, NULL);
    pthread_join(globals.ipc_th, NULL);
}

int main(int argc, char *argv[])
{
    struct sniffer_arg arg;

    arg.dev = SENDER_INF;
    arg.my_addr = STRATUM1;
    start((void*)&arg);

     /*
     * Deprecated
     * Shifted to raw socket
     */
    //start_receiver((void*)&arg);
    //start_sniffer((void*)&arg);
    return 0;
}
