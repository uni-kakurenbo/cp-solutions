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
#include "data_structure/range_action/range_set_range_sum.hpp"

signed main() {
    int n; cin >> n;
    vector<ll> a(n); input >> a;

    lib::lazy_segment_tree<lib::actions::range_set_range_sum<ll>> data(ALL(a));

    REP(i, n) {
        int j = i-1;
        while(j >= 0 and data[j] != data[i]) --j;
        if(j < 0) continue;
        data.set(j, i, a[i]);
    }

    ITR(v, data) cout << v << "\n";

    return 0;
}
