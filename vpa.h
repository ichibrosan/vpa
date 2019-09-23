// vpa.h

#ifndef VPA_H
#define VPA_H


#define RMJ 19
#define RMN 9
#define RUP 15
#define RPT 9

#define VPA_DISC_PORT "5164"
#define VPA_IP_NUMBER "10.0.1.1"
#define VPA_BROADCAST "10.0.1.255"

struct VPA_VERSION {
	int rmj;
	int rmn;
	int rup;
	int rpt;
};

struct DISCOVERY_REQUEST {
	struct VPA_VERSION version; 	
	int	sockfd;
};

struct RESPONSE_PACKET {
	struct 	VPA_VERSION version;
	char 	szVpaIP[18];
	int	instance_number;	
};

struct DISCOVERY_RESPONSE {
	struct VPA_VERSION version;
	int	sockfd;
	struct sockaddr to_addr;
	socklen_t addr_len;
	struct RESPONSE_PACKET packet;
};

#endif // VPA_H

/////////////////
// eof - vpa.h //
/////////////////

