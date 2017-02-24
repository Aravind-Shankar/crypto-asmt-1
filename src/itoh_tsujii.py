import sys

def mult(x, y, rtail):
    res = 0
    sy = bin(y)[::-1]
    i = 0
    addend = 0
    for b in sy:
        if b == '1':
            addend = (x << i)
            for p in xrange(14, 7, -1):
                if addend & (1<<p) > 0:
                    addend = (addend & ~(1<<p)) ^ (rtail << (p-8))
            res = res ^ addend
        i += 1
    return res

def sqr(x, rtail):
    return mult(x, x, rtail)

def inverse(x, rtail):
    if x == 0:
        return 0
    b1 = x
    b2 = mult( sqr(b1, rtail) , b1, rtail )
    b4 = mult( sqr(sqr(b2, rtail), rtail) , b2, rtail )
    b6 = mult( sqr(sqr(b4, rtail), rtail) , b2, rtail )
    b7 = mult( sqr(b6, rtail) , b1, rtail )
    return sqr(b7, rtail)

def test():
    base = int(sys.argv[3])
    R = int(sys.argv[1], base)
    P = int(sys.argv[2], base)
    Rtail = R & ~(1<<8)
    print hex(inverse(P, Rtail))

if __name__ == "__main__":
    test()