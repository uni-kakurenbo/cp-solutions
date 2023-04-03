/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    int h, w; cin >> h >> w;
    int c; cin >> c;

    lib::grid<int> a(h, w); a.read();

    lib::minimum<ll> ans = INF64;

    auto solve = [&]() {
        int h = a.height(), w = a.width();
        lib::grid<ll> dp(h+1, w+1, INF64);
        FOR(i, 1, h) FOR(j, 1, w) {
            if(chmin(dp(i,j), min(dp(i-1,j), dp(i,j-1)))) {
                dp(i,j) += c;
                ans <<= dp(i,j) + a(i-1,j-1);
            };
            chmin(dp(i,j), 1LL * a(i-1,j-1));
            debug(dp);
        }
    };

    LOOP(4) {
        a.rotate();
        solve();
    }

    print(ans);

    return 0;
}
