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

#include <boost/range/adaptor/reversed.hpp>

void solve() {
    i64 n; cin >> n;

    i64 ans = 0;

    ITR(q, l, r, lib::quotient_enumerator(n)) {
        ans += (r - l + 1) * q;
    }

    print(ans);
}
