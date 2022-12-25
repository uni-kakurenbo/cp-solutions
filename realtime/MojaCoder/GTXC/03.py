# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from math import gcd
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = int(input())
A = [*map(int, input().split())]
B = [*map(int, input().split())]

g = 0

for a, b, in zip(A, B):
    g = gcd(g, abs(a - b))

if g == 0:
    print(0)
    exit()

ans = 0
for a, b, in zip(A, B):
    ans += abs(a - b) // g

print(ans)
