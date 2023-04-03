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

#include "iterable/count_inversion.hpp"

void solve() {
    i64 n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;
    lib::accumulation cum(ALL(a));
    debug(cum);

    valarray<i64> s(n+1);
    FOR(i, n) s[i] = cum[i] - i*k;
    s *= -1;
    debug(s);

    print(lib::inversion<false>::count_with_compressing(ALL(s)));
}
