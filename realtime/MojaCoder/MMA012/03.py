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

A = [0] * n

for i in range(n):
    s, *T = input().split()
    T = [*map(int, T)]
    solved = m - T.count(-1)
    last_task = max(T)
    debug(solved, last_task)
    A[i] = (-solved, last_task, i, s)

A.sort()
for a in A:
    print(a[-1])
