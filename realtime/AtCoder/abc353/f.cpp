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
    i64 n, c; input >> n >> c;
    i32 m; input >> m;
    vector<i64> t(m), p(m); input >> uni::views::zip(t, p);
    t -= 1;

    uni::vector<i64> dp(n);

    REP(i, m) {
        auto next = dp;
        REP(j, n) {
            chmin(next[t[i]], dp[j] + p[i] - std::abs(j - t[i]));
        }
        dp = next;
    }

    debug(dp.max());
}
