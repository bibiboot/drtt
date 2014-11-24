#include "recv_ts.h"

void drtt_request_handler( struct receiver_arg *arg,
                           struct timestamp recv_kern,
                           unsigned char *payload )
{
    struct timeval recv_usr;
    gettimeofday(&recv_usr, 0);

    reverse_kernel_timestamp(payload, CH_LEN);
    reverse_kernel_timestamp(payload, CH_LEN + TIMESTAMP_LEN);

    unsigned long local_xmit_time  = (unsigned long)EXTRACT_64BITS(payload + CH_LEN);
    unsigned long remote_recv_time = (unsigned long)EXTRACT_64BITS(payload + CH_LEN + TIMESTAMP_LEN);
    unsigned long user_recv_time   = (unsigned long)recv_usr.tv_sec * SECONDS + recv_usr.tv_usec * MICROSECONDS;

    printf("[Kernel][ %lu ] : Local transmit timestamp\n", local_xmit_time);
    printf("[Kernel][ %lu ] : Remote recieve timestamp\n", remote_recv_time);
    printf("[User  ][ %lu ] : Sending DRTT response\n", user_recv_time);

    struct custom_packet_header *hdr = (struct custom_packet_header*)payload;
    create_drtt_response(hdr);

    send_packet(arg->send_sfd, &(arg->sk), (void*)payload, CH_LEN + (2 * TIMESTAMP_LEN));

    printf("DRTT Response send\n");
}

void*
start_receiver(void *argument)
{
    struct msghdr msg;
    struct iovec entry;
    struct control control;
    unsigned char *packet;
    int recv_socket_fd;
    struct sockaddr_in from_addr;
    int payload_len = globals.config.recv_payload_len;
    struct receiver_arg *arg = (struct receiver_arg*)argument;

    setup_receiver(arg, &recv_socket_fd,
                   &packet, payload_len,
		   &msg, &entry,
                   &control, &from_addr);

    int err_packet;
    int num_bytes_read;
    struct timestamp recv_kern;
    struct timestamp roundtrip_delay;
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

	if (is_drtt_request(packet)) {

            drtt_request_handler(arg, recv_kern, packet);

        } else if (is_drtt_reply(packet)) {

            unsigned long kernel_recv_time = (unsigned long)recv_kern.sec * SECONDS + recv_kern.fsec * NANOSECONDS;

 	    //printf("[Kernel][ %lu ] : Recieved DRTT response\n", kernel_recv_time);
            printf("Num bytes read : %d\n", num_bytes_read);

            cal_roundtrip_delay(&roundtrip_delay, &recv_kern, packet + CH_LEN);

        } else {

           //printf("Unknown packet\n");

        }
    }
}
