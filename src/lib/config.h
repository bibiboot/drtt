#pragma once

#define CONFIG_INIT { \
    .packet_len = 65535 , \
    .ipc_sleep_time = 2*1, \
    .recv_payload_len = 1024, \
    .rtt = 2 ,}

struct config {
    uint16_t rtt;
    uint16_t packet_len;
    uint16_t ipc_sleep_time;
    uint16_t recv_payload_len;
};

