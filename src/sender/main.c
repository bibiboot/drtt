#include "globals.h"

int main(int argc, char *argv[])
{
    globals.src_node = atoi(argv[1]);

    send_drtt_req();
    return 0;
}
