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

ans = -1

for d in range(1, 10):
    mod = 0
    pro_ans = "-1"
    for i in range(1, n+1):
        mod = (mod * 10 + d) % m
        if mod == 0:
            pro_ans = str(d) * i

    ans = max(ans, int(pro_ans))

print(ans)
