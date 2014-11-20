#include "globals.h"

int main(int argc, char *argv[])
{
    globals.src_node = atoi(argv[1]);
    globals.sender_inf = argv[2];

    send_drtt_req();
    return 0;
}
