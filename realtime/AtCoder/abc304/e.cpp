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

#include "data_structure/disjoint_set_union.hpp"

void solve() {
    int n, m; cin >> n >> m;

    lib::dsu uf(n);

    REP(m) {
        int u, v; cin >> u >> v; --u, --v;
        uf.merge(u, v);
    }

    debug(uf.groups());

    set<spair<int>> ng;

    int k; cin >> k;
    REP(k) {
        int x, y; cin >> x >> y; --x, --y;
        ng.emplace(uf.leader(x), uf.leader(y));
    }
    debug(ng);

    int q; cin >> q;
    REP(q) {
        int p, q; cin >> p >> q; --p, --q;
        int i = uf.leader(p), j = uf.leader(q);
        if(ng.contains({ i, j }) or ng.contains({ j, i })) {
            print("No");
        }
        else {
            print("Yes");
        }
    }
}
