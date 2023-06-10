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

#include "numeric/prime.hpp"
#include "numeric/divisor_multiple_transform.hpp"

using mint = lib::modint998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    auto divs = lib::divisors(n);
    std::vector<pair<int,mint>> res;

    ITR(dv, divs) {
        if(dv == n) continue;
        valarray<int> msk(dv, 1);
        REP(i, n) msk[i % dv] &= s[i] == '#';
        int cnt = msk.sum();
        res.emplace_back(dv, mint{2}.pow(cnt));
    }

    res.emplace_back(n, 0);
    debug(res);
    lib::divisor_transform::mebius(ALL(res));
    debug(res);
    print(-res.back().second);
}
