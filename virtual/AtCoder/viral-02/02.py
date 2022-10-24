# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

MAX = 2*10^5;

a, b = map(int, input().split())
S = set(range(a,b+1))

ans = 1
for i in range(1, b+1):
    if sum(j in S for j in range(i, b+1, i)) < 2: continue
    ans = max(ans, i)

print(ans)
