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
    lib::graph G(n); G.read_bidirectionally(m);

    int p = (1 << n);
    auto f = [&](int x, int v) -> int {
        return (v << n) + x;
    };

    using edge = typename lib::virtual_graph<int>::edge;
    auto map = [&](int v) -> vector<edge> {
        vector<edge> res;
        if(v == 0) {
            REP(i, n) {
                res.emplace_back(v, f(1 << i, i));
            }
        }
        else {
            int i = v >> n;
            ITR(nv, G[i]) {
                res.emplace_back(v, f((v % p) ^ (1 << nv), nv));
            }
        }
        return res;
    };

    lib::virtual_graph<int> H(n * p, map);
    debug(H.size());

    auto dists = H.distances_without_cost(0);
    debug(dists);

    int ans = 0;
    REP(x, p) {
        int cost = INF32;
        REP(i, n) chmin(cost, dists[f(x, i)]);
        debug(std::bitset<8>(x), cost);
        ans += cost;
    }

    print(ans);
}
