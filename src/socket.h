#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <net/ethernet.h> /* the L2 protocols */
#include <errno.h>
#include "message.h"

#define DEVICE "eth0"
#define TRIES  10
#define ERROR  -1

int create_socket();
struct ifreq assoc_socket(int sockfd);
int bind_socket(int sockfd, struct ifreq ifr);
int promisc_socket(int sockfd, struct ifreq ifr);
int timeout_socket(int sockfd);
int open_socket();
int send_msg(int sockfd, unsigned char *msg);
unsigned char *recv_msg(int sockfd);
int close_socket(int sockfd);

#endif /* Final de SOCKET_H */