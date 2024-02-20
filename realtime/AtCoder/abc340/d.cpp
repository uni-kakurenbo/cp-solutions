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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "graph/shortest_path.hpp"

void solve() {
    int n; input >> n;
    valarray<i64> a(n - 1), b(n - 1), x(n - 1); input >> lib::views::zip(a, b, x);
    x -= 1;

    lib::graph<i64> graph(n);

    REP(i, n - 1) {
        graph.add_edge(i, i + 1, a[i]);
        graph.add_edge(i, x[i], b[i]);
    }

    print(graph.distances_with_cost(0)[n - 1]);
}
