#!/usr/bin/python

import os
import hashlib


def fileName(path):
    return os.path.basename(path)


def hashSha256(string):
    return hashlib.sha256(string).hexdigest()
