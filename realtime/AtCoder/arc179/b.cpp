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

using mint = uni::modint998244353;

#include "template/warnings.hpp"
void solve() {
    i32 m, n; input >> m >> n;
    vector<i64> x(m); input >> x; x -= 1;
    debug(x);

    uni::multi_container<mint, 2> dp(n + 1, 1UL << m);
    dp[0][0] = 1;

    REP(i, n) {
        REP(s, 1UL << m) {
            REP(j, m) {
                if(uni::bit(s, j)) {
                    if(uni::bit(s, x[j])) dp[i + 1][s] += dp[i][s];
                }
                else {
                    if(x[j] != j) dp[i + 1][uni::set_bit(s, j)] += dp[i][s];
                }
            }
        }
    }
    debug(dp, mint{ m }.pow(n), dp[n].sum());

    print(mint{ m }.pow(n) - dp[n].sum());
}
