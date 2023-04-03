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

ld f(i64 x, i64 y, i64 z) {
    return ld(x + y + z) / (x * y * z);
}

ld INF = std::numeric_limits<ld>::infinity();

signed main() {
    int n; cin >> n;
    vector<i64> v(n); input >> v;

    ld p = INF, q = -INF;
    REP(i, n) REP(j, i+1, n) REP(k, j+1, n) {
        ld x = f(v[i], v[j], v[k]);
        chmin(p, x);
        chmax(q, x);
    }

    print(p, q);

    return 0;
}
