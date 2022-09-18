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
f = True
for i in range(n-1):
    if f and A[i] > A[i+1]: print(1, end=" "); f = not f
    elif not f and A[i] < A[i+1]: print(1, end=" "); f = not f
    else: print(0, end=" ")
print(0 if f else 1)
