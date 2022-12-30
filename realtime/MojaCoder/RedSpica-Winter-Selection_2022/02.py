# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

days = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)

mn, c = 10**10, 0
ans_m, ans_d = -1, -1
for m in range(1, 13):
    for d in range(1, 1+days[m-1]):
        c += 1
        x = abs(m/d - c/365)
        if x <= mn:
            mn = x
            ans_m, ans_d = m, d

print(f"{ans_m}/{ans_d}")
