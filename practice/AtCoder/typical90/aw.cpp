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

#include "graph/spanning_tree.hpp"

void solve() {
    i32 n, m; input >> n >> m;

    uni::graph<i64> graph(n + 1);

    REP(i, m) {
        i32 c, l, r; input >> c >> l >> r; --l;
        graph.add_edge_bidirectionally(l, r, c);
    }

    print(graph.minimum_spanning_tree().value_or(-1));
}
