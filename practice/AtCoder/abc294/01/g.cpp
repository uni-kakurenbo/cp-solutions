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
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "graph/centroid_path_decomposition.hpp"
#include "data_structure/segment_tree.hpp"
#include "data_structure/range_action/range_sum.hpp"

void solve() {
    int n; cin >> n;
    lib::graph<int> G(n); G.read_bidirectionally<true>(n - 1);

    lib::centroid_path_decomposition hld(G);
    lib::segment_tree<lib::actions::range_sum<i64>> cost(n - 1);

    REP(i, n-1) {
        hld.edges_on_path(G.edges()[i].from, G.edges()[i].to, [&](int l, int) { cost[l] = G.edges()[i].cost; });
    }

    int q; cin >> q;
    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int i, w; cin >> i >> w; --i;
            hld.edges_on_path(G.edges()[i].from, G.edges()[i].to, [&](int l, int) { cost[l] = w; });
        }
        if(t == 2) {
            int u, v; cin >> u >> v; --u, --v;
            i64 res = 0;
            hld.edges_on_path(u, v, [&](int l, int r) { res += cost(l, r).fold(); });
            print(res);
        }
    }
}
