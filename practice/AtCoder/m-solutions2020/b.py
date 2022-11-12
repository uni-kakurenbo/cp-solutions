# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

a, b, c = map(int, input().split())
k = int(input())
while b <= a: b *= 2; k -= 1
while c <= b: c *= 2; k -= 1
print("Yes" if k >= 0 else "No")
