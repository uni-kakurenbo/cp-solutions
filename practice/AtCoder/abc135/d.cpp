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

using mint = lib::modint1000000007;

void solve() {
    lib::string s; cin >> s;
    // debug(s);

    int n = s.size();

    vector<mint> dp(13);
    dp[0] = 1;

    REP(i, n) {
        vector<mint> nxt(13);
        REP(j, 13) REP(k, 10) {
            if(s[i] == '?' or s[i] == '0' + k) nxt[lib::mod(j*10 + k,13)] += dp[lib::mod(j,13)];
        }
        // debug(nxt);
        dp = std::move(nxt);
    }

    print(dp[5]);
}
