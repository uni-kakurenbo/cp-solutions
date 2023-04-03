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
    grid<char,string> a(n,n), b(m,m); input >> a >> b;

    bool res = false;

    FOR(di, n-m) FOR(dj, n-m) {
        bool ok = true;
        REP(i, m) REP(j, m) {
            int p = i + di, q = j + dj;
            ok &= a(p,q) == b(i,j);
        }
        res |= ok;
    }

    print(res ? "Yes" : "No");
}
