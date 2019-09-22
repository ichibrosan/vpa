CC=g++
CFLAGS=$(DEBUG) -c

TARGETS=listener client

all:	$(TARGETS)

listener:	listener.o udpbind.o 
	$(CC) listener.cpp udpbind.cpp -o listener

client:		client.cpp vpa.h
	$(CC) client.cpp udpbind.cpp -o client

