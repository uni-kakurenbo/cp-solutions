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

#include "graph/lowest_common_ancestor.hpp"

void solve() {
    int n, s, t; cin >> n >> s >> t; --s, --t;
    lib::graph<int> G(n); G.read_bidirectionally(n-1);

    lib::lowest_common_ancestor lca(G, s);

    REP(i, n) {
        print(lca.distance(i, lca(i, t)) + 1);
    }
}
