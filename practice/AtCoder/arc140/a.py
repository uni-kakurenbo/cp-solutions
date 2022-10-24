# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

def divisors(n):
    d0, d1 = [], []
    i = 1
    while i*i <= n:
        if n % i == 0:
            d0.append(i)
            if i != n // i:
                d1.append(n//i)
        i += 1
    return d0 + d1[::-1]

n, k = map(int, input().split())
S = input()

ans = n
divs = divisors(n)

for div in divs:
    diff = 0
    for i in range(div):
        cnt = [0] * 26
        for j in range(i,n,div):
            cnt[ord(S[j])-ord('a')] += 1
        diff += n//div - max(cnt)
    if diff <= k: ans = min(ans, div)

print(ans)
