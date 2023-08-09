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
    vector<int> a(n); input >> a;

    lib::multi_container<ll,3> dp(n+1, m+1, 2, INT_MAX);
    dp[0][0][1] = 0;

    FOR(i, 1, n) FOR(j, m) {
        chmin(dp[i][j][0], dp[i-1][j][0]);
        chmin(dp[i][j][0], dp[i-1][j][1] + 1);
        if(j >= a[i-1]) {
            chmin(dp[i][j][1], dp[i-1][j-a[i-1]][0]);
            chmin(dp[i][j][1], dp[i-1][j-a[i-1]][1]);
        }
    }
    debug(dp);

    FOR(i, 1, m) {
        int res = min(dp[n][i][0], dp[n][i][1]);
        print(res == INT_MAX ? -1 : res);
    }

    return 0;
}
