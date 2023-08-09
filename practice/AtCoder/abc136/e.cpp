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
    int n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;
    i64 sum = a.sum();
    auto divs = lib::divisors(sum);

    maximum<i64> ans = 1;

    ITR(d, divs) {
        debug(d);
        auto b = a; b %= d, b.sort();
        lib::accumulation cum(ALL(b));
        REP(i, n) {
            if(cum(0, i) == (n - i) * d - cum(i, n)) {
                debug(cum(0, i), i);
                if(cum(0, i) <= k) ans <<= d;
            }
        }
    }

    print(ans);
}
