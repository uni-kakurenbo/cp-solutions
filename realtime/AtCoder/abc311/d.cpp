/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

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
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w); input >> G;
    debug(G);

    queue<tuple<int,int,int>> que;
    set<tuple<int,int,int>> seen;

    que.emplace(1, 1, -1), seen.emplace(1, 1, -1);

    while(!que.empty()) {
        auto [ x, y, d ] = que.front(); que.pop();
        // debug(x, y, d);
        if(d == -1) {
            REP(nd, 4) {
                if(seen.contains({ x, y, nd })) continue;
                seen.emplace(x, y, nd), que.emplace(x, y, nd);
            }
            continue;
        }
        int nx = x + DIRS4[d].first, ny = y + DIRS4[d].second;
        if(G(nx, ny) == '#') {
            if(seen.contains({ x, y, -1 })) continue;
            que.emplace(x, y, -1), seen.emplace(x, y, -1);
            continue;
        }
        if(seen.contains({ nx, ny, d })) continue;
        que.emplace(nx, ny, d), seen.emplace(nx, ny, d);
    }

    set<spair<int>> ans;
    ITR(x, y, _, seen) ans.emplace(x, y);

    // debug(seen);
    print(ans.size());
}
