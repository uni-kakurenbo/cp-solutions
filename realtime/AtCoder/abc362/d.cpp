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

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n >> m;
    valarray<i64> a(n); input >> a;
    uni::graph<i64> g(2 * n);

    REP(i, n) {
        g.add_edge_bidirectionally(2 * i, 2 * i + 1, a[i]);
    }
    REP(m) {
        i32 u, v, b; input >> u >> v >> b; --u, --v;
        g.add_edge(2 * u + 1, 2 * v, b);
        g.add_edge(2 * v + 1, 2 * u, b);
    }

    auto dist = g.shortest_path_with_cost(0);
    REP(i, 1, n) {
        print << dist[i * 2 + 1] << " ";
    }
}
