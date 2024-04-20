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

#include "iterable/counter.hpp"

void solve() {
    i64 n, p; cin >> n >> p;
    valarray<i64> a(n); input >> a;
    i64 ans = 0;
    for(int k=1; lib::pow(p, k) <= INF32; ++k) {
        valarray<i64> b = a; b %= lib::pow(p, k);
        lib::counter<int> cnt(ALL(b));
        ITR(v, cnt) ans += lib::nCr<i64>(v.second, 2);
    }
    print(ans);
}
