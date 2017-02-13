# CC	= g++ -std=c++11 -Wall -L/home/arendon/zmq/lib  -I/home/arendon/zmq/include
CC	= g++ -std=c++11 -Wall -L/home/utp/zmq/lib  -I/home/utp/zmq/include
LDFLAGS = -lpthread -lzmqpp -lzmq

all: server client

server: server.cc
	$(CC) -o server.out server.cc $(LDFLAGS)

client: client.cc
	$(CC) -o client.out client.cc $(LDFLAGS)

clean:
	rm -f client.out server.out
