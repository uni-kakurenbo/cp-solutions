# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

h, w = map(int, input().split())
A = [[*map(int, input().split())] for _ in range(h)]
debug(A)
mx = 0
ans = (-1, -1)
for i, row in enumerate(A):
    for j, v in enumerate(row):
        if mx < v:
            mx = v
            ans = (i+1, j+1)

print(*ans)
