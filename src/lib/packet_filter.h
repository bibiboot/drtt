#include "globals.h"

#define IS_BROADCAST(pkt) \
    ((pkt->dst_addr == BROADCAST_ADDR) && \
    (pkt->next_hop_addr == BROADCAST_ADDR)) 

#define IS_DRTT_REQUEST(pkt) \
    ((pkt->dst_port == DRTT_REQ_PORT) && IS_BROADCAST(pkt) )

#define IS_DRTT_RESPONSE(pkt) \
    (pkt->dst_port == DRTT_RES_PORT)

#define IS_CNTP(pkt) \
    (pkt->dst_port == CNTP_PORT)

#define IS_DST_MATCH(pkt, sa) (pkt->dst_addr == (sa))

#define IS_SRC_ADDR_MATCH(pkt, sa) (pkt->src_addr == (sa))

