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

#include "numeric/boundary_seeker.hpp"
#include "graph/topological_sort.hpp"

void solve() {
    int n, m; cin >> n >> m;
    valarray<tuple<int,int,i64,i64>> graph(m);
    input >> graph;

    auto ok = [&](ld r) -> bool {
        lib::graph<ld> G(n);
        REP(i, m) {
            auto [ u, v, b, c ] = graph[i];
            G.add_edge(u - 1, v - 1, b - r * c);
        }

        valarray<ld> dp(n, -INF64);
        dp[0] = 0;
        REP(v, n) ITR(nv, G[v]) chmax(dp[nv], dp[v] + nv.cost);

        return dp[n-1] >= 0;
    };

    lib::boundary_seeker<ld> seeker(ok);
    print(seeker.bound<false,80>(0, INF32));
}
