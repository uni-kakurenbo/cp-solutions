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

void solve() {
    i64 a, b; cin >> a >> b;

    i64 ans = -1;

    auto solve = [&](const auto& solve, i64 x, i64 y) -> void {
        if(x > y) std::swap(x, y);
        if(x == 0) return;
        debug(x, y);
        ans += y/x;
        solve(solve, y%x, x);
    };
    solve(solve, a, b);

    print(ans);
}
