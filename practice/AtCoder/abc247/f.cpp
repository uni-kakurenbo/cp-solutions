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

using mint = lib::modint998244353;

void solve() {
    int n; cin >> n;
    valarray<i64> p(n), q(n); input >> p >> q;
    p -= 1, q -= 1;

    lib::graph G(n);
    ITR(x, y, lib::views::zip(p, q)) {
        G.add_edge_bidirectionally(x, y);
    }

    valarray<mint> lucas(n+1);
    lucas[0] = 2, lucas[1] = 1;
    FOR(i, 2, n) lucas[i] = lucas[i-1] + lucas[i-2];

    auto gs = G.components().groups();

    print(std::accumulate(ALL(gs), 1_mod998244353, [&](mint acc, auto&& c) { return acc * lucas[c.size()]; }));
}
