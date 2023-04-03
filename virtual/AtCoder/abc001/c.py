# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #
#region template
from bisect import bisect_left, bisect_right
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

Deg = [ 0, 1125, 3375, 5625, 7875, 10125, 12375, 14625, 16875, 19125, 21375, 23625, 25875, 28125, 30375, 32625, 34875 ]
Deg_ = [ "N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW", "N" ]
Dis = [ 0, 3, 16, 34, 55, 80, 108, 139, 172, 208, 245, 285, 327 ]

deg, dis = map(int, input().split())
deg *= 10
dis = int(dis/6 + 0.5)

debug(deg, dis)

i = bisect_right(Deg, deg)
j = bisect_right(Dis, dis)
print(Deg_[i-1] if j-1 > 0 else "C", j-1);
