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
    REP(i, m) {
        int u, v, a; cin >> u >> v >> a; --u, --v;
        if(a == 0) u += n, v += n;
        G.add_edge_bidirectionally(u, v, 1);
    }
    REP(i, k) {
        int s; cin >> s; --s;
        G.add_edge_bidirectionally(s, s + n, 0);
    }

    auto dists = G.distances_with_01cost(0);
    debug(dists);
    ll res = std::min(dists[n-1], dists[2*n - 1]);
    print(res == LONG_LONG_MAX ? -1 : res);

    return 0;
}
