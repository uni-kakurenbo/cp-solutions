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

using mint = lib::modint998244353;

void solve() {
    i64 n; cin >> n;

    mint ans = 1;

    FOR(i, 2L, n) {
        i64 f = n / i;
        if(f < i) break;
        ans += mint(f - 1) * i;
        ans += mint(f - 1) * 3;
        ans += 1;
        debug(i, ans);
    }

    print(ans);
}
