#pragma once

#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

#include "config.h"
#include "color.h"
#include "cprotocol.h"
#include "uthash.h"
#include "logger.h"

/*
 * Port nomenclature
 *
 * DRTT Request port : 1
 * DRTT Reply port   : 2
 * DRTT Recv addr    : 3
 * CNTP port         : 3
 */
#define DRTT_REQ_PORT      1
#define DRTT_RES_PORT      2
#define DRTT_RECEIVER_ADDR 3
#define CNTP_PORT          3

#define CH_LEN        68
#define DRTT_LEN      8
#define TIMESTAMP_LEN 8

//#define BROADCAST_ADDR 0xffff
#define BROADCAST_ADDR 0x0FF00      /* Filter at kernel for 0x00FF */
#define IDENTIFIER     0x0FF00

#define SECONDS      1000000000
#define MILLISECONDS 1000000
#define MICROSECONDS 1000
#define NANOSECONDS  1

#define EXTRACT_64BITS(p) \
            ((u_int64_t)((u_int64_t)*((const u_int8_t *)(p) + 0) << 56 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 1) << 48 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 2) << 40 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 3) << 32 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 4) << 24 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 5) << 16 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 6) << 8 | \
                                         (u_int64_t)*((const u_int8_t *)(p) + 7)))


typedef uint16_t addr_t;
typedef uint16_t port_t;

/*
 * Not used
 */
typedef struct hashl {
    int key;
    char value[100];
    UT_hash_handle hh;
} dict_node;

/*
 * Custom protocol
 */
struct custom_packet_header{
    addr_t identifier;     /* Custom protocol identifier */
    addr_t next_hop_addr;
    addr_t dst_addr;
    addr_t src_addr;
    port_t dst_port;
    char padding[58];
};

/*
 * Timestamp is of 64 bit
 */
struct timestamp{
    uint32_t sec;
    uint32_t fsec;
};

struct globals {
    char *drtt;             /* Calculated drtt stored here */
    dict_node *hashl;       /* Not used */
    uint16_t src_node;      /* custom IP of the node running drtt */
    pthread_t recv_th;
    pthread_t ipc_th;
    char *recv_inf;
    char *sender_inf;
    struct config config;
};

extern struct globals globals;
