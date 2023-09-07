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
    int n; cin >> n;
    valarray<i64> x(n), y(n), z(n);
    input >> lib::views::zip(x, y, z);

    i64 need = (z.sum() + 1) / 2;
    REP(i, n) if(x[i] > y[i]) need -= z[i];

    debug(need);

    if(need < 0) {
        print(0);
        return;
    }

    valarray<i64> c(n);
    REP(i, n) c[i] = (x[i] + y[i] + 1) / 2 - x[i];
    debug(c, z);

    valarray<i64> dp(need + 1, INF64);
    dp[0] = 0;
    REP(i, n) FORD(j, need) {
        if(c[i] > 0) chmin(dp[lib::min(need, j + z[i])], dp[j] + c[i]);
    }

    debug(dp);
    print(dp[need]);
}
