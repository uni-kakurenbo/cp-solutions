# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

from itertools import product

h, w = map(int, input().split())
G = [input() for _ in [0] * h]

ans = 0
for i, j in product(range(h), range(w)):
    if G[i][j] == '#': continue
    if i+1 < h and G[i+1][j] == '.': ans += 1
    if j+1 < w and G[i][j+1] == '.': ans += 1

print(ans)
