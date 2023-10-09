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
    i64 frt = std::ceil(std::pow(n, 1.0 / 5.0));
    i64 sqrt = lib::sqrt_ceil(n);
    debug(frt);

    i64 cnt = 0;

    lib::prime_enumerator<i64> primes0(frt);
    lib::prime_enumerator<i64> primes1(sqrt);
    debug(primes0.size(), primes1.size());

    ITR(a, primes0) ITR(c, primes1) {
        if(a * a * c * c > n) break;
        if(a >= c) continue;
        i64 l = a + 1;
        i64 r = lib::min(c - 1, n / (a * a * c * c));
        if(r < l) continue;
        cnt += primes1.count(l, r);
    }

    print(cnt);
}
