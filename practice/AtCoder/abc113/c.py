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
A = [0] * m
for i in range(m):
    p, y = map(int, input().split())
    p -= 1
    A[i] = (p, y, i)

A.sort()

cnt = [1] * n
ans = [""] * m
for a in A:
    ans[a[2]] += str(a[0]+1).zfill(6)
    ans[a[2]] += str(cnt[a[0]]).zfill(6)
    cnt[a[0]] += 1

print(*ans, sep = "\n")
