/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

struct rectangle {
    int x0, y0, z0;
    int x1, y1, z1;
    rectangle() : x0(0), y0(0), z0(0), x1(0), y1(0), z1(0) {}
    rectangle(int x0, int y0, int z0, int x1, int y1, int z1) : x0(x0), y0(y0), z0(z0), x1(x1), y1(y1), z1(z1) {}
    spair<std::tuple<int,int,int>> _debug() const { return { { x0, y0, z0 }, { x1, y1, z1 } }; }
};

std::istream& operator>>(std::istream& out, rectangle& rect) {
    int x0, y0, z0;
    int x1, y1, z1;
    out >> x0 >> y0 >> z0 >> x1 >> y1 >> z1;
    rect = { x0, y0, z0, x1, y1, z1 };
    return out;
}

void solve() {
    int n; cin >> n;
    valarray<rectangle> rects(n); input >> rects;
    debug(rects);

    REP(i, n) {
        int x0 = rects[i].x0;
        int x0 = rects[i].x0;
    }
}
