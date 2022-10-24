# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from collections import defaultdict
from sys import setrecursionlimit, stderr, argv

# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = int(input())
R = [*map(int, input().split())]
C = [*map(int, input().split())]

rev_R = [0] * (n+1)
rev_C = [0] * (n+1)

for i in range(n):
    rev_R[R[i]] = i+1
    rev_C[C[i]] = i+1

q = int(input())
Qr = defaultdict(list)
Qc = defaultdict(list)

for _ in [0] * q:
    r, c = map(int, input().split())
    Qr[r].append(c)
    Qc[c].append(r)

ans = {}

for i in range(n, 0, -1):
    j = n-i+1
    for c in Qr[rev_R[i]]:
        if (rev_R[i],c) not in ans:
            ans[(rev_R[i],c)] = "#"
    for r in Qr[rev_C[i]]:
        if (rev_C[i],r) not in ans:
            ans[(rev_C[i],r)] = "#"

    for c in Qr[rev_R[j]]:
        if (rev_R[j],c) not in ans:
            ans[(rev_R[j],c)] = "."
    for r in Qr[rev_C[j]]:
        if (rev_C[j],r) not in ans:
            ans[(rev_C[j],r)] = "."
debug(ans)

for r,v in Qr.items():
    for c in v:
        print(ans[(r,c)], end="");
