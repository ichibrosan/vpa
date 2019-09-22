// listener.cpp 
// Copyright (c) 2019 Douglas Wade Goodall. All Rights Reserved.

#include "listener.h"

int main(int argc,char **argv)
{
	struct DISCOVERY_REQUEST  request;
	struct DISCOVERY_RESPONSE response;

	int retcode1 = discovery_listener ((struct DISCOVERY_REQUEST  *)&request );
	int retcode2 = discovery_responder((struct DISCOVERY_RESPONSE *)&response);

	return EXIT_SUCCESS;
}
