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
    vector<int> a(m); input >> a;
    ITRR(v, a) v--;
    lib::set<int> st(ALL(a));

    lib::dsu ds(n);
    REP(i, n) {
        if(st.contains(i)) ds.merge(i, i+1);
    }

    auto groups = ds.groups();
    debug(groups);
    ITRP(group, groups) {
        sort(RALL(group));
        ITR(v, group) print(v + 1);
    }

    return 0;
}
