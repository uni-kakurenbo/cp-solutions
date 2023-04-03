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

void solve() {
    int n; cin >> n;

    map<int,vector<int>> G;
    REP(n) {
        int a, b; cin >> a >> b; --a, --b;
        G[a].push_back(b), G[b].push_back(a);
    }

    queue<int> que;
    map<int,int> dists;

    que.push(0), dists[0] = 0;

    while(!que.empty()) {
        auto v = que.front(); que.pop();
        for(auto& nv : G[v]) {
            if(dists.count(nv)) continue;
            dists[nv] = dists[v] + 1;
            que.push(nv);
        }
    }
    debug(dists);

    print(max_element(ALL(dists))->first + 1);
}

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}
