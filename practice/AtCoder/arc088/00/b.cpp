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

#include "numeric/boundary_seeker.hpp"

void solve() {
    std::string s; cin >> s;
    int n = s.size();

    int ans = n;

    REP(i, 1, n) if(s[i-1] != s[i]) ans = lib::max(i, n - i);
    REPD(i, 1, n) if(s[i-1] != s[i]) chmin(ans, lib::max(i, n - i));

    print(ans);
}
