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
    string s; input >> s;

    uni::multi_container<i64, 2> dp(n + 1, 3, -INF64);
    REP(i, 3) dp[0][i] = 0;

    auto lose = [&](auto a, auto b) {
        if(a == 'R' && b == 'P') return true;
        if(a == 'P' && b == 'S') return true;
        if(a == 'S' && b == 'R') return true;
        return false;
    };

    REP(i, n) REP(j, 3) REP(k, 3) {
        if(j != k && !lose("RPS"[k], s[i])) {
            debug("RPS"[k], s[i]);
            chmax(dp[i + 1][k], dp[i][j] + ("RPS"[k] != s[i]));
        }
    }
    debug(dp);

    print(dp[n].max());
}
