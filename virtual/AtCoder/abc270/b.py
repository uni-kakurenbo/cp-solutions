# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from operator import xor
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

x, y, z = map(int, input().split())
if xor(x>0, y>0) or abs(x) < abs(y): print(abs(x))
elif xor(z>0, y>0) or abs(z) < abs(y): print(abs(z) + abs(y - z) + abs(y - x))
else: print(-1)
