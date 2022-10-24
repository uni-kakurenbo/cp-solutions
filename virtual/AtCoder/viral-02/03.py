# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

h, w = map(int, input().split())
if h > 1 and w > 1:
    print((h-2)*(w-2))
    exit()

if h == 1 and w > 1:
    print(w-2)
    exit()

if w == 1 and h > 1:
    print(h-2)
    exit()

print(1)
