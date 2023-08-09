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

#include <atcoder/scc>

void solve() {
    int n; cin >> n;
    atcoder::scc_graph G(n);
    valarray<i64> a(n); input >> a; a -= 1;
    REP(i, n) {
        G.add_edge(i, a[i]) ;
    }

    auto v = G.scc();

    ITR(x, v) {
        if(x.size() > 1) {
            print(x.size());
            int s = a[x[0]];
            print(s + 1);
            while(s !=  x[0]) {
                s = a[s];
                print(s + 1);
            }
            return;
        }
    }
}
