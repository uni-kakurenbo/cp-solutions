from itertools import product
from math import prod
from PIL import Image, ImageDraw

with open(".pred") as f:
    l = int(f.readline())
    val = [[*map(int, f.readline().split())] for _ in [0] * l]

mx = max(max(v for v in row) for row in val)

import numpy as np
import matplotlib.pyplot as plt
# from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize = (20, 20))

ax = fig.add_subplot(111, projection='3d')

# 軸ラベルを設定
ax.set_xlabel("x", size = 14)
ax.set_ylabel("y", size = 14)
ax.set_zlabel("z", size = 14)

ax.view_init(elev=60, azim=-90)

ax.invert_yaxis()

x, y, z = [0] * 40000, [0] * 40000, [0] * 40000
for k, (i, j) in enumerate(product(range(l), range(l))):
    y[k], x[k], z[k] = i, j, val[i][j]

ax.scatter(x, y, z, s = 2, c = "blue")

plt.savefig("vis1.png")
