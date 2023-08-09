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

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint998244353;
#include "data_structure/fenwick_tree.hpp"
#include "data_structure/range_action/range_sum.hpp"

void solve() {
    int n; cin >> n;
    valarray<int> a(n-1); input >> a;

    lib::fenwick_tree<lib::actions::range_sum<mint>> dp(n); // dp[i] := i にいるとき、振る回数の期待値
    dp[n-1] = 0_mod998244353;

    REPD(i, n-1) {
        dp[i] = dp[i] + dp(i, i+a[i]+1).fold();
        dp[i] = dp[i].val() + a[i] + 1;
        dp[i] = dp[i].val() / a[i];
    }

    print(dp[0]);
}
