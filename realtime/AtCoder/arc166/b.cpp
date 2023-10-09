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
    int n;
    i64 a, b, c; cin >> n >> a >> b >> c;
    valarray<i64> v(n); input >> v;

    valarray<array<i64,8>> dp(n + 1);
    ITRR(r, dp) r.fill(INF64);
    debug(dp);

    dp[0][0] = 0;
    REP(i, n) REP(x, 8) {
        chmin(dp[i+1][x | 0b000], dp[i][x]);
        chmin(dp[i+1][x | 0b001], dp[i][x] + lib::mod(-v[i], a));
        chmin(dp[i+1][x | 0b010], dp[i][x] + lib::mod(-v[i], b));
        chmin(dp[i+1][x | 0b100], dp[i][x] + lib::mod(-v[i], c));
        chmin(dp[i+1][x | 0b011], dp[i][x] + lib::mod(-v[i], lib::lcm(a, b)));
        chmin(dp[i+1][x | 0b101], dp[i][x] + lib::mod(-v[i], lib::lcm(a, c)));
        chmin(dp[i+1][x | 0b110], dp[i][x] + lib::mod(-v[i], lib::lcm(b, c)));
        chmin(dp[i+1][x | 0b111], dp[i][x] + lib::mod(-v[i], lib::lcm(a, b, c)));
    }
    debug(dp);

    print(dp[-1][7]);
}
