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

#include <atcoder/modint>
using namespace atcoder;

#include "graph.hpp"
#include "graph/spanning_tree.hpp"
using namespace Lib;

signed main() {
    int n, m; cin >> n >> m; modint::set_mod(m);
    vector<int> a(n); input >> a;

    Graph graph(n);

    REP(i, n) REP(j, n) {
        graph.add_edge_bidirectionally(i, j, (modint{a[i]}.pow(a[j]) + modint{a[j]}.pow(a[i])).val());
    }

    print(graph.maximum_spanning_tree_cost());

    return 0;
}
