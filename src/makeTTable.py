import sys

from itoh_tsujii import *

rtail = 283 & ~(1<<8)

multiplier = []
if sys.argv[1] == 'e':
    multiplier = [0x2, 0x1, 0x1, 0x3]
elif sys.argv[1] == 'd':
    multiplier = [0xe, 0x9, 0xd, 0xb]

with open(sys.argv[2], "w") as f:
    f.write('static const u32 T[256] =\n{\n')
    for n in xrange(256):
        entry = 0
        for m in multiplier:
            entry = (entry << 8) | mult(n, m, rtail)
        f.write('{0:#0{1}x}U, '.format(entry, 10))
        if n % 4 == 3:
            f.write("\n")
    f.write("};")