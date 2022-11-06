# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n, m = map(int, input().split())
G = [[] for _ in range(n)]
for _ in range(m):
    a, b = map(int, input().split())
    G[a-1].append(b)
    G[b-1].append(a)

for i in range(n):
    G[i].sort();
    print(len(G[i]), *G[i])
