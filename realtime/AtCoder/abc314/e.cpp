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
    int n, m; cin >> n >> m;
    valarray<ld> c(n);
    lib::grid<int> G(n, 0);
    REP(i, n) {
        cin >> c[i];
        int p; cin >> p;
        int cnt = 0;
        REP(p) {
            int g; cin >> g;
            cnt += g == 0;
            if(g > 0) G[i].push_back(g);
        }
        c[i] *= p;
        c[i] /= (p - cnt);
    }

    lib::valarray<ld> dp(m+1, 0);
    dp[m] = 0;

    REPD(i, m) {
        int ch = -1;
        ld min_sum = INF<ld>;
        REP(j, n) {
            ld sum = c[j];
            ITR(x, G[j]) sum += dp[lib::min(m, i + x)] / G[j].size();
            if(chmin(min_sum, sum)) ch = j;
            // debug(i, j, sum);
        }
        // debug(i, ch);
        dp[i] = min_sum;
    }
    debug(dp);

    print(dp[0]);
}
