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

void solve() {
    int n, m; input >> n >> m;
    lib::graph<int> graph(n); graph.read_bidirectionally(m);

    int ans = 0;

    REP(i, n) {
        int cnt = 0;
        ITR(v, graph[i]) if(v < i) cnt++;
        ans += cnt == 1;
    }

    print(ans);
}
