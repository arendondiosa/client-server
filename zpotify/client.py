#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import ffile
import zmq

context = zmq.Context()

ip = "localhost"
port = "5555"

#  Socket to talk to server
print("Connecting to hello world server...")
socket = context.socket(zmq.REQ)
socket.connect("tcp://" + ip + ":" + port)

print(ffile.fileName('~/Documents/client-server'))

print(ffile.hashSha256("hola soy alejo"))

#  Do 10 requests, waiting each time for a response
# for request in range(2):
#     print("Sending request %s ..." % request)
#     socket.send(b"Hello")
#
#     #  Get the reply.
#     message = socket.recv()
#     print("Received reply %s [ %s ]" % (request, message))
