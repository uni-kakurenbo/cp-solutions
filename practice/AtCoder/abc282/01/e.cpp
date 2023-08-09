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

#include "graph/spanning_tree.hpp"

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;

    lib::graph G(n);

    REP(i, n) REP(j, i+1, n) {
        int x = a[i], y = a[j];
        G.add_edge_bidirectionally(i, j, lib::mod(lib::pow_mod(x, y, m) + lib::pow_mod(y, x, m), m));
    }
    debug(G);

    print(G.maximum_spanning_tree());
}
