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

n, q = map(int, input().split())
A = [*map(int, input().split())]
S = [*accumulate(A)]
S.insert(0, 0)
for _ in [0] * q:
    l, r = map(int, input().split())
    print(S[r] - S[l-1])
