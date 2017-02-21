import sys

import numpy as np
import csv

def lin_combo(A, X):
    return np.bitwise_xor.reduce(np.bitwise_and(A, X))

def main():
    if len(sys.argv) < 2:
        print "Please pass input sbox file name"
        sys.exit()
    fname = sys.argv[1]

    LEN_X, LEN_Y = 16, 10
    X_RANGE, Y_RANGE = np.arange(2**LEN_X), np.arange(2**LEN_Y)

    with open(fname, "r") as f:
        reader = csv.reader(f)
        sbox = []
        for row in reader:
            sbox.append(row)

    sbox = np.array(sbox).flatten()
    sbox = np.vstack((X_RANGE, sbox)).transpose()

    A,B = np.meshgrid(X_RANGE, Y_RANGE)
    A,B = A.transpose(), B.transpose()

    

main()