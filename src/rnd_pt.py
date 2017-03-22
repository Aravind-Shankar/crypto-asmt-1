import numpy.random as rnd
import sys

size = int(sys.argv[1])
outBytes = rnd.randint(0, 256, 1<<size)

with open("alice.txt", "w") as f:
    for b in outBytes:
        f.write((hex(b)[2:-1]).zfill(2))