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
    int n, m; cin >> n >> m;
    lib::graph G(n); G.read_bidirectionally(m);

    int k; cin >> k;
    valarray<int> co(n, -1), ok(n, 1);
    REP(i, k) {
        int p, d; cin >> p >> d; --p;
        co[p] = d;
        ok[p] = 0;
    }
    debug(co, ok);

    string res;

    REP(i, n) {
        auto dists = G.distances_without_cost(i);
        debug(i, dists);

        bool valid = true;
        REP(j, n) valid &= co[j] <= dists[j];
        if(valid) REP(j, n) {
            ok[j] |= co[j] == dists[j];
        }
        debug(valid);

        res += "01"[valid];
    }
    debug(ok);

    if(*max_element(ALL(res)) == '0' or ok.min() == 0) {
        print("No");
        return;
    }
    print("Yes");
    print(res);
}
