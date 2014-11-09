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

FILE *LOGFILE;

typedef struct hashl {
    int key;
    char value[100];
    UT_hash_handle hh;
} dict_node;

struct globals {
    struct config config;
    dict_node *hashl;
};
struct custom_packet_hdr{                                                       
    uint16_t next_hop_addr;                                                     
    uint16_t dst_addr;                                                          
    uint16_t src_addr;                                                          
    uint16_t dst_port;                                                          
};                                                                              
extern struct globals globals;

#define CUSTOM_HEADER_SZ sizeof(struct custom_packet_hdr)                       
#define TIMESTAMP_SZ sizeof(uint64_t)                                           
#define DRTT_SZ (CUSTOM_HEADER_SZ + TIMESTAMP_SZ)

