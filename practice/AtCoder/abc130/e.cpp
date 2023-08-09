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


using mint = lib::modint1000000007;

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> s(n), t(m); input >> s >> t;

    lib::valgrid<mint> dp(n+1, m+1);
    FOR(i, n) dp[i][0] = 1; FOR(i, m) dp[0][i] = 1;
    FOR(i, 1, n) FOR(j, 1, m) {
        if(s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j] + dp[i][j-1];
        else dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
    }
    debug(dp);

    print(dp.back().back());
}
