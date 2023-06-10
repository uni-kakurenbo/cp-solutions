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
    int n, m, q; std::cin >> n >> m >> q;
    std::valarray<int> a(q), b(q), c(q), d(q);
    REP(i, q) input >> a[i] >> b[i] >> c[i] >> d[i];
    a -= 1, b -= 1;

    std::vector<int> cur(n);

    auto dfs = [&](auto &&dfs, int i) {
        if(i == n) {
            debug(cur);
            i64 ans = 0;
            REP(k, q) {
                if(cur[b[k]] - cur[a[k]] == c[k]) ans += d[k];
            }
            return ans;
        }

        i64 res = 0;

        int f = i == 0 ? 1 : cur[i - 1];
        FOR(v, f, m) {
            cur[i] = v;
            chmax(res, dfs(dfs, i + 1));
        }

        return res;
    };

    print(dfs(dfs, 0));
}
