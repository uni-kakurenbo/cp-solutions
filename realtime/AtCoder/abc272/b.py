# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from itertools import combinations
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, m = map(int, input().split())
D = [tuple(map(int, input().split())) for _ in [0] * m]

F = [[0] * n for _ in [0] * n]
for i in range(n): F[i][i] = 1

for d in D:
    for i, j in combinations(d[1:], 2):
        F[i-1][j-1] = F[j-1][i-1] = 1

debug(F)
print("Yes" if min(min(f) for f in F) > 0 else "No")
