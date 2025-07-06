/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i64 n, m; input >> n >> m;

    i64 mx = uni::comb(n, 2);
    i64 es = uni::mod(2L, mx);
    debug(mx, es);

    uni::grid<i32> edge_to_id(n, n, -1);
    uni::vector<spair<i32>> id_to_edge(mx);

    i32 cnt = 0;
    REP(i, n) REP(j, i + 1, n) {
        edge_to_id(i, j) = cnt;
        edge_to_id(j, i) = cnt;
        id_to_edge[cnt++] = { i, j };
    }
    debug(edge_to_id, id_to_edge);

    u32 base = 0;
    REP(m) {
        i32 u, v; input >> u >> v; --u, --v;
        base |= (1UL << edge_to_id(u, v));
    }

    std::vector<i32> ds(n);
    std::vector<u32> sols;

    auto dfs = [&](auto&& self, i32 id, u32 edge, i32 cnt2) {
        if(id >= mx) {
            // debug(cnt2);
            if(cnt2 == n) sols.push_back(edge);
            return;
        }

        auto [ u, v ] = id_to_edge[id];

        self(self, id + 1, edge, cnt2);

        cnt2 -= (ds[u]++ == 2);
        cnt2 -= (ds[v]++ == 2);
        cnt2 += ds[u] == 2;
        cnt2 += ds[v] == 2;

        self(self, id + 1, edge | (1UL << id), cnt2);

        --ds[u], --ds[v];
    };

    dfs(dfs, 0, 0, 0);
    debug(sols);

    i32 ans = INF32;

    ITR(sol, sols) {
        auto cost = std::popcount(base ^ sol);
        chmin(ans, cost);
    }

    print(ans);
}
