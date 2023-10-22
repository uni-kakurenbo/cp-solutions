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

#include "graph/from_grid.hpp"
#include "graph/connected_components.hpp"

void solve() {
    int h, w; cin >> h >> w;
    lib::grid<char,string> S(h, w); input >> S;
    lib::dsu ds(h * w + 1);
    debug(S);

    REP(i, h) REP(j, w) {
        if(S(i, j) == '.') {
            ds.merge(S.id(i, j), h * w);
            continue;
        }
        ITR(di, dj, DIRS8) {
            int ii = i + di, jj = j + dj;
            if(not S.is_valid(ii, jj)) continue;
            if(S(ii, jj) == '.') continue;
            ds.merge(S.id(ii, jj), S.id(i, j));
        }
    }
    debug(ds.groups());

    print(ds.group_count() - 1);
}
