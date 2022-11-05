# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

def divisors(n):
    d0, d1 = [], []
    i = 1
    while i*i <= n:
        if n % i == 0:
            d0.append(i)
            if i != n // i:
                d1.append(n//i)
        i += 1
    return d0 + d1[::-1]

x, y = map(int, input().split())
st = set(divisors(y-x)) & set(divisors(x-2015))
print(*st, sep="\n")
