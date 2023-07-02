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
    int n; cin >> n;
    valarray<tuple<i64,i64,int>> p(n);
    REP(i, n) {
        int a, b;
        cin >> a >> b;
        p[i] = { a, b, i };
    }

    std::stable_sort(ALL(p), [&](auto& p, auto& q) {
        auto [ a0, b0, _i0 ] = p;
        auto [ a1, b1, _i1 ] = q;
        return a0 * (a1 + b1) > a1 * (a0 + b0);
    });

    REP(i, n) print(std::get<2>(p[i]) + 1);
}
