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

void solve() {
    i32 n, l; input >> n >> l;
    vector<mint> dp(n + 1);
    dp[0] = 1;
    REP(i, n) {
        dp[i + 1] += dp[i];
        if(i + l <= n) dp[i + l] += dp[i];
    }

    print(dp[n]);
}
