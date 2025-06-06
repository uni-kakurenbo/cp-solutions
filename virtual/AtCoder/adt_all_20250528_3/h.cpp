/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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
    uni::graph<i64> g(n); g.read_bidirectionally<true>(m);

    uni::vector<i64> dist(n);
    g.shortest_path_with_cost(0, &dist);
    debug(dist);

    uni::set<i32> ans;

    REP(i, n) {
        int id = -1;

        ITR(e, g[i]) {
            if(dist[e.from] - dist[e.to] == e.cost) id = e.index;
        }

        debug(id);

        if(id >= 0) ans.insert(id + 1);
    }

    print(ans);
}
