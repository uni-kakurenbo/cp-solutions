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


p = [list() for _ in [0,0]]
for a in A:
    p[a%2].append(a)

p[0].sort()
p[1].sort()

ans = -1

if len(p[0]) > 1:
    ans = max(ans, p[0][-1] + p[0][-2])

if len(p[1]) > 1:
    ans = max(ans, p[1][-1] + p[1][-2])

print(ans)
