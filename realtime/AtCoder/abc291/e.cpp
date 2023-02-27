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
    int n, m; cin >> n >> m;
    lib::graph G(n); G.read(m);

    std::vector<int> a, b;
    G.sort_topologically_with_priority<std::greater<int>>(&a);
    G.sort_topologically_with_priority<std::less<int>>(&b);

    vector<int> ans(n);
    REP(i, n) ans[a[i]] = i+1;

    bool ok = a == b;
    print(ok ? "Yes" : "No");
    if(ok) print(ans);

    return 0;
}
