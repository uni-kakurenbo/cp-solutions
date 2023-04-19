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
    lib::matrix<int> a(n, n), b(n, n);
    input >> a >> b;
    REP(4) {
        debug(a, b);
        bool ans = true;
        REP(i, n) REP(j, n) {
            if(a[i][j] == 1) {
                ans &= b[i][j] == 1;
            }
        }
        if(ans) {
            print("Yes");
            return;
        }
        a.rotate();
    }

    print("No");
}
