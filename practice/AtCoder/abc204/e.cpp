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
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(m), b(m), c(m), d(m);
    input >> lib::views::zip(a, b, c, d);
    a -= 1, b -= 1;

    lib::graph G(n);
    REP(i, m) {
        G.add_edge_bidirectionally(a[i], b[i]);
    }

    valarray<i64> dists(n);

    auto f = [&](int v, int i, i64 t) -> i64 {
        return t - dists[v] + c[i] + d[i] / (t + 1);
    };

    using edge = lib::virtual_graph<int,i64>::edge;
    auto next = [&](int v) -> vector<edge> {
        vector<edge> res;
        ITR(e, G[v]) {
            debug(e.index);
            res.emplace_back(v, e.to, f(v, e.index, lib::max(dists[v], (i64)std::round(std::sqrt(d[e.index])) - 1)));
        }
        debug(dists);
        debug(v, res);
        return res;
    };

    lib::virtual_graph<int,i64> H(next, n);

    H.distances_with_cost(0, &dists);
    debug(dists);

    print(lib::to_optional_if_or_over(dists[n-1], INF64).value_or(-1));
}
