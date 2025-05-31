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
    i32 n; input >> n;
    vector<ld> p(n); input >> p;

    vector<ld> dp(n + 1);
    dp[0] = 1;

    REP(i, n) {
        vector<ld> nxt(n + 1);
        REP(j, n) {
            nxt[j + 1] += dp[j] * p[i];
            nxt[j] += dp[j] * (1 - p[i]);
        }
        dp = std::move(nxt);
    }

    debug(dp);

    ld sum = 0;
    FOR(i, (n + 1) / 2, n) {
        sum += dp[i];
    }

    print(sum);
}
