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


constexpr int need[] = { 2, 5, 5, 4, 5, 6, 3, 7, 6 };
constexpr int rank[] = { 0, 6, 3, 4, 2, 1, 8, 5, 7 };

void solve() {
    int n, m; cin >> n >> m;
    valarray<i64> a(m); input >> a;

    using table = lib::range_extractor<valarray<array<int,10>>>;

    array<int,10> init;
    init.fill(0), init[0] = -1;

    table dp(n + 1, init);
    dp[0][0] = 0;

    REP(i, n) {
        if(dp[i][0] < 0) continue;
        ITR(j, a) {
            auto v = dp[i];
            v[0] += 1, v[9-j+1]++;
            // debug(j, need[j-1]);
            chmax(dp[i + need[j-1]], v);
        }
    }

    vector<i64> ds;
    REP(i, 1, 10) REP(dp[n][i]) ds.push_back(9-i+1);

    ds.sort().reverse();
    print(lib::join(ds));
}
