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

namespace atcoder {}
using namespace atcoder;

namespace Lib {}
using namespace Lib;

#include "template.hpp"
/* #endregion */

#include "multi_container.hpp"

signed main() {
    int n; cin >> n;

    if(n == 1) { print(1); return 0; }
    if(n == 2) { print(2); return 0; }

    vector<int> divs(n+1);
    FOR(i, 1, n) FOR(j, i, n, i) ++divs[j];
    debug(divs);

    MultiContainer<ll,2> dp(n+1, n+1, INT64_MIN);

    FOR(i, 0, n) dp[i][0] = 0;

    REP(i, n) FOR(j, 0, n) {
        if(j >= i) chmax(dp(i+1,j), dp(i,j-i) + divs[i]);
        chmax(dp(i+1,j), dp(i,j));
    }
    debug(dp);

    ll res = 0;
    FOR(i, 0, n) chmax(res, dp[i][n]);
    print(res);

    return 0;
}
