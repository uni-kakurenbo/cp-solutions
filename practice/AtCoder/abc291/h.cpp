/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"
#include "graph/centroid_decomposition.hpp"

signed main() {
    int n; cin >> n;
    lib::graph G(n); G.read_bidirectionally(n-1);

    lib::centroid_decomposition cd(G);

    std::vector<int> ans(n, -1);

    queue<std::tuple<int,int,int>> que; que.emplace(-1, 0, n);
    while(not que.empty()) {
        auto [ p, u, sz ] = que.front(); que.pop();
        debug(p, u, sz);
        auto res = cd.decompose(u, sz);
        ans[res.first] = p;
        ITR(v, s, res.second) {
            que.emplace(res.first, v, s);
        }
    }

    std::transform(
        ALL(ans),
        std::ostream_iterator<int>(cout, " "),
        [&](int v) { return v < 0 ? -1 : v + 1; }
    );

    return 0;
}
