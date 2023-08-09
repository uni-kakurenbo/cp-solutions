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
    i32 n, m; std::cin >> n >> m;

    int i = 0, j = m + 1;
    FORD(d, 1, m) {
        print(lib::mod(i, n) + 1, lib::mod(i+d, n) + 1);
        i++;
        std::swap(i, j);
    }
}
