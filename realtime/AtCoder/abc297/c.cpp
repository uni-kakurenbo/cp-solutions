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

#include "iterable/run_length_encoding.hpp"

void solve() {
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w);
    REP(i, h) REP(j, w) cin >> G[i][j];

    REP(i, h) {
        REP(j, w-1) {
            if(G[i][j] == 'T' and G[i][j+1] == 'T') {
                G[i][j] = 'P';
                G[i][j+1] = 'C';
            }
        }
        print(G[i]);
    }
}
