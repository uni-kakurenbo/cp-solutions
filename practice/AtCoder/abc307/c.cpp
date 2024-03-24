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
    lib::set<spair<int>> grid[3];

    REP(p, 3) {
        int h, w; input >> h >> w;
        REP(i, h) REP(j, w) {
            char x; input >> x;
            if(x == '#') grid[p].emplace(i, j);
        }
    }
    debug(grid);

    FOR(i, -10, 10) FOR(j, -10, 10) {
        lib::set<spair<int>> cp0;
        ITR(s, t, grid[0]) cp0.emplace(s + i, t + j);

        FOR(ii, -10, 10) FOR(jj, -10, 10) {
            lib::set<spair<int>> cp1;
            ITR(s, t, grid[1]) cp1.emplace(s + ii, t + jj);

            if((cp0 | cp1) == grid[2]) {
                print.yes();
                return;
            }
        }
    }

    print.no();
}
