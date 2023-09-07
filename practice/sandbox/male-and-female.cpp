/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
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
    valarray<i64> a(n), b(n); input >> a >> b;

    struct Comparer {
        bool operator()(int i, int j) const { return std::abs(i) < std::abs(j); };
    };
    lib::set<int,Comparer> dp;

    REP(i, n) {
        auto cp = dp;
        cp.insert(0);
        ITR(v, cp) dp.insert(v + a[i] - b[i]);
        debug(dp);
    }

    print(std::abs(dp.min()));
}
