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
    lib::graph G(n); G.read_bidirectionally(n - 1);

    valarray<i64> size(n, -1), root(n, -1);
    auto dfs0 = [&](auto&& dfs0, int v, int p) -> i64 {
        root[v] = p;
        int res = 1;
        ITR(e, G[v]) {
            if(e.to == p) continue;
            res += dfs0(dfs0, e.to, v);
        }
        return size[v] = res;
    };
    dfs0(dfs0, 0, -1);
    debug(size, root);

    i64 ans = 0;
    REP(i, n) {
        i64 sum0 = n - size[i], sum1 = lib::pow(n - size[i], 2);
        ITR(v, G[i]) {
            if(v == root[i]) continue;
            sum0 += size[v];
            sum1 += size[v] * size[v];
        }
        i64 comb = sum0 * sum0 - sum1;
        comb /= 2;
        debug(i, comb);
        ans += comb;
    }

    print(lib::nCr<i64>(n, 3) - ans);
}
