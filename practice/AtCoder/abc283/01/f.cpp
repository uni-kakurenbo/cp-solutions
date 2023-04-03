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
    valarray<int> x(n), y(n);
    std::iota(ALL(x), 1);
    input >> y;

    lib::graph G(n);
    G.build_manhattan_mst(ALL(x), ALL(y));

    REP(i, n) {
        i64 ans = INF64;
        ITR(e, G[i]) chmin(ans, e.cost);
        print << ans << SPC;
    }
    print();
}
