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

using mint = lib::modint998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    lib::valgrid<mint> dp(27, 27);
    dp[26][26] = 1;

    REP(i, n) {
        lib::valgrid<mint> nxt(27, 27);
        FOR(a, 26) REP(b, -1, 26) REP(c, 26) {
            if(a == b or b == c or c == a) continue;
            if(s[i] == 'a'+c or s[i] == '?') {
                if(i == 0 and a == 0 and b == 26) debug(a, b, c);
                nxt[b][c] += dp[a][b];
            }
        }
        dp = std::move(nxt);
    }

    print(dp.sum().sum());
}
