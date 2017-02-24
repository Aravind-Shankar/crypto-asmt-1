import csv
import numpy as np
with open("AES.csv", "r") as f:
        reader = csv.reader(f)
        sbox = []
        for row in reader:
            sbox.append(row)

sbox = np.array(sbox, dtype=int).flatten()
tts = []

for k in range(0,8):
    tts.append((sbox&(1<<k))>>k)
mini=[300]*8
for k in range(0,8):
         mini[k] =min(mini[k], sum(tts[k])) 
print mini    