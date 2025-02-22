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
    debug(__cplusplus);
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
    int n, s; cin >> n >> s;
    valarray<i64> a(n); input >> a;

    lib::range_extractor<valarray<mint>> dp(s+1);
    dp[0] = mint{2}.pow(n);
    FOR(i, 1, n) FORD(j, 0, s) dp[j+a[i-1]] += dp[j] * INV<2>;
    debug(dp);
    print(dp[s]);
}
