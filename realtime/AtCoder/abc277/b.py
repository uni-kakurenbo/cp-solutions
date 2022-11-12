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
st = set()
for _ in [0] * n:
    S = input()
    if S[0] not in ('H', 'D', 'C', 'S'): break
    if S[1] not in ("A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"): break
    if S in st: break
    st.add(S)
else:
    print("Yes")
    exit()
print("No")
