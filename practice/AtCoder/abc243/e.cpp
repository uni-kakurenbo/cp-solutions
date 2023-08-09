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

#include "graph/shortest_path.hpp"

void solve() {
    int n, m; cin >> n >> m;
    lib::grid<i64> G(n, n, INF64);
    valarray<tuple<int,int,int>> edges(m);

    REP(i, m) {
        int a, b, c; cin >> a >> b >> c; --a, --b;
        edges[i] = { a, b, c };
        G(a, b) = G(b, a) = c;
    }

    REP(k, n) REP(i, n) REP(j, n) {
        chmin(G[i][j], G[i][k] + G[k][j]);
    }

    int ans = 0;

    ITR(a, b, c, edges) {
        bool can = false;
        REP(i, n) {
            if(G(a, i) + G(i, b) <= c) {
                can |= true;
                if(can) break;
            }
        }
        ans += can;
    }

    print(ans);
}
