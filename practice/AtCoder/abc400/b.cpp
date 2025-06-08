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

#include "template/warnings.hpp"
void solve() {
    i64 n, m; input >> n >> m;
    constexpr i64 M = uni::pow(10UL, 9) + 1;

    i64 x = 0;
    i64 p = 1;
    FOR(i, m) {
        x = uni::add_clamp(x, p, -INF64, M);
        p = uni::mul_clamp(p, n, -INF64, M);
    }

    if(x >= M) print("inf");
    else print(x);
}
