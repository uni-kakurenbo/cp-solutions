# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from itertools import combinations
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, m = map(int, input().split())

st = [set() for _ in range(n)]

for i in range(n):
    S = input()
    for j, s in enumerate(S):
        if s == 'o': st[i].add(j)

ans = 0
for i, j in combinations(range(n), 2):
    if len(st[i] | st[j]) == m:
        ans += 1

print(ans)
