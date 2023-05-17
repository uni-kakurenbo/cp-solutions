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

#include "numeric/prime.hpp"

void solve() {
    i64 a, b; cin >> a >> b;
    if(a > b) std::swap(a, b);
    if(a == b) {
        print(1);
        return;
    }
    debug(a, b);

    i64 ans = 0;

    while(a >= 1 and b >= 1) {
        i64 g = std::gcd(a, b);
        a /= g, b /= g;
        debug(g, a, b);

        i64 d = b - a;

        if(d == 1) {
            ans += std::min(a, b);
            break;
        }

        auto facts = lib::prime_factors(d);
        debug(facts);

        i64 t = INF32;
        ITR(x, facts) chmin(t, lib::mod(a, x));

        a -= t, b -= t;
        ans += t;

        debug(t, a, b, ans);
    }

    print(ans);
}
