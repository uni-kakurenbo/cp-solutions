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
    int n, w; cin >> n >> w;
    valarray<spair<i64>> ab(n); input >> ab;
    ab.sort().reverse();

    i64 ans = 0;
    ITR(a, b, ab) {
        i64 take = lib::min(b, w);
        ans += a * take;
        w -= take;
    }

    print(ans);
}
