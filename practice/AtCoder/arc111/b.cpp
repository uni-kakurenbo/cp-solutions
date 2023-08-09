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
    valarray<i32> a(n), b(n); input >> lib::zip(a, b);
    a -= 1, b -= 1;
    int m = lib::max(a.max(), b.max()) + 1;

    vector<multiset<int>> G(m);
    ITR(x, y, lib::zip(a, b)) G[x].insert(y), G[y].insert(x);
    debug(G);

    set<int> used;

    while(true) {
        bool flag = true;
        REP(i, m) {
            if(G[i].size() == 1) {
                flag = false;
                used.insert(i);
                int j = *G[i].begin();
                G[i].remove(j);
                G[j].remove(i);
            }
        }
        if(flag) break;
    }
    debug(used);

    REP(i, m) if(G[i].size() >= 1) used.insert(i);

    debug(used);
    print(used.size());
}
