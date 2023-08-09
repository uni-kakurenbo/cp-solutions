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

#include "data_structure/segment_tree.hpp"
#include "data_structure/range_action/range_gcd.hpp"

void solve() {
    i64 n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;
    lib::segment_tree<lib::actions::range_gcd<i64>> gcd(ALL(a));

    i64 ans = 0;

    REP(l, n) {
        ans += gcd.max_right(l, [&](i64 gcd) { return gcd == 0 or gcd >= m; }) - gcd.max_right(l, [&](i64 gcd) { return gcd == 0 or gcd > m; });
    }

    print(ans);
}
