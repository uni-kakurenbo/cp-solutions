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

void solve() {
    int n; mint m; input >> n >> m;

    auto f = [&](auto&& f, int n) -> mint {
        if(n == 1) return 0;
        if(n == 2) return m * (m - 1);
        return m * (m - 1).pow(n - 2) * (m - 2) + f(f, n - 2);
    };

    print(f(f, n));
}
