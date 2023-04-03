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
    vector<int> a(n); input >> a; ITRR(v, a) --v;

    vector<int> seen(n, -1);

    int ans = 0;

    REP(i, n) {
        if(seen[i] >= 0) continue;

        debug(i);

        auto dfs = [&](auto& dfs, int v) -> void {
            seen[v] = 1;

            int nv = a[v];
            if(seen[nv] == 1) {
                int u = a[nv];
                ans++;
                while(u != nv) {
                    debug(u);
                    assert(seen[u] == 1);
                    u = a[u];
                    ans++;
                }

                seen[v] = 0;

                return;
            }

            if(seen[nv] == -1) dfs(dfs, nv);

            seen[v] = 0;
        };
        dfs(dfs, i);
        debug(seen);
    }

    print(ans);
}
