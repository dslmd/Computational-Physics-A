from matplotlib import pyplot as plt #用来绘制图形
import numpy as np  #用来处理数据
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D  #用来给出三维坐标系。
import math #用来转换phi，theta画图

#打开x,y,z数据文件并转换成列表
f_x = open('x.txt')
s_x = f_x.read()
p_x = list(float(i) for i in s_x.split())
f_y = open('y.txt')
s_y = f_y.read()
p_y = list(float(i) for i in s_y.split())
f_z = open('z.txt')
s_z = f_z.read()
p_z = list(float(i) for i in s_z.split())

#搞定xyz数列
x=p_x
y=p_y
z=p_z



mpl.rcParams['font.size'] = 10#生成图纸，绘制3D柱状图子图
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

hist, xedges, yedges = np.histogram2d(x, y, bins=10)
elements = (len(xedges) - 1) * (len(yedges) - 1)


#设置作图点的坐标，meshgrid函数用两个坐标轴上的点在平面上画格
xpos, ypos = np.meshgrid(xedges[:-1] + .25, yedges[:-1] + .25)
# 多维数组变为一维数组
xpos = xpos.flatten()
ypos = ypos.flatten()
zpos = np.zeros(elements)
#变量dx,dy表示每一个矩形条底部的宽度，这里设置xy平面的每一个位置给定的值为0.1个点的宽度
dx = .1 * np.ones_like(zpos) # zpos一致的全1数组
dy = dx.copy()#定义了柱状图的高度
dz = hist.flatten()




u = np.linspace(0, 2 * np.pi, 20)
v = np.linspace(0, np.pi, 20)
x =  np.outer(np.cos(u), np.sin(v))+0.2
y =  np.outer(np.sin(u), np.sin(v))+0.2
z =  15*np.abs(np.outer(np.ones(np.size(u)), 1/np.cos(v)))


# Plot the surface
ax.plot_surface(x, y, z, color='b')
            
ax.bar3d(xpos, ypos, zpos, dx, dy, dz, color='r', alpha=0.4)

#ax.plot_surface(x_theory,y_theory,z_theory,c='b')#点为红色三角形
plt.show()