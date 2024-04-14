# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy #
#region template

import sys
from random import choice


# sys.setrecursionlimit(10**5)
def debug(*args, **opts):
    if "LOCAL_JUDGE" in sys.argv: print(*args, **opts, file=sys.stderr)


class istream():

    def __init__(self, source=sys.stdin):
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
P = [*map(lambda x: int(x) - 1, input().split())]

ok = 0

for x in range(1 << n):
    A = ""
    for i in range(n):
        A += "L" if (x >> i) & 1 else "R"

    used = [False] * n

    for p in P:
        if A[p] == 'L':
            if not used[p % n]:
                used[p % n] = True
            elif not used[(p + 1) % n]:
                used[(p + 1) % n] = True
            else:
                # debug(A)
                break

        if A[p] == 'R':
            if not used[(p + 1) % n]:
                used[(p + 1) % n] = True
            elif not used[p % n]:
                used[p % n] = True
            else:
                # debug(A)
                break
    else:
        ok += 1
        print(A)
print(ok)
