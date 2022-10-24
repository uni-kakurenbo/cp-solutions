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

m = 0
for a in A:
    if m <= a:
        m = a
    else:
        break
B = []
for a in A:
    if a != m: B.append(a)
print(*B)
