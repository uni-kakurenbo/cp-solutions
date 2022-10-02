# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from collections import defaultdict
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, m, t = map(int, input().split())
A = [*map(int, input().split())]

B = defaultdict(int)

for i in range(m):
    x, y = map(int, input().split())
    B[x-1] = y


for i in range(n-1):
    t -= A[i]
    debug(t)
    if t <= 0: break
    t += B[i+1]
    debug(t)
else:
    exit(print("Yes"))

print("No")
