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

#include "graph/connected_components.hpp"

signed main() {
    int n, m; cin >> n >> m;
    graph G(n);
    vector<int> deg(n);

    REP(m) {
        int u, v; cin >> u >> v; --u, --v;
        deg[u]++, deg[v]++;
        G.add_edge_bidirectionally(u, v);
    }

    modint998244353 ans = 1;

    auto comps = G.components();
    auto groups = comps.groups();
    debug(groups);

    ITR(group, groups) {
        int e = 0;
        ITR(v, group) e += deg[v];
        debug(e);
        e /= 2;
        if(e == (int)group.size()) {
            ans *= 2;
        }
        else {
            ans *= 0;
        }
    }

    print(ans);

    return 0;
}
