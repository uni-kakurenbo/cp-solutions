# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #
#region template

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
S = input()
A = [*map(int, S)]

for i in range(n - 1):
    if A[i] > 1 and A[i+1] != 1:
        print("-1")
        exit()

MOD = 998244353

prev = 0
B = []
s = 0
for i in range(1, n):
    if A[i] > 1:
        B += [(A[i] - 1, n-i)]
        s += A[i] - 1
        s %= MOD

debug(B, s)

ans = 0
l = n

while B:
    l += (s - 1) * B[-1][-1]
    ans += B[-1][-1]
    ans
    s -= B[-1][0]
    l %= MOD
    ans %= MOD
    s %= MOD

    B.pop()
ans += l

print((ans - 1) % MOD)
