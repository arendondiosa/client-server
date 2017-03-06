CC	= g++ -std=c++11 -Wall
# CC	= g++ -std=c++11 -Wall -L/home/utp/zmq/lib  -I/home/utp/zmq/include
LDFLAGS = -lzmqpp -lzmq

all: server client broker

server: server.cc
	$(CC) -o server.out server.cc $(LDFLAGS)

client: client.cc
	$(CC) -o client.out client.cc $(LDFLAGS)

broker: broker.cc
	$(CC) -o broker.out broker.cc $(LDFLAGS)

clean:
	rm -f client.out server.out broker.out
