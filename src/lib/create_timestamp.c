#include "create_timestamp.h"

void
create_timestamp(struct timestamp* ts)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ts->sec = tv.tv_sec;
    ts->fsec = tv.tv_usec;
}

void print_timestamp_hex(unsigned char *timestamp_payload)
{
    printf("Timestamp payload : ");
    int i;
    for(i=0; i<8; i++) {
        printf(" %.2X", timestamp_payload[i]);
    }
    printf("\n");
}

void reverse_kernel_timestamp(unsigned char *payload, int offset)
{
    unsigned char *timestamp_payload = payload + offset;

    //print_timestamp_hex(timestamp_payload);
    int i;
    for(i=0; i<4; i++) {
        char temp = timestamp_payload[i];
        timestamp_payload[i] = timestamp_payload[7-i];
        timestamp_payload[7-i] = temp;
    }
    //print_timestamp_hex(timestamp_payload);

    //printf("Timestamp payload :  %lu\n",EXTRACT_64BITS(timestamp_payload));
}

/*
 * Parses the payload of drtt response
 * and gets the following values
 *
 *      1. local transmit time
 *      2. remote recieve time
 *      3. local recieve time
 *      4. remote transmit time
 *
 * Reverse the remove transmit time as it is kernel time.
 *
 * The difference is calculated as
 *
 *      Remote processing = remote receieve time - remote transmit time
 *      Total delay = local receive time - local transmit time
 *
 *      Effective round trip delay = Total delay - Remote processing
 */
void
cal_roundtrip_delay(struct timestamp* roundtrip_delay,
                    struct timestamp* local_rx,
                    unsigned char *payload)
{
    /*
    struct timestamp *local_tx, *remote_rx, *remote_tx;
    local_tx = (struct timestamp *)(payload + CH_LEN);
    remote_rx = local_tx + 1;
    remote_tx = local_tx + 2;
    printf("\n");
    */

    /*
     * Local tx and Remote tx are kernel time
     * Must be printed in kernel way
     * Remote tx must be reversed before reading.
     */
    /* Reverse Remote transmission timestamp */
    reverse_kernel_timestamp(payload, 2*TIMESTAMP_LEN);
    reverse_kernel_timestamp(payload, 3*TIMESTAMP_LEN);

    unsigned long local_xmit_time  = (unsigned long)EXTRACT_64BITS(payload);
    unsigned long remote_recv_time = (unsigned long)EXTRACT_64BITS(payload + TIMESTAMP_LEN);
    unsigned long remote_xmit_time = (unsigned long)EXTRACT_64BITS(payload + 2*TIMESTAMP_LEN);
    unsigned long local_recv_time  = (unsigned long)EXTRACT_64BITS(payload + 3*TIMESTAMP_LEN);

    unsigned long user_recv_time  = (unsigned long)local_rx->sec * SECONDS + local_rx->fsec * NANOSECONDS;

    printf("Local transmit timestamp   : %lu\n", local_xmit_time);
    printf("Remote receieve timestamp  : %lu\n", remote_recv_time);
    printf("Remote transmit timestamp  : %lu\n", remote_xmit_time);
    printf("Local receieve timestamp   : %lu\n", local_recv_time);
    printf("User Local receieve time   : %lu\n", user_recv_time);

    unsigned long processing_time = remote_xmit_time - remote_recv_time;
    unsigned long observed_delay  = local_recv_time - local_xmit_time;

    printf("Effective round trip delay : %lu\n", observed_delay - processing_time);
    sprintf(globals.drtt, "%lu", observed_delay - processing_time);
}
