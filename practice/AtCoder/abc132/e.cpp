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
    int n, m; cin >> n >> m;

    lib::graph G(3 * n);
    REP(i, m) {
        int u, v; cin >> u >> v; --u, --v;
        G.add_edge(u, v + n), G.add_edge(u + n, v + 2*n), G.add_edge(u + 2*n, v);
    }

    int s, t; cin >> s >> t; --s, --t;

    auto dists = G.distances_without_cost(s);
    print(lib::to_optional_if_or_over(dists[t], INF64).value_or(-3) / 3);
}
