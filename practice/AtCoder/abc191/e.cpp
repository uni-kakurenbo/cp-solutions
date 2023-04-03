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

#include "graph/shortest_path.hpp"

signed main() {
    int n, m; cin >> n >> m;
    graph G(n); G.read<true>(m);

    REP(i, n) {
        auto dists = G.distances(i);
        i64 ans = INF64;

        REP(j, n) ITR(e, G[j]) {
            if(e.to != i) continue;
            if(dists[j] >= INF64) continue;
            chmin(ans, dists[j] + e.cost);
        }

        print(ans >= INF64 ? -1 : ans);
    }

    return 0;
}
