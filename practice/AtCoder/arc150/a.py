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

    cnt0, cnt1 = [0] * (n+1), [0] * (n+1)
    for i in range(n):
        cnt0[i+1] = cnt0[i] + (S[i] == '0')
        cnt1[i+1] = cnt1[i] + (S[i] == '1')
    sum1 = S.count('1')

    debug(cnt0, cnt1)

    cnt = sum(cnt0[i] == cnt0[i+k] and cnt1[i+k]-cnt1[i] == sum1 for i in range(n-k+1))

    print("Yes" if cnt == 1 else "No")
