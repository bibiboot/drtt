#include "recv_ts.h"

void drtt_request_handler( struct receiver_arg *arg,
                           struct timestamp recv_kern,
                           unsigned char *payload )
{
    struct timeval recv_usr;
    gettimeofday(&recv_usr, 0);

    reverse_kernel_timestamp(payload, CH_LEN);

    unsigned long local_xmit_time  = (unsigned long)EXTRACT_64BITS(payload + CH_LEN);
    unsigned long user_recv_time   = (unsigned long)recv_usr.tv_sec * SECONDS + recv_usr.tv_usec * MICROSECONDS;
    unsigned long kernel_recv_time = (unsigned long)recv_kern.sec * SECONDS + recv_kern.fsec * NANOSECONDS;

    printf("[Kernel][ %lu ] : Local transmit timestamp\n", local_xmit_time);
    printf("[Kernel][ %lu ] : Recieved DRTT request\n", kernel_recv_time);
    printf("[User  ][ %lu ] : Sending DRTT response\n", user_recv_time);

    struct custom_packet_header *hdr = (struct custom_packet_header*)payload;
    create_drtt_response(hdr, globals.src_node, CH_LEN + TIMESTAMP_LEN, &recv_kern);

    send_packet(arg->send_sfd, &(arg->sk), (void*)payload, CH_LEN + (2 * TIMESTAMP_LEN));

    printf("DRTT Response send\n");
}

void*
start_receiver(void *argument)
{
    struct msghdr msg;
    struct iovec entry;
    struct control control;
    char *payload;
    int recv_socket_fd;
    struct sockaddr_in from_addr;
    int payload_len = globals.config.recv_payload_len;
    struct receiver_arg *arg = (struct receiver_arg*)argument;

    setup_receiver(arg, &recv_socket_fd,
                   &payload, payload_len,
		   &msg, &entry,
                   &control, &from_addr);

    int err_packet;
    int num_bytes_read;
    struct timestamp recv_kern;
    struct timestamp roundtrip_delay;
    struct custom_packet_header* hdr;
    struct timeval recv_usr;

    while(1)
    {
        num_bytes_read = recv_rawpacket_ts(recv_socket_fd, &msg,
                                           0, &err_packet, &recv_kern);
        if (num_bytes_read < 0){
            printf("Error receiving\n");
            exit(1);
        } else if(err_packet){
	    printf("Error packet encountered. Exiting.\n");
	    exit(1);
	}

        hdr = (struct custom_packet_header*)payload;
	if (IS_SRC_ADDR_MATCH(hdr, globals.src_node)){

	    continue;

	} else if (IS_DRTT_REQUEST(hdr)) {

            drtt_request_handler(arg, recv_kern, payload);

        } else if (IS_DRTT_RESPONSE(hdr)) {

            unsigned long kernel_recv_time = (unsigned long)recv_kern.sec * SECONDS + recv_kern.fsec * NANOSECONDS;

 	    //printf("[Kernel][ %lu ] : Recieved DRTT response\n", kernel_recv_time);

            cal_roundtrip_delay(&roundtrip_delay, &recv_kern, payload);

        } else {

           //printf("Unknown packet\n");

        }
    }
}
