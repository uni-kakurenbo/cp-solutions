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
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

#include <atcoder/modint>
using namespace atcoder;

using mint = modint998244353;

signed main() {
    ll n, _p; cin >> n >> _p;
    auto p = mint{_p} / 100, q = 1 - p;

    vector<mint> dp(n+2);

    dp[n+1] = 1;
    FORD(i, n+1, 1LL) {
        if(i >= 2) dp[i-1] += q * (dp[i] + 1);
        if(i >= 2) dp[i-2] += p * (dp[i] + 2);
    }
    debug(dp);

    print(dp[0] + dp[1]);

    return 0;
}
