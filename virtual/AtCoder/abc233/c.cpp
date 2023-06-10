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
    i64 n, x; std::cin >> n >> x;

    std::vector<std::vector<i64>> a(n);
    REP(i, n) {
        int l; cin >> l;
        a[i].resize(l);
        input >> a[i];
    }

    auto dfs = [&](auto &&dfs, i64 p, int i) -> i64 {
        if(p > x) return 0;
        if(i >= n) return p == x;
        i64 res = 0;
        ITR(v, a[i]) res += dfs(dfs, p * v, i + 1);
        return res;
    };

    print(dfs(dfs, 1, 0));
}
