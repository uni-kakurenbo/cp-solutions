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

using mint = lib::modint1000000007;

#include "numeric/divisor_multiple_transform.hpp"

void solve() {
    i64 n, k; cin >> n >> k;

    valarray<mint> cnt(k);
    FOR(i, 1, k) cnt[i-1] = mint{ k / i }.pow(n);

    lib::multiple_transform::mobius(ALL(cnt));

    mint ans = 0;
    FOR(i, 1, k) ans += cnt[i-1] * i;

    print(ans);
}
