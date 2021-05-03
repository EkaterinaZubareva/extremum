#import json
import sys
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import json
from matplotlib import cm
import math
dim = int(sys.argv[1])
with open("data.txt", "r") as read_file:
    data = json.load(read_file)

for i in range(1,dim+1):
	x = data["x"+str(i)]
	for j in range(i+1,dim+1):
		y = data["x"+str(j)]
		z = data["z"]
		pointx = x
		pointy = y
		pointz = z

		fig = plt.figure()
		ax = Axes3D(fig)
		ax = fig.gca(projection='3d')
		ax.set_title("x = x"+str(i)+", y = x"+str(j))

		ax.plot_trisurf(x, y, z, linewidth=0.2, antialiased=True, cmap=cm.coolwarm)
		ax.scatter(pointx, pointy, pointz, c='r', s=3)
plt.show()
		