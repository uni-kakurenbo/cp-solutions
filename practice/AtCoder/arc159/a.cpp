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

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    i64 n, k; cin >> n >> k;
    lib::grid<int> A(n, n); input >> A;

    lib::grid<int> dist(n, n, INF32);
    REP(i, n) REP(j, n) {
        int a = A[i][j];
        if(a == 1) dist(i, j) = a;
    }
    debug(A, dist);

    REP(k, n) REP(i, n) REP(j, n) chmin(dist[i][j], dist[i][k] + dist[k][j]);

    int q; cin >> q;
    REP(q) {
        i64 s, t; cin >> s >> t; --s, --t;
        int p = s % n, q = t % n;;
        int res = dist[p][q];
        print(res < INF32 ? res : -1);
    }
}
