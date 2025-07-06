/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

// #include "template/debug.hpp"
// #include "snippet/aliases.hpp"
// #include <bits/stdc++.h>
// using namespace std;

using i32 = int;
using i64 = long;

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 0;
    while(true) {
        debug_("Case: #" + std::to_string($++));
        solve();
    }
    return 0;
}

#include "structure/graph.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    if(n == 0) exit(0);

    uni::graph<i64> g(n);

    vector<i64> dp(n, INF64);

    REP(v, 1, n) {
        i32 p; i64 w; input >> p >> w; --p;
        g.add_edge_bidirectionally(v, p, w);
        dp[v] = w;
    }

    auto dfs = [&](auto& self, i32 v, i32 p) -> i64 {
        i64 res = INF64;

        ITR(e, g[v]) {
            if(e == p) continue;
            chmin(res, self(self, e, v));
        }

        chmin(dp[v], res - 1);
        return dp[v];
    };
    dfs(dfs, 0, -1);

    debug(dp);

    vector<spair<i64>> ps;
    REP(i, 1, n) ps.emplace_back(dp[i], i);
    ps.sort();

    REP(i, n - 1) {
        if(ps[i].first < i) {
            print("no");
            return;
        }
    }

    print("yes");
    vector<i32> ans(n - 1);
    REP(i, n - 1) ans[i] = ps[i].second;
    print(ans + 1);
}
