/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; cin >> n;
    lib::graph G(n); G.read_bidirectionally(n - 1);
    debug(G);

    valarray<int> sz(n);
    valarray<i64> ans(n);

    {
        auto dfs = [&](auto&& dfs, int v, int p, int d) -> int {
            int res = 1;
            ans[0] += d;
            ITR(e, G[v]) if(e.to != p) res += dfs(dfs, e.to, v, d+1);
            return sz[v] = res;
        };
        dfs(dfs, 0, -1, 0);
        debug(sz, ans[0]);
    }

    {
        auto dfs = [&](auto&& dfs, int v, int p) -> void {
            if(p >= 0) ans[v] = ans[p] + n - (sz[v] << 1);
            ITR(e, G[v]) if(e.to != p) dfs(dfs, e.to, v);
        };
        dfs(dfs, 0, -1);
        debug(ans);
    }

    print(ans);
}
