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

namespace atcoder {}
using namespace atcoder;

namespace Lib {}
using namespace Lib;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"
#include "graph/dijkstra.hpp"

signed main() {
    int n, m; cin >> n >> m;

    Graph G(n*3);
    REP(m) {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        G.add_edge_bidirectionally(u, v, w);
        G.add_edge_bidirectionally(n + u, n + v, w);
        G.add_edge_bidirectionally(2*n + u, 2*n + v, w);
    }

    int k; cin >> k;
    REP(k) {
        int p; cin >> p; --p;
        G.add_edge(p, n + p);
    }
    G.add_edge(2*n-1, 2*n);

    vector<ll> dists(3*n);
    G.dijkstra(0, &dists);
    debug(dists);

    print(dists[3*n-1]);

    return 0;
}
