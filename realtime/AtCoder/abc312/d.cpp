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
    string s; cin >> s;
    int n = s.size();

    // dp[i][j] = (i 文字目まで，和が j)
    lib::range_extractor<valarray<mint>> dp(n+1);
    dp[0] = 1;
    REP(i, n) {
        lib::range_extractor<valarray<mint>> nxt(n+1);
        FORD(v, n) {
            if((s[i] == '(') or (s[i] == '?')) nxt[v+1] += dp[v];
            if((s[i] == ')') or (s[i] == '?') and (v > 0)) nxt[v-1] += dp[v];
        }
        dp = std::move(nxt);
    }
    print(dp[0]);
}
