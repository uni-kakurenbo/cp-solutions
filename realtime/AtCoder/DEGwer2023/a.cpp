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
    int n, k, t; input >> n >> k >> t;
    valarray<i64> a(k); input >> a; a -= 1;

    valarray<i64> b(n);
    ITR(v, a) ++b[v];

    lib::graph<i64> G(n + 1);

    REP(i, n) G.add_edge(i + 1, i, 0);
    REP(i, n) G.add_edge(i, i + 1, b[i]);
    FOR(i, n - t) G.add_edge(i, i + t, 1);

    auto dists = G.distances_with_cost(0);  // Dijkstra's
    debug(dists);
    print(k - dists[n]);
}
