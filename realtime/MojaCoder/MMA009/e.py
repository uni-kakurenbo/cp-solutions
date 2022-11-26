# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

x, q = map(int, input().split())
dp = [ [x] * (q+1) for _ in [0] * (q+2) ]

for i in range(q):
    a, k = map(int, input().split())
    for j in range(0, q+2):
        dp[i+1][j] = max(dp[i][j] + a, (dp[i][j-1] | a) if j > 0 else 0)
    debug(dp)
    print(dp[i+1][k])
