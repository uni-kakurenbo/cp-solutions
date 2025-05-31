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

#include "graph/topological_sort.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n >> m;
    uni::graph<i32> graph(n); graph.read(m);

    vector<uni::graph<i32>::node_type> vs;
    graph.sort_topologically(&vs);

    std::vector dp(n, 0);
    for(auto x : vs) {
        for(auto e : graph[x]) {
            dp[e] = uni::max(dp[e], dp[x] + 1);
        }
    }

    print(std::ranges::max(dp));
}
