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
    i64 a, b; cin >> a >> b;

    i64 sqrt = lib::sqrt_floor(a);
    debug(sqrt);

    auto factors = lib::count_factors(a);
    debug(factors);

    mint cnt = 1;
    int sub = 1;
    ITR(fact, c, factors) {
        cnt *= mint{b} * c + 1;
        if(((b % 2) * (c % 2) + 1) % 2 == 0) sub = 0;
    }
    debug(cnt);

    mint ans = mint{ b } * (cnt - sub) / 2;
    debug(ans);

    if(b % 2 == 0 or sqrt * sqrt == a) ans += b / 2;

    print(ans);
}
