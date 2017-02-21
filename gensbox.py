import csv
import sys
import numpy as np

# [1,2] - size, [2] - fname
m = int(sys.argv[1])
n = int(sys.argv[2])
fname = sys.argv[3]

sbox = np.random.randint( 0, 2**n, ((2**(m/2)), (2**(m/2))) )
with open(fname, "w") as f:
    wr = csv.writer(f)
    wr.writerows(sbox)
