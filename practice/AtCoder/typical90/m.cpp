/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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
    uni::graph<i64> grid(n); grid.read_bidirectionally<true>(m);

    auto dists_0 = grid.shortest_path_with_cost(0);
    auto dists_n = grid.shortest_path_with_cost(n - 1);

    REP(i, n) {
        print(dists_0[i] + dists_n[i]);
    }
}
