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
    int n, m; cin >> n >> m;
    lib::multi_container<mint,4> dp(n+1, m+1, m+1, m+1, 0);

    dp[0][m][m][m] = 1;

    REP(i, n) FOR(p, m) FOR(q, p, m) FOR(r, q, m) {
        mint prv = dp[i][p][q][r];
        if(prv == 0) continue;
        REP(v, m) {
            if(v <= p) dp[i+1][v][q][r] += prv;
            else if(v <= q) dp[i+1][p][v][r] += prv;
            else if(v <= r) dp[i+1][p][q][v] += prv;
        }
    }
    debug(dp);

    mint ans = 0;
    REP(p, m) REP(q, p+1, m) REP(r, q+1, m) ans += dp[n][p][q][r];

    print(ans);

    return 0;
}
