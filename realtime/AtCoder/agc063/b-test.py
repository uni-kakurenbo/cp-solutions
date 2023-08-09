# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #
#region template
from random import randint
from sys import setrecursionlimit, stdin, stderr, argv

from more_itertools import adjacent, difference

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

n, m = map(int, input().split())

X = [  ]

for i in range(n):
    k = randint(1, m)
    j = randint(0, len(X))
    X[j:j+1] = [*range(1, k+1)]
    debug(X)

    Y = [0] * len(X)
    for i in range(len(X) - 1):
        Y[i] = X[i+1] - X[i]
    Y[-1] = -(X[-1] - 1)
    debug(Y)


print(len(X))
print(*X)
