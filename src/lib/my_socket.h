#include "globals.h"
#include <sys/types.h>          
#include <sys/socket.h>
#include <linux/if_ether.h> 
#include <linux/if_packet.h>
int create_socket();
void set_socket_inf(int, char*, struct sockaddr_ll*);
int inf_to_index(char*);
