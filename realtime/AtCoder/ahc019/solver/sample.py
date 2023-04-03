# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #
#region template
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

D = int(input())
f = [[] for i in range(2)]
r = [[] for i in range(2)]
for i in range(2):
    for k in range(D):
        f[i].append(input())
    for k in range(D):
        r[i].append(input())
b = [[0 for j in range(D * D * D)] for i in range(2)]
n = 0
for i in range(2):
    for x in range(D):
        for y in range(D):
            for z in range(D):
                debug(z, x, f[0][z][x])
                if f[i][z][x] == '1' and r[i][z][y] == '1':
                    n += 1
                    b[i][x * D * D + y * D + z] = n

print(n)
print(' '.join(map(str, b[0])))
print(' '.join(map(str, b[1])))
