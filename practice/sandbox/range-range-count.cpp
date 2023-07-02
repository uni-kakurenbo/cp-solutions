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

#include "data_structure/wavelet_matrix.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a;
    lib::wavelet_matrix<int>::compressed data(ALL(a));

    int q; cin >> q;
    REP(q) {
        int l, r, x, y; cin >> l >> r >> x >> y;
        print(data(--l, r).count_in_range(x, ++y));
    }
}
