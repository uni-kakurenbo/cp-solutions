# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

from itertools import product
from functools import reduce
from collections import defaultdict

MOD = 998244353

a, b = map(int, input().split())

def solve(x):
    v = str(x)
    n = len(v)
    dp = defaultdict(int)
    dp[0, 0, 0, 0, 0] = 1

    for i, less, has2, has7, total in product(range(n), (0, 1), (0, 1), (0, 1), range(74)):
        max_d = 9 if less else int(v[i])
        for d in range(max_d+1):
            less_ = less or d < max_d
            has2_ = has2 or d == 2
            has7_ = has7 or d == 7
            total_ = min(73, total + d)
            dp[i+1, less_, has2_, has7_, total_] += dp[i, less, has2, has7, total]
            dp[i+1, less_, has2_, has7_, total_] %= MOD

    criteria = ((n, less, has2, has7, total) for less, has2, has7, total
                                    in product((0, 1), (0, 1), (0, 1), range(74))
                                    if (has2 and has7) or total==72)

    return reduce(lambda a, b: (a + b) % MOD, (dp[c] for c in criteria))

debug(solve(a-1))
debug(solve(b))

print((solve(b) - solve(a-1)) % MOD)
