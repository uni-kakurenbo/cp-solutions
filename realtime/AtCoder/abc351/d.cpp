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

void solve() {
    i32 h, w; input >> h >> w;
    uni::grid<char> grid(h, w); input >> grid;

    REP(i, h) REP(j, w) {
        if(grid(i, j) == '#') {
            ITR(ni, nj, grid.vicinities4(i, j)) {
                if(grid(ni, nj) == '.') grid(ni, nj) = '@';
            }
        }
    }
    debug(grid);

    uni::unordered_set<i32> seen;
    uni::unordered_map<i32, i32> visited;

    i32 t = 0;

    auto dfs = [&](auto&& dfs, i32 i, i32 j, i32& cnt) -> void {
        if(grid(i, j) == '#') return;

        if(visited[grid.id(i, j)] == t) return;
        visited[grid.id(i, j)] = t;

        cnt++;
        if(grid(i, j) == '@') return;

        if(seen.contains(grid.id(i, j))) return;
        seen.emplace(grid.id(i, j));

        ITR(ni, nj, grid.vicinities4(i, j)) {
            dfs(dfs, ni, nj, cnt);
        }
    };

    i32 ans = 0;

    REP(i, h) REP(j, w) {
        if(grid(i, j) == '#') continue;
        ++t;

        i32 cnt = 0;

        dfs(dfs, i, j, cnt);
        debug(i, j, cnt);
        chmax(ans, cnt);
    }

    print(ans);
}
