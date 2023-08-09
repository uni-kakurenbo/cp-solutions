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

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "graph/topological_sort.hpp"

void solve() {
    int n, m; cin >> n >> m;
    lib::graph<int> G(n); G.read(m);

    lib::vector<int> a, b;
    G.sort_topologically_with_priority<std::greater<int>>(&a);
    G.sort_topologically_with_priority<std::less<int>>(&b);
    if(a[0] == b[0]) print(a[0] + 1);
    debug(a, b);
    else print(-1);
}
