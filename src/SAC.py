import csv
import numpy as np
def SAC(file):
 with open(file, "r") as f:
        reader = csv.reader(f)
        sbox = []
        for row in reader:
            sbox.append(row)

 sbox = np.array(sbox, dtype=int).flatten()
 tts = []
 abox=sbox
 b=[]
 for k in range(0,8):  
   b=[]  
   for i in range(0,256)   :
     t=np.bitwise_xor( sbox[i]&(1<<k)>>k ,(sbox[np.bitwise_xor(i,16)]&(1<<k))>>k )  # each bit is taken
     b.append(t)  
   tts.append(b)
 mini=[300]*8
 for k in range(0,8):
         mini[k] =min(mini[k], sum(tts[k])) 
 avg=sum(mini)/8    
 #print mini,avg
 return mini,avg
 

#SAC("C:\Users\USER\Desktop\Crypto\Assignment\crypto-asmt-1\data\clef2.csv")