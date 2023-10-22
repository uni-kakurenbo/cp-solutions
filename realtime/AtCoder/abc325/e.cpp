/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i64 n, a, b, c; cin >> n >> a >> b >> c;
    lib::grid<i64> D(n, n); input >> D;
    debug(D);

    lib::graph<i64> G(2 * n);
    REP(i, n) {
        G.add_edge(i, i + n, 0);
        REP(j, n) {
            if(i == j) continue;
            G.add_edge(i, j, D(i, j) * a);
            G.add_edge(i + n, j + n, D(i, j) * b + c);
        }
    }
    debug(G);

    auto dists = G.distances_with_cost(0);
    debug(dists);
    print(lib::min(dists[n - 1], dists[2 * n - 1]));
}
