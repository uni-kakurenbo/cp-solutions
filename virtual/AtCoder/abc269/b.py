# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

S = [input() for _ in [0] * 10]
a, c = 0, 0
while S[a] == "..........": a += 1
while S[a][c] == ".": c += 1
d = c
while d < 10 and S[a][d] == "#": d += 1
b = a
while b < 10 and S[b] != "..........": b += 1
print(a+1, b)
print(c+1, d)
