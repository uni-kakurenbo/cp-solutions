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
    lib::valgrid<int> G(4, 4); input >> G;

    i64 ans = 0;

    REP(x, 1UL, 1UL << 16) {
        lib::valgrid<int> F(6, 6);
        REP(i, 4) REP(j, 4) F(i+1, j+1) = (x >> G.id(i, j)) & 1;

        bool ok = true;

        lib::dsu uf(36);

        REP(i, 6) REP(j, 6) {
            if(i < 4 and j < 4 and !F(i+1, j+1) and G(i,j)) ok = false;
            if(i+1 < 6 and F(i, j) == F(i+1, j)) uf.merge(F.id(i, j), F.id(i+1, j));
            if(j+1 < 6 and F(i, j) == F(i, j+1)) uf.merge(F.id(i, j), F.id(i, j+1));
        }

        if(ok and uf.group_count() == 2) debug(F);

        ans += ok and uf.group_count() == 2;
    }

    print(ans);
}
