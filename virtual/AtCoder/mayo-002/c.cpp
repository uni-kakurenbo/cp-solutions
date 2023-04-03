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

signed main() {
    string s; cin >> s;
    int n = s.size();

    std::queue<string> que;
    unordered_map<string,int> dists;

    que.push(s), dists[s] = 0;

    while(!que.empty()) {
        auto v = que.front(); que.pop();
        REP(i, n-1) {
            auto u = v;
            std::swap(u[i], u[i+1]);
            if(dists.count(u)) continue;
            que.push(u);
            dists[u] = dists[v] + 1;
        }
    }

    print(dists["atcoder"]);

    return 0;
}
