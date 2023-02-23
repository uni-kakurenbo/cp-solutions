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
    ll h, n; cin >> h >> n;
    vector<ll> a(n); input >> a;

    vector<ll> dp(h+1, INT_MAX);
    dp[h] = 0;

    FORD(i, h/2+1, h) REP(j, n) {
        chmin(dp[max(i-a[j], 0LL)], dp[i] + 1);
    }
    // debug(dp);

    print(dp[0] == INT_MAX ? -1 : dp[0]);

    return 0;
}
