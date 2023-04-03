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

#include "graph/topological_sort.hpp"

signed main() {
    int n, m; cin >> n >> m;

    graph G(n); G.read(m);

    vector<int> v(n);
    if(not G.sort_topologically_with_priority<std::greater<int>>(&v)) {
        print(-1);
        return 0;
    }
    ITRR(x, v) ++x;

    print(v);

    return 0;
}
