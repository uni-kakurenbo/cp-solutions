# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

from decimal import Decimal
from itertools import combinations

n = int(input())
P = [*map(Decimal,input().split())]

cnt = [0] * (n+1)
for i in range(1 << n):
    p = 1
    for j in range(n):
        if i & (1 << j):
            p *= P[j]/100
        else:
            p *= 1 - P[j]/100
    popcnt = bin(i).count('1')
    cnt[popcnt] += p
debug(cnt)
print(min(cnt))
