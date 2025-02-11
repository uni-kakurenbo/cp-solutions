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

void solve() {
    i32 n; input >> n;
    vector<i64> a(2 * n); input >> a;

    multi_container<i64, 2> dp(2 * n, 2 * n, INF64);

    debug(INF64);

    auto dfs = [&](auto&& dfs, i32 l, i32 r) -> i64 {
        if(r < l) return 0;
        if((r - l) % 2 == 0) return INF64;
        if(dp[l][r] < INF64) return dp[l][r];

        dp[l][r] = dfs(dfs, l + 1, r - 1) + std::abs(a[r] - a[l]);

        REP(i, l + 1, r) {
            chmin(dp[l][r], dfs(dfs, l, i) + dfs(dfs, i + 1, r));
        }

        return dp[l][r];
    };

    print(dfs(dfs, 0, 2 * n - 1));
    debug(dp);
}
