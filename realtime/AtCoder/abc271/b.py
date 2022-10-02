# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, q = map(int, input().split())
Fs = [0] * n
for i in range(n):
    l, *A = map(int, input().split())
    Fs[i] = A

for i in range(q):
    s, t = map(int, input().split())
    print(Fs[s-1][t-1])
