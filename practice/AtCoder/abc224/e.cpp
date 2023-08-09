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
    int h, w, n; cin >> h >> w >> n;
    valarray<i64> r(n), c(n), a(n); input >> lib::views::zip(r, c, a); r -= 1, c -= 1;

    map<i64,vector<int>> mp;
    REP(i, n) mp[a[i]].push_back(i);

    valarray<i64> dp(n), rmx(h), cmx(w);

    for(auto itr = mp.rbegin(); itr != mp.rend(); ++itr) {
        ITR(i, itr->second) dp[i] = lib::max(rmx[r[i]], cmx[c[i]]);
        ITR(i, itr->second) chmax(rmx[r[i]], dp[i] + 1), chmax(cmx[c[i]], dp[i] + 1);
    }

    print(dp);
}
