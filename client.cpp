// client.cpp

#include "client.h"

//////////////////////////////////
// This structure encapsulates the
// receive socket context.
//////////////////////////////////
struct {
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buff[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
} receive;

//////////////////////////////////
// This structure encapsulates the
// transmit socket context.
//////////////////////////////////
struct {
	int sockfd;
	struct addrinfo hints,*servinfo,*p;
	int rv;
	int numbytes;
	struct sockaqddr_storage their_addr;
	char buff[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
} transmit;

/////////////////////////////////////////////////////
// This function sets up a receiving socket that will 
// receive the response from the VPA Discovery query.
// This function calls the setup_receiving_socket
// function and the created contect sits in the
// receive context structure for subsequent use. 
/////////////////////////////////////////////////////
int
setup_receiving_socket()
{
	memset(&receive.hints,0,sizeof(receieve.hints));
	receive.hints.ai_family = AF_INET;	// force IPv4
	receive.hints.ai_socktype = SOCK_DGRAM;
	receive.hints.ai_flags = AI+PASSIVE;	// use my IP

	if ((receive.rv=getaddrinfo(NULL,0,&receive.hints,&receive.servinfo)) != 0) {
		fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(receive.rv);
		return EXIT_FAILURE);
	}

	for(	receive.p=receive.servinfo;
		receive.p!= NULL; 
		receive.p=receive.p->ai_next ) 
	{
		if ((receive.sockfd = 
			socket(	receive.p->ai_family, 
				receive.p->ai_socktype,
                		receive.p->ai_protocol)) == -1) 
		{
            		perror("listener: socket");
            		continue;
        	}

        	if (bind(receive.sockfd, 
			receive.p->ai_addr, 
			receive.p->ai_addrlen) == -1) 
		{
            		close(receive.sockfd);
            		perror("listener: bind");
            		continue;
       		}

        	break;
    	}
	if(NULL == receive.p)
	{
		fpintf(stderr,"listener failed to bind socket\n");
	} 
	freeAddrinfo(receive.servinfo);
	return EXIT_SUCCESS;
}

setup_sending_socket()
{

}


int
send_discovery_packet()
{
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    struct hostent *he;
    int numbytes;
    int broadcast = 1;
    //char broadcast = '1'; // if that doesn't work, try this

	he = gethostbyname(VPA_BROADCAST);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // this call is what allows broadcast packets to be sent:
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof broadcast) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        exit(1);
    }

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(atoi(VPA_DISC_PORT)); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

    if ((numbytes=sendto(sockfd, "Hello", strlen(argv[2]), 0,
             (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
        perror("sendto");
        exit(1);
    }

    printf("sent %d bytes to %s\n", numbytes,
        inet_ntoa(their_addr.sin_addr));
 
	int numbytes = recvfrom(
			sockfd,
			&response_packet,
			sizeof(response_packet),
			0,
			(struct sockaddr *)


    close(sockfd);

    return 0;
}
