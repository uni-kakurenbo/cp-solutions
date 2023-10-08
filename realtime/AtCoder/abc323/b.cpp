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

void solve() {
    int n; cin >> n;
    lib::grid<char,string> G(n, n); input >> G;

    valarray<int> cnt(n);
    REP(i, n) cnt[i] = std::count(ALL(G[i]), 'o');

    valarray<int> p(n); std::iota(ALL(p), 0);
    std::stable_sort(ALL(p), [&](int i, int j) { return cnt[i] > cnt[j]; });

    print(p += 1);
}
