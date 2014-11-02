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

extern struct globals globals;
