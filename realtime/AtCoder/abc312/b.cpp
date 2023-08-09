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
    int n, m; cin >> n >> m;
    lib::grid<char,string> G(n, m); input >> G;

    FOR(si, n-9) FOR(sj, m-9) {
        debug(si, sj);
        REP(di, 9) REP(dj, 9) {
            int i = si + di, j = sj + dj;
            if(di <= 3 and dj <= 3) {
                if(di == 3 or dj == 3) {
                    if(G(i, j) == '#') goto no;
                }
                else {
                    if(G(i, j) == '.') goto no;
                }
            }
            if(5 <= di and 5 <= dj) {
                if(di == 5 or dj == 5) {
                    if(G(i, j) == '#') goto no;
                }
                else {
                    if(G(i, j) == '.') goto no;
                }
            }
        }
        print(si + 1, sj + 1);
        no:;
    }
}
