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
    lib::grid<char,string> G(n, n); input >> G;

    auto check = [&](int si, int sj, int di, int dj) -> bool {
        int i = si, j = sj;
        int cnt = 0;
        REP(6) {
            if(not G.is_valid(i, j)) return false;
            cnt += G(i, j) == '#';
            i += di, j += dj;
        }
        return cnt >= 4;
    };

    REP(i, n) REP(j, n) {
        ITR(di, dj, DIRS8) {
            if(check(i, j, di, dj)) {
                print("Yes");
                return;
            };
        }
    }

    print("No");
}
