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
    int n, k; cin >> n >> k;

    std::vector<int> cnt(k);
    FOR(i, 1, n) cnt[i%k]++;

    i64 ans = cnt[0] * cnt[0] * cnt[0];
    if(k%2 == 0) ans += cnt[k/2] * cnt[k/2] * cnt[k/2];

    print(ans);
}
