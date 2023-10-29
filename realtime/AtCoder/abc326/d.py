# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy #
#region template

from copy import deepcopy
from itertools import combinations, combinations_with_replacement, permutations, product
import sys

# sys.setrecursionlimit(10**5)
def debug(*args, **opts):
    if "LOCAL_JUDGE" in sys.argv: print(*args, **opts, file=sys.stderr)

class istream():
    def __init__(self, source = sys.stdin):
        self.pos = -1
        self.buffer = []
        self.source = source

    def one(self):
        self.pos += 1
        if self.pos >= len(self.buffer): self.buffer.extend(self.source.readline().split())
        return self.buffer[self.pos]

    def __call__(self, *types):
        if len(types) == 0: return str(self.one())

        if len(types) == 1:
            tp, count = types[0], 1
            if isinstance(tp, int):
                tp, count = str, tp
            if count == 1:
                return tp(self.one())
            else:
                return tuple(tp(self.one()) for _ in [0] * count)

        if len(types) == 2 and isinstance(types[1], int):
            return tuple(types[0](self.one()) for _ in [0] * types[1])

        return tuple(map(lambda type: type(self.one()), types))

    def line(self, type):
        return tuple(map(type, self.source.readline().split()))

cin = istream()

# setrecursionlimit(10**5)

#endregion

n = int(input())
r = input()
c = input()

fs = range(n - 2)

A = ord('A')

first = product(fs, repeat=n)
for a, b in product(first, repeat=2):
    G = [ [ 'D' ] * n for i in range(n) ]
    ng = False

    for i in range(n):
        G[i][a[i]] = r[i]
        G[b[i]][i] = c[i]

    for i in range(n):
        for j in range(n):
            if G[i][j] == 'D':
                continue
            if G[i][j] == r[i]:
                break
            else:
                ng = True
                break
    if ng: continue

    for i in range(n):
        for j in range(n):
            if G[j][i] == 'D':
                continue
            if G[j][i] == c[i]:
                break
            else:
                ng = True
                break

    if ng: continue

    cnt_r = [ [ 0, 0, 0, 0 ] for i in range(n) ]
    cnt_c = [ [ 0, 0, 0, 0 ] for i in range(n) ]
    for i in range(n):
        for j in range(n):
            cnt_r[i][ord(G[i][j]) - A] += 1
            cnt_c[j][ord(G[i][j]) - A] += 1
    for i in range(n):
        cnt_r[i].pop()
        cnt_c[i].pop()
        if max(cnt_r[i]) > 1:
            ng = True
            break
        if max(cnt_c[i]) > 1:
            ng = True
            break
    if ng: continue

    rest = [0] * n
    for i in range(n):
        yet = []
        for j in range(n):
            if G[i][j] == 'D' and i > b[j] and j > a[i]:
                yet.append(j)
        rest[i] = permutations(yet, 3 - sum(cnt_r[i]))

    ABC = [ [ 0, 1, 2 ] for i in range(n) ]
    for i in range(n):
        for j in range(n):
            try:
                ABC[i].remove(ord(G[i][j]) - A)
            except:
                pass
    for inds in product(*rest):
        cnt = deepcopy(cnt_c)
        H = deepcopy(G)
        for i in range(n):
            for j in range(len(ABC[i])):
                cnt[inds[i][j]][ABC[i][j]] += 1
                H[i][inds[i][j]] = chr(ABC[i][j] + A)
        for i in range(n):
            if max(cnt[i]) > 1:
                break
        else:
            debug(a, b, inds)
            debug(G)
            print("Yes")
            for h in H: print("".join(h).replace('D', '.'))
            exit()

print("No")
