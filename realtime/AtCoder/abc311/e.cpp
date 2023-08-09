/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

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
    int h, w, n; cin >> h >> w >> n;

    lib::grid<int> G(h, w);
    REP(i, n) {
        int a, b; cin >> a >> b; --a, --b;
        G(a, b) = 1;
    }

    i64 ans = 0;

    lib::grid<i64> dp(h+1, w+1);
    FOR(i, 1, h) FOR(j, 1, w) {
        if(G(i-1, j-1) == 0) dp[i][j] = lib::min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]) + 1;
        ans += dp[i][j];
    }

    print(ans);
}
