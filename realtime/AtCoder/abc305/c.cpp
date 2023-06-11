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

void solve() {
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w); input >> G;

    int min_i = INF32, max_i = -1, min_j = INF32, max_j = -1;

    REP(i, h) REP(j, w) {
        if(G(i, j) == '.') continue;
        chmin(min_i, i), chmax(max_i, i);
        chmin(min_j, j), chmax(max_j, j);
    }

    REP(i, h) REP(j, w) {
        if(G(i, j) == '#') continue;
        if(i < min_i or max_i < i) continue;
        if(j < min_j or max_j < j) continue;
        print(i+1, j+1);
        return;
    }
}
