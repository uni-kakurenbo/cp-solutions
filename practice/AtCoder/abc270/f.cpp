/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph/spanning_tree.hpp"
#include "graph/connected_components.hpp"

signed main() {
    int n, m; cin >> n >> m;
    vector<i64> x(n), y(n); input >> x >> y;

    lib::graph G(n+2); G.read<true>(m);

    i64 ans = LONG_LONG_MAX;

    REP(i, 2) REP(j, 2) {
        auto H = G;
        if(i) REP(v, n) H.add_edge(v, n, x[v]);
        if(j) REP(v, n) H.add_edge(v, n+1, y[v]);
        if(H.components().size(0) < n) continue;
        chmin(ans, H.minimum_spanning_tree_cost());
    }

    print(ans);

    return 0;
}
