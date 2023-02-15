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

    int cnt = 0;

    REP(m) {
        int a, b; cin >> a >> b; --a, --b;
        cnt += uf.same(a, b);
        uf.merge(a, b);
    }

    print(cnt);

    return 0;
}
