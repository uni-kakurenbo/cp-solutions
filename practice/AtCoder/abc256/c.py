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

h0, h1, h2, w0, w1, w2 = map(int, input().split())

ans = 0
for a00, a01, a10, a11 in product(range(1, 30), range(1, 30), range(1, 30), range(1, 30)):
    a20 = h0 - a00 - a10
    a02 = w0 - a00 - a01
    a21 = h1 - a01 - a11
    a12 = w1 - a10 - a11
    a22 = h2 - a02 - a12
    if w2 - a20 - a21 != a22: continue
    if a20 > 0 and a02 > 0 and a21 > 0 and a12 > 0 and a22 > 0:
        debug(a00, a01, a02)
        debug(a10, a11, a12)
        debug(a20, a21, a22)
        ans += 1
print(ans)
