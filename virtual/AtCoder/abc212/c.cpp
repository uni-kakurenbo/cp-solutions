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

#include "data_structure/wavelet_matrix.hpp"

signed main() {
    int n, m; cin >> n >> m;
    vector<i64> a(n), b(m); input >> a >> b;
    lib::wavelet_matrix<i64>::compressed wm(ALL(b));

    i64 ans = INF64;

    REP(i, n) {
        chmin(ans, std::abs(wm.next(a[i]).value_or(INF64) - a[i]));
        chmin(ans, std::abs(wm.prev(a[i]).value_or(INF64) - a[i]));
    }

    print(ans);

    return 0;
}
