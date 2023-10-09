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
    lib::grid<char,string> G(h, w); input >> G;

    int n = lib::min(h, w);
    valarray<i64> cnt(n);

    REP(i, 1, h-1) REP(j, 1, w-1) {
        if(G[i][j] == '.') continue;
        if(G[i+1][j+1] == '.') continue;
        if(G[i+1][j-1] == '.') continue;
        if(G[i-1][j+1] == '.') continue;
        if(G[i-1][j-1] == '.') continue;

        debug(i, j);

        int ii = i, jj = j;
        while(G.is_valid(ii, jj) and G(ii, jj) == '#') ii++, jj++;
        debug(ii, jj);

        cnt[ii - i - 2]++;
    }

    print(cnt);
}
;
