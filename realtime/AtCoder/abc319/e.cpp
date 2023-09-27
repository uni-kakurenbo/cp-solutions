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
    long n, x, y; cin >> n >> x >> y;
    valarray<i64> p(n-1), t(n-1); input >> lib::views::zip(p, t);

    multi_container<i64,2> dp(n, 8);

    REP(i, n) REP(a, 8) {
        dp[i+1][a + t[i]][b] = dp[i][a][b];
    }

    int q; cin >> q;
    REP(q) {
        long s; cin >> s;

    }
}
