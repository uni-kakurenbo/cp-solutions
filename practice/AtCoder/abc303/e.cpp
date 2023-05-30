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
    int n; cin >> n;
    lib::graph G(n); G.read_bidirectionally(n - 1);

    int c = 0;

    REP(i, n) {
        if(G.degree(i) == 1) {
            c = G[i][0].to;
        }
    }

    auto dists = G.distances_without_cost(c);
    debug(dists);

    vector<int> ans;
    REP(i, n) {
        if(dists[i] % 3 == 0) ans.push_back(G.degree(i));
    }

    ans.sort();

    print(ans);

    std::min(0, 1);
}
