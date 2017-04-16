#!/usr/bin/python
import zmq
import random
import sys
import time
import hashlib
import json
import string

#Node data
node_id = random.randint(0, 100)
hash_table = {}
lower_bound = ''  # predecessor's id
upper_bound = ''  # successor's id


def sha256(toHash):
    return str(hashlib.sha256(str(toHash)).hexdigest())


def get_id():
    json_data = open('config.json', 'r')
    d = json.load(json_data)

    # print(d["nodes"])

    while True:
        rnd = random.randint(0, 100)
        rnd_sha = sha256(rnd)
        print rnd_sha
        # print(json.dump(d))
        if rnd_sha not in d["nodes"] or d["nodes"][rnd_sha] == "off":
            d["nodes"][rnd_sha] = "on"
            print rnd_sha
            break
        else:
            print(rnd_sha + "Yes")

    f = open('config.json', 'w')
    f.write(json.dumps(d, sort_keys=True,
                       indent=2))  # python will convert \n to os.linesep
    f.close()


def main():
    print node_id
    get_id()


if __name__ == '__main__':
    main()
