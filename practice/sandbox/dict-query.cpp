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

    map<i64,set<i64>> vals;
    map<i64,i64> sum;
    multiset<i64> sums;

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            i64 i, x; cin >> i >> x;
            if(vals[i].insert(x).second) sums.remove(sum[i]), sums.insert(sum[i] += x);
        }
        if(t == 2) {
            i64 i, x; cin >> i >> x;
            if(vals[i].erase(x)) sums.remove(sum[i]), sums.insert(sum[i] -= x);
        }
        if(t == 3) print(*sums.rbegin());
    }
}
