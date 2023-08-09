# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #
#region template
from itertools import permutations
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

n, m = map(int, input().split())

ps = [0] * n
funcs = [set() for _ in range(n)]

for i in range(n):
    p, c, *F = map(int, input().split())
    ps[i] = p
    funcs[i] = set(F)

debug(ps, funcs)

for i, j in permutations(range(n), 2):
    if not (ps[i] >= ps[j]): continue
    if not (funcs[i] <= funcs[j]): continue
    if not(ps[i] > ps[j] or funcs[i] < funcs[j]): continue
    debug(i, j, funcs[i], funcs[j])
    print("Yes")
    exit()

print("No")
