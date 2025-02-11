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

void solve() {
    i32 h, w; input >> h >> w;
    lib::grid<char> grid(h, w); input >> grid;

    i32 n = h * w;

    i64 ans = -1;

    REP(s, n) {
        if(grid(grid.pos(s)) == '#') continue;

        multi_container<i32, 2> dp(1 << n, n, -INF32);

        dp[0][s] = 0;

        REP(x, 1UL << n) {
            REP(i, n) {
                ITR(ni, nj, grid.vicinities4(grid.pos(i))) {
                    if(grid(ni, nj) == '#') continue;
                    i32 j = grid.id(ni, nj);
                    if(lib::bit(x, j)) continue;
                    chmax(dp[x | lib::shiftl(1UL, j)][j], dp[x][i] + 1);
                }
            }
        }

        REP(x, 1UL << n) {
            i32 v = dp[x][s];
            if(v > 2) chmax(ans, v);
        }
    }

    print(ans);
}
