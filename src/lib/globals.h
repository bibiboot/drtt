#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

#include "config.h"
#include "color.h"
#include "cprotocol.h"
#include "uthash.h"

#define CUSTOM_HEADER_SZ sizeof(struct custom_packet_header)
#define TIMESTAMP_SZ sizeof(struct timestamp)
#define DRTT_SZ (CUSTOM_HEADER_SZ + TIMESTAMP_SZ)
#define STRATUM0 1
#define STRATUM1 2
#define DRTT_REQ_PORT 1
#define DRTT_RES_PORT 2
#define CNTP_PORT 3
#define BROADCAST_ADDR 0xffff

//FILE *LOGFILE;
typedef uint16_t addr_t;
typedef uint16_t port_t;

typedef struct hashl {
    int key;
    char value[100];
    UT_hash_handle hh;
} dict_node;

struct custom_packet_header{
    addr_t next_hop_addr;
    addr_t dst_addr;
    addr_t src_addr;
    port_t dst_port;
};

struct timestamp{
    uint32_t sec;
    uint32_t fsec;
};

struct globals {
    struct config config;
    dict_node *hashl;
    pthread_t recv_th;
    pthread_t ipc_th;
    char *drtt;
};

extern struct globals globals;
