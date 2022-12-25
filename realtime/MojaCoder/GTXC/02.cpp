/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "grid.hpp"
using namespace Lib;

signed main() {
    int h, w, n; cin >> h >> w >> n;

    Grid<char> grid(h, w, '-');
    Grid<int> visited(h, w, 0);

    REP(n) {
        int i, j; char d; cin >> i >> j >> d; --i, --j;
        grid(i, j) = d;
    }

    int i = 0, j = 0, di = 1, dj = 0;
    while(i >= 0 and i < h and j >= 0 and j < w and not visited(i,j)) {
        char dir = grid(i, j);

        visited(i, j) = true;

        if(dir == 'U') di = -1, dj = 0;
        if(dir == 'D') di = 1, dj = 0;
        if(dir == 'L') di = 0, dj = -1;
        if(dir == 'R') di = 0, dj = 1;
        i += di, j += dj;
    }

    int q; cin >> q;
    REP(q) {
        int a, b; cin >> a >> b; --a, --b;
        print(visited(a, b) ? "Yes" : "No");
    }

    return 0;
}
