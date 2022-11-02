import numpy as np
import matplotlib.pyplot as plt

with open("file_names.txt") as f:
    names = [line for line in f]
  

with open("file_names.txt") as f:
    names = [line.rstrip() for line in f]

count=0
x=[]
y=[]
for name in names:
    with open(name,"r") as f:
        for line in f:
            count += 1
            if count%2==1:
                x.append(float(line.rstrip()))
            else:
                y.append(float(line.rstrip()))
    with open(name,"w") as f:
        for c in np.polyfit(x,y,len(x)-1):
            f.write(str(c)) 
            f.write("\n")
    x=[]
    y=[]    
    count=0