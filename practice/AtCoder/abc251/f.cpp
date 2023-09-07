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
    int n, m; cin >> n >> m;
    lib::graph<int> G(n); G.read_bidirectionally(m);

    {
        valarray<bool> visited(n);
        auto dfs = [&](auto&& dfs, int v, int p) -> void {
            if(p >= 0) print(v+1, p+1);
            visited[v] = true;
            ITR(e, G[v]) {
                if(visited[e]) continue;
                dfs(dfs, e, v);
            }
        };
        dfs(dfs, 0, -1);
    }

    {
        valarray<i64> dists(n), prev(n, -2);
        G.distances_without_cost(0, &dists, &prev, -1, -2);
        debug(dists, prev);
        REP(i, n) {
            if(prev[i] >= 0) print(i+1, prev[i]+1);
        }
    }
}
