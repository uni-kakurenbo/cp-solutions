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
    lib::grid<int> A(m, n); input >> A;
    lib::grid<int> ans(n, n);

    REP(i, m) REP(j, n-1) {
        ans[A[i][j]-1][A[i][j+1]-1] = true;
    }

    int res = 0;
    REP(i, n) REP(j, i+1, n) res += !ans[i][j] and !ans[j][i];

    print(res);
}
