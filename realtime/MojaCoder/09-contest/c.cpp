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
    int n, m; cin >> n >> m;
    i64 p[3]; input >> p[0] >> p[1] >> p[2];

    vector<i64> y(n), z(n);

    REP(i, n) {
        i64 x; cin >> x >> y[i] >> z[i];
        y[i] *= p[x-1];
    }

    lib::multi_container<i64,2> dp(n+1, m+1, -INF64);
    dp[0][0] = 0;

    REP(i, n) FOR(j, m) {
        chmax(dp[i+1][j], dp[i][j]);
        if(j + z[i] <= m) chmax(dp[i+1][j + z[i]], dp[i][j] + y[i]);
    }
    debug(dp);

    print(*max_element(ALL(dp[n])));

    return 0;
}
