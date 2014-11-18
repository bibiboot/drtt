#include "recv_lib.h"
void 
setup_receiver(struct receiver_arg* arg, int* s, char** payload, 
			   int payload_len, struct msghdr* msg, struct iovec* entry, 
			   struct control* control, struct sockaddr_in* from_addr)
{                                         
    arg->inf_index = inf_to_index(arg->dev);                                    
    arg->send_sfd = create_sending_socket(arg->dev, &(arg->sk));                
                                                                                
    *payload = (char *)malloc(payload_len);        
	if (NULL == payload){
		printf("malloc failed\n");
		exit(1);
	}                              
    memset(*payload, 0, payload_len);                                            
                                                                                
    *s = create_recv_rawsocket_ts(arg->dev);                                     
    set_promisc(arg->dev, *s);                                                   
    setup_raw_msghdr(msg,                                                      
                 entry,                                                        
                 control,                                                      
                 *payload,                                                       
                 payload_len,                                                   
                 from_addr);      
}

/*Returns the custom packets payload len. The first arg is custom packet start
 *and second is the total size as received (which includes custom header)*/
int
get_cpacket_payload_len(char *pkt, int total_sz)
{
	int c_pl_len, c;
	struct timestamp* fts;
	struct timestamp* nts;
	//Minimum raw socket can receive is 60 bytes
	if (total_sz > 60){
		return (60 - CUSTOM_HEADER_SZ);
	}
	c = 0;
	fts = FIRST_TS(pkt);
	nts = fts;
	while (!IS_TS_ZERO(nts)){
		nts = NEXT_TS(nts);	
		c++;
	}
	printf("c_packet_payload_len returning:%lu\n",c * TIMESTAMP_SZ);
	return c * TIMESTAMP_SZ;
}

int 
get_cntp_hops(char* pkt, int total_sz)
{
	int pl_sz;
	int hops = -1;
	pl_sz = get_cpacket_payload_len(pkt, total_sz);
	if (pl_sz % TIMESTAMP_SZ){
		//Sanity check
		printf("cntp packet payload size is not multiple of TIMESTAMP_SZ\n");
		exit(1);
	}
	if (pl_sz == (2 * TIMESTAMP_SZ)){
		hops = 0; 
	}
	else if (pl_sz >  (2 * TIMESTAMP_SZ)){
		hops = ((pl_sz / TIMESTAMP_SZ) - 2) / 3;
	}
	
	if (-1 == hops){
		printf("Not expected number of timestamps in the packet\n");
		exit(1);
	}
	printf("cntp_hops:%d\n", hops);
	return hops;
}
uint64_t
cal_offset(char *pkt, int total_sz, struct timestamp* s1_rx_ts)
{
	uint64_t proc_time, offset, total_proc_time, total_drtt;
	int hops;
	int c;
	
	struct timestamp* fts;
	struct timestamp* nts;
	struct timestamp* rx;
	struct timestamp* drtt;
	struct timestamp* tx;

    offset = 0;
	proc_time = 0;
    total_proc_time = 0;
    total_drtt = 0;
  
	fts = FIRST_TS(pkt);
	printf("s0_drtt_ts:\t%u.%u\n", fts->sec, fts->fsec);
	nts = NEXT_TS(fts);
	printf("s0_tx_ts:\t%u.%u\n", nts->sec, nts->fsec);

	hops = get_cntp_hops(pkt, total_sz);
	c = 0;
	while (c < hops){
		rx = NEXT_TS(nts);
		printf("rtr%d_rx_ts:\t%u.%u\n", c, rx->sec, rx->fsec); 
		drtt = NEXT_TS(rx);
		printf("rtr%d_drtt_ts:\t%u.%u\n", c, drtt->sec, drtt->fsec); 
		tx = NEXT_TS(drtt);
		printf("rtr%d_tx_ts:\t%u.%u\n", c, tx->sec, tx->fsec);
		proc_time = ((tx->sec - rx->sec) * 1000 * 1000 ) 
                    + (tx->fsec - rx->fsec);
		total_proc_time += proc_time;
		printf("rtr%d_proc time:\t%" PRIu64 "\n", c, proc_time);
		printf("total proc time:\t%" PRIu64 "\n", total_proc_time);
		c++; 
	}
}
