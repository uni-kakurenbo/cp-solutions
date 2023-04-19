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

#include "graph/shortest_path.hpp"

void solve() {
    int k; cin >> k;

    lib::graph G(k+1);
    G.add_edge(k, 1, 1);

    REP(i, k) {
        G.add_edge(i, lib::mod(i + 1, k), 1);
        G.add_edge(i, lib::mod(10 * i, k), 0);
    }

    print(G.distances_with_01cost(k)[0]);
}
