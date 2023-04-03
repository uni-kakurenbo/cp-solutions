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

    map<spair<i64>,i64> snuke;
    i64 T = 0;
    REP(n) {
        i64 t, x, a; cin >> t >> x >> a;
        snuke[{ t, x }] = a;
        chmax(T, t);
    }

    lib::multi_container<i64,2,lib::valarray> dp(T+1, 6, -INF64); // (i, j) := 時刻 i で j の穴

    dp(0,0) = 0;
    REP(t, T) REP(p, 5) {
        dp(t+1,p) = max({ dp(t,p-1), dp(t,p), dp(t,p+1) }) + snuke[{ t+1, p }];
    }
    debug(dp);

    print(dp[T].max());

    return 0;
}
