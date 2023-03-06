# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #
#region template
from math import cos, pi, sin
from sys import setrecursionlimit, stdin, stderr, argv

def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

class istream():
    def __init__(self, source = stdin):
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

a, b = map(int, input().split())
if a > b: a, b = b, a
ans = 0
ans = max(ans, a / cos(15 * pi / 180))
if a * 2 <= b * (3 ** 0.5): ans = max(ans, a * 2 / (3 ** 0.5))
if a * 2 <= b * (3 ** 0.5): ans = max(ans, a * 2 / (3 ** 0.5))
if a * 2 <= b * (3 ** 0.5): ans = max(ans, a * 2 / (3 ** 0.5))
if(a * (3 ** 0.5) <= b * 2): ans = max(ans, a)
print(ans)
