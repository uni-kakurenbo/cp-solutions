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

#include "graph/connected_components.hpp"

void solve() {
    int n, m; cin >> n >> m;
    lib::graph G(n); G.read_bidirectionally(m);

    auto uf = G.components();
    debug(uf.groups());

    vector<int> checked(n), cnts(n);
    vector<unordered_map<int,int>> colors(n);

    bool flag = true;

    REP(i, n) {
        int l = uf.leader(i);
        if(checked[l]) continue;
        checked[l] = true;

        auto& cnt = cnts[l];
        auto& color = colors[l];

        queue<int> que;
        que.push(i), color[i] = -1, cnt = 1;

        while(!que.empty()) {
            auto v = que.front(); que.pop();
            for(auto& nv : G[v]) {
                if(color[nv] != 0) {
                    if(color[nv] == color[v]) flag = false;
                    continue;
                }
                color[nv] = color[v] * -1;
                cnt += color[nv] == -1;
                que.push(nv);
            }
        }
    }

    debug(flag);

    if(not flag) {
        print(0);
        return;
    }

    i64 ans = 0;
    REP(i, n) {
        int l = uf.leader(i);
        auto& color = colors[l];
        int a = cnts[l], b = uf.size(i) - a;
        if(color[i] == 1) ans += a - (int)G[i].size();
        if(color[i] == -1) ans += b - (int)G[i].size();
        ans += n - (int)uf.size(i);
    }
    ans /= 2;

    print(ans);
}
