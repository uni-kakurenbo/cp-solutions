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
    i32 n; input >> n;
    uni::graph<i32> graph(n); graph.read_bidirectionally(n - 1);

    vector<i64> size(n);
    {
        auto dfs = [&](auto&& dfs, i32 v, i32 p) -> i32 {
            i32 acc = 1;
            ITR(nv, graph[v]) {
                if(nv == p) continue;
                acc += dfs(dfs, nv, v);
            }
            return size[v] = acc;
        };
        dfs(dfs, 0, -1);
    }
    debug(size);

    i64 ans = 0;
    REP(i, 1, n) ans += size[i] * (n - size[i]);

    print(ans);
}
