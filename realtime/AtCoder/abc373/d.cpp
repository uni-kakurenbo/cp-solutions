/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

#include <atcoder/scc>

#include "template/warnings.hpp"
void solve() {
    i64 n, m; input >> n >> m;

    uni::graph<i64> g(n);
    REP(m) {
        i64 u, v, w; input >> u >> v >> w; --u, --v;
        g.add_edge(u, v, w);
        g.add_edge(v, u, -w);
    }

    vector<i64> id(n, INF64);

    auto dfs = [&](auto&& self, i64 v, i64 num) -> void {
        if(id[v] != INF64) return;
        id[v] = num;
        ITR(e, g[v]) {
            self(self, e.to, num + e.cost);
        }
    };

    REP(i, n) {
        dfs(dfs, i, 0);
    }

    auto min = id.min();

    i64 constexpr M = 1'000'000'000'000'000'000;
    if(min < -M) id += std::abs(-M - min);

    auto max = id.min();
    if(max > M) id -= std::abs(M - min);

    print(id);


    // atcoder::scc_graph g(n);

    // vector<i64> ws(m);
    // vector<vector<i32>> nxt(n);

    // REP(i, m) {
    //     i32 u, v, w; input >> u >> v >> w; --u, --v;
    //     nxt[u].push_back(v);
    //     ws[i] = w;
    //     g.add_edge(u, v);
    // }

    // auto scc = g.scc();
    // debug(scc);

    // ITRR(vs, scc) {

    // }
}
