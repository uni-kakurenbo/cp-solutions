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
    valarray<int> a(n); input >> a;
    a -= 1;

    valarray<int> seen(n, -1);

    int ans = 0;

    REP(i, n) {
        int v = i;
        while(seen[v] < 0) {
            seen[v] = i;
            debug(v);
            v = a[v];
            if(seen[v] == i) {
                int u = v;
                do {
                    u = a[u];
                    ans++;
                } until(u == v);
            }
        }
        debug(seen);
    }

    print(ans);
}
