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

void solve() {
    string s; cin >> s;
    int n = s.size();
    int k; cin >> k;

    valarray<int> a(n);
    REP(i, n) a[i] = s[i] == '.';

    int ans = 0;

    int sum = 0;
    int r = 0;
    REP(l, n) {
        while(r < n and sum + a[r] <= k) sum += a[r++];
        chmax(ans, r - l);
        sum -= a[l];
    }

    print(ans);
}
