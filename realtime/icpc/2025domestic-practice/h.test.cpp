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
    i32 h, w; input >> h >> w;
    uni::grid<i32> grid(h, w);

    REP(i, h) std::iota(ALL(grid[i]), 0);

    auto dfs = [&](auto&& dfs, i32 i) {
        if(i == h) {
            bool f = true;
            REP(j, w) {
                i64 p = 1;
                REP(i, h) p *= grid(i, j), p %= w;
                if(p != j) f = false;
            }

            if(f) print(grid);

            return;
        }

        do {
            dfs(dfs, i+1);
        } while(std::ranges::next_permutation(grid[i]).found);
    };

    dfs(dfs, 0);
}
