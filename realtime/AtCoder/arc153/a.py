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
n -= 1

A = [1, 0, 0, 0, 0, 0]

for i in range(6):
    A[6-i-1] = n % 10
    n //= 10

A[0] += 1

a, b, c, d, e, f = map(str, A)
print(a + a + b + c + d + d + e + f + e)
