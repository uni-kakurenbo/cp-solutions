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

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(n); input >> a;
    a.sort().reverse();

    valarray<i64> b(n);

    int i = 0;
    REP(m) b[i] += a[i], ++i;
    REP(j, n - i) b[m - j - 1] += a[i], ++i;

    i64 ans = 0;
    ITR(v, b) ans += v * v;

    print(ans);
}
