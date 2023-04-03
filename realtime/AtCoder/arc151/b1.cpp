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
#include "numeric/modint.hpp"

using mint = lib::modint998244353;

signed main() {
    int n, m; cin >> n >> m;
    vector<int> p(n); input >> p; ITRR(v, p) -- v;

    mint ans = 0;

    lib::dsu ds(n);
    REP(i, n) {
        if(ds.same(i, p[i])) continue;
        ds.merge(i, p[i]);
        ans += mint{m} * (m - ds.size(i) - 1) / 2 * mint{m}.pow(n - 1);
    }

    print(ans);

    return 0;
}
