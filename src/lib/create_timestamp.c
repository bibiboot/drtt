#include "create_timestamp.h"
void 
create_timestamp(struct timestamp* ts) 
{   
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ts->sec = tv.tv_sec;
    ts->fsec = tv.tv_usec;
}

void
cal_time_diff(struct timestamp* dst, struct timestamp* a, struct timestamp* b)
{
    dst->sec = a->sec - b->sec;
    dst->fsec = a->fsec - b->fsec;
}
