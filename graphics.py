import sys
 
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import json
from matplotlib import cm
import math
#dim = int(sys.argv[1])
dim=2
with open("func.txt", "r") as read_file:
    data = json.load(read_file)
with open("data.txt", "r") as read_file:
    file = json.load(read_file)
for i in range(1,dim+1):
    x = data["x"+str(i)]
    X = file["x"+str(i)]
    for j in range(i+1,dim+1):
        y = data["x"+str(j)]
        z = data["z"]
        Y = file["x"+str(j)]
        Z = file["z"]
        pointx = X
        pointy = Y
        pointz = Z
        fig = plt.figure()
        ax = Axes3D(fig)
        ax = fig.gca(projection='3d')
 
        ax.set(xlabel='x'+str(i), ylabel='x'+str(j), title='Graphic')
        ax.plot_trisurf(x, y, z, linewidth=0.2, antialiased=True, cmap=cm.coolwarm) 
        ax.scatter(pointx, pointy, pointz, c='r', s=3)
        
plt.show()