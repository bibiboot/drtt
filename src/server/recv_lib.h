#include "globals.h"
#include "my_rawsocket_ts.h"
#include "utils.h"                                                              
#include "packet_filter.h"                                                      
#include "create_drtt_response.h"                                               
#include "my_socket.h" 
struct receiver_arg                                                             
{                                                                               
    char* dev;             /* device name */                                    
    addr_t my_addr;                                                             
    int inf_index;                                                              
    int send_sfd;          /* sender file descriptor */                         
    struct sockaddr_ll sk;                                                      
};  
  
void setup_receiver(struct receiver_arg*, int**, char*, int, struct msghdr*,
					struct iovec*, struct control*, struct sockaddr_in*);
