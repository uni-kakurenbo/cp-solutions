# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

h, w, n = map(int, input().split())
si, sj = map(int, input().split())

S = input()
T = input()

l, r, u, d = sj, sj, si, si

for i in range(n):
  if S[i] == "L":
    l -= 1
    if l < 1: exit(print("NO"))
  if S[i] == "R":
    r += 1
    if r > w: exit(print("NO"))
  if S[i] == "U":
    u -= 1
    if u < 1: exit(print("NO"))
  if S[i] == "D":
    d += 1
    if d > h: exit(print("NO"))

  if T[i] == "L":
    r = max(1, r-1)
  if T[i] == "R":
    l = min(w, l+1)
  if T[i] == "U":
    d = max(1, d-1)
  if T[i] == "D":
    u = min(h, u+1)

print("YES")
