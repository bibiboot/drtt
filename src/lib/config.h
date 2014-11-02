#pragma once

#define CONFIG_INIT { \
    .packet_len = 65535, \
    .rtt = 2, }

struct config {
    uint16_t rtt;
    uint16_t packet_len;
};
