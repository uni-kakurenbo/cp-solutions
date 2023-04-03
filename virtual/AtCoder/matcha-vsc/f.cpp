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

void solve() {
    int n; cin >> n;
    vector<int> t(n);
    multi_container<int,2> P(n);
    REP(i, n) {
        cin >> t[i];
        int k; cin >> k;
        P[i].resize(k);
        REP(j, k) cin >> P[i][j], P[i][j]--;
    }
    debug(t, P);

    i64 ans = 0;
    valarray<bool> al(n);

    auto dfs = [&](auto&& dfs, int v) -> void {
        if(al[v]) return;
        al[v] = true;
        ans += t[v];
        debug(v, P[v]);
        ITR(p, P[v]) {
            debug(p);
            dfs(dfs, p);
        }
    };
    dfs(dfs, n-1);

    print(ans);
}

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}
