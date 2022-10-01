# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, m = map(int, input().split())
A = [*map(int, input().split())]

INF = 10 ** 18

dp = [[-INF] * (m+1) for _ in [0] * (n+1)]

for i in range(n+1):
    dp[i][0] = 0

for i in range(1, n+1):
    for j in range(1, m+1):
        dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + A[i-1] * j)

print(dp[n][m])
