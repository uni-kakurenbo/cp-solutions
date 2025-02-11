/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = uni::modint1000000007;

#include "numeric/binomial_coefficient.hpp"

void solve() {
    i32 n; input >> n;

    uni::binomial_coefficient_prime_power_mod<i32, mint> binom(n);

    FOR(k, 1, n) {
        mint ans = 0;

        FOR(i, 1, n) {
            mint now = binom.lucus(n - (k - 1) * (i - 1), i);
            if(now == 0) break;
            ans += now;
        }

        print(ans);
    }
}
