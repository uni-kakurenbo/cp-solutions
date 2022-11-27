# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

h, w = map(int, input().split())
_S = [input() for _ in [0] * h]
_T = [input() for _ in [0] * h]

from itertools import product

S = [[""] * h for _ in [0] * w]
T = [[""] * h for _ in [0] * w]

for i, j in product(range(h), range(w)):
    S[j][i] = _S[i][j]
    T[j][i] = _T[i][j]


S.sort()
T.sort()

print("Yes" if S == T else "No")
