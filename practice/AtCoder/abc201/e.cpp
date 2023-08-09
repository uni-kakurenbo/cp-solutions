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
    debug("C++: ", __cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "algebraic/bitxor.hpp"
#include "graph/lowest_common_ancestor.hpp"

using mint = lib::modint1000000007;

void solve() {
    int n; cin >> n;
    lib::graph<lib::algebraic::bitxor<i64>> G(n); G.read_bidirectionally<true>(n-1);

    lib::lowest_common_ancestor lca(G);

    auto dists = lca.cost;
    debug(dists);

    mint ans = 0;

    REP(d, 60) {
        valarray<lib::algebraic::bitxor<i64>> v = (dists >> d) & 1;
        debug(v);
        mint cnt0 = v.count(0), cnt1 = v.count(1);
        ans += cnt0 * cnt1 * mint{2}.pow(d);
    }

    print(ans);
}
