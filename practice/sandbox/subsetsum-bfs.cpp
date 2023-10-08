/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>
#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
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
    i64 n, s, t; cin >> n >> s >> t;
    valarray<i64> a(n); input >> a; a.sort();

    auto f = [&](int i, int x) { return i * (t + 1) + x; };

    lib::graph<int> G((n + 1) * (t + 1));

    valarray<bool> can(t + 1);
    can[0] = true;

    REP(i, n) FORD(x, t) {
        G.add_edge(f(i, x), f(i + 1, x), 0);
        if(i > 0 and a[i-1] == a[i]) G.add_edge(f(i + 1, x), f(i, x), 0);
        if(not can[x]) continue;
        if(x + a[i] > t) continue;
        G.add_edge_bidirectionally(f(i, x), f(i + 1, x + a[i]), 1);
        can[x + a[i]] = true;
    }

    print(G.distances_with_01cost(s)[f(n, t)]);
}
