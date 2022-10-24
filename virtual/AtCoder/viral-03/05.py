# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = 1 << 20
q = int(input())

A = [-1] * n
L = [-1] * n

def merge(p):
    if L[p % n] >= 0:
        L[p % n] = merge(L[p % n])
        return L[p % n]
    if A[p % n] == -1:
        A[p % n] = x
        return p
    L[p % n] = merge(p + 1)
    return L[p % n]

for _ in range(q):
    t, x = map(int, input().split())
    if t == 1:
        merge(x)
    if t == 2:
        print(A[x%n])
