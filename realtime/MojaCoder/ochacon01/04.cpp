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

#include "data_structure/disjoint_set_union.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a;

    lib::dsu ds(n);

    int q; cin >> q;
    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y; --x, --y;
            if(ds.same(x, y)) continue;
            i64 v = a[ds.leader(x)] xor a[ds.leader(y)];
            a[ds.merge(x, y)] = v;
        }
        if(t == 2) {
            int x; cin >> x; --x;
            print(a[ds.leader(x)]);
        }
        debug(a, ds.groups());
    }
}
