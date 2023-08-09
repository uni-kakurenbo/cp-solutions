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

using mint = lib::modint1000000007;

void solve() {
    int n, m; cin >> n >> m;
    valarray<mint> x(n), y(m); input >> x >> y;
    lib::adjacent_difference p(ALL(x)), q(ALL(y));
    REP(i, n - 1) p[i] *= (i + mint{1}) * (n - i - 1);
    REP(i, m - 1) q[i] *= (i + mint{1}) * (m - i - 1);

    print(p.sum() * q.sum());
}
