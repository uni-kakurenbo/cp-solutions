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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/range_add_range_sum.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a;

    int q; cin >> q;
    valarray<i64> l(q), r(q); REP(i, q) cin >> l[i] >> r[i];

    auto p = lib::concat(a, l, r);
    lib::compressed comp(ALL(p));
    debug(comp.values);

    lib::lazy_segment_tree<lib::actions::range_add_range_sum<i64>> data(comp.rank_sup());

    int t = 0;
    REP(i, n) {
        while(comp.value(t) != a[i]) {
            if(i%2==0) data(t, t+1) <<= comp.value(t+1) - comp.value(t);
            t++;
        }
    }
    debug(data);

    REP(i, q) {
        print(data(comp.rank(l[i]), comp.rank(r[i])).fold());
    }
}
