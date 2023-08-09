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
    i64 m; cin >> m;
    valarray<i64> a(n); input >> a;

    valarray<i64> v(n);

    REP(i, n) {
        int cnt = 0;
        while(a[i] % m == 0) a[i] /= m, cnt++;
        v[i] = cnt;
    }
    debug(v);

    if(std::count(ALL(v), 1) == 0) {
        print(-1);
        return;
    }

    i64 gcd = 0;
    int cnt = 0;
    REP(i, n) if(v[i] >= 1) gcd = std::gcd(gcd, a[i]), ++cnt;
    if(gcd != 1) {
        print(-1);
        return;
    }

    print(cnt);
}
