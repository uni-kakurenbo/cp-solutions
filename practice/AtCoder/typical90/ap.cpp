/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

using mint = lib::modint1000000007;


void solve() {
    i32 k; input >> k;
    if(k % 9) {
        print(0);
        return;
    }

    vector<mint> dp(k + 1);
    dp[0] = 1;
    FOR(i, k) {
        dp[i] += lib::sum(dp.begin() + i - lib::min(i, 9), dp.begin() + i);
    }
    print(dp[k]);
}
