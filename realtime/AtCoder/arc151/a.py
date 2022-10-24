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
S = input()
T = input()

# ハミング距離: XOR の popcount

cntS, cntT = 0, 0

for i in range(n):
    cntS += int(S[i])
    cntT += int(T[i])

d = abs(cntS - cntT)

debug(cntS, cntT, d)
if d%2 == 1:
    exit(print(-1))

ans = []
for i in range(n-1,-1,-1):
    if d > 0 and (cntS < cntT and S[i] == "0" and T[i] == "1" or cntS > cntT and S[i] == "1" and T[i] == "0"):
        ans.append("1")
        d -= 2
    else:
        ans.append("0")

ans = reversed(ans)
print(*ans, sep="")
