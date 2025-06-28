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
    i32 n; input >> n;
    uni::grid<i64> grid(101);
    REP(n) {
        i32 a, b, c, d; input >> a >> b >> c >> d;
        grid(a, c) += 1;
        grid(a, d) += -1;
        grid(b, c) += -1;
        grid(b, d) += 1;
    }
    uni::accumulation_2d cum(grid);
    i64 ans = 0;
    FOR(i, 101) FOR(j, 101) {
        ans += cum[i][j] > 0;
    }
    print(ans);
}
