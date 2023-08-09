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

#include "graph/from_grid.hpp"
#include "graph/shortest_path.hpp"

void solve() {
    int h, w, t; cin >> h >> w >> t;
    lib::grid<char,string> A(h, w); input >> A;
    lib::graph<int> G; G.from_grid<true>(A, '#');
    debug(A, G);

    using point = lib::point<int>;

    point s, g;
    vector<point> ps;

    REP(i, h) REP(j, w) {
        if(A(i,j) == 'S') s = { i, j };
        if(A(i,j) == 'G') g = { i, j };
        if(A(i,j) == 'o') ps.emplace_back(i, j);
    }
    ps.insert(ps.begin(), s);
    ps.push_back(g);
    debug(s, g, ps);

    int n = ps.size();
    grid<i64> cost(n, n);
    REP(i, n) {
        int p = A.id(ps[i].x(), ps[i].y());
        auto dist = G.distances_without_cost(p);
        REP(j, i, n) {
            int q = A.id(ps[j].x(), ps[j].y());
            cost[i][j] = cost[j][i] = dist[q];
        }
    }
    debug(n, cost);

    grid<i64> dp(1 << n, n, INF32);
    dp[1][0] = 0;

    REP(s, 1 << n) REP(i, n) REP(j, n) {
        if(s != 0 and !(s & (1 << j))) continue;
        if((s & (1 << i)) != 0) continue;
        if(i != j) chmin(dp[s | (1 << i)][i], dp[s][j] + cost[j][i]);
    }

    i64 res = -1;

    REP(x, 1 << (n - 2)) {
        int s = (1 << (n - 1)) | (x << 1) | 1;
        debug(lib::base_n_string(s), dp[s][n-1]);
        if(dp[s][n-1] <= t) {
            chmax(res, __builtin_popcount(s) - 2);
        }
    }

    print(res);
}
