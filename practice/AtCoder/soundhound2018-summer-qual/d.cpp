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

constexpr i64 BUDGET = 1'000'000'000'000'000UL;

#include "graph/shortest_path.hpp"

void solve() {
    i64 n, m, s, t; cin >> n >> m >> s >> t; --s, --t;

    lib::graph G(2 * n);

    REP(i, m) {
        i64 u, v, a, b; cin >> u >> v >> a >> b; --u, --v;
        G.add_edge_bidirectionally(u, v, a);
        G.add_edge_bidirectionally(u + n, v + n, b);
    }

    auto s_dist = G.distances_with_cost(s);
    auto t_dist = G.distances_with_cost(t + n);
    debug(s_dist, t_dist);

    lib::range_extractor<valarray<i64>> res(n, INF64);
    res.set_default(INF64);

    REPD(i, n) chmin(res[i], res[i+1], s_dist[i] + t_dist[n + i]);
    res *= -1, res += BUDGET;
    debug(res);

    print(res);
}
