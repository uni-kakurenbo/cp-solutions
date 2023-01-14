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

p = S.count('1')
q = T.count('1')

if abs(p - q) % 2:
    print(-1)
    exit()

if p < q:
    p, q = q, p
    T, S = S, T

S, T = reversed(S), reversed(T)

ans = []
for s, t in zip(S, T):
    if p!=q and s == '1' and t == '0':
        p -= 2
        ans.append('1')
    else:
        ans.append('0')

print("".join(reversed(ans)))
