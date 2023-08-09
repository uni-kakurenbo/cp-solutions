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
    int n, m; cin >> n >> m;
    valarray<int> p(n, -1); input(p.begin() + 1, p.end()); p -= 1;

    lib::graph G(n);
    REP(i, 1, n) {
        G.add_edge_bidirectionally(i, p[i]);
    }

    map<int,vector<int>> mp;

    REP(i, m) {
        int x, y; cin >> x >> y; --x;
        mp[x].push_back(y);
    }
    debug(mp);

    valarray<int> ans(n, 0);

    auto dfs = [&](auto&& dfs, int v, int cnt) -> void {
        ITR(x, mp[v]) chmax(cnt, x + 1);

        ans[v] = cnt > 0;
        debug(v, cnt);

        ITR(i, G[v]) {
            if(i == p[v]) continue;
            dfs(dfs, i, std::max(0, cnt - 1));
        }
    };
    dfs(dfs, 0, 0);

    print(ans.sum());
}
