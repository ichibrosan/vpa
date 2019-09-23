// main.cpp
#include <stdio.h>

void callback()
{
	printf("callback() called\n");	
}

void listen_for_event(void (*ptr)())
{
	(*ptr)();
}

int main()
{
	void (*ptr)() = &callback;
	listen_for_event(ptr);
	return 0;
}

