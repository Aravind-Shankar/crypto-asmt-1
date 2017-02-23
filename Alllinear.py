#to generate all linear truth tables 
import numpy as np
import csv

def bitfield(n):
    return [int(digit) for digit in bin(n)[2:]] # [2:] to chop off the "0b" part 
ttall=[] #truth table
for i in range(0,2**8):
 tt=[]
 for j in range(0,2**8):
  tt.append(np.bitwise_xor.reduce(bitfield(np.bitwise_and(j,i))))
 #print tt
 ttall.append(tt)

with  open("LIN8.csv" ,"w") as f: 
     wr=csv.writer(f)
     wr.writerows(ttall) 