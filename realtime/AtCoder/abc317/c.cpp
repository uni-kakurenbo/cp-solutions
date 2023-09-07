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

void solve() {
    int n, m; cin >> n >> m;
    valarray<lib::set<int>> G(n);
    lib::map<spair<int>,i64> cost;
    REP(m) {
        int a, b, c; cin >> a >> b >> c; --a, --b;
        G[a].insert(b), G[b].insert(a);
        cost[{ a, b }] = cost[{ b, a }] = c;
    }

    valarray<i64> p(n); std::iota(ALL(p), 0);

    i64 ans = 0;

    do {
        i64 dist = 0;
        REP(i, 1, n) {
            if(not G[p[i-1]].contains(p[i])) break;
            dist += cost[{ p[i-1], p[i] }];
        }
        chmax(ans, dist);
    } while(std::next_permutation(ALL(p)));

    print(ans);
}
