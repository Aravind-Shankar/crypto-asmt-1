import csv
import numpy as np
with open("4x4Test.csv", "r") as f:
        reader = csv.reader(f)
        sbox = []
        for row in reader:
            sbox.append(row)

sbox = np.array(sbox, dtype=int).flatten()
tts = []
for k in range(0,4):
    tts.append((sbox&(1<<k))>>k)
    print tts
mini=[300]*4
with open("LIN4.csv","r") as f:
    reader = csv.reader(f)
    for row in reader:
        row=[int(x,2) for x in row]
        for k in range(0,4):
         mini[k] =min(mini[k], sum(np.bitwise_xor(tts[k],row))) 
print mini        