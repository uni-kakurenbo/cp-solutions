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


signed main() {
    int n; cin >> n;
    vector<i64> a(n), b(n+1); input >> a;
    FOR(i, 1, n) b[i] = b[i-1] + a[(i-1)/2];
    debug(b);

    lib::multi_container<i64,2> dp(n+1, n+1, -INF64); // n 日目．直前の休日が k 日前

    dp[0][0] = 0;

    REP(i, n) REP(j, n) {
        chmax(dp[i+1][j+1], dp[i][j]);
        chmax(dp[i+1][0], dp[i][j] + b[j]);
    }
    debug(dp);

    i64 ans = -INF32;
    REP(i, n) chmax(ans, dp[n-1][i] + b[i]);

    print(ans);

    return 0;
}
