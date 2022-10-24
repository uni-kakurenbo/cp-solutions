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

ans = 10**100
for i in range(1, n):
    a = sum(int(d) for d in str(i))
    b = sum(int(d) for d in str(n-i))
    debug(i, n-i, a, b)
    ans = min(ans, a+b)
print(ans)
