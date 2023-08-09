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

using mint = lib::modint998244353;

void solve() {
    int n, l; cin >> n >> l;
    valarray<string> s(n); input >> s;
    valarray<int> v(n); REP(i, n) ITR(x, s[i]) v[i] |= 1 << (x - 'a');

    mint ans = 0;

    REP(i, 1U, 1U << n) {
        unsigned st = (1 << 26) - 1;
        REP(j, n) if(((i >> j) & 1)) st &= v[j];
        mint cnt = mint{lib::popcount(st)}.pow(l);
        if((lib::popcount(i) & 1) == 0) cnt *= -1;
        ans += cnt;
    }

    print(ans);
}
