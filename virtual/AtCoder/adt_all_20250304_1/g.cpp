/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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
    i32 a, b; u64 s; input >> a >> b >> s;

    uni::grid<i64> dp(61, 61, -1);

    dp(0, 0) = 0;

    REP(d, 60) {
        decltype(dp) next(61, 61, -1);

        REP(i, 60) REP(j, 60) {
            if(dp(i, j) < 0) continue;

            next[i][j + uni::bit(s, d)] = dp[i][j];
            next[i + 1][j + uni::bit(~s, d)] = dp[i][j] | (1UL << d);
        }

        dp = std::move(next);
        // debug(dp);
    }

    auto x = dp(a, b);
    if(x < 0) {
        print(-1);
        return;
    }

    print(x, x ^ s);
}
