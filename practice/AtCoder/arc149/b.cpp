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

#include "iterable/longest_increasing_subsequence.hpp"

void solve() {
    int n; cin >> n;
    valarray<i64> a(n), b(n); input >> a >> b;

    valarray<spair<i64>> ab(n);
    REP(i, n) ab[i] = { a[i], b[i] };
    std::sort(ALL(ab));

    REP(i, n) std::tie(a[i], b[i]) = ab[i];

    print(lib::lis<false>(ALL(a)).size() + lib::lis<false>(ALL(b)).size());
}
