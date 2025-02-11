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
    i32 n; input >> n;
    uni::graph<i32> graph(n);

    vector<i32> ss;

    REP(i, n) {
        i32 a, b; input >> a >> b; --a, --b;
        graph.add_edge(a, i);
        graph.add_edge(b, i);
        if(a == i || b == i) ss.emplace_back(i);
    }

    auto dists = graph.shortest_path_without_cost(ss);

    if(dists.max() >= INF32) {
        print(-1);
        return;
    }

    valarray<i32> is(n); std::iota(ALL(is), 0);
    is.sort([&](i32 i, i32 j) { return dists[i] > dists[j]; });
    is += 1;

    print(is);
}
