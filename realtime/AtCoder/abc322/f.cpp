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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/range_action/range_affine_range_minmax.hpp"

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;

    lib::lazy_segment_tree<lib::actions::range_affine_range_minmax<int>> data(n);
    REP(i, n) data[i] = s[i] == '1';
}
