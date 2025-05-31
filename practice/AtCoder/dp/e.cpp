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
    i64 n, m; input >> n >> m;
    vector<i64> w(n), v(n); input >> uni::views::zip(w, v);

    constexpr i32 M = 100000;
    array<i64, M + 1> dp; dp.fill(INF64);

    dp[0] = 0;

    REP(i, n) FORD(j, M) {
        if(j < v[i]) continue;
        dp[j] = uni::min(dp[j], dp[j - v[i]] + w[i]);
    }
    // debug(dp);

    FORD(i, M) {
        if(dp[i] <= m) {
            print(i);
            return;
        }
    }
}
