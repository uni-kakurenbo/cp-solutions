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

#include "graph/shortest_path.hpp"

void solve() {
    i32 n, m; input >> n >> m;

    uni::graph<i32> graph(n + m);

    REP(i, m) {
        i32 k; input >> k;
        REP(k) {
            i32 v; input >> v; --v;
            graph.add_edge_bidirectionally(v, i + n);
        }
    }

    auto dist = graph.shortest_path_with_cost(0);

    REP(i, n) {
        print(uni::to_optional_if_over(dist[i] / 2, n).value_or(-1));
    }
}
