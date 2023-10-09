/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint998244353;

void solve() {
    i64 n; cin >> n;

    auto facts = lib::count_factors(n);
    if(facts.rend()->first > 5) {
        print(0);
        return;
    }

    lib::map<i64,mint> dp;
    dp[n] = 1;

    auto race = [&](auto&& race, i64 x) {
        if(x > n) return MINT<0>;
        if(dp.contains(x)) return dp[x];
        return dp[x] = (race(race, 2 * x) + race(race, 3 * x) + race(race, 4 * x) + race(race, 5 * x) + race(race, 6 * x)) * INV<5>;
    };

    print(race(race, 1));
}
