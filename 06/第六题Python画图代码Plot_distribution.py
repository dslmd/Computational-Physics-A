# -*- coding: utf-8 -*-
import numpy as np
import math
import matplotlib.pyplot as plt

#plt.figure(num=2,dpi=300)

#画频数图
f = open('lorentzian.txt')
s = f.read()
p = list(float(i) for i in s.split())

#画出理论图
x=np.arange(-1,1,0.05)
y=[  2500*np.exp(-0.5*x**2)  for a in x]

plt.hist(p, bins=20,range=(-1,1))


ax=plt.gca()
plt.plot(x,y,color='red',linewidth=1.0,linestyle='-')
plt.xlim(-1,1)
#plt.ylim(0,1)
plt.xlabel('N')
plt.ylabel('Distribution of random number')
ax.set_title('Distribution',fontsize=14,color='r')
plt.show()