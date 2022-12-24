# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, t = map(int, input().split())
A = [*map(int, input().split())]

t %= sum(A)

acc = 0
for i, a in enumerate(A, 1):
    if acc+a >= t:
        exit(print(i, t-acc))
    acc += a
