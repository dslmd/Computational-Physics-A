# -*- coding: utf-8 -*-
import numpy as np
import math
import matplotlib.pyplot as plt

plt.figure(num=2,dpi=300)

f = open('data.txt')    #用test.txt先试试
s = f.read()
p = list(float(i) for i in s.split())
print(p)
l=len(p)

plt.scatter(p[0:80000:1], p[1:80001:1], s=0.01, c='r')

ax=plt.gca()
plt.xlim(0,1)
plt.ylim(0,1)
plt.xlabel('First random number')
plt.ylabel('Second random number')
ax.set_title('Distribution',fontsize=14,color='r')
plt.show()
