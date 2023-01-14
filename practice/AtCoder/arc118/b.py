# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

k, n, m = map(int, input().split())
A = [*map(int, input().split())]

def valid(x):
    l = sum((m * a - x + n - 1) // n for a in A)
    r = sum((m * a + x) // n for a in A)
    return l <= m <= r

def build(x):
    B = [(m * a - x + n - 1) // n for a in A]
    s = sum(B)
    debug(s)
    for i in range(k):
        rais = min((m * A[i] + x) // n - B[i], m - s)
        s += rais
        B[i] += rais
    return B


ng, ok = -1, 10**18
while ok - ng > 1:
    mid = (ng + ok) // 2
    if valid(mid): ok = mid
    else: ng = mid

debug(ok)

print(*build(ok))
