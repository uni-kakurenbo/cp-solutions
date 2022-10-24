# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from math import log2
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = int(input())
A = [*map(int, input().split())]

D = [0] * 500000

for i in range(1, n+1):
    D[i*2] = D[i*2+1] = D[A[i-1]] + 1

for k in range(1, 2*n+2):
    print(D[k])
