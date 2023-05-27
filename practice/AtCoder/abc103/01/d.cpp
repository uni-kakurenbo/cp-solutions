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
    int n, m; cin >> n >> m;

    vector<spair<int>> ps(m);
    input >> ps;

    std::sort(ALL(ps), [&](auto p, auto q) { return p.second < q.second; });

    int ans = 0, cur = 0;
    ITR(l, r, ps) {
        if(l < cur) continue;
        cur = r;
        ans++;
    }

    print(ans);
}
