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

#include "graph.hpp"

signed main() {
    int n, m; cin >> n >> m;
    lib::graph G(n);

    REP(m) {
        int u, v; cin >> u >> v; --u, --v;
        G.add_edge_bidirectionally(u, v);
    }

    int res = 0;

    vector<int> seen(n);
    auto dfs = [&](auto &dfs, int v) -> bool {
        ++res;
        if(res >= 1000000) return true;
        ITR(nxt, G[v]) {
            auto nv = nxt.to;
            if(seen[nv]) continue;
            seen[nv] = true;
            if(dfs(dfs, nv)) return true;
            seen[nv] = false;
        }
        return false;
    };
    seen[0] = true;
    dfs(dfs, 0);

    print(res);

    return 0;
}
