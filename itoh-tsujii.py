import sys

R = int(sys.argv[1], 2)
P = int(sys.argv[2], 2)

Rtail = R & ~(1<<8)

def mult(x, y):
    res = 0
    sy = bin(y)[::-1]
    i = 0
    addend = 0
    for b in sy:
        if b == '1':
            addend = (x << i)
            for p in xrange(14, 7, -1):
                if addend & (1<<p) > 0:
                    addend = (addend & ~(1<<p)) ^ (Rtail << (p-8))
            res = res ^ addend
        i += 1
    return res

def sqr(x):
    return mult(x, x)

def inverse(x):
    if x == 0:
        return 0
    
    b1 = x
    b2 = mult( sqr(b1) , b1 )
    b4 = mult( sqr(sqr(b2)) , b2 )
    b6 = mult( sqr(sqr(b4)) , b2 )
    b7 = mult( sqr(b6) , b1 )
    return sqr(b7)

print hex(inverse(P))