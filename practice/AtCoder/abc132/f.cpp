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


#include "numeric/quotient_enumerator.hpp"

// #include <boost/range/adaptor/reversed.hpp>

void solve() {
    int n, k; cin >> n >> k;

    vector<tuple<int,int,int>> qs(ALL(lib::quotient_enumerator(n)));
    int m = qs.size();

    using mint = modint1000000007;

    valarray<mint> dp(m);
    dp[0] = 1;

    REP(i, k) {
        reverse(ALL(dp));

        valarray<mint> dp2(m);
        mint add = 0;

        REPD(j, m) {
            auto [ q, l, r ] = qs[j];
            add += dp[j];
            dp2[j] = add * (r - l + 1);
        }

        dp = std::move(dp2);
    }

    print(dp.sum());
}
