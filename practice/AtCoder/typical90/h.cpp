/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using mint = lib::modint1000000007;

constexpr std::string_view S = "atcoder";

constexpr i32 m = S.size();

void solve() {
    i32 n; input >> n;
    string s; input >> s;

    multi_container<mint, 2> dp(n + 1, m + 1);
    dp[0][0] = 1;

    REP(i, n) FOR(j, m) {
        dp[i + 1][j] += dp[i][j];
        if(j < m and S[j] == s[i]) dp[i + 1][j + 1] += dp[i][j];
    }
    debug(dp);

    print(dp[n][m]);
}
