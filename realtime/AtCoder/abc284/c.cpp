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

#include <atcoder/dsu>

signed main() {
    int n, m; cin >> n >> m;
    atcoder::dsu uf(n);
    REP(m) {
        int u, v; cin >> u >> v; --u, --v;
        uf.merge(u, v);
    }

    print(uf.groups().size());

    return 0;
}
