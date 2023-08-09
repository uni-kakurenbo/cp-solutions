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

#include <atcoder/scc>

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;

    lib::graph<int> G(n);
    atcoder::scc_graph G0(n);
    REP(m) {
        int u, v; cin >> u >> v; --u, --v;
        G0.add_edge(v, u);
        G.add_edge(v, u);
    }

    auto scc = G0.scc();
    debug(scc);

    REP(i, scc.size()) {
        i64 g = 0;
        ITR(c, scc[i]) g = std::gcd(g, a[c]);
        ITR(c, scc[i]) a[c] = g;
        ITR(c, scc[i]) ITR(j, G[c]) a[j] = std::gcd(a[j], a[c]);
    }

    print(a);
}
