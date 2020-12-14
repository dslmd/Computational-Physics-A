import numpy as np
import matplotlib.pyplot as plt

f = open('diedai.txt')
s = f.read()
p = list(float(i) for i in s.split())
N = 50

for i in range(N):
    plt.scatter(p[0::N+1],p[i::N+1],s=0.01,c = "black")
