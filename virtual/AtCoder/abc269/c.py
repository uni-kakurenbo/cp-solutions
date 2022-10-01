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
q = []

for i, bit in enumerate(bin(n)[:1:-1]):
    if bit == '1': q.append(i)

debug(q)

ans = []
for msk in range(1 << len(q)):
    num = 0
    for i in range(len(q)):
        if msk & (1 << i) > 0:
            num += 1 << q[i]
    ans.append(num)

ans.sort()
print(*ans, sep = "\n")
