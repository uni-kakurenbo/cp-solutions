# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)


t = int(input())
for _ in [0] * t:
    n, k = map(int, input().split())
    S = input()

    m = S.count("1")

    cnt0 = [0] * (n+1)
    cnt1 = [0] * (n+1)
    for i, s in enumerate(S):
        cnt0[i+1] = (s == "0") + cnt0[i]
        cnt1[i+1] = (s == "1") + cnt1[i]

    ok = 0
    for i in range(n-k+1):
        if cnt0[i+k] - cnt0[i] == 0 and cnt1[i+k] - cnt1[i] == m:
            ok += 1

    debug(ok)

    print("Yes" if ok == 1 else "No")
