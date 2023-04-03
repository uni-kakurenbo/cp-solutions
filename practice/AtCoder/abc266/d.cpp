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

void solve() {
    int n; cin >> n;

    valarray<i64> t(n), x(n), a(n);
    REP(i, n) cin >> t[i] >> x[i] >> a[i];

    map<spair<i64>,i64> snuke;
    REP(i, n) snuke[{ t[i], x[i] }] = a[i];

    i64 T = t.max();
    lib::multi_container<maximum<i64>,2> dp(T+1, 6, -INF64);
    dp[0][0] = 0;

    REP(t, T) REP(p, 5) {
        i64 v = snuke[{ t+1, p }];
        dp[t+1][p] <<= dp[t][p-1] + v;
        dp[t+1][p] <<= dp[t][p] + v;
        dp[t+1][p] <<= dp[t][p+1] + v;
        // debug(dp);
    }

    print(dp[T].max());
}

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}
