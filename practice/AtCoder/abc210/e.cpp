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
    int n, m; cin >> n >> m;
    valarray<spair<i64>> ac(m); input >> ac;
    ac.sort([&](auto& p, auto& q) { return p.second < q.second; });

    i64 rest = n;
    i64 ans = 0;

    REP(i, m) {
        i64 gcd = std::gcd(rest, ac[i].first);
        i64 pr = rest;
        if(chmin(rest, gcd)) ans += ac[i].second * (pr / gcd - 1) * gcd;
        debug(ans, gcd);
    }

    print(rest == 1 ? ans : -1);
}
