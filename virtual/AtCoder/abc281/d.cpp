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

#include "multi_container.hpp"
#include "utility/applier.hpp"
using namespace Lib;

signed main() {
    int n, k, d; cin >> n >> k >> d;
    vector<ll> a(n); REP(i, n) cin >> a[i];

    MultiVector<Max<ll>,3> dp(n+1, k+2, d+0, Max<ll>{ -1 });

    REP(i, n) {
        dp[i][0][0] = 0;
        REP(j, k+1) REP(p, d) {
            auto cur = dp(i,j,p).val();
            if(cur < 0) continue;
            dp(i+1,j,p) <<= cur;
            dp(i+1,j+1,mod(p+a[i],d)) <<= cur + a[i];
        }
    }
    debug(dp);

    print(dp(n,k,0));

    return 0;
}
