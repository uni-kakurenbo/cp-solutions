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
    int n; cin >> n;
    lib::graph G(n); G.read_bidirectionally(n - 1);

    valarray<i64> dp(n, -1);
    auto dfs0 = [&](auto&& dfs0, int v, int p) -> i64 {
        int res = 1;
        ITR(e, G[v]) {
            if(e.to == p) continue;
            res += dfs0(dfs0, e.to, v);
        }
        return dp[v] = res;
    };
    dfs0(dfs0, 0, -1);
    debug(dp);

    i64 ans = 0;
    REP(i, n) {
        i64 sum0 = 0, sum1 = 0;
        ITR(v, G[i]) {
            sum0 += dp[i];
            sum1 += dp[i] * dp[i];
        }
        ans += sum0 * sum0 - sum1;
    }

    print(ans);
}
