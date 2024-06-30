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

#include "numeric/binomial_coefficient.hpp"

#include "template/warnings.hpp"

using mint = uni::modint998244353;

void solve() {
    i32 k; input >> k;
    array<i32, 26> c; input >> c;
    debug(c);

    uni::binomial_coefficient_prime_power_mod<i64, mint> binom(1000);

    vector<mint> dp(k + 1);
    dp[0] = 1;

    REP(t, 26) {
        vector<mint> next(k + 1);

        FOR(i, k) {
            FOR(j, std::min(i, c[t])) {
                next[i] += dp[i - j] * binom.comb(i, j);
            }
        }

        dp = std::move(next);
        // debug(dp);
    }

    print(dp.sum() - 1);
}
