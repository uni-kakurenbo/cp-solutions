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

using mint = uni::modint998244353;

void solve() {
    mint n; input >> n;
    i32 k; input >> k;

    if(n == 1) {
        print(1);
        return;
    }

    mint dp0 = 1, dp1 = 0;
    auto nn = n * n;

    REP(k) {
        auto p0 = dp0, p1 = dp1;
        dp0 = p1 * 2 * (n - 1) / nn + p0 * (n - 1) * (n - 1) / nn + p0 / nn;
        dp1 = (1 - dp0) / (n - 1);
    }

    debug(dp0, dp1);
    print(dp0 + dp1 * ((n * (n + 1) / 2) - 1));
}
