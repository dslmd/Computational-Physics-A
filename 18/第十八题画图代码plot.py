import numpy as np
import matplotlib.pyplot as plt

f = open('point.txt')
s = f.read()
p = list(float(i) for i in s.split())
N=601
x=[]
y=[]

plt.figure(dpi=300)
for i in range(N):
    for j in range(N):
        if p[i+601*j]==1:
            x.append(i)
            y.append(j)
plt.scatter(x,y,s=0.1,c = "black")
plt.xlabel("x")
#plt.xlim(0,600)
#plt.ylim(0,600)
plt.ylabel("y")
plt.title("Plot",c="r",size=17)