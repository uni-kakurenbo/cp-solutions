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

#include "graph/topological_sort.hpp"

signed main() {
    int n; cin >> n;

    map<string,int> ids;
    lib::graph<int> G(2*n);

    REP(n) {
        string s, t; cin >> s >> t;
        if(not ids.count(s)) ids[s] = ids.size();
        if(not ids.count(t)) ids[t] = ids.size();
        G.add_edge(ids[s], ids[t]);
        debug(ids);
    }

    print(G.sort_topologically() ? "Yes" : "No");

    return 0;
}
