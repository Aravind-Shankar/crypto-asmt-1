from affine import *
from math import *
import numpy as np
#to find branch number of AES mixcols matrix

rtail=283 & ~(1<<8)
mds=[[2,3,1,1],[1,2,3,1],[1,1,2,3],[3,1,1,2]]
def track_bit(i,j,val): 
    # function which tracks the bits changed
    out=[0,0,0,0]
    t=[]
    for a in range(0,4): 
     out[a]=mult(mds[a][i],val,rtail)
     x=[32*(3-a) + 8*(3-j)+(len(bin(out[a])[2:])-1-pos) for pos, char in enumerate(bin(out[a])[2:]) if char == '1']
     
    #print x,
     
     #only mds matrix multiplication's effects are noted
     #now we need to see the affect of shift rows
     # x goes to (x+8*i)mod (32*floor(x/32)) 
     
     y=[int(32*floor(b/32)+((b-32*floor(b/32)+8*a)%(32))) for b in x]
     #print y
     t.extend(y)
    #print t, 
    return t


bits_trail=[]
col1=[]
for i in range(0,4):#each row
 for j in range(0,4): #each column
  for val in range(0,8): #each bit
  #i,j,val refers actually to 0,0,val which is actually the (32*(3-i) + 8*(3-j)+val)th bit
   val=(1<<val)
   col1.append( (32*(3-i) + 8*(3-j)+val))
   bits_trail.append(track_bit(i,j,val)) 

#for i in xrange(128): 
#    print bits_trail[i]

rows = zip(col1,bits_trail)
with open("Diffusion-Tracking.csv","w") as f:
   wr = csv.writer(f)
   wr.writerows(rows)      





