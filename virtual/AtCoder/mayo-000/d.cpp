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

#include "graph/shortest_path.hpp"

signed main() {
    int n, m, k; cin >> n >> m >> k;
    lib::graph G(2*n);

    REP(m) {
        int u, v, a; cin >> u >> v >> a; --u, --v;
        if(a) G.add_edge_bidirectionally(u, v);
        else G.add_edge_bidirectionally(u+n, v+n);
    }

    REP(k) {
        int s; cin >> s; --s;
        G.add_edge_bidirectionally(s, n+s, 0);
    }

    auto dists = G.distances_with_01cost(0);
    debug(dists);
    i64 res = min(dists[n-1], dists[2*n-1]);
    print(res >= INF64 ? -1 : res);

    return 0;
}
