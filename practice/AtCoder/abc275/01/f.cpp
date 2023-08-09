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
    int n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;

    using table = lib::valgrid<i64>;

    table dp(m+1, 2, INF64);
    dp[0][1] = 0;
    REP(i, n) {
        table nxt_dp(m+1, 2, INF64);
        FOR(s, m) {
            chmin(nxt_dp[s][0], dp[s][1] + 1);
            chmin(nxt_dp[s][0], dp[s][0]);
            REP(ch, 2) {
                if(s + a[i] > m) continue;
                chmin(nxt_dp[s + a[i]][1], dp[s][ch]);
            }
        }
        dp = std::move(nxt_dp);
        debug(dp);
    }

    FOR(i, 1, m) { print(lib::to_optional_if(dp[i].min(), INF64).value_or(-1)); }
}
