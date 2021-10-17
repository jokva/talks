import numpy as np
import matplotlib.pyplot as plt

from random import randrange


xs = [randrange(1, 120) for _ in range(30)]
ys = [randrange(1, 80) for _ in range(30)]
p = (xs[0], ys[0])

fig, ax = plt.subplots()
ax.scatter(xs[1:], ys[1:], color = 'black')
ax.scatter([p[0]], [p[1]], marker = 'x', color = 'black')
cir = plt.Circle(p, 30, color='black', fill=False)
ax.set_aspect('equal', adjustable='datalim')
ax.add_patch(cir)
plt.savefig('1-plot.svg')
