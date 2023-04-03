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

#include "iterable/counter.hpp"

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n); input >> a;
    lib::counter<int> cnt(ALL(a));

    bool ans = false;

    REP(i, n) {
        if(cnt[a[i] + x] > 0) ans = true;
    }

    print(ans ? "Yes" : "No");
}
