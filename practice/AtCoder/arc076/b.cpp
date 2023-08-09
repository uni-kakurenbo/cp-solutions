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

#include "graph/manhattan_minimum_spanning_tree.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> x(n), y(n); input >> lib::views::zip(x, y);
    valarray<int> ind(n); std::iota(ALL(ind), 0);

    lib::graph G(n);

    auto cost = [&](int i, int j) {
        return lib::min(std::abs(x[i] - x[j]), std::abs(y[i] - y[j]));
    };

    ind.sort([&](int i, int j) { return x[i] < x[j]; });
    REP(i, 1, n) G.add_edge_bidirectionally(ind[i], ind[i-1], cost(ind[i], ind[i-1]));

    ind.sort([&](int i, int j) { return y[i] < y[j]; });
    REP(i, 1, n) G.add_edge_bidirectionally(ind[i], ind[i-1], cost(ind[i], ind[i-1]));

    print(G.minimum_spanning_tree());
}
