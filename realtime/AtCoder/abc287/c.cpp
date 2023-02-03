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

signed main() {
    int n, m; cin >> n >> m;

    lib::dsu uf(n);

    vector<int> cnt(n);

    REP(m) {
        int u, v; cin >> u >> v; --u, --v;
        uf.merge(u, v);
        ++cnt[u], ++cnt[v];
    }

    print((count(ALL(cnt), 1) == 2 and count(ALL(cnt), 2) == n-2 and m == n-1 and uf.group_count() == 1 ? "Yes" : "No"));

    return 0;
}
