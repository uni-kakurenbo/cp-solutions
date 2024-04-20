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

#include "iterable/compression.hpp"

void solve() {
    int n; cin >> n;
    vector<i64> l(n), p(n, -1), a(n);
    lib::graph G(n);

    REP(i, 1, n) {
        cin >> l[i] >> a[i]; --a[i];
        G.add_edge(a[i], i);
    }

    lib::compression comp(ALL(l));

    i64 m = comp.rank(INF32);
    vector<i64> ans0(m + 1);

    auto dfs = [&](auto&& dfs, int v) -> void {
        chmax(p[v], l[v]);
        chmax(p[v], p[a[v]]);
        ans0[comp.rank(p[v])]++;
        ITR(e, G[v]) dfs(dfs, e.to);
    };
    dfs(dfs, 0);
    debug(comp, l, p, ans0);

    REP(i, m) ans0[i+1] += ans0[i];
    debug(ans0);

    int q; cin >> q;
    REP(q) {
        i64 t, x; cin >> t >> x;
        if(t == 1) {
            debug(comp.rank2(x));
            print(ans0[comp.rank2(x)]);
        }
        if(t == 2) {
            --x;
            print(p[x]);
        }
    }
}
