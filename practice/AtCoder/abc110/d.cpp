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
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint1000000007;

void solve() {
    i64 n, m; input >> n >> m;
    auto facts = lib::count_factors(m);
    debug(facts);
    mint ans = 1;
    ITR(p, c, facts) ans *= lib::nCr<i64,mint>(n+c-1, c);
    print(ans);
}
