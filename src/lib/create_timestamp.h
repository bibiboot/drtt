#include "globals.h"

#include <sys/time.h>

void create_timestamp(struct timestamp*);

void cal_time_diff(struct timestamp*, struct timestamp*, unsigned char* payload);

void reverse_kernel_timestamp(unsigned char *payload, int offset);
