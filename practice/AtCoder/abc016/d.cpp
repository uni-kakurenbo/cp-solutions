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

using point = lib::point<i64>;

void solve() {
    lib::segment<point> l; cin >> l;
    int n; cin >> n;
    valarray<point> ps(n); input >> ps;

    int cnt = 0;

    REP(i, n) {
        cnt += lib::is_intersecting(l, { ps[i], ps[lib::mod(i + 1, n)] });
    }

    print(cnt / 2 + 1);
}
