# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

S = input()
n = len(S)
ans = 0
for i, s in enumerate(S):
    if s == "U":
        ans += n-i-1
        ans += i*2
    if s == "D":
        ans += i
        ans += (n-i-1)*2
print(ans)
