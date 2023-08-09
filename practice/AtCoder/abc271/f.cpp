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
    lib::grid<int> G(n, n); input >> G;

    lib::map<spair<int>,int> s, t;

    auto dfs0 = [&](auto&& dfs, int i, int j, int x) -> void {
        x ^= G(i, j);
        if(i + j >= n-1) {
            s[{ i, x }]++;
            return;
        }
        dfs(dfs, i + 1, j, x), dfs(dfs, i, j + 1, x);
    };
    auto dfs1 = [&](auto&& dfs, int i, int j, int x) -> void {
        if(i + j <= n-1) {
            t[{ i, x }]++;
            return;
        }
        x ^= G(i, j);
        dfs(dfs, i - 1, j, x), dfs(dfs, i, j - 1, x);
    };
    dfs0(dfs0, 0, 0, 0), dfs1(dfs1, n-1, n-1, 0);
    debug(s, t);

    i64 ans = 0;

    ITR(x, c, s) ans += 1UL * c * t[x];

    print(ans);
}
