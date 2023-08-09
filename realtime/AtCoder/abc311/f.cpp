/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

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

using mint = lib::modint998244353;

void solve() {
    int n, m; cin >> n >> m;
    lib::grid<char,string> G(n, m); input >> G;

    REP(i, n) REP(j, m) {
        if(G(i, j) == '#') {
            if(i < n-1) G(i+1, j) = '#';
            if(i < n-1 and j < m-1) G(i+1, j+1) = '#';
        }
    }


    debug(G);
}
