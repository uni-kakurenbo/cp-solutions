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
    int n, m; input >> n >> m;

    std::vector<int> deg(n);
    lib::dsu ds(n);

    REP(i, m) {
        int a, c; char b, d; input >> a >> b >> c >> d; --a, --c;
        deg[a]++, deg[c]++;
        ds.merge(a, c);
    }

    const auto groups = ds.groups();
    debug(groups, deg);

    int p = 0, q = 0;
    ITR(group, groups) {
        bool f = true;
        ITR(l, group) {
            if(deg[l] == 2) continue;
            f = false;
        }
        (f ? p : q) += 1;
    }

    print(p, q);

    return 0;
}
