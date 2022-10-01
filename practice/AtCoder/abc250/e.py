# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from itertools import accumulate
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

n = int(input())
A = [*map(int, input().split())]
B = [*map(int, input().split())]
q = int(input())

setA = set()
setB = set()
hashA = [0] * (n+1)
hashB = [0] * (n+1)

def hash(x):
    return x * 2654435761 % (1 << 32)

for i in range(n):
    if not A[i] in setA:
        hashA[i+1] = hashA[i] ^ hash(A[i])
        setA.add(A[i])
    else:
        hashA[i+1] = hashA[i]
    if not B[i] in setB:
        hashB[i+1] = hashB[i] ^ hash(B[i])
        setB.add(B[i])
    else:
        hashB[i+1] = hashB[i]

for _ in [0] * q:
    x, y = map(int, input().split())
    print("Yes" if hashA[x] == hashB[y] else "No")
