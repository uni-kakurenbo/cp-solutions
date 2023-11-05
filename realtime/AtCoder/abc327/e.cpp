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
    int n; input >> n;
    valarray<i64> a(n); input >> a;

    ld ans = -1200L;

    lib::valgrid<ld> dp(n + 1, n + 1, -10);
    dp[0][0] = 0;
    REP(i, n) REP(j, n) {
        if(dp[i][j] < 0) continue;
        chmax(dp[i + 1][j], dp[i][j]);
        chmax(dp[i + 1][j + 1], dp[i][j] * 0.9 + a[i]);
    }
    debug(dp);

    ld div = 0;
    FOR(k, 1, n) {
        div *= 0.9L;
        div += 1L;
        ld term = 1200.0L / std::sqrt((long double)k);

        chmax(ans, dp[n][k] / div - term);
    }

    print(ans);
}
