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


#include "multi_container.hpp"
#include "numeric/modint.hpp"

signed main() {
    int n; cin >> n;

    lib::multi_container<lib::modint998244353,2> dp(n+1, 11);

    FOR(i, 1, 9) dp[1][i] = 1;

    REP(i, 1, n) {
        FOR(j, 1, 9) {
            dp[i+1][j-1] += dp[i][j];
            dp[i+1][j] += dp[i][j];
            dp[i+1][j+1] += dp[i][j];
        }
    }

    debug(dp);

    print(accumulate(dp[n].begin()+1, dp[n].end()-1, lib::modint998244353{0}));

    return 0;
}
