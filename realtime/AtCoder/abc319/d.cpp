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
    i64 n, m; cin >> n >> m;
    valarray<i64> l(n); input >> l;

    auto ng = [&](i128 v) -> bool {
        debug(v);
        i128 col = 0;
        i64 row = 0;
        REP(i, n) {
            col += l[i] + 1;
            if(col > v) {
                col = l[i] + 1;
                row++;
            }
        }
        row++;
        debug(row, col);
        return row > m;
    };
    debug(ng(26));

    lib::boundary_seeker<i128> seeker(ng);
    i64 ans = seeker.bound(l.max(), l.sum() + n + 1);

    print(ans);

    return;
}
