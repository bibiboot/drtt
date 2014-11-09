#include "globals.h"
#include <sys/time.h>
void 
create_timestamp(uint32_t *ts) 
{   
    struct timeval tv;
    gettimeofday(&tv, NULL);
    *ts = tv.tv_sec;
    *(ts + 1) = tv.tv_usec;
}
