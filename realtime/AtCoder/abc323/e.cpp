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

using mint = lib::modint998244353;

void solve() {
    int n, x; cin >> n >> x;
    valarray<i64> t(n); input >> t;
    mint p = mint{n}.inv();

    lib::array<lib::valarray<mint>,2> dp0;
    dp0[0].resize(x + 2), dp0[1].resize(x + 2);
    lib::valarray<mint> dp1(x + 1);

    dp1[0] = 1;
    FOR(j, x) REP(i, n) {
        dp0[i == 0][j] += p * dp1[j];
        if(j + t[i] <= x) {
            dp0[i == 0][j + t[i] + 1] -= p * dp1[j];
            dp1[j + t[i]] += p * dp1[j];
        }
        // debug(dp0);
        // debug(dp1);
    }

    FOR(i, x) dp0[1][i+1] += dp0[1][i];
    print(dp0[1][-1]);
}
