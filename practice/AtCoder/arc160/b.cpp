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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i64 n; cin >> n;
    i64 m = std::sqrt(n);

    using mint = lib::modint998244353;

    mint ans = 0;
    FOR(v, 1L, m) {
        ans += 6 * (v - 1) * (n/v - v);
        ans += 3 * ((v - 1) + (n/v - v));
        ans += 1;
    }

    print(ans);
}
