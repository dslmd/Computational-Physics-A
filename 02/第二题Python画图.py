# -*- coding: utf-8 -*-
import numpy as np
import math
import matplotlib.pyplot as plt

plt.figure(num=2,dpi=300)

#图像中x的范围
x=[10,100,1000,10000,100000,1000000,10000000,100000000]

#图像中y1,y2,y3的范围
y1=[-0.066667,0.083333,0.000333,0.002533,-0.000027, 0.000445, 0.000120, 0.000028] #16807

y2=[-0.066667,0.003333,0.017333,0.007433,0.000513,0.000290, 0.000125, 0.000017] #带载

y3=[0.133333,0.043333, 0.020333,  0.006933, 0.000813, 0.000823, 0.000120, -0.000058] #【2，10】

plt.plot(x,y1,color='red',linewidth=1.0,linestyle='-')
plt.plot(x,y2,color='y',linewidth=1.0,linestyle='-')
plt.plot(x,y3,color='blue',linewidth=1.0,linestyle='-')

ax=plt.gca()
ax.set_xscale("log")
plt.ylim(-0.15,0.15)
plt.xlabel('N')
plt.ylabel('The relative deviation')
ax.set_title('The relative deviation of three random number generator',fontsize=14,color='r')
plt.show()