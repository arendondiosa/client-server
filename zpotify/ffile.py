#!/usr/bin/python

import os
import hashlib


def fileName(path):
    return os.path.basename(path)


def hashSha256(string):
    return hashlib.sha256(string).hexdigest()


def readFile(fileName):
    f = open(fileName, 'rb')
    binary = ""
    while True:
        piece = f.read(1024)
        binary += piece
        if not piece:
            return binary
            break
    f.close()


def fileSha256(fileName):
    binary = readFile(fileName)
    return hashSha256(binary)


def readFileChunks(fileName):
    f = open(fileName, 'rb')
    while True:
        piece = f.read(1024)
        if not piece:
            break
        # print(hashSha256(piece))
    f.close()
