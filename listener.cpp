// listener.cpp 
// Copyright (c) 2019 Douglas Wade Goodall. All Rights Reserved.

#include "listener.h"

int callback(struct DISCOVERY_REQUEST *pRequest)
{
	if( (pRequest.version.rmj == RMJ) &
	    (pRequest.version.rmn == RMN) &
	    (pRequest.version.rup == RUP) &
	    (pRequest.version.rpt == RPT) )
	{
		struct DISCOVERY_RESPONSE response;
		response.client_addr = pRequest->from_addr;
		response.client_port = pRequest->from_port;	
		response.vpasvr_ipaddr = myaddr;
		response.vpasvr_portno = myport;
		response.vpasvr.version.rmj = RMJ;
		response.vpasvr.version.rmn = RMN;
		response.vpasvr.version.rup = RUP;
		response.vpasvr.version.rpt = RPT;	
		int retcode = transport_send_udp(&response);
	}
}

int main(int argc,char **argv)
{
	int (
	int retcode = transport_recv_udp( callback(void * buf,inc length) );

	return EXIT_SUCCESS;
}
