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

#include "graph/spanning_tree.hpp"

using mint = lib::modint998244353;

void solve() {
    int n, k; cin >> n >> k;
    valarray<i64> a(n); input >> a;

    valarray<int> p(n); std::iota(ALL(p), 0);
    i64 ans = 0;
    do {
        lib::graph<int> G(n);
        REP(i, n) REP(j, i+1, n) {
            if(j - i <= k) G.add_edge_bidirectionally(i, j, lib::max(a[p[i]], a[p[j]]));
        }
        ans += G.minimum_spanning_tree();
    } while(std::next_permutation(ALL(p)));
    print(ans);
}
