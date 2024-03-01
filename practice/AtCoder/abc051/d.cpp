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
    int n, m; input >> n >> m;
    lib::graph<i64> graph(n); graph.read_bidirectionally<true>(m);

    valarray<int> used(m, false);

    REP(i, n) {
        auto dists = graph.distances_with_cost(i);
        REP(j, m) {
            auto edge = graph.edges()[j];
            if(std::abs(dists[edge.from] - dists[edge.to]) == edge.cost) {
                used[edge.index] = true;
            }
        }
    }

    print(used.count(false));
}
