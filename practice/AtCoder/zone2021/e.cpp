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
    int r, c; cin >> r >> c;
    lib::valgrid<int> a(r, c-1), b(r-1, c); input >> a >> b;
    a += a, b += b;
    debug(a, b);

    auto id = [&](int i, int j) { return 2 * c * i + j; };

    lib::graph G(r * c * 2);
    REP(i, r) REP(j, c) {
        if(j + 1 < c) G.add_edge(id(i, j), id(i, j + 1), a[i][j]);
        if(0 < j) G.add_edge(id(i, j), id(i, j - 1), a[i][j - 1]);
        if(i + 1 < r) G.add_edge(id(i, j), id(i + 1, j), b[i][j]);
        G.add_edge_bidirectionally(id(i, j), id(i, c + j), 1);
    }
    REP(k, c) REP(i, 1, r) G.add_edge(id(i, c + k), id(i - 1, c + k), 2);

    auto dists = G.distances(id(0, 0));
    debug(dists);

    print(dists[id(r-1, c-1)] / 2);
}
