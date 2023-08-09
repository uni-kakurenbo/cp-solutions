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

#include "graph/shortest_path.hpp"

void solve() {
    int n, m; cin >> n >> m;
    lib::graph<int> G(n); G.read_bidirectionally(m);

    int k; cin >> k;
    valarray<int> c(k); input >> c; c -= 1;
    lib::inverse inv(ALL(c));

    lib::grid<int> dists(k, k);
    REP(i, k) {
        auto costs = G.distances_without_cost(c[i]);
        REP(j, k) {
            dists[i][j] = costs[c[j]];
        }
    }
    debug(dists);

    lib::valgrid<int> dp(1 << k, k, INF32);
    REP(i, k) dp[1 << i][i] = 0;
    REP(x, 1 << k) {
        REP(i, k) REP(j, k) {
            chmin(dp[x | (1 << i)][i], dp[x][j] + dists[j][i]);
        }
    }

    int ans = dp[lib::shiftl(1UL, k) - 1].min();
    debug(ans);
    print(ans >= INF32 ? -1 : ans + 1);
}
