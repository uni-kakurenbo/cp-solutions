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

void solve() {
    int n; cin >> n;
    valarray<i64> a(n); input >> a;
    std::string s; cin >> s;

    valarray<pair<int,char>> p(n);
    REP(i, n) p[i] = { a[i], s[i] };

    lib::inverse inv_s(ALL(s));
    lib::inverse cnt_p(ALL(p));

    i64 ans = 0;

    ITR(e, inv_s['E']) {
        REP(i, 3) REP(j, 3) {
            const auto& p0 = cnt_p[{ i, 'M' }];
            const auto& p1 = cnt_p[{ j, 'X' }];
            i64 v = std::lower_bound(ALL(p0), e) - p0.begin();
            i64 u = p1.end() - std::lower_bound(ALL(p1), e);
            debug(v, u, i, j, a[e], lib::mex(i, j, a[e]));
            ans += v * u * lib::mex(i, j, a[e]);
        }
    }

    print(ans);
}
