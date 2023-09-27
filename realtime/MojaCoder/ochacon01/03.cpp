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

#include "numeric/boundary_seeker.hpp"

void solve() {
    int n, k; cin >> n >> k;
    valarray<i64> a(n), b(n); input >> b >> a;

    auto ok = [&](ld r) {
        valarray<i64> is(n); std::iota(ALL(is), 0);
        is.sort([&](int i, int j) { return a[i] - r * b[i] > a[j] - r * b[j]; });

        i64 x = 0, y = 0;
        REP(i, k) x += a[is[i]], y += b[is[i]];

        return x - r * y >= 0;
    };

    lib::boundary_seeker<ld> seeker(ok);
    print(seeker.bound<false,1000>(0, INF64));
}
