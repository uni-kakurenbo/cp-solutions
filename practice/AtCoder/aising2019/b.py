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
a, b = map(int, input().split())
P = [*map(int, input().split())]
cnt0, cnt1, cnt2 = 0, 0, 0
for p in P:
    cnt0 += p <= a
    cnt1 += a < p <= b
    cnt2 += b < p

print(min(cnt0, cnt1, cnt2))
