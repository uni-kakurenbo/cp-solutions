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
    int n, k; cin >> n >> k;
    int m = k * k / 2;
    debug(m);
    lib::grid<int> G(n, n); input >> G;

    auto can = [&](int v) -> bool {
        lib::grid<int> H(n, n);
        REP(i, n) REP(j, n) H(i, j) = G(i, j) > v;
        lib::accumulation_2d cum(ALL(H));
        debug(v, H);

        FOR(i, n - k) FOR(j, n - k) {
            int cnt = cum({ i, i + k }, { j, j + k });
            debug(i, j, cnt);
            if(cnt <= m) return true;
        }
        return false;
    };

    lib::boundary_seeker<int> seeker(can);
    print(seeker.bound<true>(INF32));
}
