# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = int(input())
A = [*map(int, input().split())]

MOD = 10 ** 9 + 7

dp0, dp1 = [0] * n, [1] * n
for i in range(n-1):
    dp0[i+1] = dp1[i] % MOD
    dp1[i+1] = (dp0[i] + dp1[i]) % MOD
debug(dp0, dp1)

sum0, sum1 = [0] * n, [A[0]] * n
for i in range(n-1):
    sum0[i+1] = (sum1[i] - A[i+1] * dp0[i+1]) % MOD
    sum1[i+1] = (sum0[i] + sum1[i] + A[i+1] * dp1[i+1]) % MOD
print((sum0[-1] + sum1[-1]) % MOD)
