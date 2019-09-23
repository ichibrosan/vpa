CC=g++
CFLAGS=$(DEBUG) -c

TARGETS=responder

all:	$(TARGETS)

responder:	responder.cpp
	$(CC) -g $< -o $@

listener:	listener.o udpbind.o 
	$(CC) listener.cpp udpbind.cpp -o listener

client:		client.cpp vpa.h
	$(CC) client.cpp udpbind.cpp -o client

clean:
	rm -f $(TARGETS) *.o
