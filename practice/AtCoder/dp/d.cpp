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
    i32 n, m; input >> n >> m;
    vector<i64> w(n), v(n); input >> uni::views::zip(w, v);

    vector<i64> dp(m + 1);

    REP(i, n) FORR(j, 0, m) {
        if(j < w[i]) continue;
        dp[j] = uni::max(dp[j], dp[j - w[i]] + v[i]);
    }

    print(std::ranges::max(dp));
}
