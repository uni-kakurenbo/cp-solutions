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
    lib::graph G(n); G.read_bidirectionally(n - 1);

    valarray<int> sz(n);
    auto dfs = [&](auto&& dfs, int v, int p) {
        if(sz[v] > 0) return sz[v];
        sz[v] = 1;
        ITR(e, G[v]) {
            if(e == p) continue;
            sz[v] += dfs(dfs, e, v);
        }
        return sz[v];
    };
    dfs(dfs, 0, -1);
    debug(sz);

    i64 ans = INF64;

    ITR(e, G[0]) {
        chmin(ans, n - sz[e]);
    }

    print(ans);
}
