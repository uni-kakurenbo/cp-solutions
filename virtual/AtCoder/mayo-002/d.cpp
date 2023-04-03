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

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;

    lib::accumulation<int> l(ALL(a), 0, std::gcd<int,int>), r(RALL(a), 0, std::gcd<int,int>);
    debug(l, r);

    int ans = -INF32;

    REP(i, n) {
        int pro = std::gcd(l[i], r[n-i-1]);
        chmax(ans, pro);
    }

    print(ans);

    return 0;
}
