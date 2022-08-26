# @uni_kakurenbo
# https://github.com/uni-kakurenbo/competitive-programming-workspace
#
# CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja

# #language PyPy3 #

from sys import setrecursionlimit, stderr, argv
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr)

r, c = map(int, input().split())
grid = [
    "###############",
    "#.............#",
    "#.###########.#",
    "#.#.........#.#",
    "#.#.#######.#.#",
    "#.#.#.....#.#.#",
    "#.#.#.###.#.#.#",
    "#.#.#.#.#.#.#.#",
    "#.#.#.###.#.#.#",
    "#.#.#.....#.#.#",
    "#.#.#######.#.#",
    "#.#.........#.#",
    "#.###########.#",
    "#.............#",
    "###############",
    ];

debug(grid);

print("black" if grid[r-1][c-1] == '#' else "white");
