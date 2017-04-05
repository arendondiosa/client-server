#!/usr/bin/python

import zmq
import ffile


def main():
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind("tcp://*:5555")

    while True:
        print("Broker waiting...")
        message = socket.recv()
        print("Received request: %s" % message)

        #  Send reply back to client
        socket.send(b"World")


if __name__ == '__main__':
    main()
