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
    int n; cin >> n;
    lib::grid<char,string> G(n, n), H(n, n); input >> G;
    H = G;
    REP(i, n-1) {
        H[0][i+1] = G[0][i];
        H[i][0] = G[i+1][0];
        H[n-1][i] = G[n-1][i+1];
        H[i+1][n-1] = G[i][n-1];
    }
    G[0][0] = G[1][0];
    G[n-1][0] = G[n-1][1];
    G[0][n-1] = G[0][n-2];
    G[n-1][n-1] = G[n-2][n-1];

    print(H);
}
