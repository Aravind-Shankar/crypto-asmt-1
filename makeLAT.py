import sys

import numpy as np
import csv

def bitfield(n):
    return [int(digit) for digit in bin(n)[2:]] # [2:] to chop off the "0b" part 

def lin_combo(A, X):
    return np.bitwise_xor.reduce(bitfield(np.bitwise_and(A, X)))

def writeLATAndRetMaxBias():
    if len(sys.argv) < 2:
        print "Please pass input sbox file name"
        sys.exit()
    fname = sys.argv[1]

    LEN_X, LEN_Y = 4, 4
    X_RANGE, Y_RANGE = np.arange(2**LEN_X), np.arange(2**LEN_Y)

    with open(fname, "r") as f:
        reader = csv.reader(f)
        sbox = []
        for row in reader:
            sbox.append(row)

    sbox = np.array(sbox, dtype=int).flatten()
    
    A,B = X_RANGE, Y_RANGE
    
    LAT = np.zeros( (len(A), len(B)) )
    out = np.zeros( (len(A), len(B)) )
    for x in X_RANGE:
        y = sbox[x]
        for a in A:
            for b in B:
                out[a,b] = np.bitwise_xor(lin_combo(a, x), lin_combo(b, y))
        LAT += out

    LAT = 16 - LAT
    with open("LAT.csv","w") as f:
        wr = csv.writer(f)
        wr.writerows(LAT)

    maxbias = np.max(np.max(np.abs(LAT - (len(X_RANGE) / 2)))) / len(X_RANGE)
    return maxbias

writeLATAndRetMaxBias()