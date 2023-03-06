/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"
#include "graph/dijkstra.hpp"

signed main() {
    int n, m; std::cin >> n >> m;
    lib::graph G(n); G.read(m);

    std::vector dists(n, std::vector<int>(n));
    REP(i, n) G.dijkstra(i, &dists[i]);
    // debug(dists);

    int ans = 0;
    REP(i, n) REP(j, n) {
        if(dists[i][j] == INT_MAX) continue;
        ans += dists[i][j] >= 2;
    }

    print(ans);

    return 0;
}
