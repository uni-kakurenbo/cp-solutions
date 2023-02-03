/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "graph.hpp"
#include "numeric/modint.hpp"

using mint = lib::modint998244353;

signed main() {
    int n; cin >> n;
    lib::graph G(n); G.read_bidirectionally(n-1);

    debug(G);
    vector<mint> ans(n+1, n+1);

    auto dfs = [&](auto &dfs, int cur, int parent) -> mint {
        mint res;

        ITR(v, G[cur]) {
            if(v.to == parent) continue;
            res *= dfs(dfs, v.to, cur);
        }
        debug(cur);

    };

    dfs(dfs, 0, -1);

    // print()


    return 0;
}
