#!/usr/bin/python

import random
import sys
import time
import hashlib
import json
import string

import fnode

#Node data
node_id = ''
hash_table = {}
lower_bound = ''  # predecessor's id
upper_bound = ''  # successor's id
ip = ''


# Get a random id. Put in config.json id, port
def get_id():
    global node_id, ip

    d = fnode.load_json('config.json')

    while True:
        rnd = random.randint(0, 100)
        rnd_sha = fnode.sha256(rnd)
        # print rnd_sha
        # print(json.dump(d))
        if rnd_sha not in d["nodes"] or d["nodes"][rnd_sha] == "off":
            d["nodes"][rnd_sha] = {"state": "on", "ip": ip}
            # print rnd_sha
            node_id = rnd_sha
            break
        # else:
        #     print("This id exist!")

    f = open('config.json', 'w')
    f.write(json.dumps(d, sort_keys=True,
                       indent=2))  # python will convert \n to os.linesep
    f.close()


def get_edges():
    global lower_bound, upper_bound
    nodes = []

    d = fnode.load_json('config.json')

    for node in d["nodes"]:
        if d["nodes"][node]["state"] == "on":
            nodes.append(json.dumps(node))

    nodes = sorted(nodes)

    if len(nodes) == 1:
        lower_bound = upper_bound = node_id
        print "hola"
    else:
        # for node in range(0, len(nodes)):
        #     print str(node) + " -> " + nodes[node]
        #     target = nodes[node]
        #     if node == 0:



def main():
    global ip
    ip = sys.argv[1]

    get_id()
    get_edges()
    print lower_bound + "   " + upper_bound
    # print node_id
    # print ip


if __name__ == '__main__':
    main()
