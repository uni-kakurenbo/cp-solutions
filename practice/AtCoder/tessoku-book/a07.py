# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from itertools import accumulate
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

d = int(input())
n = int(input())
A = [0] * (d+1)
for _ in [0] * n:
    l, r = map(int, input().split())
    A[l-1] += 1
    A[r] -= 1

print(*[*accumulate(A)][:-1], sep = "\n")
