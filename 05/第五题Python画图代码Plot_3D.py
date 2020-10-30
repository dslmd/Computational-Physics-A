from matplotlib import pyplot as plot #用来绘制图形
import numpy as np  #用来处理数据
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


x=p_x
y=p_y
z=p_z
           


#打开一个画布：
figure = plot.figure()

#画出三维坐标系：
axes = Axes3D(figure)

axes.scatter3D(x,y,z,c='g',s=1)#点为红色三角形

#图形可视化：
plot.show()