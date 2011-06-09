#include "socket.h"

/* Handle a socket */
int create_socket() {
    int sockfd;

    /* <<GUILHERME>> ERA AF_PACKET */
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, 0)) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to open socket.\n", errsv);
        exit (EXIT_FAILURE);
    }   
    
    return sockfd;
}

/* Associating sockfd with SIOCGIFINDEX signal */
struct ifreq assoc_socket(int sockfd) {
    struct ifreq ifr;
    
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, DEVICE, IFNAMSIZ);

    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to index socket.\n", errsv);
        exit (EXIT_FAILURE);
    }
    
    return ifr;
}

/* Binding socket */
int bind_socket(int sockfd, struct ifreq ifr) {
    struct sockaddr_ll socket_address;    

    /* <<GUILHERM>> ERA AF_PACKET */
    socket_address.sll_family = AF_PACKET;
    socket_address.sll_ifindex = ifr.ifr_ifindex;
    socket_address.sll_protocol = htons(ETH_P_ALL);

    if (bind(sockfd, (const struct sockaddr *) &socket_address, sizeof(socket_address)) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to bind socket.\n", errsv);
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/* Setting Promiscuous Mode */
int promisc_socket(int sockfd, struct ifreq ifr) {
    struct packet_mreq member;

    memset(&member, 0, sizeof(member));
    member.mr_ifindex = ifr.ifr_ifindex;
    member.mr_type = PACKET_MR_PROMISC;
    
    /* <<GUILHERME>> ERA SOL_PACKET */
    if (setsockopt(sockfd, SOL_SOCKET, PACKET_ADD_MEMBERSHIP, &member, sizeof(member)) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to set promiscuous mode.\n", errsv);        
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int timeout_socket(int sockfd) {
    struct timeval tv;
    
    tv.tv_sec = 15;
    tv.tv_usec = 0;
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to set timeout to receiving messages.\n", errsv);        
        exit (EXIT_FAILURE);
    }
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to set timeout to sending messages.\n", errsv);        
        exit (EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}

/* Function to open socket */
int open_socket() {
    struct ifreq ifr;
    int sockfd;

    sockfd = create_socket();
    ifr = assoc_socket(sockfd);
    bind_socket(sockfd, ifr);
    promisc_socket(sockfd, ifr);
    timeout_socket(sockfd);
    
    return sockfd;
}

/* Send Message to Remote Host */
int send_msg(int sockfd, unsigned char *msg) {
    if (send(sockfd, msg, TAM_MAX_MESS, 0) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to send message.\n", errsv);
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

/* Recive Message from Remote Host */
unsigned char *recv_msg(int sockfd) {
    unsigned char *msg_ptr = (unsigned char *) calloc(TAM_MAX_MESS, sizeof(unsigned char));
    int i;
    
    if (msg_ptr == NULL) {
        fprintf (stderr, "Error on allocating msg_ptr\n");
        return NULL;
    }

    for (i = 0; (recv(sockfd, msg_ptr, TAM_MAX_MESS, 0) == ERROR) && (i < TRIES); i++) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to receive message.\n", errsv);
    }
    
    if (i >= TRIES) {
        fprintf (stderr, "Número máximo de time out's atingido\n");
        exit (EXIT_FAILURE);
    }

    // <<GUILHERME>> VERIFICAR SE NÃO DA PROBLEMA POR CAUSA DO CALLOC
    return msg_ptr;
}

/* Function to close socket connection  */
int close_socket(int sockfd) {
    if (shutdown( sockfd, SHUT_RDWR) == ERROR) {
        int errsv = errno;
        fprintf (stderr, "Erro number: %d, fail to close socket.\n", errsv);
        exit (EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}