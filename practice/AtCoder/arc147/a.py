# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from collections import deque

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = int(input())
A = deque(sorted(map(int, input().split())))

cnt = 0
while A:
    min, max = A[0], A.pop()
    if max % min > 0: A.appendleft(max % min)
    cnt += 1

print(cnt - 1)
