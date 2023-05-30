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

#include "graph/shortest_path.hpp"

void solve() {
    i64 x, y, z; cin >> x >> y >> z;
    string s; cin >> s;
    int n = s.size();

    auto id = [&](int i, int f) -> int {
        if(f == 0) return i;
        return i + (n + 1);
    };

    lib::graph G(2 * (n + 1));

    REP(i, n) REP(f, 2) {
        if((s[i] == 'a' and !f) or (s[i] == 'A' and f)) G.add_edge(id(i, f), id(i+1, f), x);
        if((s[i] == 'a' and f) or (s[i] == 'A' and !f)) {
            G.add_edge(id(i, f), id(i+1, f), y);
        }
        G.add_edge(id(i, f), id(i, !f), z);
    }

    auto dists = G.distances(0); // dijkstra

    print(std::min(dists[id(n, 0)], dists[id(n, 1)]));
}
