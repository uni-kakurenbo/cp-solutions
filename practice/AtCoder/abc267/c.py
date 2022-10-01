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

n, m = map(int, input().split())
A = [*map(int, input().split())]

acc_sum = [*accumulate(A)]
acc_sum.insert(0, 0)

ans = cur = sum(A[i] * (i+1) for i in range(m))
for i in range(m,n):
    cur += A[i] * m
    cur -= acc_sum[i] - acc_sum[i-m]
    ans = max(ans, cur)

print(ans)
