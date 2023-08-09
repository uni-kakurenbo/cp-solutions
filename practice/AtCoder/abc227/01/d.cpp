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

#include "numeric/boundary_seeker.hpp"

void solve() {
    i64 n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;

    auto can = [&](i64 v) -> bool {
        i64 cnt = 0;
        REP(i, n) cnt += lib::min(a[i], v);
        return cnt >= 1LL * v * k;
    };

    lib::boundary_seeker<i64> seeker(can);
    print(seeker.bound(0));
}
