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
    i32 n, k; input >> n >> k;
    vector<i64> a(n); input >> a;

    vector<i32> dp(k + 1, false);

    FOR(j, k) {
        REP(i, n) {
            if(j >= a[i]) dp[j] |= !dp[j - a[i]];
        }

        // debug(dp);
    }

    print.conditional(dp[k], "First", "Second");
}
