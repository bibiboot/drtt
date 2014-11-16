#include "globals.h"
#include "my_rawsocket_ts.h"
//#include "my_socket_ts.h"

void* start_receiver(void *argument);

struct receiver_arg
{
    char* dev;             /* device name */
    addr_t my_addr;
    int inf_index;
    int send_sfd;          /* sender file descriptor */
    struct sockaddr_ll sk;
};

