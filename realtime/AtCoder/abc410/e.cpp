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

#include "numeric/leveler.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, h, m; input >> n >> h >> m;
    vector<i64> a(n), b(n); input >> uni::views::zip(a, b);

    uni::grid<i64> dp(n + 1, m + 1, -INF64);
    dp(0, m) = h;

    REP(i, n) FOR(k, m) {
        chmax(dp(i + 1, k), dp(i, k) - a[i]);
        if(k + b[i] <= m) chmax(dp(i + 1, k), dp(i, k + b[i]));
    }

    FORD(i, n) {
        if(dp[i].max() >= 0) {
            print(i);
            return;
        }
    }
}
