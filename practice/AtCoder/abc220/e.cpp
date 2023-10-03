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
    i64 n, d; cin >> n >> d;

    mint ans = 0;

    REP(i, n) {
        mint cur = 0;
        if(d + i < n) cur += MINT<2>.pow(d + 1);
        if(d == 1 or 2 * (n - i - 1) < d) {}
        else if(d + i < n) cur += MINT<2>.pow(d - 1) * (d - 1);
        else cur += MINT<2>.pow(d - 1) * (2 * (n - i) - d - 1);
        ans += cur * MINT<2>.pow(i);
    }

    print(ans);
}
