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

#include "data_structure/fenwick_tree.hpp"
#include "data_structure/range_action/range_bitxor.hpp"

signed main() {
    int n, q; cin >> n >> q;
    vector<int> a(n); input >> a;
    lib::fenwick_tree<lib::actions::range_bitxor<int>> data(ALL(a));

    REP(q) {
        int t; cin >> t;
        if(t == 1) {
            int p, x; cin >> p >> x; --p;
            data.apply(p, x);
        }
        if(t == 2) {
            int l, r; cin >> l >> r; --l;
            print(data.prod(l, r));
        }
    }

    return 0;
}
