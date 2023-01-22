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
A = [*input()]
B = [*input()]

for i in range(n):
    if A[i] > B[i]:
        A[i], B[i] = B[i], A[i]
debug(A, B)

print(int("".join(A)) * int("".join(B)) % 998244353)
