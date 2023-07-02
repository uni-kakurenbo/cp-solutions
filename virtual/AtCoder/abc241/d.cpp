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
    int q; cin >> q;

    multiset<i64> data;

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            i64 x; cin >> x;
            data.insert(x);
        }
        if(t == 2) {
            i64 x, k; cin >> x >> k;
            print(data.prev(x, --k).value_or(-1));
        }
        if(t == 3) {
            i64 x, k; cin >> x >> k;
            print(data.next(x, --k).value_or(-1));
        }
    }
}
