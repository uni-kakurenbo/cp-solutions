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

r = m%9

ans = -1
for i in range(1, 10):
    for j in range(1, n+1):
        if i * j % 9 == r:
            p = str(i) * j
            if int(p) % m == 0:
                ans = str(i) * j
print(ans)
