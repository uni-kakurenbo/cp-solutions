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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "data_structure/range_add.hpp"

signed main() {
    int n; cin >> n;

    Lib::RangeAdd<int> v(200002);

    LOOP(n) {
        int l, r; cin >> l >> r;
        v.add(l, r, 1);
    }

    FOR(i, 1, 200001) {
        if(v.get(i-1) == 0 and v.get(i) > 0) {
            print << i << " ";
        }
        if(v.get(i-1) > 0 and v.get(i) == 0) {
            print(i);
        }
    }

    return 0;
}
