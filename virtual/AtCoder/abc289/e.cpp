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

#include "data_structure/disjoint_set_union.hpp"
#include "graph/shortest_path.hpp"

void solve() {
    int n, m; cin >> n >> m;
    vector<int> c(n); input >> c;
    lib::graph G(n); G.read_bidirectionally(m);

    lib::graph H(n*n);
    REP(i, n) REP(j, n) {
        ITR(p, G[i]) ITR(q, G[j]) {
            if(c[p.to] == c[q.to]) continue;
            debug(i, j, p.to, q.to);
            H.add_edge(i*n + j, p.to*n + q.to);
        }
    }

    auto dists = H.distances_without_cost(n-1);
    print(dists[(n-1)*n]);
}

signed main() {
    int $; cin >> $;
    while($--) solve();
    return 0;
}
