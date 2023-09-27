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

#include "convolution/sum.hpp"
using mint = lib::modint998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    lib::inverse inv(ALL(s));

    valarray<mint> l(n), r(n);
    ITR(v, inv['^']) {
        l[v] = inv['('].lower_bound(v) - inv['('].begin();
        r[v] = inv[')'].end() - inv[')'].upper_bound(v);
    }
    debug(l, r);

    auto conv = lib::convolution(ALL(l), RALL(r));
    debug(conv);

    mint ans = 0;
    REP(i, n - 1) ans += conv[i];

    print(ans);
}
