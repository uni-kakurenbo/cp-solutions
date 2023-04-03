/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

#include "data_structure/fenwick_tree.hpp"
#include "data_structure/range_action/range_add.hpp"

signed main() {
    int n, k; cin >> n >> k;
    vector<int> l(k), r(k); REP(i, k) cin >> l[i] >> r[i];
    ITRR(v, r) v++;

    using mint = modint998244353;

    lib::fenwick_tree<lib::actions::range_add<mint>> dp(n);

    dp.set(0, 1);

    REP(i, n) {
        REP(j, k) dp.add(std::min(n, i+l[j]), std::min(n, i+r[j]), dp[i]);
        debug(dp);
    }

    print(dp[n-1]);

    return 0;
}
