# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from decimal import Decimal
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

a, b = map(int, input().split())
def r(val, digit=0):
    p = 10 ** digit
    return (val * p * 2 + 1) // 2 / p

print('{:.03f}'.format(r(b/a, 4)))
