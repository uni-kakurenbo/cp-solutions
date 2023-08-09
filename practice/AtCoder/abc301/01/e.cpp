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

    lib::grid<char,string> G(h, w); input >> G;
    using edge = lib::virtual_graph<int,int>::edge;
    auto next = [&](const int& v) -> vector<edge> {
        vector<edge> res;
        ITR(nv, G.vicinities4(v/w, v%w)) if(G(nv) != '#') res.emplace_back(v, G.id(nv));
        return res;
    };

    lib::virtual_graph<int,int> H(next, h * w);

    int s, g;
    vector<int> os;

    REP(i, h) REP(j, w) {
        if(G(i, j) == 'o') os.emplace_back(G.id(i, j));
        if(G(i, j) == 'S') s = G.id(i, j);
        if(G(i, j) == 'G') g = G.id(i, j);
    }
    os.insert(os.begin(), s), os.push_back(g);

    int m = os.size();

    lib::valgrid<int> dists(m);
    REP(i, m) {
        auto cost = H.distances_without_cost(os[i]);
        REP(j, m) dists[i][j] = cost[os[j]];
    }

    lib::valgrid<int> dp(1 << m, m, INF32);
    dp[1][0] = 0;
    REP(x, 1 << m) {
        REP(i, m) REP(j, m) {
            chmin(dp[x | (1 << i)][i], dp[x][j] + dists[j][i]);
        }
    }
    debug(dp);

    int ans = -1;

    REP(x, 1 << (m - 2)) {
        int s = (1 << (m - 1)) | (x << 1) | 1;
        debug(lib::base_n_string(s), dp[s][-1]);
        if(dp[s][m-1] <= t) {
            chmax(ans, __builtin_popcount(s) - 2);
        }
    }

    print(ans);
}
