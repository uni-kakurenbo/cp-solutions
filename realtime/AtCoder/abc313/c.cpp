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
    a.sort();

    i64 sum = lib::sum(a);

    i64 d = sum / n;
    debug(sum, sum - d * n);

    vector<i64> b;
    REP(n - (sum - d * n)) b.push_back(d);
    REP((sum - d * n)) b.push_back(d+1);

    i64 ans = 0;
    REP(i, n) ans += abs(a[i] - b[i]);

    print(ans / 2);
}
