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
    int n, m; std::cin >> n >> m;
    valarray<i64> a(n); input >> a;
    a.sort();

    lib::maximum<i64> ans = 0;

    REP(i, n) {
        auto itr = a.lower_bound(a[i] + m);
        ans <<= itr - (a.begin() + i);
    }

    print(ans);
}
