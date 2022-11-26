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
A = [*map(int, input().split())]
m = int(input())
B = [*map(int, input().split())]

x = 0
for a in A:
    x += a
    if x in B:
        x = 0
print(x)
