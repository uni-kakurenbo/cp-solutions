# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

A = input()
B = input()
C = input()

cards = [[*reversed(A)], [*reversed(B)], [*reversed(C)]]

TURN = ('a', 'b', 'c')

turn = 0
while 1:
    if not cards[turn]: exit(print(TURN[turn].upper()))
    _turn = TURN.index(cards[turn][-1])
    cards[turn].pop()
    turn = _turn
