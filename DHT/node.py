#!/usr/bin/python

import random
import sys
import time
import hashlib
import json
import string
import numpy

import fnode

#Node data
node_id = ''
hash_table = {}
lower_bound = ''  # predecessor's id
upper_bound = ''  # successor's id
ip = ''


# Get a random id. Put in config.json id, port
def get_id(some_ip):
    if some_ip:
        print "Hay más nodos"
    global node_id, ip
    rnd = random.randint(0, 100)
    return fnode.sha256(rnd)

    # f = open('config.json', 'w')
    # f.write(json.dumps(d, sort_keys=True,
    #                    indent=2))  # python will convert \n to os.linesep
    # f.close()


def get_edges(some_ip):
    

def main():
    global ip
    ip = sys.argv[1]
    print len(sys.argv)
    some_ip = ''

    if len(sys.argv) == 3:
        print 'Hay alguien ' + sys.argv[2]
        some_ip = sys.argv[2]
    else:
        print 'Nadie'

    print get_id(some_ip)

if __name__ == '__main__':
    main()
