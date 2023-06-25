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

void solve() {
    int h; cin >> h;

    lib::valarray<i64> dp(h + 1, INF64);

    dp[0] = 0;

    int n; cin >> n;
    REP(n) {
        int a, b; cin >> a >> b;
        REP(j, 0, h) chmin(dp[std::min<i64>(h, j + a)], dp[j] + b);
    }

    // debug(dp);

    print(dp[h]);
}
