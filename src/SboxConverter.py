import csv
import numpy as np
box=[]
with open('clef.txt') as fp:
    for line in fp:
        a=line.split()
        a=[int(x,16) for x in a]
        box.append(a)
       #box.append(line)    
       
print box       

with  open("clef.csv" ,"w") as f:        
     wr=csv.writer(f)
     wr.writerows(box)
