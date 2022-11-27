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

AKIHABARA = "AKIHABARA"

for t in "KIHBR":
    if t not in S: exit(print("NO"))

i, j = 0, 0
while j < len(S) and i < len(AKIHABARA):
    debug(i, j)
    if S[j] == AKIHABARA[i]:
        i += 1
        j += 1
        continue
    else:
        if AKIHABARA[i] == 'A': i += 1
        else: break
else:
    debug("A")
    if j == len(S): print("YES")
    else: print("NO")
    exit()
print("NO")
