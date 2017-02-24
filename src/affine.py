import numpy as np

from itoh_tsujii import *
from makeLAT import *

def ror(x, p, i):
    """
    Returns the right-rotation of x by i bits to length p
    Can be used with -ve i to do left-rotation by |i| bits
    """
    if i == 0:
        return x

    i = i % p
    a = x >> i
    b = (x << (p - i)) & (2**p - 1)
    return a | b

def affine(A, X, B, p, Rtail):
    """
    Computes (A')(X^-1) + B in the GF 2^p and irred polynomial R (tail = Rtail).

    Arguments:-
    A:          vector of p bits. Will be rotated *right* p times, top to bottom, to form the affine matrix A'.
    X:          input p-bit vector to compute the affine transformation for (will be inverted in the process).
    B:          vector of p bits. Will be added to the result of AX
    Rtail:      binary form of irred polynomial R, without the leading '1'. Same as (R & ~(1<<p))

    Returns:-
                A p-bit vector y = AX + B over GF(2^p) with irred polynomial R (tail = Rtail).
    """
    Xvec = inverse(X, Rtail)
    str_res = ""
    Bvec = bitfield(B, p)
    
    for i in xrange(p):
        str_res = str_res + str(Bvec[i] ^ lin_combo(ror(A, p, i), Xvec))

    return int(str_res, 2)