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
    int n0, n1, m; cin >> n0 >> n1 >> m;
    lib::graph G0(n0), G1(n1);
    REP(m) {
        int a, b; cin >> a >> b; --a, --b;
        if(a > b) std::swap(a, b);
        if(b < n0) G0.add_edge_bidirectionally(a, b);
        else G1.add_edge_bidirectionally(a - n0, b - n0);
    }

    auto d0 = G0.distances_without_cost(0);
    auto d1 = G1.distances_without_cost(n1 - 1);

    print(*std::max_element(ALL(d0)) + *std::max_element(ALL(d1)) + 1);
}
