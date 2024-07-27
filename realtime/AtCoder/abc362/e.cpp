/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

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

#include "template/warnings.hpp"

using mint = uni::modint998244353;

void solve() {
    i32 n; input >> n;
    vector<i64> a(n); input >> a;

    uni::multi_container<mint, 3> dp(n, n, n + 1);
    REP(i, n) REP(j, i+1, n) dp[i][j][2] = 1;

    REP(i, n) REP(j, i + 1, n) REP(k, j + 1, n) FOR(l, 3, n) {
        if(a[j] - a[i] == a[k] - a[j]) dp[j][k][l] += dp[i][j][l - 1];
    }
    debug(dp);

    vector<mint> ans(n);
    ans[0] = n;
    REP(l, 1, n) REP(i, n) REP(j, i+1, n) {
        ans[l] += dp[i][j][l + 1];
    }

    print(ans);
}
