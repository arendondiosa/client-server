#!/usr/bin/python

#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

from __future__ import print_function  #print without newline
import ffile
import zmq
import sys
import subprocess


def main():
    context = zmq.Context()

    ip = sys.argv[1]
    # port = sys.argv[2]
    port = "5555"

    # print sys.argv

    #  Socket to talk to server
    print("Connecting from " + ip + ":" + port)
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://" + ip + ":" + port)

    # print(ffile.fileSha256("files/sirius.png"),
    #       ffile.fileName("files/sirius.png"))

    while True:
        print('$', end=' ')
        user_in = raw_input()
        if user_in == "exit":
            print("See you later. Zpotify team")
            break
        else:
            opt, fileName = user_in.split()
            print(opt)

            if opt == "add":
                print("adding " + fileName)
            elif opt == "delete":
                print("deleting " + fileName)
            elif opt == "get":
                print("getting " + fileName)
            elif opt == "play":
                print("Play " + fileName)
                pid = subprocess.call(["vlc", fileName]).wait()
                print("Sending request %s ..." % fileName)
                socket.send(b"Hello")

                #  Get the reply.
                message = socket.recv()
                print(message)

    #  Do 10 requests, waiting each time for a response
    # for request in range(2):
    #     print("Sending request %s ..." % request)
    #     socket.send(b"Hello")
    #
    #     #  Get the reply.
    #     message = socket.recv()
    #     print("Received reply %s [ %s ]" % (request, message))


if __name__ == '__main__':
    main()
