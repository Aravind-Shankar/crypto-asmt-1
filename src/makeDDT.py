import sys

import numpy as np
import csv

def lin_combo(A, X):
    return np.bitwise_xor.reduce(np.bitwise_and(A, X))

def writeDDTAndReturnPropRatio(fname):
    '''
    if len(sys.argv) < 2:
        print "Please pass input sbox file name da"
        sys.exit()
    fname = sys.argv[1]
   '''
    LEN_X, LEN_Y = 8,8
    X_RANGE, Y_RANGE = np.arange(2**LEN_X), np.arange(2**LEN_Y)

    with open(fname, "r") as f:
        reader = csv.reader(f)
        sbox = []
        for row in reader:
            sbox.append(row)

    sbox = np.array(sbox,dtype=int).flatten()
    
    # sbox(x,1) = y is the (x,y) pair of the input output 
 
    y= np.zeros((len(X_RANGE),len(Y_RANGE) ))          
    for i in X_RANGE: #input values
      for j in X_RANGE: #input difference
        # now to find all possible output differences and tabulate
        y[j][np.bitwise_xor(sbox[i],sbox[np.bitwise_xor(i,j)])]+=1
         
    #y is the differential table
    '''
    with  open("DDT.csv","w") as f:
     wr=csv.writer(f)
     wr.writerows(y)
    '''
    y[0][0] =0
    prop_ratio = np.max(np.max(y)) / len(X_RANGE)
    #print prop_ratio
    return prop_ratio
         
#writeDDTAndReturnPropRatio()