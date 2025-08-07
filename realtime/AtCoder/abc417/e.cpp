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
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i32 n, m, x, y; input >> n >> m >> x >> y, --x, --y;
    vector<vector<i32>> g(n);
    REP(i, m) {
        i32 u, v; input >> u >> v, --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    REP(i, n) g[i].sort();

    vector<i32> visited(n, 0);
    vector<i32> path;
    auto dfs = [&](auto&& self, auto v) {
        if(visited[v]) return false;
        visited[v] = 1;
        path.push_back(v);

        if(v == y) return true;

        ITR(e, g[v]) if(self(self, e)) return true;

        path.pop_back();
        return false;
    };
    dfs(dfs, x);

    print(path + 1);
}
