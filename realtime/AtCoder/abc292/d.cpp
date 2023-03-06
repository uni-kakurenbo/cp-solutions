/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
yy/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"
#include "data_structure/disjoint_set_union.hpp"

signed main() {
    int n, m; input >> n >> m;

    std::vector<int> deg(n);
    lib::dsu ds(n);

    REP(i, m) {
        int u, v; std::cin >> u >> v; --u, --v;
        deg[u]++, deg[v]++;
        ds.merge(u, v);
    }

    auto groups = ds.groups();

    print(all_of(ALL(groups), [&](auto& g) { return std::accumulate(ALL(g), 0LL, [&](int acc, int e) { return acc + deg[e]; }) == g.size() * 2; }) ? "Yes" : "No");

    return 0;
}
