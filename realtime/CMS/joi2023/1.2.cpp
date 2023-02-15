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

#include "data_structure/lazy_segment_tree.hpp"
#include "data_structure/wavelet_matrix.hpp"
#include "data_structure/range_action/range_set_range_sum.hpp"

signed main() {
    int n; cin >> n;
    vector<ll> a(n); input >> a;

    lib::lazy_segment_tree<lib::actions::range_set_range_sum<ll>> data(ALL(a));
    lib::wavelet_matrix<ll> b(ALL(a));

    REP(i, n) {
        ll v = a[i];

        ll r = b.select(v, b.range(0, i).count(v)+1);

        if(r == n) continue;
        data.set(i, r, v);

        i = r-1;
    }

    ITR(v, data) cout << v << "\n";

    return 0;
}
