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
    i64 n, k; cin >> n >> k;
    valarray<spair<i64>> ab(n); input >> ab;
    std::sort(ALL(ab));
    debug(ab);

    i64 now = 0;
    ITR(a, b, ab) now += b;

    if(now <= k) {
        print(1);
        return;
    }

    REP(i, n) {
        now -= ab[i].second;
        if(now <= k) {
            print(ab[i].first + 1);
            return;
        }
    }
}
