/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

using mint = lib::modint998244353;

signed main() {
    int n, m, k; cin >> n >> m >> k;
    lib::graph G(n); G.read_bidirectionally(m);

    lib::multi_container<mint,2> dp(k+1, n);

    dp[0][0] = 1;

    REP(i, k) {
        mint all = 0;
        REP(j, n) all += dp[i][j];
        REP(j, n) {
            dp[i+1][j] += all - dp[i][j];
            ITR(e, G[j]) dp[i+1][j] -= dp[i][e.to];
        }
    }
    debug(dp);

    print(dp[k][0]);

    return 0;
}
