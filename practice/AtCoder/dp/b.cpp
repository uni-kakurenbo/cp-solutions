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
void solve() {
    i32 n, k; input >> n >> k;
    vector<i64> h(n); input >> h;

    vector<i64> dp(n, INF64);

    dp[0] = 0;

    REP(i, n) FOR(j, 1, k) {
        if(i + j >= n) continue;
        dp[i + j] = std::min(dp[i + j], dp[i] + std::abs(h[i + j] - h[i]));
    }

    print(dp[-1]);
}
