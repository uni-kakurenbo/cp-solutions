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
G = [input() for _ in range(h)]

i, j = 0, 0

st = set()
st.add((0, 0))

while True:
    if i > 0 and G[i][j] == 'U': i -= 1
    elif i < h-1 and G[i][j] == 'D': i += 1
    elif j > 0 and G[i][j] == 'L': j -= 1
    elif j < w-1 and G[i][j] == 'R': j += 1
    else: break
    if (i, j) in st:
        exit(print(-1))
    st.add((i, j))

print(i+1, j+1)
