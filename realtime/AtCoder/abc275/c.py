# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from itertools import product
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

S = [input() for _ in range(9)]

R0to9 = range(9)

ans = 0
for si, sj in product(R0to9, R0to9):
    for ti, tj in product(range(si, 9), range(sj, 9)):
        if si == ti and sj == tj: continue
        if sj == tj: continue

        di = ti - si
        dj = tj - sj

        ui, uj = ti + dj, tj - di
        gi, gj = ui - di, uj - dj

        if ui < 0 or ui >= 9 or uj < 0 or uj >= 9: continue
        if gi < 0 or gi >= 9 or gj < 0 or gj >= 9: continue

        if S[si][sj] == S[ti][tj] == S[ui][uj] == S[gi][gj] == "#":
            debug((si, sj), (ti, tj), (ui, uj), (gi, gj))
            ans += 1


print(ans)
