/*
** Listen for broadcast VPA Discovery Broadcast
	Copyright (c) 2019 Douglas Wade Goodall
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "vpa.h"

#define MAXBUFLEN 100


//////////////////////////////////////
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

////////////////////////////////////////////////////////
int 
discovery_listener( struct DISCOVERY_REQUEST  * request)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

	struct RESPONSE_PACKET packet;

	printf("Virtual Protocol Adapter Discovery Listener\n");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, VPA_DISC_PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    printf("listener: waiting to recvfrom...\n");

    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

    printf("listener: got packet from %s\n",
        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s));
    printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: packet contains \"%s\"\n", buf);

	response_packet.version.rmj = RMJ;
	response_packet.version.rmn = RMN;
	response_packet.version.rup = RUP;
	response_packet.version.rpt = RPT;
	strcpy(response_packet.szVpaIP,VPA_IP_NUMBER);	
	response_packet.instance = 1;

	sendto( sockfd,
		&response_packet,
		sizeof(response_packet),
		0,
		(struct sockaddr *)&their_addr, 
		addr_len);

    close(sockfd);

    return 0;
}

int 
discovery_responder(struct DISCOVERY_RESPONSE * response)
{
	struct RESPONSE_PACKET packet;
	packet.version.rmj = RMJ;
	packet.version.rmn = RMN;
	packet.version.rup = RUP;
	packet.version.rpt = RPT;

	int retcode = sendto(
			response->sockfd,
			buf,
			MAXBUFLEN-1,
			0,
			(struct sockaddr *)&to_addr,
			addr_len);
}

