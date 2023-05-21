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
#include "graph/centroid_path_decomposition.hpp"

#include "data_structure/disjoint_sparse_table.hpp"
#include "data_structure/range_action/range_max.hpp"

void solve() {
    int n, m, q; cin >> n >> m >> q;

    lib::graph G(n); G.read_bidirectionally<true>(m);

    lib::graph mst;
    G.minimum_spanning_tree(&mst);

    lib::centroid_path_decomposition cpd(mst);

    valarray<int> _cost(n - 1);
    ITR(e, mst.edges()) {
        cpd.edges_on_path(e.from, e.to, [&](int l, int) { _cost[l] = e.cost; });
    }
    debug(_cost);
    lib::disjoint_sparse_table<lib::actions::range_max<int>> cost(ALL(_cost));

    REP(q) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        int mx_c = 0;
        cpd.edges_on_path(u, v, [&](int l, int r) { chmax(mx_c, cost(l, r).fold()); });

        debug(mx_c);

        print(m < mx_c ? "Yes" : "No");
    }
}
