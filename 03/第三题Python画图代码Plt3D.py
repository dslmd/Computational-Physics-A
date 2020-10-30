from matplotlib import pyplot as plot #用来绘制图形
import numpy as np  #用来处理数据
from mpl_toolkits.mplot3d import Axes3D  #用来给出三维坐标系。
import math #用来转换phi，theta画图

#打开phi和theta的两个数据文件并转换成列表
f_phi = open('phi.txt')
s_phi = f_phi.read()
p_phi = list(float(i) for i in s_phi.split())
f_theta = open('theta.txt')
s_theta = f_theta.read()
p_theta = list(float(i) for i in s_theta.split())

#将数据转化成cos，sin的形式，方便进行坐标转化
sin_phi = np.sin(p_phi)
cos_phi = np.cos(p_phi)
sin_theta = np.sin(p_theta)
cos_theta = np.cos(p_theta)

x=[]
y=[]
z=[]
#将坐标转化成直角坐标
for i in range(10000):
    x.append(sin_theta[i]*cos_phi[i])
    y.append(sin_theta[i]*sin_phi[i])
    z.append(cos_theta[i])

#打开一个画布：
figure = plot.figure()

#画出三维坐标系：
axes = Axes3D(figure)

axes.scatter3D(x,y,z,c='r',s=1)#点为红色三角形

#图形可视化：
plot.show()