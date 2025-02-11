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

using mint = uni::modint1000000007;
using mintB = uni::dynamic_barrett_modint_32bit<0>;

void solve() {
    u64 n; i32 b, k; input >> n >> b >> k;
    mintB::set_mod(b);
    debug(n, b, k);

    vector<i32> c(k); input >> c;
    debug(c);

    array<mintB, 61> pow10{};
    pow10[0] = 10;
    REP(i, 60) pow10[i + 1] = pow10[i] * pow10[i];
    debug(pow10);

    array<vector<mint>, 61> dp{};
    dp.fill(vector<mint>(b));
    ITR(v, c) dp[0][v % b] += 1;
    // debug(dp[0]);

    REP(d, 60) {
        REP(i, b) REP(j, b) {
            auto h = i * pow10[d] + j;
            dp[d + 1][h.val()] += dp[d][i] * dp[d][j];
        }
    }
    // debug(dp);

    vector<mint> ans(b);
    ans[0] = 1;

    REP(d, 60) {
        if(uni::bit(n, d)) {
            vector<mint> nxt(b);
            REP(i, b) REP(j, b) {
                auto h = i * pow10[d] + j;
                nxt[h.val()] += ans[i] * dp[d][j];
            }
            ans = std::move(nxt);
        }
    }

    print(ans[0]);
}
