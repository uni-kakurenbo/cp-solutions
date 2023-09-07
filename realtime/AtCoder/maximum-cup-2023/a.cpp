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
    valarray<i64> a(n); input >> a;

    lib::unordered_map<i64,int> cnt;
    lib::unordered_map<i64,lib::vector<i64>> divs;
    divs.set_default([](i64 v) { return lib::divisors(v); });

    i64 ans = 0;
    REPD(i, n) {
        ITR(div, divs[a[i]]) ans += cnt[div];
        cnt[a[i]]++;
    }

    print(ans);
}
