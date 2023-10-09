/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int h, w; cin >> h >> w;
    lib::grid<char,string> a(h, w), b(h, w); input >> a >> b;

    REP(di, h) REP(dj, w) {
        bool ok = true;
        REP(i, h) REP(j, w) {
            if(a(i, j) != b(lib::mod(i + di, h), lib::mod(j + dj, w))) {
                ok = false;
                break;
            }
        }
        if(ok) {
            print("Yes");
            return;
        }
    }

    print("No");
}
