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
    i64 n, m; cin >> n >> m;
    i64 p = std::min(n, (i64)std::ceil(std::sqrt(m)));

    i64 ans = INF64;

    FOR(u, 1L, p) {
        auto ok = [&](i64 v) -> bool {
            return v * u >= m;
        };
        lib::boundary_seeker<i64> seeker(ok);
        i64 bound = seeker.bound_or(n, 0, -1);
        if(bound < 0) continue;
        debug(u, bound);
        chmin(ans, u * bound);
    }

    print(ans >= INF64 ? -1 : ans);
}
