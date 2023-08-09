/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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
    lib::graph<int> G(n); G.read_bidirectionally(m);

    auto ds = G.components();

    lib::set<spair<int>> ng;

    int k; cin >> k;
    REP(k) {
        int a, b; cin >> a >> b; --a, --b;
        auto [ u, v ] = std::make_pair(ds.leader(a), ds.leader(b));
        if(u > v) std::swap(u, v);
        ng.emplace(u, v);
    }

    int q; cin >> q;
    REP(i, q) {
        int a, b; cin >> a >> b; --a, --b;
        auto [ u, v ] = std::make_pair(ds.leader(a), ds.leader(b));
        if(u > v) std::swap(u, v);
        print(not ng.contains({ u, v }) ? "Yes" : "No");
    }
}
