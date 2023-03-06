/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    int n, s; std::cin >> n >> s;
    std::vector<int> a(n); input >> a;
    int t = std::accumulate(ALL(a), 0);

    std::vector<ll> dp(std::max(s+1, t+1), INT_MAX);

    dp[t] = 0;
    REP(i, n) FOR(j, s, t) {
        if(j + a[i] <= t) chmin(dp[j], dp[j + a[i]] + 1);
    }
    debug(dp);

    print(dp[s] == INT_MAX ? -1 : dp[s]);

    return 0;
}
