// responder.cpp 2019/09/22 21:00 dwg - initial version 
// Copyright (c) 2019 Douglas Goodall

#include <stdio.h>
#include <string.h>

struct REQUEST  {
	char addr[18];
};

void callback(struct REQUEST *pRequest)
{
	printf("callback() called with addr of %s\n",pRequest->addr);
}

void listen_for_request(void (*ptr)(struct REQUEST *))
{
	struct REQUEST request;
	strcpy(request.addr,"192.168.42.42");
	(*ptr)(&request);
}

int main()
{
	void (*ptr)(struct REQUEST *) = &callback;
	listen_for_request(ptr);
	return 0;
}

/////////////////////////
// eof - responder.cpp //
/////////////////////////
