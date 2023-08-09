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
#include "data_structure/range_action/range_add_range_min.hpp"
#include "data_structure/range_action/range_add_range_sum.hpp"

void solve() {
    int n, q; cin >> n >> q;
    valarray<i64> d(n);
    REP(i, n) {
        char c; cin >> c;
        d[i] = (c == '(') ? 1 : -1;
    }
    lib::accumulation cum(ALL(d));
    debug(d, cum);

    lib::lazy_segment_tree<lib::actions::range_add_range_min<int>> v(ALL(cum));

    REP(q) {
        int t; cin >> t;
        int l, r; cin >> l >> r; --l;
        if(t == 1) {
            v(l+1, r) <<= (v[r].val() - v[r-1].val()) - (v[l+1].val() - v[l].val());
        }
        if(t == 2) {
            print((v(l, r).fold().val() >= v[l].val() and v[r].val() == v[l].val()) ? "Yes" : "No");
        }
        debug(v);
    }
}
