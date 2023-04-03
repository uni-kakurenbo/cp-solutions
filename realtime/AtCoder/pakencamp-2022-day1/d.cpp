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

signed main() {

    int n, k; cin >> n >> k;

    i64 p = n - k;
    i64 v = (k + p) / (p + 1);
    debug(p, v);

    REP(i, k) print << min(1L * n, i + i/v + 1) << " ";
    print();

    return 0;
}
