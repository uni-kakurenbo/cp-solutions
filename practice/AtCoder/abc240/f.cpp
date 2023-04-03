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

void solve() {
    int n, m; cin >> n >> m;
    vector<i64> x(n), y(n);
    REP(i, n) cin >> x[i] >> y[i];
    debug(x, y);

    vector<i64> b(n+1), l(n+1);
    REP(i, n) {
        b[i+1] = b[i] + x[i] * y[i];
        l[i+1] = l[i] + y[i];
    }
    debug(b); debug(l);

    vector<i64> s(n+1);
    REP(i, n) {
        s[i+1] = s[i] + y[i] * (2 * (b[i] + x[i]) + (y[i] - 1) * x[i]) / 2;
    }
    debug(s);

    i64 ans = -INF64;

    REP(i, n) {
        if(b[i]+x[i] >= 0 and b[i+1] <= 0 and x[i] != 0) {
            i64 t = -b[i] / x[i];
            i64 p = s[i] + t * ((b[i] + x[i]) + (b[i] + x[i] * t)) / 2;
            chmax(ans, p);
        }
        chmax(ans, s[i] + b[i] + x[i]);
        chmax(ans, s[i+1]);
    }

    print(ans);
}

signed main() {
    int $; std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}
