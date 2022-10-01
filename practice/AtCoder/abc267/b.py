# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from itertools import combinations
from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

columns = ((6,), (3,), (7, 1,), (4, 0,), (8, 2,), (5,), (9,))
S = input()
if S[0] == '1': exit(print('No'))

nonempty_columns = [];
for i, column in enumerate(columns):
    if any(S[j] == '1' for j in column): nonempty_columns.append(i)

if len(nonempty_columns) < 2: exit(print('No'))
for i, j in combinations(nonempty_columns, 2):
    for k in range(i+1, j):
        if all(S[l] == '0' for l in columns[k]): exit(print('Yes'))

print('No')
