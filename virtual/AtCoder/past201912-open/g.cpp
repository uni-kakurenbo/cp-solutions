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
    int n; cin >> n;

    lib::grid<i64> a(n, n);
    REP(i, n) REP(j, i+1, n) cin >> a[i][j], a[j][i] = a[i][j];
    debug(a);

    i64 ans = -INF64;

    REP(bits, lib::pow(3, n)) {
        i64 h = 0;
        array<vector<int>,3> G;
        REP(i, n) G[bits/lib::pow(3,i) % 3].push_back(i);
        REP(i, 3) REP(p, G[i].size()) REP(q, p+1UL, G[i].size()) {
            h += a[G[i][p]][G[i][q]];
        }
        chmax(ans, h);
    }

    print(ans);

    return 0;
}
