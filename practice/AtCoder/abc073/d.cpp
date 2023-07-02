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
    int n, m, r; cin >> n >> m >> r;
    valarray<i64> p(r); input >> p; p -= 1;

    lib::graph<i64> G(n); G.read_bidirectionally<true>(m);

    auto dists = G.make_distance_matrix();
    debug(dists);

    i64 ans = INF64;

    REP(s, r) {
        grid<i64> dp(1 << r, r, INF64);

        dp[1 << s][s] = 0;
        REP(x, 1 << r) {
            REP(i, r) REP(j, r) {
                chmin(dp[x | (1 << i)][i], dp[x][j] + dists[p[j]][p[i]]);
            }
        }
        debug(dp);

        REP(i, r) chmin(ans, dp[(1 << r) - 1][i]);
    }

    print(ans);
}
