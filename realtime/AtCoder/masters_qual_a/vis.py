from math import log2
from sys import argv, stderr

import matplotlib
import matplotlib.pyplot as plt
import six


# sys.setrecursionlimit(10**5)
def debug(*args, **opts):
    if "LOCAL_JUDGE" in argv: print(*args, **opts, file=stderr)


INPUT_FILE = open(argv[1])
OUTPUT_FILE = None
if len(argv) > 2: OUTPUT_FILE = open(argv[2])

t, N = map(int, INPUT_FILE.readline().split())

V = [[*map(int, list(INPUT_FILE.readline().strip()))] for _ in range(N)]
H = [[*map(int, list(INPUT_FILE.readline().strip()))] for _ in range(N - 1)]
A = [[*map(int, list(INPUT_FILE.readline().split()))] for _ in range(N)]

# A = [[' '] * N] * N

plt.figure(figsize=(N / 2, N / 2), dpi=160)

CellColors = [[[1.0, 1.0, 1.0] for _ in range(N)] for _ in range(N)]

prev_cost = 0
for i, v in enumerate(V):
    for j, x in enumerate(v):
        if not x: prev_cost += abs(A[i][j + 1] - A[i][j])**2

for i, h in enumerate(H):
    for j, x in enumerate(h):
        if not x: prev_cost += abs(A[i + 1][j] - A[i][j])**2

if OUTPUT_FILE:
    print("Move")
    pi, pj, qi, qj = map(int, OUTPUT_FILE.readline().split())
    while True:
        line = OUTPUT_FILE.readline()
        if not line: break

        CellColors[pi][pj][0] -= 0.1
        CellColors[qi][qj][2] -= 0.1
        CellColors[pi][pj][0] = max(CellColors[pi][pj][0], 0)
        CellColors[qi][qj][2] = max(CellColors[qi][qj][2], 0)

        s, d, e = line.split()
        print(s, d, e)

        if int(s):
            A[pi][pj], A[qi][qj] = A[qi][qj], A[pi][pj]

        if d == 'U': pi -= 1
        if d == 'D': pi += 1
        if d == 'L': pj -= 1
        if d == 'R': pj += 1

        if e == 'U': qi -= 1
        if e == 'D': qi += 1
        if e == 'L': qj -= 1
        if e == 'R': qj += 1

ax = plt.gca()
ax.axes.xaxis.set_visible(False)
ax.axes.yaxis.set_visible(False)

plt.table(
    cellText=A,
    cellColours=CellColors,
    bbox=[0, 0, 1, 1],
)

print(V, H, A)


def get_table(ax):
    table = None
    for child in ax.get_children():
        if isinstance(child, matplotlib.table.Table):
            table = child
            return table
    return table


def add_point(ax, row, col, color, linewidth=3):
    table = get_table(ax)
    y = None
    cells = [*six.iteritems(table._cells)]
    d = cells[0][1].xy[1] - cells[N][1].xy[1]
    for k, cell in cells:
        if k[0] == row:
            y = cell.xy[1]
            ax.axhline(y + d / 2, xmin=(col + 0.4) / N, xmax=(col + 0.6) / N, color=color, linewidth=linewidth)
            return


def add_vwall(ax, row, col, color, linewidth=2):
    table = get_table(ax)
    x = None
    for k, cell in six.iteritems(table._cells):
        if k[1] == col + 1:
            x = cell.xy[0]
            ax.axvline(x, ymin=1 - (row / N), ymax=(1 - (row + 1) / N), color=color, linewidth=linewidth)
            return


def add_hwall(ax, row, col, color, linewidth=2):
    table = get_table(ax)
    y = None
    for k, cell in six.iteritems(table._cells):
        if k[0] == row:
            y = cell.xy[1]
            ax.axhline(y, xmin=col / N, xmax=(col + 1) / N, color=color, linewidth=linewidth)
            return


plt.draw()

VCost = {}
HCost = {}

for i, v in enumerate(V):
    for j, x in enumerate(v):
        if x:
            add_vwall(ax, i, j, 'red')
            # else: add_vwall(ax, i, j, (0.0, 0.0, 1.0, (A[i][j + 1] - A[i][j])**2 / N**4), 10)
        else:
            VCost[(i, j)] = abs(A[i][j + 1] - A[i][j])**2

for i, h in enumerate(H):
    for j, x in enumerate(h):
        if x:
            add_hwall(ax, i, j, 'red')
            # else: add_hwall(ax, i, j, (0.0, 0.0, 1.0, (A[i + 1][j] - A[i][j])**2 / N**4), 10)
        else:
            HCost[(i, j)] = abs(A[i + 1][j] - A[i][j])**2

cost_sum = sum([*VCost.values(), *HCost.values()])
cost_max = max([*VCost.values(), *HCost.values()])

print(prev_cost, cost_sum)
print(10**6 * log2(prev_cost / cost_sum))

for (i, j), v in VCost.items():
    add_vwall(ax, i, j, (0.0, 0.0, 1.0, v / N**4), 10)

for (i, j), v in HCost.items():
    add_hwall(ax, i, j, (0.0, 0.0, 1.0, v / N**4), 10)

plt.draw()

plt.savefig(f"{ argv[1] }.png")
