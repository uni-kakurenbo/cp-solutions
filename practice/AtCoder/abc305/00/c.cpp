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

    REP(i, h) REP(j, w) {
        if(G(i, j) == '#') continue;
        int cnt = 0;
        ITR(p, q, G.vicinities4(i, j)) cnt += G(p, q) == '#';
        if(cnt >= 2) {
            print(i+1, j+1);
        }
    }
}
