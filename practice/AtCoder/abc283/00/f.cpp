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

#include "data_structure/segment_tree.hpp"
#include "data_structure/monoid/maximum.hpp"

void slv(valarray<int>& p, valarray<int>& d) {
    int n = p.size();

    lib::segment_tree<lib::monoids::maximum<i64>> data(n);
    REP(i, n) {
        chmin(d[i], (p[i] + i) - data(0, p[i]).prod());
        data[p[i]-1] = p[i] + i;
    }
}

void solve() {
    int n; cin >> n;
    valarray<int> p(n); input >> p;

    valarray<int> d(n, INF32);

    slv(p, d);

    ITRR(v, p) v = n + 1 - v;
    slv(p, d);

    reverse(ALL(p)), reverse(ALL(d));
    slv(p, d);

    ITRR(v, p) v = n + 1 - v;
    slv(p, d);

    reverse(ALL(d));
    print(d);
}

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}
