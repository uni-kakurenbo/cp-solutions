# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

MOD = 10 ** 9 + 7

def mat_mul(a, b) :
    I, J, K = len(a), len(b[0]), len(b)
    c = [[0] * J for _ in range(I)]
    for i in range(I) :
        for j in range(J) :
            for k in range(K) :
                c[i][j] += a[i][k] * b[k][j]
                c[i][j] %= MOD
    return c


def mat_pow(x, n):
    y = [[0] * len(x) for _ in range(len(x))]

    for i in range(len(x)):
        y[i][i] = 1

    while n > 0:
        if n & 1:
            y = mat_mul(x, y)
        x = mat_mul(x, x)
        n >>= 1

    return y


n, k = map(int, input().split())

A = [[*map(int, input().split())] for _ in [0] * n]

A = mat_pow(A, k)

ans = 0
for r in A:
    for a in r:
        ans += a
        ans %= MOD
print(ans)
