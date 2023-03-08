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
    int n, x; cin >> n >> x;
    std::vector<bitset<10001>> dp(n+1);

    dp[0].set(0);
    REP(i, n) {
        int a, b; cin >> a >> b;
        dp[i+1] |= dp[i] << a;
        dp[i+1] |= dp[i] << b;
    }

    print(dp[n].test(x) ? "Yes" : "No");
    return 0;
}
