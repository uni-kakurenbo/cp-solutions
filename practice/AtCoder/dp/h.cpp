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

#include "template/warnings.hpp"
void solve() {
    i32 h, w; input >> h >> w;
    uni::grid<char, string> grid(h, w); input >> grid;
    uni::grid<mint> dp(h + 1, w + 1);

    dp[0][0] = 1;

    REP(i, h) REP(j, w) {
        if(grid(i, j) == '#') continue;
        dp(i + 1, j) += dp(i, j);
        dp(i, j + 1) += dp(i, j);
    }

    print(dp(h - 1, w - 1));
}
