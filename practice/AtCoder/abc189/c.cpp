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

#include "data_structure/disjoint_sparse_table.hpp"
#include "data_structure/range_action/range_min.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a;
    lib::disjoint_sparse_table<lib::actions::range_min<int>> data(ALL(a));

    i64 ans = 0;

    REP(l, n) FOR(r, l, n) {
        chmax(ans, (r - l) * data(l, r).fold());
    }

    print(ans);
}
