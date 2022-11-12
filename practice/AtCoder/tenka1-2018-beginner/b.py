# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

a, b, k = map(int, input().split())

for i in range(k):
    if i%2 == 0:
        if a%2:
            a-=1
        a //= 2
        b += a
    else:
        if b%2:
            b-=1
        b //= 2
        a += b

print(a, b)
