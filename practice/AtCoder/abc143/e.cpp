/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

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
    int n, m, l; cin >> n >> m >> l;
    lib::grid<i64> G(n, n, INF64);
    REP(m) {
        int a, b, c; cin >> a >> b >> c; --a, --b;
        G[a][b] = G[b][a] = c;
    }

    REP(k, n) REP(i, n) REP(j, n) {
        chmin(G[i][j], G[i][k] + G[k][j]);
    }
    debug(G);

    lib::grid<int> H(n, n, INF32);
    REP(i, n) REP(j, n) {
        if(G[i][j] <= l) H[i][j] = 1;
    }

    REP(k, n) REP(i, n) REP(j, n) {
        chmin(H[i][j], H[i][k] + H[k][j]);
    }
    debug(H);

    int q; cin >> q;
    REP(q) {
        int s, t; cin >> s >> t; --s, --t;
        int res = H[s][t];
        print(res >= INF32 ? -1 : res - 1);
    }
}
