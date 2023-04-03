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

#include "numeric/boundary_seeker.hpp"

signed main() {
    int n, k; cin >> n >> k;
    lib::grid<i64> a(n, n); input >> a;

    auto can = [&](int v) -> bool {
        lib::grid<i64> b(n, n);
        REP(i, n) REP(j, n) b[i][j] = (a[i][j] > v);
        debug(v, b);
        lib::accumulation_2d<int> c(ALL(b));
        FOR(i, n-k) FOR(j, n-k) {
            if(c(i, i+k, j, j+k) < k*k/2 + 1) return true;
        }
        return false;
    };

    lib::boundary_seeker<int> seeker(can);
    print(seeker.bound<true>(INF32));

    return 0;
}
