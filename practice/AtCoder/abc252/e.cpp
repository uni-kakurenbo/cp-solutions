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

#include "graph/shortest_path.hpp"

void solve() {
    int n, m; cin >> n >> m;
    lib::graph G(n);

    map<spair<int>,int> e;
    REP(i, m) {
        int a, b, c; cin >> a >> b >> c; --a, --b;
        e[{ a, b }] = e[{ b, a }] = i;
        G.add_edge_bidirectionally(a, b, c);
    }

    auto dists = G.distances(0);
    debug(dists);

    set<int> ans;

    REP(i, n) {
        int id = -1;
        ITR(j, G[i]) {
            if(dists[i] - dists[j.to] == j.cost) id = e[{ i, j.to }];
        }
        if(id >= 0) ans.insert(id + 1);
    }

    print(ans);
}
