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

auto query() {
    int k; cin >> k;
    std::valarray<int> res(k);
    input >> res;
    res -= 1;
    return res;
}

void solve() {
    int n, m; cin >> n >> m;

    std::vector<int> al(n);

    auto dfs = [&](auto &&dfs, int v, int p) -> void {
        debug(v, p);
        al[v] = true;

        if(v == n-1) {
            string ok; cin >> ok;
            exit(0);
        }

        ITR(nv, query()) {
            if(al[nv]) continue;
            print(nv + 1), std::cout << std::flush;
            dfs(dfs, nv, v);
        }

        debug(p);

        print(p + 1), std::cout << std::flush;
        query();
    };
    dfs(dfs, 0, -1);
}
