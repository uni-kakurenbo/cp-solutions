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

#include "numeric/divisor_multiple_transform.hpp"

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    valarray<int> a(n); REP(i, n) a[i] = s[i] == '#';

    auto divs = lib::divisors(n);
    divs.pop_back();
    vector<pair<int,mint>> res;
    ITR(div, divs) {
        valarray<int> b(div);
        REP(i, n) b[lib::mod(i, div)] |= !a[i];
        debug(div, b);
        res.emplace_back(div, mint{2}.pow(b.count(0)));
    }
    res.emplace_back(n, 0);
    debug(res);

    lib::divisor_transform::mobius(ALL(res));
    debug(res);

    print(-res.back().second);
}
