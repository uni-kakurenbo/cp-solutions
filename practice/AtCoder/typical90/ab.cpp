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
    i32 n; input >> n;
    lib::grid<i32> grid(1001, 1001);
    REP(n) {
        i32 lx, ly, rx, ry; input >> lx >> ly >> rx >> ry;
        grid[lx][ly]++;
        grid[lx][ry]--;
        grid[rx][ly]--;
        grid[rx][ry]++;
    }

    lib::accumulation_2d cum(grid);
    vector<i32> cnt(n);
    FOR(i, 1000) FOR(j, 1000) if(cum[i][j] > 0) cnt[cum[i][j] - 1]++;

    print(cnt);
}
