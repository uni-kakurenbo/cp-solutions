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
    lib::grid<int> G(9, 9); input >> G;

    valarray<array<int,9>> cnt_v(9), cnt_h(9);
    REP(i, 9) cnt_v[i].fill(0), cnt_h[i].fill(0);
    REP(i, 9) {
        REP(j, 9) {
            cnt_v[i][G[i][j] - 1] += 1;
            cnt_h[j][G[i][j] - 1] += 1;
        }
    }

    REP(i, 9) REP(v, 9) {
        if(cnt_v[i][v] != 1) {
            print.no();
            return;
        }
        if(cnt_h[i][v] != 1) {
            print.no();
            return;
        }
    }

    REP(i, 3) REP(j, 3) {
        i64 sum = 0;
        REP(di, 3) REP(dj, 3) {
            int ii = i * 3 + di;
            int jj = j * 3 + dj;
            sum += G[ii][jj];
        }
        if(sum != 45) {
            print.no();
            return;
        }
    }

    print.yes();
}
