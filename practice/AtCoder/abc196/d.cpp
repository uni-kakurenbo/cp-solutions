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
    int h, w, a, b; cin >> h >> w >> a >> b;
    int n = h * w;

    auto dfs = [&](auto&& dfs, int i, int x, int y, int s) -> int {
        debug(i, x, std::bitset<16>(s));

        if(i == n - 1) return 1;
        if(not ((s >> i) & 1)) return dfs(dfs, i + 1, x, y, s);

        int res = 0;
        if(y < b) res += dfs(dfs, i + 1, x, y + 1, s & ~(1 << i));
        if(x < a and i%w != w-1 and (s >> (i + 1)) & 1) res += dfs(dfs, i + 1, x + 1, y, s & ~((1 << i) | (1 << (i + 1))));
        if(x < a and (s >> (i + w)) & 1) res += dfs(dfs, i + 1, x + 1, y, s & ~((1 << i) | (1 << (i + w))));

        return res;
    };

    print(dfs(dfs, 0, 0, 0, (1 << n) - 1));
}
