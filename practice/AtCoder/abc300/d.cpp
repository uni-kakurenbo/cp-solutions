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
    i64 n; cin >> n;

    const i64 r = std::ceil(std::pow(n, 1.0 / 5));
    const i64 m = lib::sqrt_ceil(n);

    lib::prime_enumerator<i64> p(m);

    i64 ans = 0;

    for(auto a=p.begin(), end=p.end(); a!=end; ++a) {
        if(*a > r) break;
        for(auto c=a; c!=end; ++c) {
            if(a == c) continue;
            const i64 aacc = *a * *a * *c * *c;
            if(aacc * *a > n) break;
            if(n / aacc < *c - 1) {
                if(*a + 1 <= n / aacc) ans += p.count(n / aacc) - a.index() - 1;
            }
            else if(*a + 1 < *c - 1) ans += a - c - 1;
        }
    }

    print(ans);
}
