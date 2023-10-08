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

#include "leveler.hpp"

void solve() {
    int n, k, p; cin >> n >> k >> p;
    valarray<int> c(n);
    lib::valgrid<int> A(n, k);
    input >> lib::views::zip(c, A);
    debug(c, A);

    lib::leveler<int> leveler(lib::views::repeat(p + 1, k));

    lib::valarray<i64> dp(leveler.size(), INF64);

    dp[0] = 0;
    REP(i, n) REPD(x, leveler.size()) {
        auto a = leveler.revert(x);
        a += A[i];
        ITRR(v, a) chmin(v, p);
        chmin(dp[leveler.convert(a)], dp[x] + c[i]);
    }
    debug(dp);

    print(lib::to_optional_if_or_over(dp[leveler.convert(lib::views::repeat(p, k))], INF64).value_or(-1));
}
