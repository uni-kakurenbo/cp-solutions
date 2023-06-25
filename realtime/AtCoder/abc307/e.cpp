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

using mint = lib::modint998244353;

void solve() {
    int n, m; cin >> n >> m;

    vector<mint> dp(n + 1);
    dp[1] = 0, dp[2] = mint{m} * (m -1);
    FOR(i, 3, n) {
        dp[i] += mint{m} * mint(m - 1).pow(i - 2) * (m - 2);
        dp[i] += dp[i - 2];
    }

    print(dp[n]);
}
