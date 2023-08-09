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
    vector<i64> a, b, c;
    REP(i, n) {
        int t, x; cin >> t >> x;
        if(t == 0) a.push_back(x);
        if(t == 1) b.push_back(x);
        if(t == 2) c.push_back(x);
    }
    a.sort().reverse();
    b.sort().reverse();
    c.sort().reverse();

    i64 ans = 0;

    REP(m) {
        ans += a.back();
    }
}
