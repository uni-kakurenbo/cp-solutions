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
#include "graph/connected_components.hpp"

signed main() {
    int n, m; cin >> n >> m;

    lib::graph G(n);
    G.read_bidirectionally(m);

    print(G.count_components());

    return 0;
}
